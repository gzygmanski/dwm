/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 2;        /* horizontal padding for statusbar */
static const int vertpadbar         = 2;        /* vertical padding for statusbar */
static const char *fonts[]          = { "monospace:pixelsize=16:antialias=true:autohint=false" };
static const char dmenufont[]       = "monospace:pixelsize=16:antialias=true:autohint=false";
static const char col_gray1[]       = "#282a36";
static const char col_gray2[]       = "#44475a";
static const char col_gray3[]       = "#f8f8f2";
static const char col_gray4[]       = "#f8f8f2";
static const char col_cyan[]        = "#bd93f9";
static const unsigned int baralpha = 0xF5;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray1 },
	[SchemeSel]  = { col_gray4, col_gray2, col_cyan },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};
/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tagsalt[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      		instance    title           tags mask     isfloating   monitor */
	{ "Steam",	  	NULL,       NULL,           1 << 2,       0,           -1 },
	{ NULL,	  	        NULL,       "Friends List", 1 << 2,       1,           -1 },
	{ "qutebrowser",  	NULL,       NULL,           1 << 1,       0,           -1 },
//	{ NULL,  	        NULL,       "GLava",        1 << 1,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "﩯 t",      tile },    /* first entry is default */
	{ " f",      NULL },    /* no layout function means floating behavior */
	{ "ﱢ m",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_gray2, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *browsercmd[] = { "qutebrowser", NULL };
static const char *ncmpcppcmd[] = { "st", "-e", "ncmpcpp", NULL };

/* mpc commands */
static const char *mpdtoggle[]	= { "mpc", "toggle", NULL };
static const char *mpdstop[]	= { "mpc", "stop", NULL };
static const char *mpdnext[]	= { "mpc", "next", NULL };
static const char *mpdprev[]	= { "mpc", "prev", NULL };
static const char *mpdvolp[]	= { "volpm", "-s", "mpd", "-i", "2", NULL };
static const char *mpdvolm[]	= { "volpm", "-s", "mpd", "-d", "2", NULL };
static const char *mpdseekp[]	= { "mpc", "seek", "+2%", NULL };
static const char *mpdseekm[]	= { "mpc", "seek", "-2%", NULL };
static const char *mpdinfo[]    = { "mpdinfo", NULL };

/* volume commands */
static const char *volp[]	= { "volpm", "-s", "default", "-i", "2", NULL };
static const char *volm[]	= { "volpm", "-s", "default", "-d", "2", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,	                XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,	                XK_grave,  spawn,          {.v = browsercmd} },
	{ MODKEY|ShiftMask,             XK_m, 	   spawn,          {.v = ncmpcppcmd} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
        { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,	                XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_n,      togglealttag,   {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

	/* Mediakeys mpd controls */
	{ 0,				XF86XK_AudioPlay,		spawn,	{.v = mpdtoggle } },
	{ 0,				XF86XK_AudioStop,		spawn,	{.v = mpdstop } },
	{ 0,				XF86XK_AudioNext,		spawn,	{.v = mpdnext } },
	{ 0,				XF86XK_AudioPrev,		spawn,	{.v = mpdprev } },
	{ 0,				XF86XK_AudioRaiseVolume,	spawn,	{.v = mpdvolp } },
	{ 0,				XF86XK_AudioLowerVolume,	spawn,	{.v = mpdvolm } },
	{ MODKEY,			XK_bracketright,		spawn,	{.v = mpdseekp } },
	{ MODKEY,			XK_bracketleft,			spawn,	{.v = mpdseekm } },
	{ MODKEY,			XK_slash,			spawn,	{.v = mpdinfo } },

	/* volume controls */
	{ MODKEY,		        XK_equal,			spawn,	{.v = volp } },
	{ MODKEY,		        XK_minus,			spawn,	{.v = volm } },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY|ShiftMask,      Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY|ShiftMask,      Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY|ShiftMask,      Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY|ShiftMask,      Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY|ShiftMask,      Button3,        toggletag,      {0} },
};
