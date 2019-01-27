#!/bin/bash

xmodmap -e 'clear Lock' &
xmodmap -e 'keycode 135 = Super_R' &
xmodmap -e 'keycode 66 = Escape' &
xmodmap -e 'keycode 9 = Caps_Lock' &

dunst &
#nm-applet
feh --bg-fill ~/Pictures/Wallpapers/Vaporwave/lambo.jpg &
compton -b --backend xrender &
~/.bin/greenclip daemon &
unclutter &

dwmstatus &
