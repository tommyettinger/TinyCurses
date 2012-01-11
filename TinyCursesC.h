/*TinyCurses by Bryan Strait. This library is copyrighted under the LGPLv3,*/
/*or (at your option) any later version.                                   */
/*For more information, see: http://www.gnu.org/copyleft/lgpl.html         */
/*Version 1.0a                                                             */
#ifndef _TINYCURSES_H
#define _TINYCURSES_H


/* Defining bool for C/C++ compatibility.*/
#define bool char
#define true 1
#define false 0

/* These are the keyboard keys that are defined.*/
#define KEY_UP 1001
#define KEY_DOWN 1002
#define KEY_LEFT 1003
#define KEY_RIGHT 1004
#define KEY_HOME 1005
#define KEY_END 1006
#define KEY_PAGEUP 1007
#define KEY_PAGEDOWN 1008
#define KEY_BACKSPACE 1009
#define KEY_ESCAPE 1010
#define KEY_QUIT 1011
#define KEY_INSERT 1012
#define KEY_SCROLL 1013
#define KEY_PAUSE 1014
#define KEY_PRINT 1015
#define KEY_TAB 1016
#define KEY_CAPSLOCK 1017
#define KEY_DELETE 1018
#define KEY_NUMLOCK 1019

#define KEY_CTRLDOWN 1020
#define KEY_CTRLUP 1021
#define KEY_ALTDOWN 1022
#define KEY_ALTUP 1023
#define KEY_SHIFTDOWN 1024
#define KEY_SHIFTUP 1025

#define KEY_F1 1026
#define KEY_F2 1027
#define KEY_F3 1028
#define KEY_F4 1029
#define KEY_F5 1030
#define KEY_F6 1031
#define KEY_F7 1032
#define KEY_F8 1033
#define KEY_F9 1034
#define KEY_F10 1035
#define KEY_F11 1036
#define KEY_F12 1037

#define KEY_MOUSE1 1337
#define KEY_MOUSE2 1338
#define KEY_MOUSE3 1339
#define KEY_WHEELUP 1336
#define KEY_WHEELDOWN 1335

#include "curses.h"

#define addch _addch
#define printw _printw
#define move _move
#define refresh _refresh
#define clear _clear
#define color _color
#define mvprintw _mvprintw
#define mvaddch _mvaddch
#define getch _getch
#define getstr _getstr
#define getmouse _getmouse
#define endwin _endwin
#define initscr _initscr

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
  //extern TTF_Font *TC_Font;
  //extern SDL_Surface *TC_Screen;
extern bool TC_LayersShown[7];
extern unsigned int TC_Layers[255][255][7][9];
extern char *TC_FontName;
extern int TC_FontSize;

/* This is an internally used function.*/
extern int BOUND(int x,int min,int max);
}


#endif
