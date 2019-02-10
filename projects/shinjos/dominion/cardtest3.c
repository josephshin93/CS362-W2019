/******************************************************************************
 *       Author: Joseph Shin
 * Date Created: 2019 Feb 10
 *  Description: Unit test for minion card.
 *               Minion: 
 *                 "+1 Action
 *                  Choose one: +$2; or discard your hand, +4 Cards, and each 
 *                  other player with at least 5 cards in hand discards their 
 *                  hand and draws 4 cards."[1]
 * 
 *               [1] From: http://wiki.dominionstrategy.com/index.php/List_of_cards
 *****************************************************************************/

#include "dominion.h"
#include "domtest_helpers.h"
#include <stdio.h>
#include <string.h>


/* Scenario A: Choice 1 Scenario
   3 players
   empty supply
   no embargo tokens
   no outpost played/turn
   current player = 1
   phase = action phase = 0
   1 action
   coins = 2 (copper, copper)
   1 buy
   player 0 hand = [estate, copper, estate, smithy, silver]
   player 0 deck = [copper, copper, duchy, province]
   player 0 discard = [gold]
   (current) player 1 hand = [minion, copper, copper, estate, smithy]
   (current) player 1 deck = [silver, copper, copper, estate]
   (current) player 1 discard = [gold]
   player 2 hand = [estate, copper]
   player 2 deck = [copper, silver]
   player 2 discard = [gold]
   no played cards
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
    resl->numPlayers = 3;
    resl->whoseTurn = currplayer;
    resl->phase = 0;
    resl->numActions = 1;
    resl->coins = 2; // copper, copper
    resl->numBuys = 1;
    // player 0
    resl->hand[0][0] = estate;
    resl->hand[0][1] = copper;
    resl->hand[0][2] = estate;
    resl->hand[0][3] = smithy;
    resl->hand[0][4] = silver;
    resl->handCount[0] = 5;
    resl->deck[0][0] = copper;
    resl->deck[0][1] = copper;
    resl->deck[0][2] = duchy;
    resl->deck[0][3] = province;
    resl->deckCount[0] = 4;
    resl->discard[0][0] = gold;
    resl->discardCount[0] = 1;
    // player 1 (current player)
    resl->hand[currplayer][0] = minion;
    resl->hand[currplayer][1] = copper;
    resl->hand[currplayer][2] = copper;
    resl->hand[currplayer][3] = estate;
    resl->hand[currplayer][4] = smithy;
    resl->handCount[currplayer] = 5;
    resl->deck[currplayer][0] = silver;
    resl->deck[currplayer][1] = copper;
    resl->deck[currplayer][2] = copper;
    resl->deck[currplayer][3] = estate;
    resl->deckCount[currplayer] = 4;
    resl->discard[currplayer][0] = gold;
    resl->discardCount[currplayer] = 1;
    // player 2
    resl->hand[2][0] = estate;
    resl->hand[2][1] = copper;
    resl->handCount[2] = 2;
    resl->deck[2][0] = copper;
    resl->deck[2][1] = silver;
    resl->deckCount[2] = 2;
    resl->discard[2][0] = gold;
    resl->discardCount[2] = 1;

    memcpy(expc, resl, sizeof(struct gameState));

    // manually set scenario expected game state
    expc->coins += 2;
    expc->hand[currplayer][0] = expc->hand[currplayer][expc->handCount[currplayer]-1];
    expc->hand[currplayer][--expc->handCount[currplayer]] = -1;
    expc->playedCards[0] = minion;
    expc->playedCardCount++;


    // call target function
    ret = playCard(0, 1, 0, 0, resl);


    printf("---------------------------------- Scenario A ----------------------------------\n");

    // compare return values
    printf("Return Value: ");
    compres = (expRet > ret) - (expRet < ret);
    if (compres == 0) printf("%sCORRECT%s\n", CGRN, CNRM);
    else printf("%sWRONG%s   expected(%d) %c resulting(%d)\n", CRED, CNRM, expRet, (char)('='+compres), ret);
    
    // compare game states
    compareStates(expc, resl, 1, 6);

    // compres = compareStatesAndSave(expc, resl, comp);
    // printf("compare game state return value: %d\n", compres);
    // printGscomp(comp);


    // interpret comparison(?)

    printf("--------------------------------------------------------------------------------\n");
}

/* Scenario B: Choice 2 Scenario
   3 players
   empty supply
   no embargo tokens
   no outpost played/turn
   current player = 1
   phase = action phase = 0
   1 action
   coins = 2 (copper, copper)
   1 buy
   player 0 hand = [estate, copper, estate, smithy, silver]
   player 0 deck = [copper, copper, duchy, province]
   player 0 discard = [gold]
   (current) player 1 hand = [minion, copper, copper, estate, smithy]
   (current) player 1 deck = [silver, copper, copper, estate]
   (current) player 1 discard = [gold]
   player 2 hand = [estate, copper]
   player 2 deck = [copper, silver]
   player 2 discard = [gold]
   no played cards
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
    resl->numPlayers = 3;
    resl->whoseTurn = currplayer;
    resl->phase = 0;
    resl->numActions = 1;
    resl->coins = 2; // copper, copper
    resl->numBuys = 1;
    // player 0
    resl->hand[0][0] = estate;
    resl->hand[0][1] = copper;
    resl->hand[0][2] = estate;
    resl->hand[0][3] = smithy;
    resl->hand[0][4] = silver;
    resl->handCount[0] = 5;
    resl->deck[0][0] = copper;
    resl->deck[0][1] = copper;
    resl->deck[0][2] = duchy;
    resl->deck[0][3] = province;
    resl->deckCount[0] = 4;
    resl->discard[0][0] = gold;
    resl->discardCount[0] = 1;
    // player 1 (current player)
    resl->hand[currplayer][0] = minion;
    resl->hand[currplayer][1] = copper;
    resl->hand[currplayer][2] = copper;
    resl->hand[currplayer][3] = estate;
    resl->hand[currplayer][4] = smithy;
    resl->handCount[currplayer] = 5;
    resl->deck[currplayer][0] = silver;
    resl->deck[currplayer][1] = copper;
    resl->deck[currplayer][2] = copper;
    resl->deck[currplayer][3] = estate;
    resl->deckCount[currplayer] = 4;
    resl->discard[currplayer][0] = gold;
    resl->discardCount[currplayer] = 1;
    // player 2
    resl->hand[2][0] = estate;
    resl->hand[2][1] = copper;
    resl->handCount[2] = 2;
    resl->deck[2][0] = copper;
    resl->deck[2][1] = silver;
    resl->deckCount[2] = 2;
    resl->discard[2][0] = gold;
    resl->discardCount[2] = 1;

    memcpy(expc, resl, sizeof(struct gameState));

    // manually set scenario expected game state
    expc->coins += 2;
    // player 0
    expc->hand[0][0] = province;
    expc->hand[0][1] = duchy;
    expc->hand[0][2] = copper;
    expc->hand[0][3] = copper;
    expc->hand[0][4] = -1;
    expc->handCount[0] = 4;
    expc->deck[0][0] = -1;
    expc->deck[0][1] = -1;
    expc->deck[0][2] = -1;
    expc->deck[0][3] = -1;
    expc->deckCount[0] = 0;
    expc->discard[0][1] = estate;
    expc->discard[0][2] = copper;
    expc->discard[0][3] = estate;
    expc->discard[0][4] = smithy;
    expc->discard[0][5] = silver;
    expc->discardCount[0] = 6;
    // player 1 (current player)
    expc->hand[currplayer][0] = estate;
    expc->hand[currplayer][1] = copper;
    expc->hand[currplayer][2] = copper;
    expc->hand[currplayer][3] = silver;
    expc->hand[currplayer][4] = -1;
    expc->handCount[currplayer] = 4;
    expc->deck[currplayer][0] = -1;
    expc->deck[currplayer][1] = -1;
    expc->deck[currplayer][2] = -1;
    expc->deck[currplayer][3] = -1;
    expc->deckCount[currplayer] = 0;
    expc->discard[currplayer][1] = copper;
    expc->discard[currplayer][2] = copper;
    expc->discard[currplayer][3] = estate;
    expc->discard[currplayer][4] = smithy;
    expc->discardCount[currplayer] = 5;
    expc->playedCards[0] = minion;
    expc->playedCardCount++;


    // call target function
    ret = playCard(0, 0, 1, 0, resl);


    printf("---------------------------------- Scenario B ----------------------------------\n");

    // compare return values
    printf("Return Value: ");
    compres = (expRet > ret) - (expRet < ret);
    if (compres == 0) printf("%sCORRECT%s\n", CGRN, CNRM);
    else printf("%sWRONG%s   expected(%d) %c resulting(%d)\n", CRED, CNRM, expRet, (char)('='+compres), ret);
    
    // compare game states
    compareStates(expc, resl, 1, 6);

    // compres = compareStatesAndSave(expc, resl, comp);
    // printf("compare game state return value: %d\n", compres);
    // printGscomp(comp);


    // interpret comparison(?)

    printf("--------------------------------------------------------------------------------\n");
}

void cardTest3() {
    // declare game states and game state comparison
    struct gameState expected, resulting;
    struct gscomp comp;

    printf("================================= CARD TEST 3 ==================================\n");
    printf("target function: \n");

    testScenarioA(&expected, &resulting, &comp);
    testScenarioB(&expected, &resulting, &comp);

    printf("================================================================================\n");
}


int main() {
    cardTest3();
    return 0;
}