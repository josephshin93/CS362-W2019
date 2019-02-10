/******************************************************************************
 *       Author: Joseph Shin
 * Date Created: 2019 Feb 10
 *  Description: Unit test for sea hag card.
 *               Sea Hag: 
 *                 "Each other player discards the top card of their deck, 
 *                 then gains a Curse onto their deck."[1]
 * 
 *               [1] From: http://wiki.dominionstrategy.com/index.php/List_of_cards
 *****************************************************************************/

#include "dominion.h"
#include "domtest_helpers.h"
#include <stdio.h>
#include <string.h>


/* Scenario A: Normal Scenario
   3 players
   supply = 1 curse
   no embargo tokens
   no outpost played/turn
   current player = 0
   phase = 0
   1 action
   2 coins (copper, copper)
   1 buy
   (current) player 0 hand = [sea hag, copper, estate, copper, smithy]
   (current) player 0 deck = [silver]
   (current) player 0 discard = [gold]
   player 1 hand = empty
   player 1 deck = [copper]
   player 1 dicard = empty
   player 2 hand = empty
   player 2 deck = [province]
   player 2 discard = empty
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
    int currplayer = 0;
    
    // set up scenario initial game state
    resl->numPlayers = 3;
    resl->supplyCount[curse] = 1;
    resl->whoseTurn = currplayer;
    resl->phase = 0;
    resl->numActions = 1;
    resl->coins = 2; // copper, copper
    resl->numBuys = 1;
    // player 0 (current player)
    resl->hand[currplayer][0] = sea_hag;
    resl->hand[currplayer][1] = copper;
    resl->hand[currplayer][2] = estate;
    resl->hand[currplayer][3] = copper;
    resl->hand[currplayer][4] = smithy;
    resl->handCount[currplayer] = 5;
    resl->deck[currplayer][0] = silver;
    resl->deckCount[currplayer] = 1;
    resl->discard[currplayer][0] = gold;
    resl->discardCount[currplayer] = 1;
    // player 1
    resl->deck[1][0] = copper;
    resl->deckCount[1] = 1;
    // player 2
    resl->deck[2][0] = province;
    resl->deckCount[2] = 1;
    
    memcpy(expc, resl, sizeof(struct gameState));

    // manually set scenario expected game state
    expc->supplyCount[curse] = 0;
    expc->numActions--;
    expc->hand[currplayer][0] = smithy;
    expc->hand[currplayer][4] = -1;
    expc->deck[1][0] = curse;
    expc->discard[1][0] = copper;
    expc->discardCount[1] = 1;
    expc->deck[2][0] = -1;
    expc->deckCount[2] = 0;
    expc->discard[2][0] = province;
    expc->discardCount[2] = 1;
    expc->playedCards[0] = sea_hag;
    expc->playedCardCount = 1;


    // call target function
    ret = playCard(0, 0, 0, 0, resl);


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


void cardTest4() {
    // declare game states and game state comparison
    struct gameState expected, resulting;
    struct gscomp comp;

    printf("================================= CARD TEST 4 ==================================\n");
    printf("target function: \n");

    testScenarioA(&expected, &resulting, &comp);

    printf("================================================================================\n");
}


int main() {
    cardTest4();
    return 0;
}