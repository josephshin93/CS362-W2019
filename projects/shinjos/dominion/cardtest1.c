/******************************************************************************
 *       Author: Joseph Shin
 * Date Created: 2019 Feb 10
 *  Description: Unit test for adventurer card.
 *               Adventurer: 
 *                 "Reveal cards from your deck until you reveal 2 Treasure 
 *                 cards. Put those Treasure cards into your hand and discard 
 *                 the other revealed cards."[1]
 * 
 *               [1] From: http://wiki.dominionstrategy.com/index.php/List_of_cards
 *****************************************************************************/

#include "dominion.h"
#include "domtest_helpers.h"
#include <stdio.h>
#include <string.h>


/* Scenario A: Normal Scenario
   2 players
   empty supply
   no embargo tokens
   no outpost played/turn
   current player = 0
   phase = action phase = 0
   1 action
   4 coins (copper, copper, silver)
   1 buy
   current player hand = [adventurer, copper, estate, copper, silver]
   current player deck = [copper, gold, estate, smithy, copper, estate(top)]
   current player discard = [copper]
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
    resl->numPlayers = 2;
    // supply not set - does not change
    // no embargo tokens
    // no outpost played and false outpost turn
    resl->whoseTurn = currplayer;
    resl->phase = 0; // action phase
    resl->numActions = 1;
    resl->coins = 4; // copper, copper, silver
    resl->numBuys = 1;
    resl->hand[currplayer][0] = adventurer;
    resl->hand[currplayer][1] = copper;
    resl->hand[currplayer][2] = estate;
    resl->hand[currplayer][3] = copper;
    resl->hand[currplayer][4] = silver;
    resl->handCount[currplayer] = 5;
    resl->deck[currplayer][0] = copper;
    resl->deck[currplayer][1] = gold;
    resl->deck[currplayer][2] = estate;
    resl->deck[currplayer][3] = smithy;
    resl->deck[currplayer][4] = copper;
    resl->deck[currplayer][5] = estate; // top of deck
    resl->deckCount[currplayer] = 6;
    resl->discard[currplayer][0] = copper;
    resl->discardCount[currplayer] = 1;
    // other player's hand/deck/discard is zero'd out - no change
    // no played cards from current player

    memcpy(expc, resl, sizeof(struct gameState));

    // manually set scenario expected game state
    expc->phase = 0; // not sure if this should change with playing a card
    expc->numActions--;
    expc->coins += 4; // + copper, gold
    expc->hand[currplayer][5] = copper;
    expc->hand[currplayer][6] = gold;
    expc->handCount[currplayer] += 2;
    expc->deck[currplayer][1] = -1; // revealed cards
    expc->deck[currplayer][2] = -1;
    expc->deck[currplayer][3] = -1;
    expc->deck[currplayer][4] = -1;
    expc->deck[currplayer][5] = -1;
    expc->deckCount[currplayer] -= 5;
    expc->discard[currplayer][1] = estate;
    expc->discard[currplayer][2] = smithy;
    expc->discard[currplayer][3] = estate;
    expc->discardCount[currplayer] += 3;
    expc->playedCards[0] = adventurer;
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
    compareStates(expc, resl, 1, 7);

    // compres = compareStatesAndSave(expc, resl, comp);
    // printf("compare game state return value: %d\n", compres);
    // printGscomp(comp);


    // interpret comparison(?)

    printf("--------------------------------------------------------------------------------\n");
}

/* Scenario B: Shuffle Scenario
   2 players
   empty supply
   no embargo tokens
   no outpost played/turn
   current player = 0
   phase = action phase = 0
   1 action
   4 coins (copper, copper, silver)
   1 buy
   current player hand = [adventurer, copper, estate, copper, silver]
   current player deck = [duchy, curse, estate, smithy, copper, estate(top)]
   current player discard = [gold, gold]
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
    int currplayer = 0;
    
    // set up scenario initial game state
    resl->numPlayers = 2;
    // supply not set - does not change
    // no embargo tokens
    // no outpost played and false outpost turn
    resl->whoseTurn = currplayer;
    resl->phase = 0; // action phase
    resl->numActions = 1;
    resl->coins = 4; // copper, copper, silver
    resl->numBuys = 1;
    resl->hand[currplayer][0] = adventurer;
    resl->hand[currplayer][1] = copper;
    resl->hand[currplayer][2] = estate;
    resl->hand[currplayer][3] = copper;
    resl->hand[currplayer][4] = silver;
    resl->handCount[currplayer] = 5;
    resl->deck[currplayer][0] = duchy;
    resl->deck[currplayer][1] = curse;
    resl->deck[currplayer][2] = estate;
    resl->deck[currplayer][3] = smithy;
    resl->deck[currplayer][4] = copper;
    resl->deck[currplayer][5] = estate; // top of deck
    resl->deckCount[currplayer] = 6;
    resl->discard[currplayer][0] = gold;
    resl->discard[currplayer][1] = gold;
    resl->discardCount[currplayer] = 2;
    // other player's hand/deck/discard is zero'd out - no change
    // no played cards from current player

    memcpy(expc, resl, sizeof(struct gameState));

    // manually set scenario expected game state
    expc->phase = 0; // not sure if this should change with playing a card
    expc->numActions--;
    expc->coins += 4; // + copper, gold
    expc->hand[currplayer][5] = copper;
    expc->hand[currplayer][6] = gold;
    expc->handCount[currplayer] += 2;
    expc->deck[currplayer][0] = gold; // all revealed, then got a shuffled discard pile, then one gold was drawn
    expc->deck[currplayer][1] = -1;
    expc->deck[currplayer][2] = -1;
    expc->deck[currplayer][3] = -1;
    expc->deck[currplayer][4] = -1;
    expc->deck[currplayer][5] = -1;
    expc->deckCount[currplayer] -= 5;
    expc->discard[currplayer][0] = -1;
    expc->discard[currplayer][1] = -1;
    expc->discardCount[currplayer] -=2;
    expc->playedCards[0] = adventurer;
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
    compareStates(expc, resl, 1, 7);

    // compres = compareStatesAndSave(expc, resl, comp);
    // printf("compare game state return value: %d\n", compres);
    // printGscomp(comp);


    // interpret comparison(?)

    printf("--------------------------------------------------------------------------------\n");
}

void cardTest1() {
    // declare game states and game state comparison
    struct gameState expected, resulting;
    struct gscomp comp;

    printf("================================= CARD TEST 1 ==================================\n");
    printf("target card:     Adventurer\n");
    printf("target function: int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)\n");

    testScenarioA(&expected, &resulting, &comp);
    testScenarioB(&expected, &resulting, &comp);

    printf("================================================================================\n");
}


int main() {
    cardTest1();
    return 0;
}