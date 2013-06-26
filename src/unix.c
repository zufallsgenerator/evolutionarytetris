/*****************************************************************************
 Evolutionary Tetris AI (C) Christer Byström 2005
 Artificial Intelligence course project at Linköpings Universitet, fall 2005
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <string.h>

#include "tetris.h"


/* ----------- */

static struct termios stored_settings;

void set_keypress(void)
{
    struct termios new_settings;

    tcgetattr(0,&stored_settings);

    new_settings = stored_settings;

    /* Disable canonical mode, and set buffer size to 1 byte */
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;

    tcsetattr(0,TCSANOW,&new_settings);
    return;
}

void reset_keypress(void)
{
    tcsetattr(0,TCSANOW,&stored_settings);
    return;
}

void platformInit(void)
{
  set_keypress();
}

int getkey(void)
{
  int key=0;
  
  switch(getc(stdin))
  {
    case 'z':
      return KEY_LEFT;
      break;
    case 'c':
      return KEY_RIGHT;
      break;
    case 's':
      return KEY_UP;
      break;
  }
  
  return 0;
}

void waitUpdate(void)
{
  usleep(150000);
}


int videoUpdate()
{
  int x,y;
  for(y=0;y<GRID_Y;y++)
  {
    for(x=0;x<GRID_X;x++)
    {
      switch(chGridShow[y][x])
      {
        case '\0':
          printf(" .");
          break;
        case 2:
          printf(" #");
          break;
        case 3:
          printf(" X");
          break;
        default:
          printf(" *");
        
      }
    }
    printf("\r\n");
  }
  fflush(stdout);
}
