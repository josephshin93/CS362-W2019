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
 */
void testScenarioX(struct gameState *expc, 
                   struct gameState *resl, 
                   struct gscomp *comp) {
    int compres;
    int ret, expRet = 0;
    
    // reset game states and game state comparisons
    memset(expc, 0, sizeof(struct gameState));
    memset(resl, 0, sizeof(struct gameState));
    memset(comp, 0, sizeof(struct gscomp));

    // declare scenario variables
    int targetcard = 6, currplayer = 1;
    
    // set up scenario initial game state

    memcpy(expc, resl, sizeof(struct gameState));

    // manually set scenario expected game state

    // call target function

    printf("---------------------------------- Scenario X ----------------------------------\n");

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


void unitTestX() {
    // declare game states and game state comparison
    struct gameState expected, resulting;
    struct gscomp comp;

    printf("================================= UNIT TEST X ==================================\n");
    printf("target function: \n");

    testScenarioX(&expected, &resulting, &comp);

    printf("================================================================================\n");
}


int main() {
    unitTestX();
    return 0;
}