/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Inconsolata:size=10" };
static const char dmenufont[]       = "Inconsolata:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_black[]       = "#000000";
static const char col_magenta[]     = "#cc00ff";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_black, col_magenta,  col_magenta  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	// { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of roficmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_magenta, "-sf", col_gray4, NULL };
static const char *roficmd[] = { "rofi", "-show", "run" };
static const char *rofibangscmd[] = { "/home/tovi/.bin/rofi-bangs.sh", NULL };
static const char *termcmd[]  = { "st", NULL };

static const char *firefoxcmd[]  = { "firefox", NULL };
static const char *amixercmd[]  = { "st", "alsamixer" };
static const char *volupcmd[] = { "amixer", "-q", "sset", "Master", "3%+" };
static const char *voldowncmd[] = { "amixer", "-q", "sset", "Master", "3%-" };
static const char *musiccmd[] = { "st", "ncmpcpp" };
static const char *musictoggle[] = { "mpc", "-q", "toggle" };
static const char *musicnext[] = { "mpc", "-q", "next" };
static const char *musicprev[] = { "mpc", "-q", "pre" };
static const char *rangercmd[] = { "st", "-e", "ranger", NULL };
static const char *poweroffcmd[] = { "systemctl", "poweroff", NULL };

static const char *changewp[] = { "/home/tovi/.bin/change_wp", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */


	   { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	   { MODKEY,                       XK_Return, zoom,           {0} },
	   { MODKEY,                       XK_Tab,    view,           {0} },
	   { MODKEY,                       XK_space,  setlayout,      {0} },
	   { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },


	   { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	   { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	   { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	   { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	// { MODKEY,                       XK_a,      spawn,          {.v = <++> } },
	   { MODKEY|ShiftMask,             XK_a,      spawn,          {.v = amixercmd } },
	   { MODKEY,                       XK_b,      spawn,          {.v = firefoxcmd } },
	   { MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	// { MODKEY,                       XK_c,      spawn,          {.v = <++> } },
	   { MODKEY|ShiftMask,             XK_c,      spawn,          {.v = changewp } },
	   { MODKEY,                       XK_d,      spawn,          {.v = roficmd } },
	   { MODKEY|ShiftMask,             XK_d,      spawn,          {.v = rofibangscmd } },
	// { MODKEY,                       XK_e,      spawn,          {.v = <++> } },
	// { MODKEY|ShiftMask,             XK_e,      spawn,          {.v = <++> } },
	   { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	// { MODKEY|ShiftMask,             XK_f,      spawn,          {.v = <++> } },
	// { MODKEY,                       XK_g,      spawn,          {.v = <++> } },
	// { MODKEY|ShiftMask,             XK_g,      spawn,          {.v = <++> } },
	   { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	// { MODKEY|ShiftMask,             XK_h,      spawn,          {.v = <++> } },
	   { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	   { MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
	   { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	// { MODKEY|ShiftMask,             XK_j,      spawn,          {.v = <++> } },
	   { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	// { MODKEY|ShiftMask,             XK_k,      spawn,          {.v = <++> } },
	   { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	// { MODKEY|ShiftMask,             XK_l,      spawn,          {.v = <++> } },
	   { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	   { MODKEY|ShiftMask,             XK_m,      spawn,          {.v = musiccmd } },
	   { MODKEY,                       XK_n,      spawn,          {.v = musicnext } },
	   { MODKEY|ShiftMask,             XK_n,      spawn,          {.v = musicprev } },
	// { MODKEY,                       XK_o,      spawn,          {.v = <++> } },
	// { MODKEY|ShiftMask,             XK_o,      spawn,          {.v = <++> } },
	   { MODKEY,                       XK_p,      spawn,          {.v = musictoggle } },
	// { MODKEY|ShiftMask,             XK_p,      spawn,          {.v = <++> } },
	   { MODKEY,                       XK_q,      killclient,     {0} },
	   { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	   { MODKEY,                       XK_r,      spawn,          {.v = rangercmd } },
	// { MODKEY|ShiftMask,             XK_r,      spawn,          {.v = <++> } },
	// { MODKEY,                       XK_s,      spawn,          {.v = <++> } },
	   { MODKEY|ShiftMask,             XK_s,      spawn,          {.v = poweroffcmd } },
	   { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	// { MODKEY|ShiftMask,             XK_t,      spawn,          {.v = <++> } },
	// { MODKEY,                       XK_u,      spawn,          {.v = <++> } },
	// { MODKEY|ShiftMask,             XK_u,      spawn,          {.v = <++> } },
	// { MODKEY,                       XK_v,      spawn,          {.v = <++> } },
	// { MODKEY|ShiftMask,             XK_v,      spawn,          {.v = <++> } },
	// { MODKEY,                       XK_w,      spawn,          {.v = <++> } },
	// { MODKEY|ShiftMask,             XK_w,      spawn,          {.v = <++> } },
	// { MODKEY,                       XK_x,      spawn,          {.v = <++> } },
	// { MODKEY|ShiftMask,             XK_x,      spawn,          {.v = <++> } },
	// { MODKEY,                       XK_y,      spawn,          {.v = <++> } },
	// { MODKEY|ShiftMask,             XK_y,      spawn,          {.v = <++> } },
	// { MODKEY,                       XK_z,      spawn,          {.v = <++> } },
	// { MODKEY|ShiftMask,             XK_z,      spawn,          {.v = <++> } },
	
	   { MODKEY,                       XK_F1,     spawn,          {.v = voldowncmd } },
	   { MODKEY,                       XK_F2,     spawn,          {.v = volupcmd } },

	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

