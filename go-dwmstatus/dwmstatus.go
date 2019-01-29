package main

// #cgo LDFLAGS: -lX11 -lasound
// #include <X11/Xlib.h>
// #include "getvol.h"
import "C"

import (
	"fmt"
	"io/ioutil"
	"log"
	"net"
	"strings"
	"time"
)

var dpy = C.XOpenDisplay(nil)

func getVolumePerc() int {
	return int(C.get_volume_perc())
}

func getBatteryPercentage(path string) (perc string, err error) {
	bc, err := ioutil.ReadFile(fmt.Sprintf("%s/capacity", path))
	if err != nil {
		perc = ""
		return
	}
	perc = string(bc)
	return
}

func getCpuTemp(path string) string {
	status, err := ioutil.ReadFile(fmt.Sprintf("%s/temp", path))
	if err != nil {
		return "Error"
	}
	return string(status[0:2])
}

func getLoadAverage(file string) (lavg string, err error) {
	loadavg, err := ioutil.ReadFile(file)
	if err != nil {
		return "Couldn't read loadavg", err
	}
	lavg = strings.Join(strings.Fields(string(loadavg))[:3], " ")
	return
}

func setStatus(s *C.char) {
	C.XStoreName(dpy, C.XDefaultRootWindow(dpy), s)
	C.XSync(dpy, 1)
}

func nowPlaying(addr string) (np string, err error) {
	conn, err := net.Dial("tcp", addr)
	if err != nil {
		np = "Couldn't connect to mpd."
		return
	}
	defer conn.Close()
	reply := make([]byte, 512)
	conn.Read(reply) // The mpd OK has to be read before we can actually do things.

	message := "status\n"
	conn.Write([]byte(message))
	conn.Read(reply)
	r := string(reply)
	arr := strings.Split(string(r), "\n")
	if arr[8] != "state: play" { //arr[8] is the state according to the mpd documentation
		status := strings.SplitN(arr[8], ": ", 2)
		np = fmt.Sprintf("mpd - [%s]", status[1]) //status[1] should now be stopped or paused
		return
	}

	message = "currentsong\n"
	conn.Write([]byte(message))
	conn.Read(reply)
	r = string(reply)
	arr = strings.Split(string(r), "\n")
	if len(arr) > 5 {
		var artist, title string
		for _, info := range arr {
			field := strings.SplitN(info, ":", 2)
			switch field[0] {
			case "Artist":
				artist = strings.TrimSpace(field[1])
			case "Title":
				title = strings.TrimSpace(field[1])
			default:
				//do nothing with the field
			}
		}
		np = artist + " - " + title
		return
	} else { //This is a nonfatal error.
		np = "Playlist is empty."
		return
	}
}

func formatStatus(format string, args ...interface{}) *C.char {
	status := fmt.Sprintf(format, args...)
	return C.CString(status)
}

func main() {
	if dpy == nil {
		log.Fatal("Can't open display")
	}
	for {
		t := time.Now().Format("Mon 02 15:04")
		b, err := getBatteryPercentage("/sys/class/power_supply/BAT0")
		if err != nil {
			log.Println(err)
		}
		l, err := getLoadAverage("/proc/loadavg")
		if err != nil {
			log.Println(err)
		}
		m, err := nowPlaying("localhost:6600")
		if err != nil {
			log.Println(err)
		}
		vol := getVolumePerc()
		cpu_temp := getCpuTemp("/sys/class/thermal/thermal_zone0")
		fmt.Println(b)
		if b == "" {
			s := formatStatus("%s - Vol: %d%% - Cpu: +%s° %s - %s ", m, vol, cpu_temp, l, t)
			setStatus(s)
		} else {
			s := formatStatus("%s - Vol: %d%% - Cpu: +%s° %s - %s - Bat: %s%% ", m, vol, cpu_temp, l, t, b)
			setStatus(s)
		}
		time.Sleep(time.Second)
	}
}
