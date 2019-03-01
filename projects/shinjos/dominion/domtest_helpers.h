/******************************************************************************
 *       Author: Joseph Shin
 * Date Created: 2019 Feb 06
 *  Description: Declarations of helper functions for testing the dominion 
 *               game code.
 *****************************************************************************/

#ifndef DOMINION_TEST_HELPER
#define DOMINION_TEST_HELPER

#include "dominion.h"


// struct to record deep comparison results of two game states
struct gscomp {
  int numPlayers; 
  int supplyCount[treasure_map+1];  
  int embargoTokens[treasure_map+1];
  int outpostPlayed;
  int outpostTurn;
  int whoseTurn;
  int phase;
  int numActions;
  int coins; 
  int numBuys; 
  int hand[MAX_PLAYERS][MAX_HAND];
  int handCount[MAX_PLAYERS];
  int deck[MAX_PLAYERS][MAX_DECK];
  int deckCount[MAX_PLAYERS];
  int discard[MAX_PLAYERS][MAX_DECK];
  int discardCount[MAX_PLAYERS];
  int playedCards[MAX_DECK];
  int playedCardCount;
};

struct range {
  int base;
  int width;
};

// color printing
// #define CNRM "\x1B[0m"
// #define CRED "\x1B[31m"
// #define CGRN "\x1B[32m"
#define CNRM ""
#define CRED ""
#define CGRN ""

#define ACTION_PHASE 0
#define BUY_PHASE    1
#define NUM_PHASES   3

#define COPPER_VALUE 1
#define SILVER_VALUE 2
#define GOLD_VALUE   3



int compareInts(const void* a, const void* b);

/*  Input: pointer to expected game state
 *         pointer to resulting game state
 * Output: integer reflecting deep comparison of two game states 
 * 
 * This function does a deep comparison of the two given game states.
 */
void compareStates(struct gameState *expc, struct gameState *resl, int ver, int apl);

int compareStatesAndSave(struct gameState *expc, 
                         struct gameState *resl, 
                         struct gscomp *comp);

void printGscomp(struct gscomp *comp);

int chanced(int percent);

int randomRangeVa(int base, int width);

int randomizeGameState(struct gameState *state);

void printGameState(struct gameState *state, int indent);

#endif
