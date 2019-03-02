/******************************************************************************
 *       Author: Joseph Shin
 * Date Created: 2019 Feb 06
 *  Description: Implementation of helper functions for testing the dominion 
 *               game code.
 *****************************************************************************/


#include "dominion.h"
#include "domtest_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

int compareInts(const void* a, const void* b) {
  if (*(int*)a > *(int*)b)
    return 1;
  if (*(int*)a < *(int*)b)
    return -1;
  return 0;
}

int compareIntArrays(int *leftarr, int *rightarr, int *comparr, int len) {
    int i = 0, eq = 1;
    for (i = 0; i < len; i++) {
        comparr[i] = (leftarr[i] > rightarr[i]) - (leftarr[i] < rightarr[i]);
        if (eq && comparr[i] != 0) eq = 0;
    }
    return eq;
}


int _singleValuePrintLine(char *name, int value, int indent, char *buffer, int size) {
    int i;
    memset(buffer, '\0', sizeof(char) * size);
    for (i = 0; i < indent; i++) strcat(buffer, "   ");
    sprintf(buffer, "%s%15s: %d\n", buffer, name, value);

    // printf("line buffer: \"%s\"\n", buffer);
    return 0;
}
int _1darrPrintLines(char *name, int arr[], int len, int indent, char *buffer, int size) {
    int i, j;
    memset(buffer, '\0', sizeof(char) * size);

    for (i = 0; i < indent; i++) strcat(buffer, "   ");
    sprintf(buffer, "%s%15s:\n", buffer, name);
    
    for (i = 0; i < indent+1; i++) strcat(buffer, "   ");
    strcat(buffer, "[ ");

    for (i = 0; i < len; i++) {
        sprintf(buffer, "%s%11d", buffer, arr[i]);
        if (i + 1 < len) {
            strcat(buffer, ", ");
            if ((i+1) % 8 == 0) {
                strcat(buffer, "\n");
                for (j = 0; j < indent+1; j++) strcat(buffer, "   ");
                strcat(buffer, "  ");
            }
        }
    }

    strcat(buffer, " ]\n");

    // printf("arr buffer: \"%s\"\n", buffer);

    return 0;
}
int _2darrPrintLines(char *name, int *arr[], int rows, int cols, int indent, char *buffer, int size) {
    int i, j, k;
    memset(buffer, '\0', sizeof(char) * size);

    for (i = 0; i < indent; i++) strcat(buffer, "   ");
    sprintf(buffer, "%s%15s:\n", buffer, name);

    for (i = 0; i < indent+1; i++) strcat(buffer, "   ");
    strcat(buffer, "[\n");

    for (i = 0; i < rows; i++) {
        for (k = 0; k < indent+2; k++) strcat(buffer, "   ");
        strcat(buffer, "[ ");

        for (j = 0; j < cols; j++) {
            sprintf(buffer, "%s%11d", buffer, *((arr+i*cols) + j));
            if (j + 1 < cols) {
                strcat(buffer, ", ");
                if ((j+1) % 8 == 0) {
                    strcat(buffer, "\n");
                    for (k = 0; k < indent+2; k++) strcat(buffer, "   ");
                    strcat(buffer, "  ");
                }
            }
        }

        strcat(buffer, " ]\n");
    }

    for (i = 0; i < indent+1; i++) strcat(buffer, "   ");
    strcat(buffer, "]\n");

    // printf("matrix buffer: \"%s\"\n", buffer);

    return 0;
}
// ERROR: this function seg-faults!
void printGameState(struct gameState *state, int indent) {
    int i;

    int bufs, lins, arrbufs, matxbufs;
    int MAX_IND = 5, 
        MAX_ARR_LEN = 500, 
        EL_PER_LINE = 10, 
        IND_S = 3, 
        NAME_S = 15, 
        INT_S = 11, 
        MAX_COL = 4,
        HEADER_S = (MAX_IND*IND_S) + 12;

    lins = ((indent+1)*IND_S) + NAME_S + INT_S + 3;
    arrbufs = (((indent+1)*IND_S) + NAME_S + 1) +
                ((int)ceil(MAX_ARR_LEN/EL_PER_LINE) * (((indent+2)*IND_S) + (EL_PER_LINE*(INT_S+2)) + 3));
    matxbufs = (((indent+1)*IND_S) + NAME_S + 1) +
                (MAX_COL * ((int)ceil(MAX_ARR_LEN/EL_PER_LINE) * (((indent+3)*IND_S) + (EL_PER_LINE*(INT_S+2)) + 3))) +
                (2 * (((indent+2)*IND_S) + 2));
    bufs = HEADER_S + 
            (9 * lins) +
            (6 * arrbufs) +
            (3 * matxbufs) + 100;

    // printf("lins = %d\narrbufs = %d\nmatxbufs = %d\nbufs = %d\n", lins, arrbufs, matxbufs, bufs);

    char *buffer = malloc(sizeof(char) * bufs);
    char *line = malloc(sizeof(char) * lins);
    char *arrbuffer = malloc(sizeof(char) * arrbufs);
    char *matbuffer = malloc(sizeof(char) * matxbufs);
    
    memset(buffer, '\0', sizeof(char) * bufs);
    
    strncat(buffer, "   ", indent);
    strcat(buffer, "GAME STATE:\n");

    _singleValuePrintLine("numPlayers", state->numPlayers, indent+1, line, lins);
    strcat(buffer, line);

    _1darrPrintLines("supplyCount", state->supplyCount, treasure_map+1, indent+1, arrbuffer, arrbufs);
    strcat(buffer, arrbuffer);

    _1darrPrintLines("embargoTokens", state->embargoTokens, treasure_map+1, indent+1, arrbuffer, arrbufs);
    strcat(buffer, arrbuffer);

    _singleValuePrintLine("outpostPlayed", state->outpostPlayed, indent+1, line, lins);
    strcat(buffer, line);

    _singleValuePrintLine("outpostTurn", state->outpostTurn, indent+1, line, lins);
    strcat(buffer, line);

    _singleValuePrintLine("whoseTurn", state->whoseTurn, indent+1, line, lins);
    strcat(buffer, line);

    _singleValuePrintLine("phase", state->phase, indent+1, line, lins);
    strcat(buffer, line);

    _singleValuePrintLine("numActions", state->numActions, indent+1, line, lins);
    strcat(buffer, line);

    _singleValuePrintLine("coins", state->coins, indent+1, line, lins);
    strcat(buffer, line);

    _singleValuePrintLine("numBuys", state->numBuys, indent+1, line, lins);
    strcat(buffer, line);

    _2darrPrintLines("hand", state->hand, MAX_PLAYERS, MAX_HAND, indent+1, matbuffer, matxbufs);
    strcat(buffer, matbuffer);

    _1darrPrintLines("handCount", state->handCount, MAX_PLAYERS, indent+1, arrbuffer, arrbufs);
    strcat(buffer, arrbuffer);

    _2darrPrintLines("deck", state->deck, MAX_PLAYERS, MAX_DECK, indent+1, matbuffer, matxbufs);
    strcat(buffer, matbuffer);

    _1darrPrintLines("deckCount", state->deckCount, MAX_PLAYERS, indent+1, arrbuffer, arrbufs);
    strcat(buffer, arrbuffer);

    // TODO: this one is seg faulting
    _2darrPrintLines("discard", state->discard, MAX_PLAYERS, MAX_DECK, indent+1, matbuffer, matxbufs);
    strcat(buffer, matbuffer);

    _1darrPrintLines("discardCount", state->discardCount, MAX_PLAYERS, indent+1, arrbuffer, arrbufs);
    strcat(buffer, arrbuffer);

    _1darrPrintLines("playedCards", state->playedCards, MAX_DECK, indent+1, arrbuffer, arrbufs);
    strcat(buffer, arrbuffer);

    _singleValuePrintLine("playedCardCount", state->playedCardCount, indent+1, line, lins);
    strcat(buffer, line);

    printf("%s\n", buffer);

    free(buffer);
    free(line);
    free(arrbuffer);
    free(matbuffer);
}

void printPlayerState(int player, struct gameState *state) {
    assert(player >= 0 && player < state->numPlayers);

    int linbufs = 25, arrbufs = 2048;
    char *linbuf = malloc(sizeof(char) * linbufs),
         *arrbuf = malloc(sizeof(char) * arrbufs);

    printf("State of player %d\n", player);
    
    _singleValuePrintLine("Phase", state->phase, 0, linbuf, linbufs);
    printf("%s", linbuf);
    _singleValuePrintLine("Actions", state->numActions, 0, linbuf, linbufs);
    printf("%s", linbuf);
    _singleValuePrintLine("Coins", state->coins, 0, linbuf, linbufs);
    printf("%s", linbuf);
    _singleValuePrintLine("Buys", state->numBuys, 0, linbuf, linbufs);
    printf("%s", linbuf);
    
    _singleValuePrintLine("Hand Count", state->handCount[player], 0, linbuf, linbufs);
    printf("%s", linbuf);
    _1darrPrintLines("Hand", state->hand[player], state->handCount[player], 0, arrbuf, arrbufs);
    printf("%s", arrbuf);

    _singleValuePrintLine("Deck Count", state->deckCount[player], 0, linbuf, linbufs);
    printf("%s", linbuf);
    _1darrPrintLines("Deck", state->deck[player], state->deckCount[player], 0, arrbuf, arrbufs);
    printf("%s", arrbuf);

    _singleValuePrintLine("Discard Count", state->discardCount[player], 0, linbuf, linbufs);
    printf("%s", linbuf);
    _1darrPrintLines("Discard", state->discard[player], state->discardCount[player], 0, arrbuf, arrbufs);
    printf("%s", arrbuf);

    // NOTE: needs ~6000 len char array
    // _singleValuePrintLine("Played Count", state->playedCardCount, 0, linbuf, linbufs);
    // printf("%s", linbuf);
    // _1darrPrintLines("Played", state->playedCards, state->playedCardCount, 0, arrbuf, arrbufs);
    // printf("%s", arrbuf);
    

    free(linbuf);
    free(arrbuf);
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

// TODO: improve function to return true and better printing
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


int randomRangeVal(base, width) {
    return floor(Random() * width) + base;
}

int randRangeVal(struct range* r) {
    return r->base + floor(Random() * r->width);
}

int chanced(int percent) {
    int p = floor(Random() * 100);
    return p < percent;
}

/*   Input: Pointer to game state
 *  Output: 0 = success, 1 = failed (not possible to return 1 at the moment)
 * Summary: This function randomizes the given game state. All bytes of the 
 *          game state struct will be assigned to random values; however, any 
 *          members that are used as indices assigned to a random value within 
 *          a range that will not cause seg faults. Remember, this most likely 
 *          NOT return a valid game state. The Random() from rngs.h is used to
 *          generate random numbers
 */
int randomizeGameState(struct gameState *state) {
    int i, j;

    struct range nsupply, 
                 boolVal, 
                 nplayers, 
                 nphases, 
                 nactions, 
                 ncoins, 
                 pileCounts, 
                 wcard,
                 nplayed;
    nsupply.base = -10;  nsupply.width = 200;
    boolVal.base = -1;   boolVal.width = 3;
    nplayers.base = 0;   nplayers.width = MAX_PLAYERS;
    nphases.base = -1;   nphases.width = 3;
    nactions.base = -5;  nactions.width = 100;
    ncoins.base = -20;   ncoins.width = 400;
    pileCounts.base = 0; pileCounts.width = 200;
    wcard.base = -2;     wcard.width = 30;
    nplayed.base = 0;    nplayed.width = 400;


    // number of players
    state->numPlayers = randRangeVal(&nplayers);

    // supply cards
    for (i = 0; i < treasure_map+1; i++) {
        state->supplyCount[i] = randRangeVal(&nsupply);
    }
    for (i = 0; i < treasure_map+1; i++) {
        state->embargoTokens[i] = randRangeVal(&nsupply);
    }
    
    // outpost booleans
    state->outpostPlayed = randRangeVal(&boolVal);
    state->outpostTurn = randRangeVal(&boolVal);
    
    // current player info
    state->whoseTurn = randRangeVal(&nplayers);
    state->phase = randRangeVal(&nphases);
    state->numActions = randRangeVal(&nactions);
    state->coins = randRangeVal(&ncoins);
    state->numBuys = randRangeVal(&nactions);

    // all player card piles
    for (i = 0; i < MAX_PLAYERS; i++) {
        state->handCount[i] = randRangeVal(&pileCounts);
        state->deckCount[i] = randRangeVal(&pileCounts);
        state->discardCount[i] = randRangeVal(&pileCounts);
    }
    for (i = 0; i < MAX_PLAYERS; i++) {
        for (j = 0; j < MAX_DECK; j++) {
            state->hand[i][j] = randRangeVal(&wcard);
            state->deck[i][j] = randRangeVal(&wcard);
            state->discard[i][j] = randRangeVal(&wcard);
        }
    }

    // played cards
    state->playedCardCount = randRangeVal(&nplayed);
    for (i = 0; i < MAX_DECK; i++) {
        state->playedCards[i] = randRangeVal(&wcard);
    }
    

    /* possible areas that may cause errors/invalid for game state
     * supplyCount: types of available and their supply # should be limited
     * embargoTokens: should agree with supplyCount, limited to # of curses
     * outpostPlayed: should be [0,1]
     * outpostTurn: should be [0,1]
     * whoseTurn: should be [0, numPlayers-1]
     * phase: should be [0, 1, 2] ?
     * numActions: -
     * coins: should reflect hand[whoseTurn]?
     * numBuys: -
     * hand: -
     * deck: -
     * discard: -
     * playedCards: -
     * playedCardsCount: [0, MAX_DECK-1]
     */ 

    return 0;
}
