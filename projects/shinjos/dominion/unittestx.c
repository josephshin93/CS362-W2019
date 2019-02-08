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
    
    // set up scenario 1 initial game state

    memcpy(expc, resl, sizeof(struct gameState));

    // manually(?) set scenario 1 expected game state

    // call target function

    // compare game states
    compareStates(expc, resl, 0, 0);

    // compres = compareStatesAndSave(expc, resl, comp);
    // printf("compare game state return value: %d\n", compres);
    // printGscomp(comp);


    // interpret comparison(?)

}


void unitTestX() {
    // declare game states and game state comparison
    struct gameState expected, resulting;
    struct gscomp comp;

    testScenarioA(&expected, &resulting, &comp);

}

int main() {
    unitTestX();
    return 0;
}