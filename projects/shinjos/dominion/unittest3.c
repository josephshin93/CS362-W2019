/******************************************************************************
 *       Author: Joseph Shin
 * Date Created: 2019 Feb 10
 *  Description: Template for dominion code unit testing.
 *****************************************************************************/

#include "dominion.h"
#include "domtest_helpers.h"
#include <stdio.h>
#include <string.h>


/* Scenario A: Normal Scenario
   target player = 1
   
   2 players
   target player hand = copper, estate, copper
   target player deck = province, copper
   target player discard = duchy, curse, copper
 */
void testScenarioA(struct gameState *expc, 
                   struct gameState *resl, 
                   struct gscomp *comp) {
    int compres;
    int ret, expRet = 9;
    
    // reset game states and game state comparisons
    memset(expc, 0, sizeof(struct gameState));
    memset(resl, 0, sizeof(struct gameState));
    memset(comp, 0, sizeof(struct gscomp));

    // declare scenario variables
    int targetplayer = 1;
    
    // set up scenario initial game state
    resl->numPlayers = 2;
    resl->hand[targetplayer][0] = copper;
    resl->hand[targetplayer][1] = estate;
    resl->hand[targetplayer][2] = copper;
    resl->handCount[targetplayer] = 3;
    resl->deck[targetplayer][0] = province;
    resl->deck[targetplayer][1] = copper;
    resl->deckCount[targetplayer] = 2;
    resl->discard[targetplayer][0] = duchy;
    resl->discard[targetplayer][1] = curse;
    resl->discard[targetplayer][2] = copper;
    resl->discardCount[targetplayer] = 3;


    memcpy(expc, resl, sizeof(struct gameState));

    // manually set scenario expected game state
    // no state change

    
    // call target function
    ret = scoreFor(targetplayer, resl);


    printf("---------------------------------- Scenario A ----------------------------------\n");

    // compare return values
    printf("Return Value: ");
    compres = (expRet > ret) - (expRet < ret);
    if (compres == 0) printf("%sCORRECT%s\n", CGRN, CNRM);
    else printf("%sWRONG%s   expected(%d) %c resulting(%d)\n", CRED, CNRM, expRet, (char)('='+compres), ret);
    
    // compare game states
    compareStates(expc, resl, 0, 0);

    // compres = compareStatesAndSave(expc, resl, comp);
    // printf("compare game state return value: %d\n", compres);
    // printGscomp(comp);


    // interpret comparison(?)

    printf("--------------------------------------------------------------------------------\n");
}

/* Scenario B: Bad Player Input Scenario
   target player = 3
   
   2 players
   player [1] hand = copper, estate, copper
   player [1] deck = province, copper
   player [1] discard = duchy, curse, copper
 */
void testScenarioB(struct gameState *expc, 
                   struct gameState *resl, 
                   struct gscomp *comp) {
    int compres;
    int ret, expRet = -9999;
    
    // reset game states and game state comparisons
    memset(expc, 0, sizeof(struct gameState));
    memset(resl, 0, sizeof(struct gameState));
    memset(comp, 0, sizeof(struct gscomp));

    // declare scenario variables
    int targetplayer = 3, lastplayer = 1;
    
    // set up scenario initial game state
    resl->numPlayers = 2;
    resl->hand[lastplayer][0] = copper;
    resl->hand[lastplayer][1] = estate;
    resl->hand[lastplayer][2] = copper;
    resl->handCount[lastplayer] = 3;
    resl->deck[lastplayer][0] = province;
    resl->deck[lastplayer][1] = copper;
    resl->deckCount[lastplayer] = 2;
    resl->discard[lastplayer][0] = duchy;
    resl->discard[lastplayer][1] = curse;
    resl->discard[lastplayer][2] = copper;
    resl->discardCount[lastplayer] = 3;


    memcpy(expc, resl, sizeof(struct gameState));

    // manually set scenario expected game state
    // no state change

    
    // call target function
    ret = scoreFor(targetplayer, resl);


    printf("---------------------------------- Scenario B ----------------------------------\n");

    // compare return values
    printf("Return Value: ");
    compres = (expRet > ret) - (expRet < ret);
    if (compres == 0) printf("%sCORRECT%s\n", CGRN, CNRM);
    else printf("%sWRONG%s   expected(%d) %c resulting(%d)\n", CRED, CNRM, expRet, (char)('='+compres), ret);
    
    // compare game states
    compareStates(expc, resl, 0, 0);

    // compres = compareStatesAndSave(expc, resl, comp);
    // printf("compare game state return value: %d\n", compres);
    // printGscomp(comp);


    // interpret comparison(?)

    printf("--------------------------------------------------------------------------------\n");
}


void unitTest3() {
    // declare game states and game state comparison
    struct gameState expected, resulting;
    struct gscomp comp;

    printf("================================= UNIT TEST 3 ==================================\n");
    printf("target function: \n");

    testScenarioA(&expected, &resulting, &comp);
    testScenarioB(&expected, &resulting, &comp);

    printf("================================================================================\n");
}


int main() {
    unitTest3();
    return 0;
}