/*TinyCurses by "B.". This library is copyrighted under the LGPLv3,        */
/*or (at your option) any later version.                                   */
/*For more information, see: http://www.gnu.org/copyleft/lgpl.html         */
/*Version 1.0a                                                             */
#include "TinyCurses.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

int TC_X=0,TC_Y=0,TC_R=0,TC_G=0,TC_B=0,TC_FR=255,TC_FG=255,TC_FB=255,TC_A=255,TC_FA=255,TC_L=0,TC_W=0,TC_H=0,TC_XSpace=1,TC_YSpace=1;
int TC_CR=255,TC_CG=255,TC_CB=255;
bool TC_Show=true;
TTF_Font *TC_Font=NULL;
SDL_Surface *TC_Screen=NULL;
bool TC_LayersShown[7];
Uint32 TC_Layers[255][255][7][9];
char *TC_FontName=(char *)"./Font.ttf";
int TC_FontSize=14;
bool TC_Wait=false;
bool TC_On=false;

int TC_MX=0,TC_MY=0;

void endwin();

int initscr()
{
  if(TC_On==false)
      initscrext(80,25,false);
  return 0;
};
void endwin()
{
  if(TC_Wait==false)
    getch();
  TTF_CloseFont(TC_Font);
  TTF_Quit();
  SDL_Quit();
};

int addch(int ch)
{
  if(TC_On==false)
    initscr();
  if(TC_X<0)
    TC_X=0;
  if(TC_Y<0)
    TC_Y=0;
  if(TC_X>TC_W-1)
    TC_X=TC_W-1;
  if(TC_Y>TC_H-1)
    TC_Y=TC_H-1;
  TC_Layers[TC_X][TC_Y][TC_L][0] = ch;
  TC_Layers[TC_X][TC_Y][TC_L][1] = TC_R;
  TC_Layers[TC_X][TC_Y][TC_L][2] = TC_G;
  TC_Layers[TC_X][TC_Y][TC_L][3] = TC_B;
  TC_Layers[TC_X][TC_Y][TC_L][4] = TC_A;
  TC_Layers[TC_X][TC_Y][TC_L][5] = TC_FR;
  TC_Layers[TC_X][TC_Y][TC_L][6] = TC_FG;
  TC_Layers[TC_X][TC_Y][TC_L][7] = TC_FB;
  TC_Layers[TC_X][TC_Y][TC_L][8] = TC_FA;
  TC_X++;
  if(TC_X>TC_W-1)
    {
      TC_X=0;
      TC_Y++;
      if(TC_Y>TC_H-1)
        TC_Y=TC_H-1;
    };
  return 0;
};
int printw(const char *s, ...)
{
  char buf[255];
  va_list a;
  int i;
  if(TC_On==false)
    initscr();
  strncpy(buf,s,255);
  va_start (a, s);
  vsprintf(buf,s,a);
  va_end (a);
  for(i=0;(unsigned)i<strlen(buf);i++)
    {
      if(buf[i]=='\n')
        {
          TC_Y++;
          TC_X=0;
        }else
        addch(buf[i]);
    };
  return 0;
};
int mvprintw(const char *s,int x,int y, ...)
{
  char buf[255];
  va_list a;
  int i;
  int tx,ty;
  if(TC_On==false)
    initscr();
  tx=TC_X;
  ty=TC_Y;
  move(x,y);
  strncpy(buf,s,255);
  va_start (a, y);
  vsprintf(buf,s,a);
  va_end (a);
  for(i=0;(unsigned)i<strlen(buf);i++)
    {
      if(buf[i]=='\n')
        {
          TC_Y++;
          TC_X=0;
        }else
        addch(buf[i]);
    };
  move(tx,ty);
  return 0;
};
int mvaddch(int c,int x,int y)
{
  int tx,ty;
  if(TC_On==false)
    initscr();
  tx=TC_X;
  ty=TC_Y;
  move(x,y);
  addch(c);
  move(tx,ty);
  return 0;
};
int move(char x,char y)
{
  if(TC_On==false)
    initscr();
  TC_X = x;
  TC_Y = y;
  if(TC_X>TC_W-1)
    TC_X=TC_W-1;
  if(TC_Y>TC_H-1)
    TC_Y=TC_H-1;
  if(TC_X<0)
    TC_X=0;
  if(TC_Y<0)
    TC_Y=0;
  return 0;
};
int refresh()
{
  int i,j,k;
  Uint8 a;
  SDL_Surface *s,*t;
  SDL_Rect r;
  SDL_Color c;
  Uint16 txt[2] = {'\0','\0'};
  if(TC_On==false)
    initscr();
  r.w = TC_XSpace;
  r.h = TC_YSpace;
  for(i=0;i<TC_W;i++)for(j=0;j<TC_H;j++)for(k=0;k<7;k++)if(TC_LayersShown[k]==true)
    {
      r.x = i*TC_XSpace;
      r.y = j*TC_YSpace;
      c.r = TC_Layers[i][j][k][5];
      c.g = TC_Layers[i][j][k][6];
      c.b = TC_Layers[i][j][k][7];
      a = TC_Layers[i][j][k][8];
      txt[0] = TC_Layers[i][j][k][0];
      if(txt[0]=='\0'&&txt[1]=='\0')
        txt[0]=' ';
      t=TTF_RenderUNICODE_Blended(TC_Font,txt,c);
      s=SDL_DisplayFormat(t);
      c.r = TC_Layers[i][j][k][1];
      c.g = TC_Layers[i][j][k][2];
      c.b = TC_Layers[i][j][k][3];
      SDL_FillRect(s,NULL,SDL_MapRGB(s->format,c.r,c.g,c.b));
      SDL_BlitSurface(t,NULL,s,NULL);
      if(k!=0)
        SDL_SetAlpha(s,SDL_SRCALPHA,TC_Layers[i][j][k][8]);
      if(k==0||TC_Layers[i][j][k][0]!='\0')
        SDL_BlitSurface(s,NULL,TC_Screen,&r);
      SDL_FreeSurface(s);
      SDL_FreeSurface(t);
    };

  if(TC_Show)
    {
      r.x=TC_X*TC_XSpace;
      r.y=(TC_Y*TC_YSpace)+((TC_YSpace/6)*5);
      r.w=TC_XSpace;
      r.h=TC_YSpace/6;
      SDL_FillRect(TC_Screen,&r,SDL_MapRGB(TC_Screen->format,TC_CR,TC_CG,TC_CB));
    };
  SDL_Flip(TC_Screen);
  return 0;
};
int clear()
{
  if(TC_On==false)
    initscr();
  clearext('\0',0,0,0,255,255,255);
  clearlayer(0);
  return 0;
};
int color(char r,char g,char b,char fr,char fg,char fb)
{
  if(TC_On==false)
    initscr();
  TC_R=r;
  TC_G=g;
  TC_B=b;
  TC_FR=fr;
  TC_FG=fg;
  TC_FB=fb;
  return 0;
};
int setcursor(bool c)
{
  if(TC_On==false)
    initscr();
  TC_Show=c;
  return 0;
};

int getch()
{
  SDL_Event e;
  if(TC_On==false)
    initscr();
  TC_Wait=true;
  while(1==1)
    {
      SDL_WaitEvent(&e);
      if(e.type==SDL_MOUSEBUTTONDOWN)
        {TC_MX = e.button.x;TC_MY=e.button.y;
        switch(e.button.button){
        case SDL_BUTTON_LEFT:
          return KEY_MOUSE1;
        case SDL_BUTTON_RIGHT:
          return KEY_MOUSE2;
        case SDL_BUTTON_MIDDLE:
          return KEY_MOUSE3;
        case SDL_BUTTON_WHEELUP:
          return KEY_WHEELUP;
        case SDL_BUTTON_WHEELDOWN:
          return KEY_WHEELDOWN;
        };
        };
      if(e.type==SDL_MOUSEBUTTONUP)
        {
        switch(e.button.button){
        };
        };
      if(e.type==SDL_KEYDOWN)
        switch(e.key.keysym.sym)
          {
          case SDLK_RETURN:
            return '\n';
          case SDLK_UP:
            return KEY_UP;
            break;
          case SDLK_DOWN:
            return KEY_DOWN;
            break;
          case SDLK_LEFT:
            return KEY_LEFT;
            break;
          case SDLK_RIGHT:
            return KEY_RIGHT;
            break;
          case SDLK_ESCAPE:
            return KEY_ESCAPE;
          case SDLK_HOME:
            return KEY_HOME;
          case SDLK_END:
            return KEY_END;
          case SDLK_PAGEDOWN:
            return KEY_PAGEDOWN;
          case SDLK_PAGEUP:
            return KEY_PAGEUP;
          case SDLK_INSERT:
            return KEY_INSERT;
          case SDLK_SCROLLOCK:
            return KEY_SCROLL;
          case SDLK_PAUSE:
            return KEY_PAUSE;
          case SDLK_PRINT:
            return KEY_PRINT;
          case SDLK_TAB:
            return KEY_TAB;
          case SDLK_CAPSLOCK:
            return KEY_CAPSLOCK;
          case SDLK_DELETE:
            return KEY_DELETE;
          case SDLK_NUMLOCK:
            return KEY_NUMLOCK;
          case SDLK_RCTRL:case SDLK_LCTRL:
            return KEY_CTRLDOWN;
          case SDLK_RSHIFT:case SDLK_LSHIFT:
            return KEY_SHIFTDOWN;
          case SDLK_RALT:case SDLK_LALT:
            return KEY_ALTDOWN;
          case SDLK_F1:
            return KEY_F1;
          case SDLK_F2:
            return KEY_F2;
          case SDLK_F3:
            return KEY_F3;
          case SDLK_F4:
            return KEY_F4;
          case SDLK_F5:
            return KEY_F5;
          case SDLK_F6:
            return KEY_F6;
          case SDLK_F7:
            return KEY_F7;
          case SDLK_F8:
            return KEY_F8;
          case SDLK_F9:
            return KEY_F9;
          case SDLK_F10:
            return KEY_F10;
          case SDLK_F11:
            return KEY_F11;
          case SDLK_F12:
            return KEY_F12;
          case SDLK_KP0:
            return '0';
          case SDLK_KP1:
            return '1';
          case SDLK_KP2:
            return '2';
          case SDLK_KP3:
            return '3';
          case SDLK_KP4:
            return '4';
          case SDLK_KP5:
            return '5';
          case SDLK_KP6:
            return '6';
          case SDLK_KP7:
            return '7';
          case SDLK_KP8:
            return '8';
          case SDLK_KP9:
            return '9';
          default:
            return(e.key.keysym.unicode);
          };
      if(e.type==SDL_KEYUP)
        switch(e.key.keysym.sym)
          {
          case SDLK_RCTRL:case SDLK_LCTRL:
            return KEY_CTRLUP;
          case SDLK_RALT:case SDLK_LALT:
            return KEY_ALTUP;
          case SDLK_RSHIFT:case SDLK_LSHIFT:
            return KEY_SHIFTUP;
          default:
            break;
          };
      if(e.type==SDL_QUIT)
        return KEY_QUIT;
    };
  return 0;
};
char *getstr(char *s,int l)
{
  char *b;
  char buf[255];
  int i,x,px,py;
  if(TC_On==false)
    initscr();
  x=0;
  memset(buf,0,255);
  if(s==NULL)
    b=buf;
  else
    b=s;
  refresh();
  px = TC_X;
  py = TC_Y;
  while(1==1)
    {
      i=getch();
      if(i=='\n')
        return b;
      if(isprint(i)){
        if(x>l-1)
          {
            b[l-1]=i;
            x=l;
          }
        else
          b[x]=i;}
      if(isprint(i)&&x<l)
          x++;
      if(i==SDLK_BACKSPACE&&x>0)
        {
          x--;
          b[x]=0;
        };
      mvprintw(b,px,py);
      move(px+x,py);
      addch(' ');
      move(px+x,py);
      refresh();
      if(x>250)
        return b;
    };
  return b;
};
int getmouse(int *x,int *y,bool real)
{
  *x=real?TC_MX:TC_MX/TC_XSpace;
  *y=real?TC_MY:TC_MY/TC_YSpace;
  return 0;
};

int initscrext(int w,int h,bool real)
{
  int x;
  if(TC_On==true)
    return -1;
  TC_On=true;
  atexit(endwin);
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
  SDL_EnableUNICODE(true);
  TC_Font = TTF_OpenFont(TC_FontName,TC_FontSize);
  TTF_GlyphMetrics(TC_Font,'@',&x,&x,&x,&x,&TC_XSpace);
  TC_YSpace = TTF_FontLineSkip(TC_Font)+1;
  if(real)
      TC_Screen = SDL_SetVideoMode(w,h,32,SDL_SWSURFACE);
  else
      TC_Screen = SDL_SetVideoMode(w*TC_XSpace,h*TC_YSpace,32,SDL_SWSURFACE);
  if(TC_Screen==NULL)
    TC_Screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);
  TC_W=TC_Screen->w/TC_XSpace;
  TC_H=TC_Screen->h/TC_YSpace;
  TC_LayersShown[0]=true;
  for(x=1;x<7;x++)
    TC_LayersShown[x]=false;
   clear();
  return 0;
};
int addchext(int ch,int x,int y,char r,char g,char b,char fr,char fg,char fb)
{
  int br,bg,bb,bfr,bfg,bfb;
  if(TC_On==false)
    initscr();
  br=TC_R;bg=TC_G;bb=TC_B;bfr=TC_FR;bfg=TC_FG;bfb=TC_FB;
  move(x,y);
  color(r,g,b,fr,fg,fb);
  addch(ch);
  color(br,bg,bb,bfr,bfg,bfb);
  return 0;
};
int printwext(char *s,int x,int y,char r,char g,char b,char fr,char fg,char fb, ...)
{
  char buf[255];
  va_list a;
  int i;
  int br,bg,bb,bfr,bfg,bfb;
  if(TC_On==false)
    initscr();
  br=TC_R;bg=TC_G;bb=TC_B;bfr=TC_FR;bfg=TC_FG;bfb=TC_FB;
  move(x,y);
  color(r,g,b,fr,fg,fb);
  strncpy(buf,s,255);
  va_start (a, fb);
  vsprintf(buf,s,a);
  va_end (a);
  for(i=0;(unsigned)i<strlen(buf);i++)
    {
      if(buf[i]=='\n')
        {
          TC_Y++;
          TC_X=0;
          if(TC_Y>TC_H-1)
            TC_Y=TC_H-1;
        }else
        addch(buf[i]);
    };
  color(br,bg,bb,bfr,bfg,bfb);
  return 0;
};
int getchext(int w)
{
  Uint32 t;
  SDL_Event e;
  if(TC_On==false)
    initscr();
  t=SDL_GetTicks();
  while(w>-1?SDL_GetTicks()<t+w:1==1)
    {
      SDL_PollEvent(&e);
      if(e.type==SDL_MOUSEBUTTONDOWN)
        {TC_MX = e.button.x;TC_MY=e.button.y;
        switch(e.button.button){
        case SDL_BUTTON_LEFT:
          return KEY_MOUSE1;
        case SDL_BUTTON_RIGHT:
          return KEY_MOUSE2;
        case SDL_BUTTON_MIDDLE:
          return KEY_MOUSE3;
        case SDL_BUTTON_WHEELUP:
          return KEY_WHEELUP;
        case SDL_BUTTON_WHEELDOWN:
          return KEY_WHEELDOWN;
        };
        };
      if(e.type==SDL_MOUSEBUTTONUP)
        {
        switch(e.button.button){
        };
        };
        if(e.type==SDL_KEYDOWN)
        switch(e.key.keysym.sym)
          {
          case SDLK_RETURN:
            return '\n';
          case SDLK_UP:
            return KEY_UP;
            break;
          case SDLK_DOWN:
            return KEY_DOWN;
            break;
          case SDLK_LEFT:
            return KEY_LEFT;
            break;
          case SDLK_RIGHT:
            return KEY_RIGHT;
            break;
          case SDLK_ESCAPE:
            return KEY_ESCAPE;
          case SDLK_HOME:
            return KEY_HOME;
          case SDLK_END:
            return KEY_END;
          case SDLK_PAGEDOWN:
            return KEY_PAGEDOWN;
          case SDLK_PAGEUP:
            return KEY_PAGEUP;
          case SDLK_INSERT:
            return KEY_INSERT;
          case SDLK_SCROLLOCK:
            return KEY_SCROLL;
          case SDLK_PAUSE:
            return KEY_PAUSE;
          case SDLK_PRINT:
            return KEY_PRINT;
          case SDLK_TAB:
            return KEY_TAB;
          case SDLK_CAPSLOCK:
            return KEY_CAPSLOCK;
          case SDLK_DELETE:
            return KEY_DELETE;
          case SDLK_NUMLOCK:
            return KEY_NUMLOCK;
          case SDLK_RCTRL:case SDLK_LCTRL:
            return KEY_CTRLDOWN;
          case SDLK_RSHIFT:case SDLK_LSHIFT:
            return KEY_SHIFTDOWN;
          case SDLK_RALT:case SDLK_LALT:
            return KEY_ALTDOWN;
          case SDLK_F1:
            return KEY_F1;
          case SDLK_F2:
            return KEY_F2;
          case SDLK_F3:
            return KEY_F3;
          case SDLK_F4:
            return KEY_F4;
          case SDLK_F5:
            return KEY_F5;
          case SDLK_F6:
            return KEY_F6;
          case SDLK_F7:
            return KEY_F7;
          case SDLK_F8:
            return KEY_F8;
          case SDLK_F9:
            return KEY_F9;
          case SDLK_F10:
            return KEY_F10;
          case SDLK_F11:
            return KEY_F11;
          case SDLK_F12:
            return KEY_F12;
          case SDLK_KP0:
            return '0';
          case SDLK_KP1:
            return '1';
          case SDLK_KP2:
            return '2';
          case SDLK_KP3:
            return '3';
          case SDLK_KP4:
            return '4';
          case SDLK_KP5:
            return '5';
          case SDLK_KP6:
            return '6';
          case SDLK_KP7:
            return '7';
          case SDLK_KP8:
            return '8';
          case SDLK_KP9:
            return '9';
          default:
            return(e.key.keysym.unicode);
          };
      if(e.type==SDL_KEYUP)
        switch(e.key.keysym.sym)
          {
          case SDLK_RCTRL:case SDLK_LCTRL:
            return KEY_CTRLUP;
          case SDLK_RALT:case SDLK_LALT:
            return KEY_ALTUP;
          case SDLK_RSHIFT:case SDLK_LSHIFT:
            return KEY_SHIFTUP;
          default:
            break;
          };
        if(e.type==SDL_QUIT)
          return KEY_QUIT;
    };
  return -1;
};
int clearext(int ch,char r,char g,char b,char fr,char fg,char fb)
{
  int i,j,k;
  SDL_Rect rt;
  int br,bg,bb,bfr,bfg,bfb,bl,ba,bfa;
  if(TC_On==false)
    initscr();
  br=TC_R;bg=TC_G;bb=TC_B;bfr=TC_FR;bfg=TC_FG;bfb=TC_FB;ba=TC_A;bfa=TC_FA;
  rt.x=0;
  rt.y=0;
  rt.w=TC_Screen->w;
  rt.h=TC_Screen->h;
  SDL_FillRect(TC_Screen,&rt,SDL_MapRGB(TC_Screen->format,r,g,b));
  color(r,g,b,fr,fg,fb);
  setalpha(0);
  bl=TC_L;
  for(i=0;i<TC_W;i++)
    for(j=0;j<TC_H;j++)
      for(k=0;k<7;k++)
      {
        setlayer(k);
        move(i,j);
        addch(ch);
      };
  setlayer(bl);
  setalpha(bfa);
  move(0,0);
  color(br,bg,bb,bfr,bfg,bfb);
  return 0;
};
int clearlayer(int l)
{
  int i,j;
  int br,bg,bb,bfr,bfg,bfb,bl,ba,bfa,bx,by;
  br=TC_R;bg=TC_G;bb=TC_B;bfr=TC_FR;bfg=TC_FG;bfb=TC_FB;ba=TC_A;bfa=TC_FA;bx=TC_X;by=TC_Y;bl=TC_L;
  color(0,0,0,255,255,255);
  setalpha(0);
  setlayer(l);
  for(i=0;i<TC_W;i++)
    for(j=0;j<TC_H;j++)
      mvaddch(l>0?'\0':' ',i,j);
  setlayer(bl);
  setalpha(bfa);
  move(bx,by);
  color(br,bg,bb,bfr,bfg,bfb);
  return 0;
};

int setalpha(char a)
{
  if(TC_On==false)
    initscr();
  TC_FA=a;
  return 0;
};
int setlayer(char l)
{
  if(TC_On==false)
    initscr();
  TC_L=l;
  if(TC_L<0)
    TC_L=0;
  if(TC_L>6)
    TC_L=6;
  return 0;
};
int setlayershown(char l,bool s)
{
  if(TC_On==false)
    initscr();
  if(l<0||l>6)
    return 0;
  TC_LayersShown[(int)l]=s;
  return 0;
};
int changecolor(int x,int y,char r,char g,char b,char fr,char fg,char fb)
{
  if(TC_On==false)
    initscr();
  if(x>TC_W||y>TC_H||x<0||y<0)
    return 0;
  TC_Layers[x][y][TC_L][1] = r;
  TC_Layers[x][y][TC_L][2] = g;
  TC_Layers[x][y][TC_L][3] = b;
  TC_Layers[x][y][TC_L][4] = TC_A;
  TC_Layers[x][y][TC_L][5] = fr;
  TC_Layers[x][y][TC_L][6] = fg;
  TC_Layers[x][y][TC_L][7] = fb;
  TC_Layers[x][y][TC_L][8] = TC_FA;
  return 0;
};
int changech(int ch,int x,int y)
{
  if(TC_On==false)
    initscr();
  if(x>TC_W||y>TC_H||x<0||y<0)
    return 0;
  TC_Layers[x][y][TC_L][0] = ch;
  return 0;
};
int addcolor(int x,int y,int r,int g,int b,int fr,int fg,int fb)
{
  Uint8 r2,g2,b2,fr2,fg2,fb2,a2,fa2;
  if(TC_On==false)
    initscr();
  if(x>TC_W||y>TC_H||x<0||y<0)
    return 0;
  r2 = TC_Layers[x][y][TC_L][1];
  g2 = TC_Layers[x][y][TC_L][2];
  b2 = TC_Layers[x][y][TC_L][3];
  a2 = TC_Layers[x][y][TC_L][4];
  fr2 = TC_Layers[x][y][TC_L][5];
  fg2 = TC_Layers[x][y][TC_L][6];
  fb2 = TC_Layers[x][y][TC_L][7];
  fa2 = TC_Layers[x][y][TC_L][8];
  r+=r2;
  g+=g2;
  b+=b2;
  fr+=fr2;
  fb+=fb2;
  fg+=fg2;
  changecolor(x,y,BOUND(r,0,255),BOUND(g,0,255),BOUND(b,0,255),BOUND(fr,0,255),BOUND(fg,0,255),BOUND(fb,0,255));
  return 0;
};
int setcaption(char *c)
{
  if(TC_On==false)
    initscr();
  SDL_WM_SetCaption(c,NULL);
  return 0;
};
int setcursorlook(char r,char g,char b)
{
  if(TC_On==false)
    initscr();
  TC_CR=r;
  TC_CG=g;
  TC_CB=b;
  return 0;
};
int setfont(char *f,int pt)
{
  if(f!=NULL)
    TC_FontName=f;
  TC_FontSize=pt;
  return 0;
};

int BOUND(int x,int min,int max)
{
  if(x>max)
    x=max;
  if(x<min)
    x=min;
  return x;
};
