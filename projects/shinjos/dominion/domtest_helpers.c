/******************************************************************************
 *       Author: Joseph Shin
 * Date Created: 2019 Feb 06
 *  Description: Implementation of helper functions for testing the dominion 
 *               game code.
 *****************************************************************************/


#include "dominion.h"
#include "domtest_helpers.h"
#include <stdio.h>
#include <stdlib.h>


int compareIntArrays(int *leftarr, int *rightarr, int *comparr, int len) {
    int i = 0, eq = 1;
    for (i = 0; i < len; i++) {
        comparr[i] = (leftarr[i] > rightarr[i]) - (leftarr[i] < rightarr[i]);
        if (eq && comparr[i] != 0) eq = 0;
    }
    return eq;
}

int compareStatesAndSave(struct gameState *expc, 
                         struct gameState *resl, 
                         struct gscomp *comp) {
    int i, arrcomp, eq = 1;

    // number of players
    comp->numPlayers = (int)(expc->numPlayers > resl->numPlayers) - 
                       (int)(expc->numPlayers < resl->numPlayers);
    if (eq && comp->numPlayers != 0) eq = 0;

    // supply count
    arrcomp = compareIntArrays(expc->supplyCount, 
                               resl->supplyCount, 
                               comp->supplyCount, 
                               treasure_map+1);
    if (eq && !arrcomp) eq = 0;

    // existing embargo tokens
    arrcomp = compareIntArrays(expc->embargoTokens, 
                               resl->embargoTokens, 
                               comp->embargoTokens, 
                               treasure_map+1);
    if (eq && !arrcomp) eq = 0;

    // outpost played flag and outpost turn number
    comp->outpostPlayed = (int)(expc->outpostPlayed > resl->outpostPlayed) - 
                          (int)(expc->outpostPlayed < resl->outpostPlayed);
    if (eq && comp->outpostPlayed != 0) eq = 0;

    // current player (turn)
    comp->whoseTurn = (int)(expc->whoseTurn > resl->whoseTurn) - 
                      (int)(expc->whoseTurn < resl->whoseTurn);
    if (eq && comp->whoseTurn != 0) eq = 0;

    // phase ?
    comp->phase = (int)(expc->phase > resl->phase) - 
                  (int)(expc->phase < resl->phase);
    if (eq && comp->phase != 0) eq = 0;

    // number of actions of current player
    comp->numActions = (int)(expc->numActions > resl->numActions) - 
                       (int)(expc->numActions < resl->numActions);
    if (eq && comp->numActions != 0) eq = 0;

    // coins of current player
    comp->coins = (int)(expc->coins > resl->coins) - 
                  (int)(expc->coins < resl->coins);
    if (eq && comp->coins != 0) eq = 0;

    // number of buys of current player
    comp->numBuys = (int)(expc->numBuys > resl->numBuys) - 
                    (int)(expc->numBuys < resl->numBuys);
    if (eq && comp->numBuys != 0) eq = 0;

    // all hands and hand counts
    for (i = 0; i < MAX_PLAYERS; i++) {
        arrcomp = compareIntArrays(expc->hand[i],
                                   resl->hand[i], 
                                   comp->hand[i], 
                                   MAX_HAND);
        if (eq && !arrcomp) eq = 0;
    }
    arrcomp = compareIntArrays(expc->handCount, 
                               resl->handCount, 
                               comp->handCount, 
                               MAX_PLAYERS);
    if (eq && !arrcomp) eq = 0;
    
    // all decks and deck counts
    for (i = 0; i < MAX_PLAYERS; i++) {
        arrcomp = compareIntArrays(expc->deck[i], 
                                   resl->deck[i], 
                                   comp->deck[i], 
                                   MAX_DECK);
        if (eq && !arrcomp) eq = 0;
    }
    arrcomp = compareIntArrays(expc->deckCount, 
                               resl->deckCount, 
                               comp->deckCount, 
                               MAX_PLAYERS);
    if (eq && !arrcomp) eq = 0;
    
    // all discards and discard counts
    for (i = 0; i < MAX_PLAYERS; i++) {
        arrcomp = compareIntArrays(expc->discard[i], 
                                   resl->discard[i], 
                                   comp->discard[i], 
                                   MAX_DECK);
        if (eq && !arrcomp) eq = 0;
    }
    arrcomp = compareIntArrays(expc->discardCount, 
                               resl->discardCount, 
                               comp->discardCount, 
                               MAX_PLAYERS);
    if (eq && !arrcomp) eq = 0;

    // played cards and count of played cards of current player
    arrcomp = compareIntArrays(expc->playedCards, 
                               resl->playedCards, 
                               comp->playedCards, 
                               MAX_DECK);
    if (eq && !arrcomp) eq = 0;
    comp->playedCardCount = (expc->playedCardCount > resl->playedCardCount) -
                            (expc->playedCardCount < resl->playedCardCount);
    if (eq && comp->playedCardCount != 0) eq = 0;


    return eq;
}

void compareStates(struct gameState *expc, struct gameState *resl, int ver, int apl) {
    int i, j;
    // char lt = '<', gt = '>', eq = '==', co;
    size_t apSize = sizeof(char) * apl * 50 * 5;
    char *arrayPrint = malloc(apSize);
    int comp, eq, ap;

    printf("Game State Comparison:\n");


    // number of players
    printf("numPlayers:      ");
    comp = (expc->numPlayers > resl->numPlayers) - 
           (expc->numPlayers < resl->numPlayers);
    if (comp != 0) printf("%sWRONG%s   ", CRED, CNRM);
    else printf("%sCORRECT%s ", CGRN, CNRM);
    if (ver) printf("expected(%d) %c resulting(%d)", expc->numPlayers, (char)('='+comp), resl->numPlayers);
    printf("\n");


    // supply count
    printf("supplyCount:     ");
    eq = 1;
    ap = 0;
	memset(arrayPrint, 0, apSize);
    for (i = 0; i < treasure_map+1; i++) {
        comp = (expc->supplyCount[i] > resl->supplyCount[i]) -
               (expc->supplyCount[i] < resl->supplyCount[i]);
        if (eq && comp != 0) eq = 0;
        // add to array print
        if (++ap <= apl) sprintf(arrayPrint, "%s                 [%d] -> expected(%d) %c resulting(%d)\n", arrayPrint, i, expc->supplyCount[i], (char)('='+comp), resl->supplyCount[i]);
    }
    if (!eq) printf("%sWRONG%s   ", CRED, CNRM);
    else printf("%sCORRECT%s ", CGRN, CNRM);
    printf("\n");
    if (ver) printf("%s", arrayPrint);


    // existing embargo tokens
    printf("embargoTokens:   ");
    eq = 1;
    ap = 0;
	memset(arrayPrint, 0, apSize);
    for (i = 0; i < treasure_map+1; i++) {
        comp = (expc->embargoTokens[i] > resl->embargoTokens[i]) -
               (expc->embargoTokens[i] < resl->embargoTokens[i]);
        if (eq && comp != 0) eq = 0;
        // add to array print
        if (++ap <= apl) sprintf(arrayPrint, "%s                 [%d] -> expected(%d) %c resulting(%d)\n", arrayPrint, i, expc->embargoTokens[i], (char)('='+comp), resl->embargoTokens[i]);
    }
    if (!eq) printf("%sWRONG%s   ", CRED, CNRM);
    else printf("%sCORRECT%s ", CGRN, CNRM);
    printf("\n");
    if (ver) printf("%s", arrayPrint);


    // outpost played flag and outpost turn number
    printf("outpostPlayed:   ");
    comp = (expc->outpostPlayed > resl->outpostPlayed) - 
           (expc->outpostPlayed < resl->outpostPlayed);
    if (comp != 0) printf("%sWRONG%s   ", CRED, CNRM);
    else printf("%sCORRECT%s ", CGRN, CNRM);
    if (ver) printf("expected(%d) %c resulting(%d)", expc->outpostPlayed, (char)('='+comp), resl->outpostPlayed);
    printf("\n");

    printf("outpostTurn:     ");
    comp = (expc->outpostTurn > resl->outpostTurn) - 
           (expc->outpostTurn < resl->outpostTurn);
    if (comp != 0) printf("%sWRONG%s   ", CRED, CNRM);
    else printf("%sCORRECT%s ", CGRN, CNRM);
    if (ver) printf("expected(%d) %c resulting(%d)", expc->outpostTurn, (char)('='+comp), resl->outpostTurn);
    printf("\n");



    // current player (turn)
    printf("whoseTurn:       ");
    comp = (expc->whoseTurn > resl->whoseTurn) - 
           (expc->whoseTurn < resl->whoseTurn);
    if (comp != 0) printf("%sWRONG%s   ", CRED, CNRM);
    else printf("%sCORRECT%s ", CGRN, CNRM);
    if (ver) printf("expected(%d) %c resulting(%d)", expc->whoseTurn, (char)('='+comp), resl->whoseTurn);
    printf("\n");


    // phase (?)
    printf("phase:           ");
    comp = (expc->phase > resl->phase) - 
           (expc->phase < resl->phase);
    if (comp != 0) printf("%sWRONG%s   ", CRED, CNRM);
    else printf("%sCORRECT%s ", CGRN, CNRM);
    if (ver) printf("expected(%d) %c resulting(%d)", expc->phase, (char)('='+comp), resl->phase);
    printf("\n");


    // number of actions of current player
    printf("numActions:      ");
    comp = (expc->numActions > resl->numActions) - 
           (expc->numActions < resl->numActions);
    if (comp != 0) printf("%sWRONG%s   ", CRED, CNRM);
    else printf("%sCORRECT%s ", CGRN, CNRM);
    if (ver) printf("expected(%d) %c resulting(%d)", expc->numActions, (char)('='+comp), resl->numActions);
    printf("\n");


    // coins of current player
    printf("coins:           ");
    comp = (expc->coins > resl->coins) - 
           (expc->coins < resl->coins);
    if (comp != 0) printf("%sWRONG%s   ", CRED, CNRM);
    else printf("%sCORRECT%s ", CGRN, CNRM);
    if (ver) printf("expected(%d) %c resulting(%d)", expc->coins, (char)('='+comp), resl->coins);
    printf("\n");


    // number of buys of current player
    printf("numBuys:         ");
    comp = (expc->numBuys > resl->numBuys) - 
           (expc->numBuys < resl->numBuys);
    if (comp != 0) printf("%sWRONG%s   ", CRED, CNRM);
    else printf("%sCORRECT%s ", CGRN, CNRM);
    if (ver) printf("expected(%d) %c resulting(%d)", expc->numBuys, (char)('='+comp), resl->numBuys);
    printf("\n");


    // all hands and hand counts
    printf("hand:            ");
    eq = 1;
	memset(arrayPrint, 0, apSize);
    for (i = 0; i < MAX_PLAYERS; i++) {
        ap = 0;
        for (j = 0; j < MAX_HAND; j++) {
            comp = (expc->hand[i][j] > resl->hand[i][j]) -
                   (expc->hand[i][j] < resl->hand[i][j]);
            if (eq && comp != 0) eq = 0;
            // add to array print
            if (++ap <= apl) sprintf(arrayPrint, "%s                 [%d][%d] -> expected(%d) %c resulting(%d)\n", arrayPrint, i, j, expc->hand[i][j], (char)('='+comp), resl->hand[i][j]);
        }
    }
    if (!eq) printf("%sWRONG%s   ", CRED, CNRM);
    else printf("%sCORRECT%s ", CGRN, CNRM);
    printf("\n");
    if (ver) printf("%s", arrayPrint);

    printf("handCount:       ");
    eq = 1;
    ap = 0;
	memset(arrayPrint, 0, apSize);
    for (i = 0; i < MAX_PLAYERS; i++) {
        comp = (expc->handCount[i] > resl->handCount[i]) -
               (expc->handCount[i] < resl->handCount[i]);
        if (eq && comp != 0) eq = 0;
        // add to array print
        if (++ap <= apl) sprintf(arrayPrint, "%s                 [%d] -> expected(%d) %c resulting(%d)\n", arrayPrint, i, expc->handCount[i], (char)('='+comp), resl->handCount[i]);
    }
    if (!eq) printf("%sWRONG%s   ", CRED, CNRM);
    else printf("%sCORRECT%s ", CGRN, CNRM);
    printf("\n");
    if (ver) printf("%s", arrayPrint);
    

    // all decks and deck counts
    printf("deck:            ");
    eq = 1;
	memset(arrayPrint, 0, apSize);
    for (i = 0; i < MAX_PLAYERS; i++) {
        ap = 0;
        for (j = 0; j < MAX_DECK; j++) {
            comp = (expc->deck[i][j] > resl->deck[i][j]) -
                   (expc->deck[i][j] < resl->deck[i][j]);
            if (eq && comp != 0) eq = 0;
            // add to array print
            if (++ap <= apl) sprintf(arrayPrint, "%s                 [%d][%d] -> expected(%d) %c resulting(%d)\n", arrayPrint, i, j, expc->deck[i][j], (char)('='+comp), resl->deck[i][j]);
        }
    }
    if (!eq) printf("%sWRONG%s   ", CRED, CNRM);
    else printf("%sCORRECT%s ", CGRN, CNRM);
    printf("\n");
    if (ver) printf("%s", arrayPrint);

    printf("deckCount:       ");
    eq = 1;
    ap = 0;
	memset(arrayPrint, 0, apSize);
    for (i = 0; i < MAX_PLAYERS
    ; i++) {
        comp = (expc->deckCount[i] > resl->deckCount[i]) -
               (expc->deckCount[i] < resl->deckCount[i]);
        if (eq && comp != 0) eq = 0;
        // add to array print
        if (++ap <= apl) sprintf(arrayPrint, "%s                 [%d] -> expected(%d) %c resulting(%d)\n", arrayPrint, i, expc->deckCount[i], (char)('='+comp), resl->deckCount[i]);
    }
    if (!eq) printf("%sWRONG%s   ", CRED, CNRM);
    else printf("%sCORRECT%s ", CGRN, CNRM);
    printf("\n");
    if (ver) printf("%s", arrayPrint);


    // all discards and discard counts
    printf("discard:         ");
    eq = 1;
	memset(arrayPrint, 0, apSize);
    for (i = 0; i < MAX_PLAYERS; i++) {
        ap = 0;
        for (j = 0; j < MAX_DECK; j++) {
            comp = (expc->discard[i][j] > resl->discard[i][j]) -
                   (expc->discard[i][j] < resl->discard[i][j]);
            if (eq && comp != 0) eq = 0;
            // add to array print
            if (++ap <= apl) sprintf(arrayPrint, "%s                 [%d][%d] -> expected(%d) %c resulting(%d)\n", arrayPrint, i, j, expc->discard[i][j], (char)('='+comp), resl->discard[i][j]);
        }
    }
    if (!eq) printf("%sWRONG%s   ", CRED, CNRM);
    else printf("%sCORRECT%s ", CGRN, CNRM);
    printf("\n");
    if (ver) printf("%s", arrayPrint);

    printf("discardCount:    ");
    eq = 1;
    ap = 0;
	memset(arrayPrint, 0, apSize);
    for (i = 0; i < MAX_PLAYERS
    ; i++) {
        comp = (expc->discardCount[i] > resl->discardCount[i]) -
               (expc->discardCount[i] < resl->discardCount[i]);
        if (eq && comp != 0) eq = 0;
        // add to array print
        if (++ap <= apl) sprintf(arrayPrint, "%s                 [%d] -> expected(%d) %c resulting(%d)\n", arrayPrint, i, expc->discardCount[i], (char)('='+comp), resl->discardCount[i]);
    }
    if (!eq) printf("%sWRONG%s   ", CRED, CNRM);
    else printf("%sCORRECT%s ", CGRN, CNRM);
    printf("\n");
    if (ver) printf("%s", arrayPrint);
    

    // played cards and count of played cards of current player
    printf("playedCards:     ");
    eq = 1;
    ap = 0;
	memset(arrayPrint, 0, apSize);
    for (i = 0; i < treasure_map+1; i++) {
        comp = (expc->playedCards[i] > resl->playedCards[i]) -
               (expc->playedCards[i] < resl->playedCards[i]);
        if (eq && comp != 0) eq = 0;
        // add to array print
        if (++ap <= apl) sprintf(arrayPrint, "%s                 [%d] -> expected(%d) %c resulting(%d)\n", arrayPrint, i, expc->playedCards[i], (char)('='+comp), resl->playedCards[i]);
    }
    if (!eq) printf("%sWRONG%s   ", CRED, CNRM);
    else printf("%sCORRECT%s ", CGRN, CNRM);
    printf("\n");
    if (ver) printf("%s", arrayPrint);

    printf("playedCardCount: ");
    comp = (expc->playedCardCount > resl->playedCardCount) - 
           (expc->playedCardCount < resl->playedCardCount);
    if (comp != 0) printf("%sWRONG%s   ", CRED, CNRM);
    else printf("%sCORRECT%s ", CGRN, CNRM);
    if (ver) printf("expected(%d) %c resulting(%d)", expc->playedCardCount, (char)('='+comp), resl->playedCardCount);
    printf("\n");

}

void printIntArray(int *arr, int len) {
    int i;
    
    printf("[ ");
    for (i = 0; i < len; i++) {
        printf("%d", arr[i]);
        if (i + 1 < len) printf(", ");
    }
    printf(" ]\n");
}

void printGscomp(struct gscomp *comp) {
    int i;

    printf("Game State Comparison Results:\n");

    printf("numPlayers:      %d\n", comp->numPlayers);
    printf("supplyCount:     "); printIntArray(comp->supplyCount, treasure_map+1);
    printf("embargoTokens:   "); printIntArray(comp->embargoTokens, treasure_map+1);
    printf("outpostPlayed:   %d\n", comp->outpostPlayed);


    printf("outpostTurn:     %d\n", comp->outpostTurn);
    printf("whoseTurn:       %d\n", comp->whoseTurn);
    printf("phase:           %d\n", comp->phase);
    printf("numActions:      %d\n", comp->numActions);
    printf("coins:           %d\n", comp->coins);
    printf("numBuys:         %d\n", comp->numBuys);

    printf("hand:            [\n");
    for (i = 0; i < MAX_PLAYERS; i++) {
        printf("                   ");
        printIntArray(comp->hand[i], MAX_HAND);
    }
    printf("                 ]\n");

    printf("handCount:       "); printIntArray(comp->handCount, MAX_PLAYERS);


    printf("deck:            [\n");
    for (i = 0; i < MAX_PLAYERS; i++) {
        printf("                   ");
        printIntArray(comp->deck[i], MAX_DECK);
    }
    printf("                ]\n");

    printf("deckCount:       "); printIntArray(comp->deckCount, MAX_PLAYERS);


    printf("discard:         [\n");
    for (i = 0; i < MAX_PLAYERS; i++) {
        printf("                  ");
        printIntArray(comp->discard[i], MAX_DECK);
    }
    printf("                 ]\n");

    printf("discardCount:    "); printIntArray(comp->discardCount, MAX_PLAYERS);

    printf("playedCards:     "); printIntArray(comp->discardCount, MAX_DECK);

    printf("playedCardCount: %d\n", comp->playedCardCount);
}
