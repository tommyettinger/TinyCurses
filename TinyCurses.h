/*TinyCurses by Bryan Strait. This library is copyrighted under the LGPLv3,*/
/*or (at your option) any later version.                                   */
/*For more information, see: http://www.gnu.org/copyleft/lgpl.html         */
/*Version 1.0a                                                             */
#ifndef _TINYCURSES_H
#define _TINYCURSES_H
#include "SDL.h"
#include "SDL_ttf.h"

/* Defining bool for C/C++ compatibility.*/
#define bool char
#define true 1
#define false 0

/* These are the keyboard keys that are defined.*/
#define KEY_UP SDLK_UP
#define KEY_DOWN SDLK_DOWN
#define KEY_LEFT SDLK_LEFT
#define KEY_RIGHT SDLK_RIGHT
#define KEY_HOME SDLK_HOME
#define KEY_END SDLK_END
#define KEY_PAGEUP SDLK_PAGEUP
#define KEY_PAGEDOWN SDLK_PAGEDOWN
#define KEY_BACKSPACE SDLK_BACKSPACE
#define KEY_ESCAPE SDLK_ESCAPE
#define KEY_QUIT SDL_QUIT
#define KEY_INSERT SDLK_INSERT
#define KEY_SCROLL SDLK_SCROLLOCK
#define KEY_PAUSE SDLK_PAUSE
#define KEY_PRINT SDLK_PRINT
#define KEY_TAB SDLK_TAB
#define KEY_CAPSLOCK SDLK_CAPSLOCK
#define KEY_DELETE SDLK_DELETE
#define KEY_NUMLOCK SDLK_NUMLOCK

#define KEY_CTRLDOWN SDLK_RCTRL
#define KEY_CTRLUP SDLK_LCTRL
#define KEY_ALTDOWN SDLK_RALT
#define KEY_ALTUP SDLK_LALT
#define KEY_SHIFTDOWN SDLK_RSHIFT
#define KEY_SHIFTUP SDLK_LSHIFT

#define KEY_F1 SDLK_F1
#define KEY_F2 SDLK_F2
#define KEY_F3 SDLK_F3
#define KEY_F4 SDLK_F4
#define KEY_F5 SDLK_F5
#define KEY_F6 SDLK_F6
#define KEY_F7 SDLK_F7
#define KEY_F8 SDLK_F8
#define KEY_F9 SDLK_F9
#define KEY_F10 SDLK_F10
#define KEY_F11 SDLK_F11
#define KEY_F12 SDLK_F12

#define KEY_MOUSE1 1337
#define KEY_MOUSE2 1338
#define KEY_MOUSE3 1339
#define KEY_WHEELUP 1336
#define KEY_WHEELDOWN 1335

extern "C"
{
/* These move the cursor and put things on the screen.*/
extern int addch(int ch);
extern int printw(const char *s, ...);
extern int move(char x,char y);
extern int refresh();
extern int clear();
extern int color(char r,char g,char b,char fr,char fg,char fb);
extern int setcursor(bool c);

/* These move the cursor, print the character/text and move the cursor back*/
extern int mvprintw(const char *s,int x,int y, ...);
extern int mvaddch(int c,int x,int y);

/* These get input from the user*/
extern int getch();
extern char *getstr(char *s,int l);
extern int getmouse(int *x,int *y,bool real);

/* These are extended versions of the functions above functions.*/
extern int initscrext(int w,int h,bool real);
extern int addchext(int ch,int x,int y,char r,char g,char b,char fr,char fg,char fb);
extern int printwext(char *s,int x,int y,char r,char g,char b,char fr,char fg,char fb, ...);
extern int getchext(int w);
extern int clearext(int ch,char r,char g,char b,char fr,char fg,char fb);

/* These are advanced features.*/
extern int setalpha(char a);
extern int setlayer(char l);
extern int setlayershown(char l,bool s);
extern int changecolor(int x,int y,char r,char g,char b,char fr,char fg,char fb);
extern int changech(int ch,int x,int y);
extern int addcolor(int x,int y,int r,int g,int b,int fr,int fg,int fb);
extern int setcaption(char *c);
extern int setcursorlook(char r,char g,char b);
extern int setfont(char *f,int pt);
extern int clearlayer(int l);

/* These are tinycurse's "private" variables. Using them directly IS encouraged,*/
/* but be careful! Know what you're doing :)                                    */

extern int TC_X,TC_Y,TC_R,TC_G,TC_B,TC_FR,TC_FG,TC_FB,TC_A,TC_FA,TC_L,TC_W,TC_H,TC_XSpace,TC_YSpace;
extern int TC_CR,TC_CG,TC_CB;
extern bool TC_Show;
extern TTF_Font *TC_Font;
extern SDL_Surface *TC_Screen;
extern bool TC_LayersShown[7];
extern Uint32 TC_Layers[255][255][7][9];
extern char *TC_FontName;
extern int TC_FontSize;

/* This is an internally used function.*/
extern int BOUND(int x,int min,int max);
}
#endif
