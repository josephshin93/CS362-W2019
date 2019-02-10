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
   target card = copper

   2 players
   target player hand = copper, silver, gold, copper
   target player deck = copper, copper, copper, estate, province
   target player discard = estate, estate, curse, copper
 */
void testScenarioA(struct gameState *expc, 
                   struct gameState *resl, 
                   struct gscomp *comp) {
    int compres;
    int ret, expRet = 6;
    
    // reset game states and game state comparisons
    memset(expc, 0, sizeof(struct gameState));
    memset(resl, 0, sizeof(struct gameState));
    memset(comp, 0, sizeof(struct gscomp));

    // declare scenario variables
    int targetplayer = 1;
    
    // set up scenario initial game state
    resl->numPlayers = 2;
    resl->hand[targetplayer][0] = copper;
    resl->hand[targetplayer][1] = silver;
    resl->hand[targetplayer][2] = gold;
    resl->hand[targetplayer][3] = copper;
    resl->handCount[targetplayer] = 4;
    resl->deck[targetplayer][0] = copper;
    resl->deck[targetplayer][1] = copper;
    resl->deck[targetplayer][2] = copper;
    resl->deck[targetplayer][3] = estate;
    resl->deck[targetplayer][4] = province;
    resl->deckCount[targetplayer] = 5;
    resl->discard[targetplayer][0] = estate;
    resl->discard[targetplayer][1] = estate;
    resl->discard[targetplayer][2] = curse;
    resl->discard[targetplayer][3] = copper;
    resl->discardCount[targetplayer] = 4;

    memcpy(expc, resl, sizeof(struct gameState));

    // manually set scenario expected game state
    // no state change

    
    // call target function
    ret = fullDeckCount(targetplayer, copper, resl);


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


void unitTest4() {
    // declare game states and game state comparison
    struct gameState expected, resulting;
    struct gscomp comp;

    printf("================================= UNIT TEST 4 ==================================\n");
    printf("target function: \n");

    testScenarioA(&expected, &resulting, &comp);

    printf("================================================================================\n");
}


int main() {
    unitTest4();
    return 0;
}