/******************************************************************************
 *       Author: Joseph Shin
 * Date Created: 2019 Feb 06
 *  Description: Template for dominion code unit testing.
 *****************************************************************************/

#include "dominion.h"
#include "domtest_helpers.h"
#include <stdio.h>
#include <string.h>


void testScenarioA(struct gameState *expc, 
                   struct gameState *resl, 
                   struct gscomp *comp) {
    int compres;
    
    // reset game states and game state comparisons
    memset(expc, 0, sizeof(struct gameState));
    memset(resl, 0, sizeof(struct gameState));
    memset(comp, 0, sizeof(struct gscomp));

    // declare scenario 1 variables
    int targetcard = 3, currplayer = 1;
    
    // set up scenario 1 initial game state
    resl->numPlayers = 2;
    resl->whoseTurn = currplayer;
    resl->phase = 1;
    resl->supplyCount[targetcard] = 5;
    resl->coins = 8;
    resl->numBuys = 1;

    memcpy(expc, resl, sizeof(struct gameState));

    // manually(?) set scenario 1 expected game state
    expc->supplyCount[targetcard]--;
    expc->coins -= 8;
    expc->numBuys--;
    expc->phase++;
    expc->discard[currplayer][expc->discardCount[currplayer]++] = province;

    // call target function
    buyCard(targetcard, resl);

    // compare game states
    compareStates(expc, resl, 0, 0);

    // compres = compareStatesAndSave(expc, resl, comp);
    // printf("compare game state return value: %d\n", compres);
    // printGscomp(comp);


    // interpret comparison(?)

}


void unitTest1() {
    // declare game states and game state comparison
    struct gameState expected, resulting;
    struct gscomp comp;

    testScenarioA(&expected, &resulting, &comp);

}

int main() {
    unitTest1();
    return 0;
}