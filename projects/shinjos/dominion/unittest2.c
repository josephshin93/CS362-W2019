/******************************************************************************
 *       Author: Joseph Shin
 * Date Created: 2019 Feb 08
 *  Description: Template for dominion code unit testing.
 *****************************************************************************/

#include "dominion.h"
#include "domtest_helpers.h"
#include <stdio.h>
#include <string.h>


/* Scenario A: Normal Scenario
   2 players
   no outpost has been played
   no embargo tokens

   current player = 0
   phase = 2 = clean up phase?
   no actions left
   no buys left
   1 coin left
   current player hand: copper, estate
   current player deck: copper, copper, estate, silver, copper <- top
   current player discard: silver
   (current player) played: copper, copper, copper

    next player = 1
    next player hand: copper, copper, copper, copper, estate
    next player deck is empty
    next player discard: copper, copper, silver, estate
 */
void testScenarioA(struct gameState *resl, 
                   struct gameState *expc, 
                   struct gscomp *comp) {
    int compres;
    int ret, expRet = 0;
    
    // reset game states and game state comparisons
    memset(resl, 0, sizeof(struct gameState));
    memset(comp, 0, sizeof(struct gscomp));

    // declare scenario variables
    int currplayer = 0, nextplayer = 1;
    
    // set up scenario initial game state
    resl->numPlayers = 2;
    resl->whoseTurn = currplayer;
    resl->phase = 2;
    resl->numActions = 0;
    resl->coins = 1;
    resl->numBuys = 0;
    resl->hand[currplayer][0] = copper;
    resl->hand[currplayer][1] = estate;
    resl->handCount[currplayer] = 2;
    resl->deck[currplayer][0] = copper;
    resl->deck[currplayer][1] = copper;
    resl->deck[currplayer][2] = estate;
    resl->deck[currplayer][3] = silver;
    resl->deck[currplayer][4] = copper;
    resl->deckCount[currplayer] = 5;
    resl->discard[currplayer][0] = silver;
    resl->discardCount[currplayer] = 1;
    resl->playedCards[0] = copper;
    resl->playedCards[1] = copper;
    resl->playedCards[2] = copper;
    resl->playedCardCount = 3;
    // next player
    resl->hand[nextplayer][0] = copper;
    resl->hand[nextplayer][1] = copper;
    resl->hand[nextplayer][2] = copper;
    resl->hand[nextplayer][3] = copper;
    resl->hand[nextplayer][4] = estate;
    resl->handCount[nextplayer] = 5;
    resl->discard[nextplayer][0] = copper;
    resl->discard[nextplayer][1] = copper;
    resl->discard[nextplayer][2] = silver;
    resl->discard[nextplayer][3] = estate;
    resl->discardCount[nextplayer] = 4;


    memcpy(expc, resl, sizeof(struct gameState));

    // manually set scenario expected game state
    expc->whoseTurn = nextplayer;
    expc->phase = 0;
    expc->numActions = 1;
    expc->coins = 0;
    expc->numBuys = 1;
    expc->hand[currplayer][0] = copper;
    expc->hand[currplayer][1] = silver;
    expc->hand[currplayer][2] = estate;
    expc->hand[currplayer][3] = silver;
    expc->hand[currplayer][4] = copper;
    expc->handCount[currplayer] = 5;
    expc->deckCount[currplayer] = 0;
    expc->discard[currplayer][0] = silver;
    expc->discard[currplayer][1] = copper;
    expc->discard[currplayer][2] = copper;
    expc->discard[currplayer][3] = copper;
    expc->discard[currplayer][4] = curse;
    expc->discard[currplayer][5] = estate;
    expc->discardCount[currplayer] = 6;
    expc->playedCardCount = 0;
    

    // call target function
    ret = endTurn(resl);


    printf("---------------------------------- Scenario A ----------------------------------\n");

    // compare return values
    printf("Return Value: ");
    if (ret == expRet) printf("%sCORRECT%s\n", CGRN, CNRM);
    else printf("%sWRONG%s\n", CRED, CNRM);
    
    // compare game states
    compareStates(expc, resl, 1, 10);

    // compres = compareStatesAndSave(resl, resl, comp);
    // printf("compare game state return value: %d\n", compres);
    // printGscomp(comp);


    // interpret comparison(?)

    printf("--------------------------------------------------------------------------------\n");
}

/* Scenario B: Outpost Scenario
   2 players
   outpost has been played
   outpost turn = false = 0
   no embargo tokens

   current player = 0
   phase = 2 = clean up phase?
   no actions left
   no buys left
   1 coin left
   current player hand: copper, estate
   current player deck: copper, copper, estate, silver, copper <- top
   current player discard: silver
   (current player) played: copper, copper, outpost

    next player = 1
    next player hand: copper, copper, copper, copper, estate
    next player deck is empty
    next player discard: copper, copper, silver, estate
 */
void testScenarioB(struct gameState *resl, 
                   struct gameState *expc, 
                   struct gscomp *comp) {
    int compres;
    int ret, expRet = 0;
    
    // reset game states and game state comparisons
    memset(resl, 0, sizeof(struct gameState));
    memset(comp, 0, sizeof(struct gscomp));

    // declare scenario variables
    int currplayer = 0, nextplayer = 1;
    
    // set up scenario initial game state
    resl->numPlayers = 2;
    resl->outpostPlayed = 1;
    resl->outpostTurn = 0;
    resl->whoseTurn = currplayer;
    resl->phase = 2;
    resl->numActions = 0;
    resl->coins = 1;
    resl->numBuys = 0;
    resl->hand[currplayer][0] = estate;
    resl->handCount[currplayer] = 1;
    resl->deck[currplayer][0] = copper;
    resl->deck[currplayer][1] = copper;
    resl->deck[currplayer][2] = estate;
    resl->deck[currplayer][3] = silver;
    resl->deck[currplayer][4] = copper;
    resl->deckCount[currplayer] = 5;
    resl->discard[currplayer][0] = silver;
    resl->discardCount[currplayer] = 1;
    resl->playedCards[0] = copper;
    resl->playedCards[1] = copper;
    resl->playedCards[2] = copper;
    resl->playedCards[3] = outpost;
    resl->playedCardCount = 4;
    // next player
    resl->hand[nextplayer][0] = copper;
    resl->hand[nextplayer][1] = copper;
    resl->hand[nextplayer][2] = copper;
    resl->hand[nextplayer][3] = copper;
    resl->hand[nextplayer][4] = estate;
    resl->handCount[nextplayer] = 5;
    resl->discard[nextplayer][0] = copper;
    resl->discard[nextplayer][1] = copper;
    resl->discard[nextplayer][2] = silver;
    resl->discard[nextplayer][3] = estate;
    resl->discardCount[nextplayer] = 4;


    memcpy(expc, resl, sizeof(struct gameState));

    // manually set scenario expected game state
    expc->outpostTurn = 1;
    expc->phase = 0;
    expc->numActions = 1;
    expc->coins = 0;
    expc->numBuys = 1;
    expc->hand[currplayer][0] = copper;
    expc->hand[currplayer][1] = silver;
    expc->hand[currplayer][2] = estate;
    expc->handCount[currplayer] = 3;
    expc->deck[currplayer][0] = copper;
    expc->deck[currplayer][1] = copper;
    expc->deck[currplayer][2] = estate;
    expc->deck[currplayer][3] = silver;
    expc->deck[currplayer][4] = copper;
    expc->deckCount[currplayer] = 5;
    expc->discard[currplayer][0] = silver;
    expc->discard[currplayer][1] = outpost;
    expc->discard[currplayer][2] = copper;
    expc->discard[currplayer][3] = copper;
    expc->discard[currplayer][4] = copper;
    expc->discard[currplayer][5] = estate;
    expc->discardCount[currplayer] = 6;
    expc->playedCardCount = 0;
    

    // call target function
    ret = endTurn(resl);


    printf("---------------------------------- Scenario B ----------------------------------\n");

    // compare return values
    printf("Return Value: ");
    if (ret == expRet) printf("%sCORRECT%s\n", CGRN, CNRM);
    else printf("%sWRONG%s\n", CRED, CNRM);
    
    // compare game states
    compareStates(expc, resl, 1, 10);

    // compres = compareStatesAndSave(resl, resl, comp);
    // printf("compare game state return value: %d\n", compres);
    // printGscomp(comp);


    // interpret comparison(?)

    printf("--------------------------------------------------------------------------------\n");
}

/* Scenario C: Shuffle Scenario
   2 players
   no outpost has been played
   no embargo tokens

   current player = 0
   phase = 2 = clean up phase?
   no actions left
   no buys left
   1 coin left
   current player hand: copper, estate
   current player deck: copper, copper, estate, silver <- top
   current player discard: silver
   (current player) played: copper, copper, copper

    next player = 1
    next player hand: copper, copper, copper, copper, estate
    next player deck is empty
    next player discard: copper, copper, silver, estate
 */
void testScenarioC(struct gameState *resl, 
                   struct gameState *expc, 
                   struct gscomp *comp) {
    int compres;
    int ret, expRet = 0;
    
    // reset game states and game state comparisons
    memset(resl, 0, sizeof(struct gameState));
    memset(comp, 0, sizeof(struct gscomp));

    // declare scenario variables
    int currplayer = 0, nextplayer = 1;
    
    // set up scenario initial game state
    resl->numPlayers = 2;
    resl->whoseTurn = currplayer;
    resl->phase = 2;
    resl->numActions = 0;
    resl->coins = 1;
    resl->numBuys = 0;
    resl->hand[currplayer][0] = copper;
    resl->hand[currplayer][1] = estate;
    resl->handCount[currplayer] = 2;
    resl->deck[currplayer][0] = copper;
    resl->deck[currplayer][1] = copper;
    resl->deck[currplayer][2] = estate;
    resl->deck[currplayer][3] = silver;
    resl->deckCount[currplayer] = 4;
    resl->discard[currplayer][0] = silver;
    resl->discardCount[currplayer] = 1;
    resl->playedCards[0] = copper;
    resl->playedCards[1] = copper;
    resl->playedCards[2] = copper;
    resl->playedCardCount = 3;
    // next player
    resl->hand[nextplayer][0] = copper;
    resl->hand[nextplayer][1] = copper;
    resl->hand[nextplayer][2] = copper;
    resl->hand[nextplayer][3] = copper;
    resl->hand[nextplayer][4] = estate;
    resl->handCount[nextplayer] = 5;
    resl->discard[nextplayer][0] = copper;
    resl->discard[nextplayer][1] = copper;
    resl->discard[nextplayer][2] = silver;
    resl->discard[nextplayer][3] = estate;
    resl->discardCount[nextplayer] = 4;


    memcpy(expc, resl, sizeof(struct gameState));

    // manually set scenario expected game state
    expc->whoseTurn = nextplayer;
    expc->phase = 0;
    expc->numActions = 1;
    expc->coins = 0;
    expc->numBuys = 1;
    expc->hand[currplayer][0] = silver;
    expc->hand[currplayer][1] = estate;
    expc->hand[currplayer][2] = silver;
    expc->hand[currplayer][3] = copper;
    expc->hand[currplayer][4] = copper;
    expc->handCount[currplayer] = 5;
    expc->deck[currplayer][0] = silver;
    expc->deck[currplayer][1] = copper;
    expc->deck[currplayer][2] = copper;
    expc->deck[currplayer][3] = copper;
    expc->deck[currplayer][4] = estate;
    expc->deckCount[currplayer] = 5;
    expc->discardCount[currplayer] = 0;
    expc->playedCardCount = 0;
    

    // call target function
    ret = endTurn(resl);


    printf("---------------------------------- Scenario C ----------------------------------\n");

    // compare return values
    printf("Return Value: ");
    if (ret == expRet) printf("%sCORRECT%s\n", CGRN, CNRM);
    else printf("%sWRONG%s\n", CRED, CNRM);
    
    // compare game states
    compareStates(expc, resl, 1, 10);

    // compres = compareStatesAndSave(resl, resl, comp);
    // printf("compare game state return value: %d\n", compres);
    // printGscomp(comp);


    // interpret comparison(?)

    printf("--------------------------------------------------------------------------------\n");
}


void unitTest2() {
    // declare game states and game state comparison
    struct gameState expected, resulting;
    struct gscomp comp;

    printf("================================= UNIT TEST 2 ==================================\n");
    printf("target function: int endTurn(struct gameState *state)\n");

    testScenarioA(&expected, &resulting, &comp);
    testScenarioB(&expected, &resulting, &comp);
    testScenarioC(&expected, &resulting, &comp);

    printf("================================================================================\n");
}


int main() {
    unitTest2();
    return 0;
}