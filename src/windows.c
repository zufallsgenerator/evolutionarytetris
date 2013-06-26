/*****************************************************************************
 Evolutionary Tetris AI (C) Christer Byström 2005
 Artificial Intelligence course project at Linköpings Universitet, fall 2005
 *****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include "tetris.h"


#include "sdl.h"

#define BRICK_SIZE 20

int keys[] = {
  KEY_UP, 
  KEY_UP, 
  KEY_LEFT, 
  KEY_LEFT, 
  KEY_LEFT, 
  KEY_DOWN,
  KEY_RIGHT,
  KEY_UP, 
  KEY_UP,
  KEY_RIGHT,
  KEY_RIGHT,
  KEY_RIGHT, 
  KEY_DOWN,
  KEY_RIGHT,
  KEY_RIGHT,
  KEY_DOWN,
  KEY_LEFT,
  KEY_LEFT, 
  KEY_RIGHT, 
  KEY_DOWN,
  KEY_UP,
  KEY_UP,
  KEY_LEFT,
  KEY_UP,
  KEY_UP, 
  KEY_UP, 
  KEY_LEFT, 
  KEY_LEFT, 
  KEY_RIGHT, 
  KEY_DOWN,
  KEY_RIGHT,
  KEY_LEFT,
  KEY_LEFT, 
  KEY_LEFT,
  KEY_LEFT,
  KEY_LEFT,
  KEY_DOWN,
  KEY_RIGHT, 
  KEY_RIGHT,
  KEY_RIGHT, 
  KEY_RIGHT, 
  KEY_DOWN,
//  KEY_RIGHT, 
//  KEY_RIGHT,
  
 // KEY_DOWN, 
//  KEY_RIGHT,
  0
};


SDL_Surface *screen;

void platformInit(void)
{
	SDL_Init(SDL_INIT_VIDEO);

	atexit(SDL_Quit);

	screen = SDL_SetVideoMode(200, 400, 0, 0);
  SDL_WM_SetCaption("Evolutionary Tetris", "Evolutionary Tetris");
  
//	screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, bpp, flags);
	/*if(!screen)
	{
		fprintf(stderr, "Failed to open screen!\n");
		exit(-1);
	}*/
}

void platformQuit(void)
{
//	SDL_FreeSurface(tiles);
	SDL_Quit();
}

int nLastKey=0;

void waitUpdate(void)
{
  SDL_Event event;
  while(SDL_PollEvent(&event))
  { 
			switch(event.type)
			{
			  case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
				  case SDLK_UP:
            nLastKey = KEY_UP;
            break;
          case SDLK_LEFT:
            nLastKey = KEY_LEFT;
            break;
          case SDLK_RIGHT:
            nLastKey = KEY_RIGHT;
            break;
          case SDLK_DOWN:
            nLastKey = KEY_DOWN;
            break;
				  case SDLK_ESCAPE:
            nLastKey = KEY_QUIT;
            break;
          case 'c':
            nLastKey = KEY_C;
            break;
          case 'p':
            nLastKey = KEY_PAUSE;
            break;
          case ' ':
            nLastKey = KEY_GO;
            break;
				  default:
					break;
				}
			  case SDL_KEYUP:
          break;
      }
  }
  SDL_Flip(screen);
  sleep(20);
}

int nkey=0;

int getkey(void)
{
  int n;
 

/*
  n = keys[nkey];
  if(nkey < countof(keys))
    nkey++;
  else
  */
  n=nLastKey;
    
  nLastKey=0;
   
  return n;
}

void fillRect(SDL_Surface *targetscreen, int x, int y, int w,int h, Uint32 color)
{
  SDL_Rect r;
  r.x=x;
  r.y=y;
  r.w=w;
  r.h=h;
	SDL_FillRect(targetscreen, &r, color);
}

blockRect(SDL_Surface *targetscreen,int offset, int x, int y, Uint32 color)
{
  fillRect(screen,offset+(x*BRICK_SIZE),y*BRICK_SIZE,BRICK_SIZE,BRICK_SIZE,0);
  fillRect(screen,offset+(x*BRICK_SIZE+1),y*BRICK_SIZE+1,BRICK_SIZE-2,BRICK_SIZE-2,color);
}

Uint32 blockColors[] = { 
  0x000000,
  0xff0000,
  0x00ff00,
  0x0000ff,
  0xffff00,
  0x00ffff,
  0xff00ff,
  0x808000};

int videoUpdate(GRID *pGrid)
{
  videoUpdateOffset(pGrid, 0);
}
  
  
int videoUpdateOffset(GRID *pGrid, int offset)
{
  int x,y;
  Uint32 color=0xff00ff;
  
  
  for(y=0;y<GRID_Y;y++)
  {
    for(x=0;x<GRID_X;x++)
    {
      switch(pGrid->chGrid[y][x])
      {
        case 0:
          fillRect(screen,offset+(x*BRICK_SIZE),y*BRICK_SIZE,BRICK_SIZE,BRICK_SIZE,0x8080ff);
          break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
          blockRect(screen,offset,x,y,blockColors[(pGrid->chGrid[y][x]&0x0f)]);
          break;
        case BLOCK_MARKER:
          blockRect(screen,offset,x,y,0xffffff);
          break;
        default:
          blockRect(screen,offset,x,y,blockColors[(pGrid->chGrid[y][x]&0x0f)]|(0x101010*((pGrid->chGrid[y][x]&0xf0)>>4)));
        
      }
    }
  }
  fflush(stdout);
}