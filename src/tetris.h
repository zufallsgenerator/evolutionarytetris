/*****************************************************************************
 Evolutionary Tetris AI (C) Christer Byström 2005
 Artificial Intelligence course project at Linköpings Universitet, fall 2005
 *****************************************************************************/

#ifndef __TETRIS_H__
#define __TETRIS_H__


/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/* This is where you change the configuration of the game */

#define GRID_X 10
#define GRID_Y 20

/*
#define GRID_X 6
#define GRID_Y 12
*/
#define TEST_ROUNDS 12
#define POOL_SIZE 100
#define ELITE_SELECTION 20
#define MAX_GENERATIONS 20

#define EXP_RATING FALSE
#define LINEAR_RATING TRUE
  

/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/


#define NWEIGHTS 21
#define DROP_X ((GRID_X/2)-2)


#ifndef WORD
#define DWORD unsigned long int
#define WORD unsigned short int
#define BOOL int
#endif

#define ASSERT(x) ((x ? : printf("Assertion failed in %s:%d\n",__FILE__,__LINE__)))

#ifndef TRUE 
  #define TRUE 1
  #define FALSE 0
#endif//TRUE

#ifndef NULL
#define NULL 0
#endif

#define BLOCK_SIZE 4

#define NUM_BLOCKS 4

#define countof(x) (sizeof(x) / sizeof(x[0]))   


typedef struct {
  int x;
  int y;
  int width;
  int height;
  char chPattern[BLOCK_SIZE][BLOCK_SIZE];
} BLOCKPART, *PBLOCKPART;

typedef struct {
  int nOrientations;
  int id;
  BLOCKPART Blocks[4];
} BLOCK, *PBLOCK;

typedef struct {
  char chGrid[GRID_Y][GRID_X];
  int nRemovedLines;
} GRID, *PGRID;


enum WEIGHT_TYPES 
{
  WTYPE_INTEGER=0,
  WTYPE_DOUBLE=1
};

typedef struct 
{
  int type;
  union
  {
    double d;
    int i;
  };
} WEIGHT;


typedef struct {
  int magic;
  WEIGHT w[NWEIGHTS]; /* Chromosone, consisting of weights as genes */
  int id;
  int nFitness;
  int nPrevFitness;
  int nMax;
  BOOL bCrossed;
  BOOL bMutated;
  int nLastPos;
  int nParent1;
  int nParent2;
  int selectionindex;
} IND, *PIND;

typedef struct {
  int generations;
  int eliteselection;
  int selectionmax;
  /*int poolsize;*/
  IND *pool[POOL_SIZE]; /* Pointers to individuals*/
  IND mem[POOL_SIZE]; /* Memory  */
} POPULATION, *PPOPULATION;

#define W_SET_I(x,y) (x).type = WTYPE_INTEGER ; (x).i = (y) ; 
#define W_SET_D(x,y) (x).type = WTYPE_DOUBLE ; (x).d = (y) ; 
//#define W_GET(x) ((x).type == WTYPE_INTEGER ? (x).i : (x).d)

#define W_GET(x) (x).d

//#define W_SET(x,y) if((y).type == WTYPE_INTEGER) { W_SET_I((x),(y).i) } else { W_SET_D((x),(y).d)) }
#define W_SET(x,y) if((y).type == WTYPE_INTEGER) { W_SET_I((x),(y).i); } else { W_SET_D((x),(y).d); }

extern char chGridShow[GRID_Y][GRID_X];

enum {
  KEY_NONE=0,
  KEY_LEFT,
  KEY_RIGHT,
  KEY_UP,
  KEY_DOWN,
  KEY_QUIT,
  KEY_C,
  KEY_PAUSE,
  KEY_GO
};

#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))

#define BLOCK_MARKER 100
#define BLOCK_MARKER2 101


int getkey(void);
void waitUpdate(void);
int videoUpdate(GRID *pGrid);
int videoUpdateOffset(GRID *pGrid, int offset);
BOOL blockPut(BLOCK *pWholeBlock, int xpos, int ypos, int orientation, BOOL bHighlight, GRID *pGrid);
BOOL blockTestPut(BLOCK *pWholeBlock, int xpos, int ypos, int orientation, GRID *pGrid);
int blockDrop(BLOCK *pBlock,int xpos,int ypos, int orientation);
void platformInit(void);
void platformQuit(void);
void blockInit(void);
void seed(int entrophy);

/* TETRIS ENVIRONMENT */

int gridClearAll(void);


/* AI */

int aiDrop(GRID *pGridSource, GRID *pGridTarget, BLOCK *pBlock, int xpos, int ypos, int orientation);
int aiRate(GRID *pGrid, IND *pGene);
BOOL aiDecide(GRID *pGrid,BLOCK *pBlock, int *px, int *porientation, IND *pGene);

/* IND */

void evolution(IND *pElite, int noindrations);
void indInit(IND *pGene);
int indTest(IND *pGene, int nMaxLevel);
void poolSort(IND *pool[]);
void popInit(POPULATION *ppop, BOOL bInitWeights);
void popSetSelectionIndex(POPULATION *ppop);
IND *popSelectInd(POPULATION *ppop);
int game(IND *pGene);
void gridPrint(GRID *pGrid);



/* MACROS */

#define qpow pow
#define GRID_COPY(t,s) (memcpy(t,s,sizeof(GRID)))
#define IND_COPY(t,s) (memcpy(t,s,sizeof(IND)))

#define PANIC(x) { printf("\nPanic at %s:%d: ",__FILE__,__LINE__); printf((x)); fflush(stdout); exit(-1); }

#endif//__TETRIS_H__
