/******************************************************************************
 *       Author: Joseph Shin
 * Date Created: 2019 Feb 06
 *  Description: Template for dominion code unit testing.
 *****************************************************************************/

#include "dominion.h"
#include "domtest_helpers.h"
#include <stdio.h>
#include <string.h>


/* Normal Scenario
   targetcard = 6 = gold

   2 players
   current player = 1
   phase = 1
   supply of target card = 5
   coins = 6
   buys = 1
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

    // declare scenario A variables
    int targetcard = 6, currplayer = 1;
    
    // set up scenario A initial game state
    resl->numPlayers = 2;
    resl->whoseTurn = currplayer;
    resl->phase = 1;
    resl->supplyCount[targetcard] = 5;
    resl->coins = 6;
    resl->numBuys = 1;

    memcpy(expc, resl, sizeof(struct gameState));

    // manually(?) set scenario A expected game state
    expc->supplyCount[targetcard]--;
    expc->coins -= 6;
    expc->numBuys--;
    expc->discard[currplayer][expc->discardCount[currplayer]++] = gold;

    // call target function
    ret = buyCard(targetcard, resl);

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

/* No Supply Scenario
   targetcard = 6 = gold

   2 players
   current player = 1
   phase = 1
   supply of target card = 0
   coins = 6
   buys = 1
 */
void testScenarioB(struct gameState *expc, 
                   struct gameState *resl, 
                   struct gscomp *comp) {
    int compres;
    int ret, expRet = -1;
    
    // reset game states and game state comparisons
    memset(expc, 0, sizeof(struct gameState));
    memset(resl, 0, sizeof(struct gameState));
    memset(comp, 0, sizeof(struct gscomp));

    // declare scenario B variables
    int targetcard = 6, currplayer = 1;
    
    // set up scenario B initial game state
    resl->numPlayers = 2;
    resl->whoseTurn = currplayer;
    resl->phase = 1;
    resl->supplyCount[targetcard] = 0;
    resl->coins = 6;
    resl->numBuys = 1;

    memcpy(expc, resl, sizeof(struct gameState));

    // manually(?) set scenario B expected game state
    // no change

    // call target function
    ret = buyCard(targetcard, resl);

    printf("---------------------------------- Scenario B ----------------------------------\n");

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

/* No Coins Scenario
   targetcard = 6 = gold

   2 players
   current player = 1
   phase = 1
   supply of target card = 5
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
    int targetcard = 6, currplayer = 1;
    
    // set up scenario initial game state
    resl->numPlayers = 2;
    resl->whoseTurn = currplayer;
    resl->phase = 1;
    resl->supplyCount[targetcard] = 5;
    resl->coins = 0;
    resl->numBuys = 1;

    memcpy(expc, resl, sizeof(struct gameState));

    // manually(?) set scenario expected game state
    // no change

    // call target function
    ret = buyCard(targetcard, resl);

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

/* No Buys Scenario
   targetcard = 6 = gold

   2 players
   current player = 1
   phase = 1
   supply of target card = 5
   coins = 6
   buys = 0
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
    int targetcard = 6, currplayer = 1;
    
    // set up scenario initial game state
    resl->numPlayers = 2;
    resl->whoseTurn = currplayer;
    resl->phase = 1;
    resl->supplyCount[targetcard] = 5;
    resl->coins = 6;
    resl->numBuys = 0;

    memcpy(expc, resl, sizeof(struct gameState));

    // manually(?) set scenario expected game state
    // no change

    // call target function
    ret = buyCard(targetcard, resl);

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
    printf("target function: buyCard(int supplyPos, struct gameState *state\n");

    testScenarioA(&expected, &resulting, &comp);
    testScenarioB(&expected, &resulting, &comp);
    testScenarioC(&expected, &resulting, &comp);
    testScenarioD(&expected, &resulting, &comp);

    printf("================================================================================\n");
}


int main() {
    unitTest1();
    return 0;
}