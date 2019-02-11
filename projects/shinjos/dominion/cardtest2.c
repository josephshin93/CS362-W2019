/******************************************************************************
 *       Author: Joseph Shin
 * Date Created: 2019 Feb 10
 *  Description: Unit test for smithy card.
 *               Smithy: 
 *                 "+3 Cards"[1]
 * 
 *               [1] From: http://wiki.dominionstrategy.com/index.php/List_of_cards
 *****************************************************************************/

#include "dominion.h"
#include "domtest_helpers.h"
#include <stdio.h>
#include <string.h>


/* Scenario A: Normal Scenario
   2 players
   empty suppy
   no embargo tokens
   no outpost played/turn
   current player = 0
   phase = action phase = 0
   1 action
   coins = 4 (copper, gold)
   1 buy
   current player hand = [smithy, copper, estate, gold, adventurer]
   current player deck = [duchy, curse, adventurer, silver(top)]
   current player discard = [estate]
   no played cards
   empty next player hand/deck/discard
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
    int currplayer = 0;
    
    // set up scenario initial game state
    resl->numPlayers = 2;
    resl->whoseTurn = currplayer;
    resl->phase = 0;
    resl->numActions = 1;
    resl->coins = 4; // copper, gold
    resl->numBuys = 1;
    resl->hand[currplayer][0] = smithy;
    resl->hand[currplayer][1] = copper;
    resl->hand[currplayer][2] = estate;
    resl->hand[currplayer][3] = gold;
    resl->hand[currplayer][4] = adventurer;
    resl->handCount[currplayer] = 5;
    resl->deck[currplayer][0] = duchy;
    resl->deck[currplayer][1] = curse;
    resl->deck[currplayer][2] = adventurer;
    resl->deck[currplayer][3] = silver; // top
    resl->deckCount[currplayer] = 4;
    resl->discard[currplayer][0] = estate;
    resl->discardCount[currplayer] = 1;

    memcpy(expc, resl, sizeof(struct gameState));

    // manually set scenario expected game state
    expc->phase = 0; // not sure if this should change with playing a card
    expc->numActions--;
    expc->coins += 2; // + silver
    expc->hand[currplayer][5] = silver;
    expc->hand[currplayer][6] = adventurer;
    expc->hand[currplayer][7] = curse;
    expc->handCount[currplayer] += 2;
    expc->deck[currplayer][3] = -1;
    expc->deck[currplayer][2] = -1;
    expc->deck[currplayer][1] = -1;
    expc->deckCount[currplayer] -= 3;
    expc->playedCards[0] = smithy;
    expc->playedCardCount++;


    // call target function
    ret = playCard(0, 0, 0, 0, resl);


    printf("---------------------------------- Scenario A ----------------------------------\n");

    // compare return values
    printf("Return Value: ");
    compres = (expRet > ret) - (expRet < ret);
    if (compres == 0) printf("%sCORRECT%s\n", CGRN, CNRM);
    else printf("%sWRONG%s   expected(%d) %c resulting(%d)\n", CRED, CNRM, expRet, (char)('='+compres), ret);
    
    // compare game states
    compareStates(expc, resl, 1, 8);

    // compres = compareStatesAndSave(expc, resl, comp);
    // printf("compare game state return value: %d\n", compres);
    // printGscomp(comp);


    // interpret comparison(?)

    printf("--------------------------------------------------------------------------------\n");
}

/* Scenario B: Shuffle Scenario
   2 players
   empty suppy
   no embargo tokens
   no outpost played/turn
   current player = 0
   phase = action phase = 0
   1 action
   coins = 4 (copper, gold)
   1 buy
   current player hand = [smithy, copper, estate, gold, adventurer]
   current player deck = [duchy, silver(top)]
   current player discard = [estate, estate]
   no played cards
   empty next player hand/deck/discard
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
    int currplayer = 0;
    
    // set up scenario initial game state
    resl->numPlayers = 2;
    resl->whoseTurn = currplayer;
    resl->phase = 0;
    resl->numActions = 1;
    resl->coins = 4; // copper, gold
    resl->numBuys = 1;
    resl->hand[currplayer][0] = smithy;
    resl->hand[currplayer][1] = copper;
    resl->hand[currplayer][2] = estate;
    resl->hand[currplayer][3] = gold;
    resl->hand[currplayer][4] = adventurer;
    resl->handCount[currplayer] = 5;
    resl->deck[currplayer][0] = duchy;
    resl->deck[currplayer][1] = silver; // top
    resl->deckCount[currplayer] = 2;
    resl->discard[currplayer][0] = estate;
    resl->discard[currplayer][1] = estate;
    resl->discardCount[currplayer] = 2;

    memcpy(expc, resl, sizeof(struct gameState));

    // manually set scenario expected game state
    expc->phase = 0; // not sure if this should change with playing a card
    expc->numActions--;
    expc->coins += 2; // + silver
    expc->hand[currplayer][5] = silver;
    expc->hand[currplayer][6] = adventurer;
    expc->hand[currplayer][7] = estate;
    expc->handCount[currplayer] += 2;
    expc->deck[currplayer][1] = -1; // remove 2 for draw, add 2 from shuffle, remove 1 for draw
    expc->deck[currplayer][0] = estate;
    expc->deckCount[currplayer] -= 1;
    expc->discard[currplayer][0] = -1; 
    expc->discard[currplayer][1] = -1;
    expc->discardCount[currplayer] -= 2; 
    expc->playedCards[0] = smithy;
    expc->playedCardCount++;


    // call target function
    ret = playCard(0, 0, 0, 0, resl);


    printf("---------------------------------- Scenario B ----------------------------------\n");

    // compare return values
    printf("Return Value: ");
    compres = (expRet > ret) - (expRet < ret);
    if (compres == 0) printf("%sCORRECT%s\n", CGRN, CNRM);
    else printf("%sWRONG%s   expected(%d) %c resulting(%d)\n", CRED, CNRM, expRet, (char)('='+compres), ret);
    
    // compare game states
    compareStates(expc, resl, 1, 8);

    // compres = compareStatesAndSave(expc, resl, comp);
    // printf("compare game state return value: %d\n", compres);
    // printGscomp(comp);


    // interpret comparison(?)

    printf("--------------------------------------------------------------------------------\n");
}

void cardTest2() {
    // declare game states and game state comparison
    struct gameState expected, resulting;
    struct gscomp comp;

    printf("================================= CARD TEST 2 ==================================\n");
    printf("target card:     Smithy\n");
    printf("target function: int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)\n");

    testScenarioA(&expected, &resulting, &comp);
    testScenarioB(&expected, &resulting, &comp);

    printf("================================================================================\n");
}


int main() {
    cardTest2();
    return 0;
}