/*****************************************************************************
 Evolutionary Tetris AI (C) Christer Byström 2005
 Artificial Intelligence course project at Linköpings Universitet, fall 2005
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "tetris.h"


void platformInit(void)
{
}

void platformQuit(void)
{
  exit(0);
}

void waitUpdate(void)
{
  return;
}

int videoUpdate(GRID *pGrid)
{
  videoUpdateOffset(pGrid, 0);
  return 0;
}
 
int getkey()
{
  return 0;
} 
  
int videoUpdateOffset(GRID *pGrid, int offset)
{
  int x,y;

  printf("\n");
  
  for(y=0;y<GRID_Y;y++)
  {
    if(offset)
      for(x=0;x<GRID_X+2;x++)
        printf(" ");
    for(x=0;x<GRID_X;x++)
    {
      switch(pGrid->chGrid[y][x])
      {
        case '\0':
          printf(".");
          break;
        case BLOCK_MARKER:
          printf("W");
          break;
        case BLOCK_MARKER2:
          printf("-");
          break;
        default:
          printf("#");
        
      }
    }
    printf("\n");
  }

  fflush(stdout);
  
  return 0;
}
