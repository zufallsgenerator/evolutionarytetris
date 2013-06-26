/*****************************************************************************
 Evolutionary Tetris AI (C) Christer Byström 2005
 Artificial Intelligence course project at Linköpings Universitet, fall 2005
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <time.h>

#ifdef WIN32
#include <windows.h>
#endif
#include "tetris.h"

#define DP(x) { printf("(%s:%i) ",__FILE__,__LINE__); printf(x); printf("\r\n"); fflush(stdout); }

BOOL g_bLog=FALSE;


/*  I, T, O, L, J, S, Z  */


BLOCK BlockI=
{
  2,'I',
  {
    {
      0,0,
      0,0,
      { 
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
      }
    },
    {
      0,0,
      0,0,
      { 
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0}
      }
    },
    {
      0,0,
      0,0,
      { 
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
      }
    },
    {
      0,0,
      0,0,
      { 
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
      }
    }
  }
};


BLOCK BlockT=
{
  4,'T',
  {
    {
      0,0,0,0,
      { 
        {0,0,0,0},
        {0,2,2,2},
        {0,0,2,0},
        {0,0,0,0}
      }
    },
    {
      0,0,0,0,
      { 
        {0,0,2,0},
        {0,0,2,2},
        {0,0,2,0},
        {0,0,0,0}
      }
    },
    {
      0,0,0,0,
      { 
        {0,0,2,0},
        {0,2,2,2},
        {0,0,0,0},
        {0,0,0,0}
      }
    },
    {
      0,0,0,0,
      { 
        {0,0,2,0},
        {0,2,2,0},
        {0,0,2,0},
        {0,0,0,0}
      }
    }
  }
};

BLOCK BlockO=
{
  1,'O',
  {
    {
      0,0,0,0,
      { 
        {0,0,0,0},
        {0,3,3,0},
        {0,3,3,0},
        {0,0,0,0}
      }
    },
    {
      0,0,0,0,
      { 
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
      }
    },
    {
      0,0,0,0,
      { 
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
      }
    },
    {
      0,0,0,0,
      { 
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
      }
    }
  }
};

BLOCK BlockL=
{
  4,'L',
  {
    {
      0,0,0,0,
      { 
        {0,0,0,0},
        {0,4,4,4},
        {0,4,0,0},
        {0,0,0,0}
      }
    },
    {
      0,0,0,0,
      { 
        {0,0,4,0},
        {0,0,4,0},
        {0,0,4,4},
        {0,0,0,0}
      }
    },
    {
      0,0,0,0,
      { 
        {0,0,0,4},
        {0,4,4,4},
        {0,0,0,0},
        {0,0,0,0}
      }
    },
    {
      0,0,0,0,
      { 
        {0,4,4,0},
        {0,0,4,0},
        {0,0,4,0},
        {0,0,0,0}
      }
    }
  }
};

BLOCK BlockJ=
{
  4,'J',
  {
    {
      0,0,0,0,
      { 
        {0,0,0,0},
        {0,5,5,5},
        {0,0,0,5},
        {0,0,0,0}
      }
    },
    {
      0,0,0,0,
      { 
        {0,5,5,0},
        {0,0,5,0},
        {0,0,5,0},
        {0,0,0,0}
      }
    },
    {
      0,0,0,0,
      { 
        {0,5,0,0},
        {0,5,5,5},
        {0,0,0,0},
        {0,0,0,0}
      }
    },
    {
      0,0,0,0,
      { 
        {0,0,5,0},
        {0,0,5,0},
        {0,5,5,0},
        {0,0,0,0}
      }
    }
  }
};

BLOCK BlockS =
{
  2,'S',
  {
    {
      0,0,0,0,
      { 
        {0,0,0,0},
        {0,0,6,6},
        {0,6,6,0},
        {0,0,0,0}
      }
    },
    {
      0,0,0,0,
      { 
        {0,0,6,0},
        {0,0,6,6},
        {0,0,0,6},
        {0,0,0,0}
      }
    },
    {
      0,0,0,0,
      { 
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
      }
    },
    {
      0,0,0,0,
      { 
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
      }
    }
  }
};

BLOCK BlockZ =
{
  2,'Z',
  {
    {
      0,0,0,0,
      { 
        {0,0,0,0},
        {0,7,7,0},
        {0,0,7,7},
        {0,0,0,0}
      }
    },
    {
      0,0,0,0,
      { 
        {0,0,0,7},
        {0,0,7,7},
        {0,0,7,0},
        {0,0,0,0}
      }
    },
    {
      0,0,0,0,
      { 
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
      }
    },
    {
      0,0,0,0,
      { 
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
      }
    }
  }
};

BLOCK *Blocks[]={
  &BlockI,
  &BlockT,
  &BlockO,
  &BlockL,
  &BlockJ,
  &BlockS,
  &BlockZ
  };

GRID gridShow;
GRID gridBack;


void seed(int entrophy)
{
  
  time_t t;
  time(&t);
  srand(rand() + entrophy + (int) t);
}

int gameInit()
{
  blockInit();
  seed(0);
  
  gridClearAll();
  
  return 0;
}

int gridClearAll(void)
{
  memset(&gridBack,0,sizeof(gridBack));
  memset(&gridShow,0,sizeof(gridShow));
  return 0;
}

void gridReset(void)
{
  memcpy(&gridShow,&gridBack,sizeof(gridShow));
}

/* Calculate borders for blocks */

void blockInit(void)
{
  int m,n,x,y;
  int xmin,xmax,ymin,ymax;
  BLOCK *pWholeBlock;
  BLOCKPART *pBlock;
  
  for(m=0;m<countof(Blocks);m++)
  {
    pWholeBlock=Blocks[m];
    
    for(n=0;n<pWholeBlock->nOrientations;n++)
    {
      ymin=xmin=4;
      ymax=xmax=0;
      
      pBlock=&pWholeBlock->Blocks[n];
      for(x=0;x<4;x++)
        if((pBlock->chPattern[0][x] ||
             pBlock->chPattern[1][x] ||
             pBlock->chPattern[2][x] ||
             pBlock->chPattern[3][x]))
        {
          xmin=MIN(xmin,x);
          xmax=MAX(xmax,x);
        }   

      for(y=0;y<4;y++)
        if((pBlock->chPattern[y][0] ||
             pBlock->chPattern[y][1] ||
             pBlock->chPattern[y][2] ||
             pBlock->chPattern[y][3]))
        {
          ymin=MIN(ymin,y);
          ymax=MAX(ymax,y);
        }   

      pBlock->x=xmin;
      pBlock->y=ymin;
      pBlock->width=xmax+1;
      pBlock->height=ymax+1;
      
    }
  }
}

/***********************************************************************************
  Function: blockPut
  Purpose: Put block on board
  Parameters: BLOCK *pWholeBlock - block to put
              int xpos           - 
              int ypos           -
              int orientation    - 
              BOOL bHighlight    - highlight placed block
              GRID *pGrid        - board to put block on

  Side effects: pGrid gets changed if block is placed on it
  Return value: BOOL - false if possible, true if block can't be put there
***********************************************************************************/

BOOL blockPut(BLOCK *pWholeBlock, int xpos, int ypos, int orientation, BOOL bHighlight, GRID *pGrid)
{
  int x,y;
  BLOCKPART *pBlock;
  int highlight=0;
  
  if(bHighlight)
    highlight=0xf0;

  pBlock = &pWholeBlock->Blocks[orientation];
  
  ASSERT(orientation < pWholeBlock->nOrientations);

  if(xpos < -pBlock->x || xpos+pBlock->width > GRID_X)
    return TRUE;

  for(y=pBlock->y;y<pBlock->height;y++)
  {
    for(x=pBlock->x;x<pBlock->width;x++)
    {
      if(pBlock->chPattern[y][x])
      {
        if(y+ypos < GRID_Y && 
           x+xpos < GRID_X && 
           !pGrid->chGrid[y+ypos][x+xpos])
          pGrid->chGrid[y+ypos][x+xpos]=pBlock->chPattern[y][x]|highlight;
        else
          if(pBlock->chPattern[y][x])
            return TRUE;
      }
    }
  }
  
  return FALSE;
}

/***********************************************************************************
  Function: blockTestPut
  Purpose: Check if it's possible to put block on board
  Parameters: BLOCK *pWholeBlock - block to put
              int xpos           - 
              int ypos           -
              int orientation    - 
              GRID *pGrid        - board to put block on

  Side effects: none
  Return value: BOOL - true if possible, false if block can't be put there
***********************************************************************************/

BOOL blockTestPut(BLOCK *pWholeBlock, int xpos, int ypos, int orientation, GRID *pGrid)
{
  int x,y;
  BLOCKPART *pBlock;
  

  pBlock = &pWholeBlock->Blocks[orientation];
  
  ASSERT(orientation < pWholeBlock->nOrientations);

  if(xpos < -pBlock->x || xpos+pBlock->width > GRID_X)
    return FALSE;

  for(y=pBlock->y;y<pBlock->height;y++)
  {
    for(x=pBlock->x;x<pBlock->width;x++)
    {
      if(pBlock->chPattern[y][x])
      {
        if(y+ypos < GRID_Y && 
           x+xpos < GRID_X && 
           !pGrid->chGrid[y+ypos][x+xpos])
           ;
           /* do nothing */
        else
          if(pBlock->chPattern[y][x])
            return FALSE;
      }
    }
  }
  
  return TRUE;
}


BLOCK *randomBlock(void)
{
  BLOCK *pBlock;
  pBlock=Blocks[rand()%countof(Blocks)];
  
  return pBlock;
}

int blockRotate(BLOCK *pBlock, int orientation)
{
    orientation=(orientation+1);
    if(orientation >= pBlock->nOrientations)
      orientation=0;  
      
  return orientation;
}


void collapseLine(GRID *pGrid, int targetline)
{
  int x,y;
  
  for(y=targetline;y>0;y--)
    for(x=0;x<GRID_X;x++)
      pGrid->chGrid[y][x]=pGrid->chGrid[y-1][x];
  
  for(x=0;x<GRID_X;x++)
    pGrid->chGrid[0][x]=0;
}

void gridUpdate(GRID *pGrid)
{
  int x,y;
  
  for(y=0;y<GRID_Y;y++)
  {
    for(x=0;x<GRID_X;x++)
    {
      /* Fade out highlight */
      if(pGrid->chGrid[y][x]&0xf0)
        pGrid->chGrid[y][x]=((pGrid->chGrid[y][x]&0xf0)-0x10)|(pGrid->chGrid[y][x]&0x0f);
    }
  }
}

void checkForLines(GRID *pGrid)
{
  int x,y;
  int nHole;
  
  pGrid->nRemovedLines=0;
  
  for(y=0;y<GRID_Y;y++)
  {
    nHole=0;
    for(x=0;x<GRID_X;x++)
    {
      if(!pGrid->chGrid[y][x])
      {
        nHole=1;
        /* Break out of loop */
        x=GRID_X;
      } 
    }
    /* Complete line without wholes? */
    if(!nHole)
    {
      for(x=0;x<GRID_X;x++)
        pGrid->chGrid[y][x]=0;
        
      collapseLine(pGrid,y);
      y=0; /* Start over */
      
      pGrid->nRemovedLines++;
    }
  }
}

int blockDrop(BLOCK *pBlock,int xpos,int ypos, int orientation)
{
  int y;
  
  for(y=ypos;y<GRID_Y;y++)
  {
    if(!blockTestPut(pBlock,xpos,y,orientation,&gridBack))
      return y;
  }
  
  return ypos;
}

void blockPrint(PBLOCK pWholeBlock, int orientation)
{
  int x,y;
  PBLOCKPART pBlock = &pWholeBlock->Blocks[orientation];
  
  for(y=0;y<BLOCK_SIZE;y++)
  {
    printf("\n");
    for(x=0;x<BLOCK_SIZE;x++)
    {
      if(pBlock->chPattern[y][x])
        printf("*");
      else
        printf(" ");
    }
  }
  printf("\n");
}

char g_achLog[512];

void logInit(void)
{ 
  time_t timer;
  struct tm *tm;


  timer=time(NULL);
  tm=localtime(&timer);

  sprintf(g_achLog,"log%02d%02d%02d-%02d%02d.txt",tm->tm_year-100,tm->tm_mon+1,tm->tm_mday,
                                         tm->tm_hour,tm->tm_min);
}

void logCleanup(void)
{
  ;
}


char *strGenes="genes.txt";

int main(int argc, char **argv)
{
  int n;
  IND ind;
  
  platformInit();
  gameInit();
  logInit();
  
  /* No arguments - just evolve genes.txt */
  if(argc < 2 || (argc > 1 && !strcmp(argv[1],"-evolve")))
  {
    if(argc > 2)
      strGenes = argv[2];
    
    printf("Evolving %s\n",strGenes);
    
    evolution(&ind,MAX_GENERATIONS);
    printf("Evolved: ");
    for(n=0;n<NWEIGHTS-2;n+=3)
      printf("%f %f %f\n",W_GET(ind.w[n]),W_GET(ind.w[n+1]),W_GET(ind.w[n+2]));
      
    printf("Magic: %x, Fitness %d",ind.magic,ind.nFitness);
    printf("\n");
    game(&ind); 
  } 
  else if(!strcmp(argv[1],"-play"))
  {
    if(argc > 2)
      strGenes = argv[2];
    
    /* Fetch fittest individual */
    evolution(&ind,0);
    game(&ind);
  } 
  else if(!strcmp(argv[1],"-test")) 
  {
    printf("Testing %s\n",strGenes);
    if(argc > 2)
      strGenes = argv[2];
    for(n=0;n<1;n++)
    {
      ind.nFitness=0;
      indTest(&ind,0);
      printf("Test [%d]: %d\r\n",n,ind.nFitness);
    }
  } 
  else
  {
    printf("Usage: %s <-evolve|-play|-test> <genefile>\n",argv[0]);
  }

  logCleanup();
  platformQuit();

  return 0;
}
/***********************************************************************************
  Function: popSetSelectionIndex
  Purpose: Calculate a selection index for each individual
           The difference between the selection indexes for
           two individuals is the relative probability
           for the first individual to be selected for 
           reproduction.
           
  Parameters: IND *pool[] - genepool

  Side effects: selectionindex is set for each individual, and selectionmax in
                ppop
  Return value: none
***********************************************************************************/

void popSetSelectionIndex(POPULATION *ppop)
{
  int n;
  int selectionindex=0;
  int nTotal, nMean;
  
  nTotal=0;
  for(n=0;n<POOL_SIZE;n++)
    nTotal+=ppop->pool[n]->nFitness;
    
  nMean=nTotal/POOL_SIZE;
  
  if(nMean==0)
  {
    printf("nMean is 0!\n");
    nMean=1;
  }
  for(n=0;n<POOL_SIZE;n++)
  {
    selectionindex+=pow((double)(ppop->pool[n]->nFitness/nMean),1.7);
    if(n < ELITE_SELECTION)
      selectionindex+=(nMean/2);
    
    ppop->pool[n]->selectionindex=selectionindex;
  }
  
  ppop->selectionmax=selectionindex;
  printf("selectionmax is %d\n",selectionindex);
}

IND *popSelectInd(POPULATION *ppop)
{
  int index;
  int n;

  if(ppop->selectionmax==0)
  {
    printf("ppop->selectionmax is 0!\n");
    ppop->selectionmax=1;
  }
  
  index=rand()%ppop->selectionmax;

  for(n=0;n<POOL_SIZE;n++)
  {
    if(ppop->pool[n]->selectionindex>=index)
      return ppop->pool[n];
  }

  PANIC("No individual found!");
  return NULL; /* We shouldn't come here */
}

void popCopy(POPULATION *ptarget, POPULATION *psource)
{
  int n;
  popInit(ptarget, FALSE);

  ptarget->generations=psource->generations;
  ptarget->eliteselection=psource->eliteselection;
  ptarget->selectionmax=psource->selectionmax;
  
  for(n=0;n<POOL_SIZE;n++)
    IND_COPY(ptarget->pool[n],psource->pool[n]);
}

void popReproduce(POPULATION *ppop)
{
  int n,m;
  static POPULATION popold;
  POPULATION *ppopold;
  IND *pparent1,*pparent2,*pchild1,*pchild2;
  
  /* Assume pool i sorted */

  ppopold=&popold;
  

  popSetSelectionIndex(ppop);
 
  for(n=0;n<POOL_SIZE;n++)
  {
    ppop->pool[n]->bCrossed=FALSE;
    ppop->pool[n]->bMutated=FALSE;
    ppop->pool[n]->nLastPos=n;
  }

  popInit(&popold,FALSE);
  popCopy(&popold,ppop);
  
  for(n=ELITE_SELECTION;n<(POOL_SIZE-1);n+=2)
  {
    int start, length;
    WEIGHT w;

    /* Select two parents */
    pparent1=popSelectInd(&popold);
    pparent2=popSelectInd(&popold);
    /* Two children */
    pchild1=ppop->pool[n];
    pchild2=ppop->pool[n+1];
    /* Copy parents over children */
    IND_COPY(pchild1,pparent1);
    IND_COPY(pchild2,pparent2);
    
    /* Crossover children */
    start = 3*(rand()%(NWEIGHTS/3));
    length = 3*(rand()%(NWEIGHTS/3));

    pchild1->bCrossed=TRUE;
    pchild2->bCrossed=TRUE;
    pchild1->bMutated=FALSE;
    pchild2->bMutated=FALSE;
    
    pchild2->nParent1=pchild1->nParent1=pchild1->nLastPos;
    pchild2->nParent2=pchild1->nParent2=pchild2->nLastPos;
    
    /* Set average last fitness */
    pchild1->nPrevFitness=pchild2->nPrevFitness=
    ((pchild1->nPrevFitness=pchild2->nPrevFitness)/2);
    
    for(m=start;m<start+length;m++)
    {
      W_SET(w,pchild1->w[m%NWEIGHTS]); 
      W_SET(pchild1->w[m%NWEIGHTS],pchild2->w[m%NWEIGHTS]);
      W_SET(pchild2->w[m%NWEIGHTS],w); 
    }
    
  }
}


void poolSort(IND *pool[])
{
  IND tmp;
  int n;
  BOOL bChange=TRUE;
  
  /* Simple bubble sort */
  while(bChange)
  {
    bChange=FALSE;
    for(n=0;n<POOL_SIZE-1;n++)
    {
      if(pool[n+1]->nFitness > pool[n]->nFitness)
      {
        IND_COPY(&tmp,pool[n]);
        IND_COPY(pool[n],pool[n+1]);
        IND_COPY(pool[n+1],&tmp);
        bChange=TRUE;
      }
    }
  }
}

void indInit(IND *pInd)
{
  int n;
  
  memset(pInd,0,sizeof(IND));
  
  for(n=0;n<NWEIGHTS-2;n+=3)
  {
    
    pInd->w[n].d =  (double)(rand()%1500)*0.1;
    pInd->w[n+1].d =  (double)(rand()%500)*0.1;
    /* Exponent */
    pInd->w[n+2].d =  (double)(rand()%2000)*0.001;
  }
  
  fflush(stdout);
    
  pInd->magic=0xC0FFEE;
  
}

void popInit(POPULATION *ppop, BOOL bInitWeights)
{
  int n;

  memset(ppop,0,sizeof(POPULATION));
  for(n=0;n<POOL_SIZE;n++)
  {
    ppop->pool[n] = &ppop->mem[n];
    ppop->pool[n]->magic = 0xD0DECAED; 
    if(bInitWeights)
      indInit(ppop->pool[n]);
    ppop->pool[n]->id = n;
  }
}

void evolution(IND *pElite, int nogenerations)
{
  POPULATION pop;
  BOOL bEvolve=TRUE;
  int m,n;
  int generations=1;
  int curgeneration=1;
  int nMean;
  int nMax;
  int nEliteMean;
  FILE *fp;
  float d;

  /* Init population */  

  popInit(&pop,TRUE);

  /* Load inds */

  fp=fopen(strGenes,"r");
  if(fp)
  {
    fscanf(fp,"%d ",&curgeneration);
    double dd;
    for(n=0;n<POOL_SIZE;n++)
    {
      for(m=0;m<NWEIGHTS;m++)
      {
        fscanf(fp,"%f",&d);
        dd = (double) d;
        W_SET_D(pop.pool[n]->w[m],dd);
      }
    }
    fclose(fp);
  }
  
  if(!nogenerations)
  {
    if(pElite)
      IND_COPY(pElite,pop.pool[0]);
    return;
  }
  
  while(bEvolve)
  {

    printf("Evaluating: ");
    fflush(stdout);
    for(n=0;n<POOL_SIZE;n++)
    {
      indTest(pop.pool[n],0);
      printf("#");
      fflush(stdout);
    }
    
    printf("\n");
    
    poolSort(pop.pool);

    
    nEliteMean=0;
    for(n=0;n<ELITE_SELECTION;n++)
      nEliteMean+=pop.pool[n]->nFitness;
    nEliteMean=nEliteMean/ELITE_SELECTION;

    nMax=0;
    nMean=0;
    for(n=0;n<POOL_SIZE;n++)
    {
      nMean+=pop.pool[n]->nFitness;
      if(pop.pool[n]->nMax > nMax)
        nMax=pop.pool[n]->nMax;
    }
    nMean=nMean/POOL_SIZE;

    /* Log */
    fp=fopen(g_achLog,"a");
    if(fp)
    {
      fprintf(fp,"%d\t%d\t%d\t%d\t%d\n",curgeneration,nEliteMean,nMean,pop.pool[0]->nFitness,nMax);
      fclose(fp);
    }
    
    printf("Generation: %d\tElite mean: %d\tMean: %d\tMean Max: %d\tMax: %d\n-----------------------------------\n",curgeneration,nEliteMean,nMean,pop.pool[0]->nFitness,nMax);
    
    for(n=0;n<25/*ELITE_SELECTION*/;n++)
    {
      printf("ID: %d\tFitness: %d\t(%d)\t",pop.pool[n]->id,pop.pool[n]->nFitness,pop.pool[n]->nPrevFitness);
      if(pop.pool[n]->bCrossed)
        printf("[ParLast: %d\t%d]\t",pop.pool[n]->nParent1,pop.pool[n]->nParent2);
      else
        printf("[   Last: %d]\t\t",pop.pool[n]->nLastPos);
      printf("%s%s\n",(pop.pool[n]->bCrossed ? " crossed" : ""),(pop.pool[n]->bMutated ? " mutated" : ""));
      if(n==(ELITE_SELECTION-1))
        printf("---------------------------------------------------------------------------\n");
    }
      
    if(generations++ > nogenerations)
    {
      bEvolve=FALSE;
      
      if(pElite)
        IND_COPY(pElite,pop.pool[0]);

        /*
      for(n=0;n<10;n++)
      {
        indTest(pElite,0);
        printf("E: Test [%d]: %d\r\n",n,pElite->nFitness);
      }
      */
      
      
      return;
    }  

    /* Save genes */
    fp=fopen(strGenes,"w");
    if(fp)
    {
      fprintf(fp,"%d ",curgeneration);
      for(n=0;n<POOL_SIZE;n++)
      {
        for(m=0;m<NWEIGHTS;m++)
        {
          fprintf(fp,"%f ",pop.pool[n]->w[m].d);
        }
        
        fprintf(fp,"\n");
      }
      
      fclose(fp);
    }
    else
      printf("Failed to save genepool!\n");
        
     
    
    /* Cross-over */
    popReproduce(&pop);
    
    /* Mutate */
    
    for(n=ELITE_SELECTION;n<POOL_SIZE;n++)
    {
      if(TRUE || 0==(rand()&1))
      {
        for(m=0;m<NWEIGHTS;m++)
        {
          if(0==(rand()&63))
          {
            int windex;
            windex=m;/*rand()%NWEIGHTS*/
    W_SET_D(pop.pool[n]->w[windex],W_GET(pop.pool[n]->w[windex]) * (double)(((double)(25+(rand()%150)))*0.01));
            pop.pool[n]->bMutated=TRUE;
          }
        }
      }
      
      /* Compulsory scaling */
   
      for(m=0;m<NWEIGHTS;m++)
      {
        W_SET_D(pop.pool[n]->w[m],W_GET(pop.pool[n]->w[m]) * (double)(((double)(90+(rand()%20)))*0.01));
        
      }
    }


    
    fflush(stdout);
    
    curgeneration++;
  }
}

int game(IND *pInd)
{
  BLOCK *pBlock=NULL;
  BOOL bBlockHit=FALSE;
  BOOL bQuit=FALSE;
  BOOL bAIMove=FALSE;//TRUE;
  BOOL bPause=FALSE;
  BOOL bShow=TRUE;
  int nTotalLines=0;
  int nLines;
  int xpos=2, ypos=0, orientation=0;
  int key=0;
  int nongamekey=0;
  int ticks=0;
  int targetx,targetorientation;
  int nTotalTimes=0;
  int nTimes=nTotalTimes;
  
  do {  
  
  memset(&gridBack,0,sizeof(gridBack));
  memset(&gridShow,0,sizeof(gridShow));
  xpos=2;
  ypos=0;
  orientation=0;
  key=0;
  ticks=0;
  int nShow=0;

  nLines=0;
  
  pBlock=randomBlock();
  
  
  do
  {
    if(bShow)
    {
      videoUpdate(&gridShow);
      gridUpdate(&gridBack);
    }
    
    if(bAIMove)
    { 
      aiDecide(&gridBack,pBlock,&targetx,&targetorientation,pInd);
      nongamekey=getkey();
      
      if(orientation!=targetorientation)
      {
        key=KEY_UP;
      }
      else 
        if(xpos != targetx)
        {
          if(xpos>targetx)
            key=KEY_LEFT;
          else
            key=KEY_RIGHT;
            
        } else 
            if(xpos == targetx)
              {
                key=KEY_DOWN;
              }
      
    
    }
    else
      nongamekey=key=getkey();
      
    if(nongamekey==KEY_QUIT)
      bQuit=TRUE;
      
    if(nongamekey==KEY_C)
      key=nongamekey;
      
    switch(key)
    {
      case KEY_PAUSE:
        bPause = TRUE;
        break;
      case KEY_GO:
        bPause = FALSE;
        break;
      case KEY_LEFT:
        xpos--;
        if(!blockTestPut(pBlock,xpos,ypos,orientation,&gridBack))
          xpos++;
        break;
      case KEY_RIGHT:
        xpos++;
        if(!blockTestPut(pBlock,xpos,ypos,orientation,&gridBack))
          xpos--;
        break;
      case KEY_UP:
        {
          /* Save previous orientation */
          int tmporientation=blockRotate(pBlock,orientation);
          /* Move it out from right-hand border */
          if(xpos+pBlock->Blocks[tmporientation].width > GRID_X)
            xpos=GRID_X - pBlock->Blocks[tmporientation].width;
          if(xpos < -pBlock->Blocks[tmporientation].x)
            xpos=-pBlock->Blocks[tmporientation].x;
          /* Rotation made it hit other bricks? */
          if(blockTestPut(pBlock,xpos,ypos,orientation,&gridBack))
            orientation=tmporientation;
        }
        break;
      case KEY_DOWN:
        ypos=blockDrop(pBlock,xpos,ypos,orientation);
        break;
      case KEY_QUIT:
        bQuit = TRUE;
        break;
      case KEY_C:
      if(!bPause)
      {
        /* Let computer decide */
        if(bAIMove==TRUE)
          bAIMove=FALSE;
        else
          bAIMove=TRUE;
      }
      break;
    }

    if(bShow)
    {
      nShow = 0;
      waitUpdate();
    }
    
    gridReset();
    bBlockHit = blockPut(pBlock,xpos,ypos,orientation,FALSE,&gridShow);
    
    if(!bPause)
    {
      if(bBlockHit)
      {
        if(ypos == 0)
        {
          bQuit=TRUE;
        }
        else
          nLines++;
        /* Put block on the permanent grid */
        if(blockPut(pBlock,xpos,ypos-1,orientation,TRUE,&gridBack))
        {
          ypos--;
          bBlockHit=FALSE;
          ticks=0;
        }
        /* Check for full lines */
        checkForLines(&gridBack);
        /* Copy permanent grid to display grid */
        gridReset();
        ticks=0;
      }
      else
      {
        ticks++;
        if(ticks>20)
        {
          seed(0); 
          ticks=0;
          ypos++;
        }
      }
  
      
      if(ypos>GRID_Y || bBlockHit)
      {
        ypos=0; /* TODO: Should really be -1 but it doesn't work now */
                /*       whatever, this is just the bells and whistles */
        pBlock=randomBlock();
        xpos=2;
        orientation=0;
      }
    }

  } while (!bQuit);
  
  nTotalLines+=nLines;

  
  ticks=0;
  bQuit=FALSE;
  } while(nTimes--);
  
  
  fprintf(stdout,"Average: %d\n",nTotalLines/nTotalTimes);
  
  return 0;
}



/***********************************************************************************
  Function: indTest
  Purpose: Test the fitness of an individual
  Parameters: IND *pInd

  Side effects: some parameters like fitness in pInd are set, 
                global gameboards are used
  Return value: int - fitness
***********************************************************************************/

/* Remove best and worse results */
int indTest(IND *pInd, int nMaxLevel)
{  
  BLOCK *pBlock=NULL;
  BOOL bQuit;
  int nTotalLines=0;
  int nLines;
  int targetx,targetorientation;
  int nTotalTimes=TEST_ROUNDS;
  int nMax = -1;
  int nMin = -1;
  int nTimes;
  
  nTimes=nTotalTimes;
  
  bQuit=FALSE;
  
  do /* Play n games */
  {
    nLines=0;
    gridClearAll();
    bQuit=FALSE;

    
    do /* Play a game */
    {
      pBlock=randomBlock();
  
      /* Get AI:s decision */
      if(aiDecide(&gridBack,pBlock,&targetx,&targetorientation,pInd))
      {
        /* Drop piece */
        aiDrop(&gridBack,&gridShow,pBlock,targetx,0,targetorientation);
        /* Copy gridShow onto gridBack */
        GRID_COPY(&gridBack,&gridShow);
        nLines++;
      }
      else
        bQuit = TRUE;
        
    } while (!bQuit);

    nTotalLines+=nLines;
    
    if(nMin == -1 || nLines < nMin)
      nMin = nLines;
    
    if(nLines > nMax)
      nMax = nLines;
   
   /*
    fprintf(stdout,"[%d] Average: %d Lines: %d\n",nTimes,nTotalLines/(nTotalTimes-nTimes+1),nLines);
    fflush(stdout);
   */
  } while(nTimes--);

/*  
  fprintf(stdout,"Average: %d\n",nTotalLines/nTotalTimes);
  fflush(stdout);
  */
  
  pInd->nPrevFitness=pInd->nFitness;
  pInd->nFitness = (nTotalLines-nMin-nMax)/(nTotalTimes-2);
  pInd->nMax=nMax;
  seed(0);
  
  return pInd->nFitness;
}

/***********************************************************************************
  Function: gridPrint
  Purpose: print ascii representation of board
  Parameters: GRID *pGrid - board

  Side effects: chars written to stdout
  Return value: void
***********************************************************************************/

void gridPrint(GRID *pGrid)
{
  printf("\n");
  int x,y;
  for(y=0;y<GRID_Y;y++)
  {
    for(x=0;x<GRID_X;x++)
    {
      switch(pGrid->chGrid[y][x])
      {
        case '\0':
          printf(".");
          break;
        default:
          printf("#");
        
      }
    }
    printf("\r\n");
  }
  fflush(stdout);
}

__inline BOOL gridHoleClear(GRID *pGrid, int x, int ypos)
{
  int y;
  
  for(y=ypos-1;y>=0;y--)
  {
    if(pGrid->chGrid[y][x])
      return FALSE;
  }
  
  return TRUE;
}

int gridGetConnectedHoles(GRID *pGrid)
{
  int x,y,nHoles;
  
  nHoles=0;
  
  for(y=0;y<GRID_Y;y++)
  {
    for(x=0;x<GRID_X;x++)
    {
    
      if(!pGrid->chGrid[y][x] && !gridHoleClear(pGrid, x, y))
      {
        /* Only count connected holes */
        if(x >= 0 && pGrid->chGrid[y][x-1])
          nHoles++;
      } 
    }
  }
  
  return nHoles;
}

int gridGetHoles(GRID *pGrid)
{
  int x,y,nHoles,nBricks;
  
  nHoles=0;
  
  for(y=0;y<GRID_Y;y++)
  {
    nBricks=GRID_X;
    for(x=0;x<GRID_X;x++)
    {
    
      if(!pGrid->chGrid[y][x] && !gridHoleClear(pGrid, x, y))
      {
        nHoles++;
        nBricks--;
      } 
    }
  }
  
  return nHoles;
}

__inline BOOL gridWell(GRID *pGrid, int x, int y)
{
  BOOL bRet=FALSE;
  /* Check for well */

  if(!pGrid->chGrid[y][x] && 
    (x < 1 ? TRUE : pGrid->chGrid[y][x-1]) && 
    (x >= (GRID_X-1) ? TRUE : pGrid->chGrid[y][x+1]))
    bRet = TRUE;
  
  if(bRet && g_bLog)
    fprintf(stdout,"WELL! x: %d | y: %d\r\n",x,y);

  return bRet;
}

int gridGetMaxWell(GRID *pGrid)
{
  int x,y;
  int nMax=0;
  int nCurWell;
  BOOL bWell;

  for(x=0;x<GRID_X;x++)
  {
    nCurWell=0;
    bWell = FALSE;
    
    for(y=0;y < GRID_Y;y++)
    {
      bWell = gridWell(pGrid,x,y);
      if(bWell)
        break;
    }
    
    if(bWell)
    {
      for(;!pGrid->chGrid[y][x] && y<GRID_Y;y++)
        nCurWell++;
    }
   
    if(nCurWell > nMax)
      nMax=nCurWell;
  }
  
  
  return nMax;
}

int gridGetWells(GRID *pGrid)
{
  int x,y;
  int nWells=0;
  int nCurWell;
  BOOL bWell;
  BOOL bBreakY;

  GRID tmpGrid;
  
  if(g_bLog)
    GRID_COPY(&tmpGrid,pGrid);

  
  for(x=0;x<GRID_X;x++)
  {
    nCurWell=0;
    bWell = FALSE;
    bBreakY=FALSE;
    
    for(y=0;!bBreakY && y < GRID_Y;y++)
    {
      if(pGrid->chGrid[y][x])
      {
        if(g_bLog && y > 0)
        {
          tmpGrid.chGrid[y-1][x] = BLOCK_MARKER2;
        }
        /* Break out of loop */
        break;
      }
      
      bWell = gridWell(pGrid,x,y);
      if(bWell)
      { 
        if(g_bLog)
          tmpGrid.chGrid[y][x] = BLOCK_MARKER;
        /* Break out of loop */
        break;
      }  
    }
    
    if(bWell)
    {
      for(;!pGrid->chGrid[y][x] && y<GRID_Y;y++)
      {
        tmpGrid.chGrid[y][x] = BLOCK_MARKER;
        nCurWell++;
      }
    }
   
    nWells += nCurWell;
  }
  
  if(g_bLog & nWells)
    videoUpdateOffset(&tmpGrid,400);
  
  return nWells;
}


int gridGetLow(GRID *pGrid)
{
  int nLow;
  int nLowest;
  int x,y;


  nLowest=0;
  
  for(x=0;x<GRID_X;x++)
  {
    nLow=-1;
    
    for(y=0;y<GRID_Y;y++)
    {
      if(pGrid->chGrid[y][x])
      {
        if(g_bLog)
          printf("%d ",y);
        nLow=y;
        /* Break out of loop */
        break;
      }
    }
    
    if(nLow != -1  && nLow > nLowest)
      nLowest = nLow;
    if(nLow == -1)
      nLowest = GRID_Y-1;
      
  }
  if(g_bLog)
    printf("\n");
  
  return ((GRID_Y-1)-nLowest);
}


int gridGetHeight(GRID *pGrid)
{
  int x,y,nBricks;
  
  for(y=0;y<GRID_Y;y++)
  {
    nBricks=0;
    
    for(x=0;x<GRID_X;x++)
    {
      if(pGrid->chGrid[y][x])
      {
        nBricks++;
        /* Break out of loop */
        x=GRID_X;
      } 
    }
    
    if(nBricks)
      return (GRID_Y-y);
  }
  
  return 0;
}


int gridGetAltDiffs(GRID *pGrid)
{
  int nTop;
  
  nTop = gridGetHeight(pGrid)-gridGetLow(pGrid);

  return nTop;
}

int xgridGetAltDiffs(GRID *pGrid)
{
  int x,y;
  int nLowest=GRID_Y;
  int nAvreage;
  int nTotal;
  int nDiffs;
  int nRows[GRID_X];
  
  
  for(x=0;x<GRID_X;x++)
  {
    for(y=GRID_Y-1;y >= 0;y--)
      if(pGrid->chGrid[y][x])
      {
        y++;
        break;
      }
      
    nRows[x] = y;
    
    if(y < nLowest)
      nLowest = y;
  }
  
  nTotal = 0;
  for(x=0;x<GRID_X;x++)
    nTotal += nRows[x];
    
  nAvreage = nTotal / GRID_X;
  
  nDiffs = 0;
  for(x=0;x<GRID_X;x++)
    nDiffs += abs(nRows[x] - nAvreage);
    
  nDiffs = nDiffs / GRID_X;

  return nDiffs;
}

/*
int gridGetAltDiff(GRID *pGrid)
{
  return gridGetHeight(pGrid) - gridGetLowest(pGrid);
}
*/
/***********************************************************************************
  Function: aiDrop
  Purpose: Drop block
  Parameters: 

  Side effects: pGridTarget is affected
  Return value: int - 0 for successful drop, 1 otherwise 
***********************************************************************************/

int aiDrop(GRID *pGridSource, GRID *pGridTarget, BLOCK *pBlock, int xpos, int ypos, int orientation)
{
  int y;
  BOOL bHit=FALSE;
  
  for(y=ypos;!bHit;y++)
  {
    GRID_COPY(pGridTarget,pGridSource);
      
    bHit = blockPut(pBlock,xpos,y,orientation,FALSE,pGridTarget);
    
    /* Did we hit the wall before even dropping piece? */
    if(bHit && y==ypos)
      return 1;
  }
  
  y-=2;
  
  GRID_COPY(pGridTarget,pGridSource);
  blockPut(pBlock,xpos,y,orientation,FALSE,pGridTarget);
  checkForLines(pGridTarget);
  
  return 0;
}



/***********************************************************************************
  Function: aiRate
  Purpose: Rate a board
  Parameters: GRID *pGRID - board to rate
              IND *pInd - contains weights for rating

  Side effects: none
  Return value: int - rating of board
***********************************************************************************/

BOOL g_bExp=EXP_RATING;
BOOL g_bLin=LINEAR_RATING;

int aiRate(GRID *pGrid, IND *pInd)
{
  int rating;
  int nHeight, nHoles,nConnectedHoles, nWells,nDiffs,nMaxWell;
  
  nHeight = gridGetHeight(pGrid);
  nHoles = gridGetHoles(pGrid);
  nConnectedHoles = gridGetConnectedHoles(pGrid);
  nWells = gridGetWells(pGrid);
  nMaxWell = gridGetMaxWell(pGrid);
  nDiffs = gridGetAltDiffs(pGrid);

// Funkar skitbra:  rating = 3*nHeight + 5*nGridHoles + 2*(nWells) + nDiffs;
  
//  rating = 3*nHeight + 5*nGridHoles + 2*(nWells) + nDiffs;
//  rating = fRateHeight*nHeight + fRateHole*nGridHoles + fRateWells*nWells + fRateDiffs*nDiffs;
  
  
  rating = (g_bLin ? (W_GET(pInd->w[0]) * nHeight) : 0) +
           (g_bExp ? (W_GET(pInd->w[1])*qpow(nHeight,W_GET(pInd->w[2]))) : 0) +
           (g_bLin ? (W_GET(pInd->w[3]) * nHoles) : 0)+
           (g_bExp ? (W_GET(pInd->w[4])*qpow(nHoles,W_GET(pInd->w[5]))) : 0)+
           (g_bLin ? (W_GET(pInd->w[6]) * nWells) : 0) +
           (g_bExp ? (W_GET(pInd->w[7])*qpow(nWells,W_GET(pInd->w[8]))) : 0)+
           (g_bLin ? (W_GET(pInd->w[9]) * nDiffs) : 0) +
           (g_bExp ? (W_GET(pInd->w[10])*qpow(nDiffs,W_GET(pInd->w[11]))) : 0) +
           (g_bLin ? (W_GET(pInd->w[12]) * nConnectedHoles) : 0) +
           (g_bExp ? (W_GET(pInd->w[13])*qpow(nConnectedHoles,W_GET(pInd->w[14]))) : 0)+
           (W_GET(pInd->w[15]) * pGrid->nRemovedLines) +
           (g_bExp ? (W_GET(pInd->w[16])*qpow(pGrid->nRemovedLines,W_GET(pInd->w[17]))) : 0)+
           (W_GET(pInd->w[18]) * nMaxWell) +
           (g_bExp ? (W_GET(pInd->w[19])*qpow(nMaxWell,W_GET(pInd->w[20]))) : 0);

/*
  rating = (pInd->w[0] * nHeight) +
           ((pInd->w[1]/10) * (nHeight^2)) +
           (pInd->w[2] * nHoles) +
           ((pInd->w[3]/10) * (nHoles^2)) +
           (pInd->w[4] * nWells) +
           ((pInd->w[5]/10) * (nWells^2)) +
           (pInd->w[6] * nDiffs) +
           ((pInd->w[7]/10) * (nDiffs^2)) +
           (pInd->w[8] * nConnectedHoles) +
           ((nConnectedHoles^(int)pInd->w[9])) +
           (pInd->w[10] * pGrid->nRemovedLines) +
           ((pGrid->nRemovedLines^(int)pInd->w[11]));
*/  
  
  if(g_bLog)
    fprintf(stdout,"Height: %d Holes: %d Wells: %d Diffs: %d => ",nHeight,nHoles,nWells,nDiffs);
  
  return rating;
}
/***********************************************************************************
  Function: aiDecide
  Purpose: Get AI's decision for best move
  Parameters: GRID *pGRID       - current board
              BLOCK *pBlock     - block to try
              int *px           - receives decided x position
              int *porientation - receives decided orientation
              IND *pInd       - contains weights
  
  Side effects: px, porientation are changed
  
  Return value: BOOL - FALSE if not choice could be made, TRUE otherwise
***********************************************************************************/

BOOL aiDecide(GRID *pGrid,BLOCK *pBlock, int *px, int *porientation, IND *pInd)
{
  int x=0;
  int tmpx;
  int tmpy;
  BOOL bCanMove;
  PBLOCKPART pBlockPart;
  int orientation=0;
  int tmporientation;
  int lastx=0;
  int lastorientation=0;
  int y;
  BOOL bSuccessFulDrop=FALSE;
  float newrating=0;
  float rating=0;
  static GRID gridTarget;
  

  /* Start dropping from just above lowest (highest) row where */  
  y = (GRID_Y-gridGetHeight(pGrid));
  
  if(y > 4)
    y-=4;
  else
    y=1;
    
  y=1; /* remove */


/* Loop through all orientations and x-positions to check
   for best placement, and choose placement that gives
   board with best rating */
  
  for(x=-2;x<GRID_X-1;x++)
  {

      for(orientation=0;orientation<pBlock->nOrientations;orientation++)
      {
        pBlockPart=&pBlock->Blocks[orientation];
        switch(pBlock->id)
        {
          case 'O':
          case 'S':
          case 'Z':
          case 'L':
          case 'J':
          case 'T':
            if(orientation==0)
              y=-1;
            else
              y=0;
            break;
          case 'I':
            if(orientation==0)
              y=-1;
            else
              y=0;
            break;
        };
      bCanMove=TRUE;

      tmpy=y;
      
      if(orientation)
        for(tmporientation=0;tmporientation<=orientation;tmporientation++)
        {
          if(!blockTestPut(pBlock,DROP_X,tmpy,tmporientation,pGrid))
          {
            y=0;
            tmpy=0;
            if(!blockTestPut(pBlock,DROP_X,0,tmporientation,pGrid))
            {
              bCanMove=FALSE;
              /* break out of loop */
              break;
            }
          }
        }


        
    if(bCanMove)
    {
      if(x>DROP_X)
      {
        for(tmpx=DROP_X;tmpx<x;tmpx++)
          if(!blockTestPut(pBlock,tmpx,y,orientation,pGrid))
          {
            bCanMove=FALSE;
            /* break out of loop */
            break;
          }
      }
      
      if(x<DROP_X)
      {
        for(tmpx=DROP_X;tmpx>x;tmpx--)
          if(!blockTestPut(pBlock,tmpx,y,orientation,pGrid))
          {
            bCanMove=FALSE;
            /* break out of loop */
            break;
            
          }
      }
    }
    
    if(bCanMove)
    {
        /* IS drop possible? */
        if(!aiDrop(pGrid, &gridTarget, pBlock, x, y, orientation))
        {
          /* YES */
          newrating = aiRate(&gridTarget,pInd);
        
          /* Check for better rating */
          if(rating==0 || newrating < rating)
          {
            rating=newrating;
            lastorientation=orientation;
            lastx=x;
          }
          
          bSuccessFulDrop = TRUE;
        }
        else
        {
  //        printf("Orientation: %d/%d, block %c, drop-heigh: %d, x: %d\r\n",orientation,pBlock->nOrientations,(char)pBlock->id,y,x);
          /* NO, so if we can't rotate at this height, we can't rotate the block to 
              next orientation niether. Break out of loop */
      //    break;
        }
      }
    }
  }
  
  if(!bSuccessFulDrop)
    return FALSE;
  
  if(aiDrop(pGrid,&gridTarget, pBlock, lastx, 0, lastorientation))
    return FALSE;
   
  newrating = aiRate(&gridTarget,pInd);
  
  g_bLog=FALSE;
  
  if(px && porientation)
  {
    *px=lastx;
    *porientation=lastorientation;
  }
    
  return TRUE;
}
