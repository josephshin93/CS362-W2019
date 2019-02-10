/******************************************************************************
 *       Author: Joseph Shin
 * Date Created: 2019 Feb 06
 *  Description: Template for dominion code unit testing.
 *****************************************************************************/

#include "dominion.h"
#include "domtest_helpers.h"
#include <stdio.h>
#include <string.h>


/* Scenario A: Normal Scenario
   targetcard = 6 = gold

   2 players
   current player = 1
   phase = 1
   supply of gold = 30
   coins = 6
   buys = 1
   all others = 0
 */
void testScenarioA(struct gameState *expc, 
                   struct gameState *resl, 
                   struct gscomp *comp) {
    int compres;
    int ret, expRet = 0;
    
    // reset game states and game state comparisons
    memset(expc, 0, sizeof(struct gameState));
    memset(resl, 0, sizeof(struct gameState));
    memset(comp, 0, sizeof(struct gscomp));

    // declare scenario variables
    int currplayer = 1;
    
    // set up scenario initial game state
    resl->numPlayers = 2;
    resl->whoseTurn = currplayer;
    resl->phase = 1;
    resl->supplyCount[gold] = 30;
    resl->coins = 6;
    resl->numBuys = 1;

    memcpy(expc, resl, sizeof(struct gameState));

    // manually set scenario expected game state
    expc->supplyCount[gold]--;
    expc->coins -= 6;
    expc->numBuys--;
    expc->discard[currplayer][expc->discardCount[currplayer]++] = gold;

    // call target function
    ret = buyCard(gold, resl);

    printf("---------------------------------- Scenario A ----------------------------------\n");

    // compare return values
    printf("Return Value: ");
    if (ret == expRet) printf("%sCORRECT%s\n", CGRN, CNRM);
    else printf("%sWRONG%s\n", CRED, CNRM);
    
    // compare game states
    compareStates(expc, resl, 0, 0);

    // compres = compareStatesAndSave(expc, resl, comp);
    // printf("compare game state return value: %d\n", compres);
    // printGscomp(comp);


    // interpret comparison(?)

    printf("--------------------------------------------------------------------------------\n");
}

/* Scenario B: Embargo Scenario
   targetcard = 6 = gold

   2 players
   current player = 1
   phase = 1
   supply of gold = 30
   supply of curse = 10
   coins = 6
   buys = 1
   all others = 0
 */
void testScenarioB(struct gameState *expc, 
                   struct gameState *resl, 
                   struct gscomp *comp) {
    int compres;
    int ret, expRet = 0;
    
    // reset game states and game state comparisons
    memset(expc, 0, sizeof(struct gameState));
    memset(resl, 0, sizeof(struct gameState));
    memset(comp, 0, sizeof(struct gscomp));

    // declare scenario variables
    int currplayer = 1;
    
    // set up scenario initial game state
    resl->numPlayers = 2;
    resl->whoseTurn = currplayer;
    resl->phase = 1;
    resl->supplyCount[gold] = 30;
    resl->supplyCount[curse] = 10;
    resl->embargoTokens[gold] = 1;
    resl->coins = 6;
    resl->numBuys = 1;

    memcpy(expc, resl, sizeof(struct gameState));

    // manually set scenario expected game state
    expc->supplyCount[gold]--;
    expc->supplyCount[curse]--;
    expc->coins -= 6;
    expc->numBuys--;
    expc->discard[currplayer][expc->discardCount[currplayer]++] = gold;
    expc->discard[currplayer][expc->discardCount[currplayer]++] = curse;

    // call target function
    ret = buyCard(gold, resl);

    printf("---------------------------------- Scenario B ----------------------------------\n");

    // compare return values
    printf("Return Value: ");
    if (ret == expRet) printf("%sCORRECT%s\n", CGRN, CNRM);
    else printf("%sWRONG%s\n", CRED, CNRM);
    
    // compare game states
    compareStates(expc, resl, 1, 7);

    // compres = compareStatesAndSave(expc, resl, comp);
    // printf("compare game state return value: %d\n", compres);
    // printGscomp(comp);


    // interpret comparison(?)

    printf("--------------------------------------------------------------------------------\n");
}

/* Scenario C: No Coins Scenario
   targetcard = 6 = gold

   2 players
   current player = 1
   phase = 1
   supply of gold = 30
   coins = 0
   buys = 1
 */
void testScenarioC(struct gameState *expc, 
                   struct gameState *resl, 
                   struct gscomp *comp) {
    int compres;
    int ret, expRet = -1;
    
    // reset game states and game state comparisons
    memset(expc, 0, sizeof(struct gameState));
    memset(resl, 0, sizeof(struct gameState));
    memset(comp, 0, sizeof(struct gscomp));

    // declare scenario variables
    int currplayer = 1;
    
    // set up scenario initial game state
    resl->numPlayers = 2;
    resl->whoseTurn = currplayer;
    resl->phase = 1;
    resl->supplyCount[gold] = 30;
    resl->coins = 0;
    resl->numBuys = 1;

    memcpy(expc, resl, sizeof(struct gameState));

    // manually set scenario expected game state
    // no change

    // call target function
    ret = buyCard(gold, resl);

    printf("---------------------------------- Scenario C ----------------------------------\n");

    // compare return values
    printf("Return Value: ");
    if (ret == expRet) printf("%sCORRECT%s\n", CGRN, CNRM);
    else printf("%sWRONG%s\n", CRED, CNRM);
    
    // compare game states
    compareStates(expc, resl, 0, 0);

    // compres = compareStatesAndSave(expc, resl, comp);
    // printf("compare game state return value: %d\n", compres);
    // printGscomp(comp);


    // interpret comparison(?)

    printf("--------------------------------------------------------------------------------\n");
}

/* Scenario D: Wrong Phase Scenario
   targetcard = 6 = gold

   2 players
   current player = 1
   phase = 0
   supply of gold = 30
   coins = 6
   buys = 1
 */
void testScenarioD(struct gameState *expc, 
                   struct gameState *resl, 
                   struct gscomp *comp) {
    int compres;
    int ret, expRet = -1;
    
    // reset game states and game state comparisons
    memset(expc, 0, sizeof(struct gameState));
    memset(resl, 0, sizeof(struct gameState));
    memset(comp, 0, sizeof(struct gscomp));

    // declare scenario variables
    int currplayer = 1;
    
    // set up scenario initial game state
    resl->numPlayers = 2;
    resl->whoseTurn = currplayer;
    resl->phase = 0;
    resl->supplyCount[gold] = 30;
    resl->coins = 6;
    resl->numBuys = 1;

    memcpy(expc, resl, sizeof(struct gameState));

    // manually set scenario expected game state
    // no change

    // call target function
    ret = buyCard(gold, resl);

    printf("---------------------------------- Scenario D ----------------------------------\n");

    // compare return values
    printf("Return Value: ");
    if (ret == expRet) printf("%sCORRECT%s\n", CGRN, CNRM);
    else printf("%sWRONG%s\n", CRED, CNRM);
    
    // compare game states
    compareStates(expc, resl, 0, 0);

    // compres = compareStatesAndSave(expc, resl, comp);
    // printf("compare game state return value: %d\n", compres);
    // printGscomp(comp);


    // interpret comparison(?)

    printf("--------------------------------------------------------------------------------\n");
}

void unitTest1() {
    // declare game states and game state comparison
    struct gameState expected, resulting;
    struct gscomp comp;

    printf("================================= UNIT TEST 1 ==================================\n");
    printf("target function: int buyCard(int supplyPos, struct gameState *state)\n");

    testScenarioA(&expected, &resulting, &comp);
    testScenarioB(&expected, &resulting, &comp);
    // testScenarioC(&expected, &resulting, &comp);
    // testScenarioD(&expected, &resulting, &comp);

    printf("================================================================================\n");
}


int main() {
    unitTest1();
    return 0;
}