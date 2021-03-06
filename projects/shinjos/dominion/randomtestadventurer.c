/******************************************************************************
 *       Author: Joseph Shin
 * Date Created: 2019 Feb 27
 *  Description: Unit test for effect of Adventurer card. A random testing 
 *               method is used, and the card's effect is executed through the 
 *               playCard function.
 *****************************************************************************/

#include "dominion.h"
#include "rngs.h"
#include "domtest_helpers.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



// generate random values used to play adventure card
void randomInput(int *handPos, int *c1, int *c2, int *c3, struct gameState *state) {
    // random choice
    *c1 = randValInRange(0, 2);
    *c2 = randValInRange(0, 2);
    *c3 = randValInRange(0, 2);

    // random game state
    randomizeGameState(state);

    state->handCount[state->whoseTurn] = randValInRange(10, 10);
    state->deckCount[state->whoseTurn] = randValInRange(10, 30);
    state->discardCount[state->whoseTurn] = randValInRange(10, 30);

    // place adventurer card in hand
    *handPos = randValInRange(0, state->handCount[state->whoseTurn]);    

    // ~86% chance that card will be played
    // NOTE: in the event that the card in handPos is not an adventurer, it 
    //       must either be < 7 or > 26 or else another action card is 
    //       played with the this input, which could lead to infinite loops
    //       or the program crashing
    if (chanced(95)) state->hand[state->whoseTurn][*handPos] = adventurer;
    else state->hand[state->whoseTurn][*handPos] = 0; 
    if (chanced(95)) state->phase = 0;
    if (chanced(95) && state->numActions < 0) state->numActions *= -1;
}


// compute expected state from original state
void testOrcale(int handPos, struct gameState *orig, struct gameState *expc, long seed) {
    memcpy(expc, orig, sizeof(struct gameState));

    int player = expc->whoseTurn;

    // check if card can be played can be done
    if (expc->phase != ACTION_PHASE || 
        expc->numActions < 1 || 
        expc->hand[player][handPos] != adventurer) return;    

    int i, j, card;
    int origTop = expc->deckCount[player] - 1;
    int found = 0;
    int treasures[2] = {0, 0};

    int newDeck[MAX_DECK];
    int shuffledCount, newDeckCount = 0;
    
    
    // add treasures from deck
    while (expc->deckCount[player] > 0 && found < 2) {
        card = expc->deck[player][expc->deckCount[player]-1];
        if (card == copper || card == silver || card == gold) {
            treasures[found++] = card;
            for (i = expc->deckCount[player]-1; i < origTop; i++) {
                expc->deck[player][i] = expc->deck[player][i+1];
            }
            origTop--;
        }
        expc->deckCount[player]--;
    }

    // shuffle discard and add to deck then search for more treasures in deck
    if (found < 2 && expc->discardCount[player] > 0) {
        assert(expc->deckCount[player] == 0);

        PutSeed(seed);

        // NOTE: the following code is from the dominion.c shuffle function
        // sort card in deck to ensure determinism
        qsort((void*)(expc->discard[player]), 
              expc->discardCount[player], 
              sizeof(int), 
              compareInts);
        // randomly choose each card to get shuffled order
        while (expc->discardCount[player] > 0) {
            card = floor(Random() * expc->discardCount[player]);
            newDeck[newDeckCount++] = expc->discard[player][card];
            for (i = card; i < expc->discardCount[player]-1; i++) {
                expc->discard[player][i] = expc->discard[player][i+1];
            }
            expc->discardCount[player]--;
        }
        shuffledCount = newDeckCount;
        
        // add treasures from new deck
        for (i = newDeckCount-1; i >= 0 && found < 2; i--) {
            card = newDeck[i];
            if (card == copper || card == silver || card == gold) {
                treasures[found++] = card;
                for (j = i; j < newDeckCount-1; j++) newDeck[j] = newDeck[j+1];
                newDeckCount--;
            }
        }

        // printf("%d revealed from deck + %d revealed from shuffle = %d\n", origTop+1, newDeckCount-i+1, origTop + 1 + newDeckCount - i + 1);
        assert(origTop + 1 + newDeckCount - i + 1 < MAX_DECK); // or else seg fault
        
        // put revaled cards (still "in deck") into discard pile
        while (origTop >= expc->deckCount[player] && expc->discardCount[player] < MAX_DECK) {
            expc->discard[player][expc->discardCount[player]++] = expc->deck[player][origTop--];
        }
        assert(origTop == -1);
        // put revealed cards from new deck into discard pile
        for (j = newDeckCount-1; j > i && expc->discardCount[player] < MAX_DECK; j--) {
            expc->discard[player][expc->discardCount[player]++] = newDeck[j];
        }
        assert(j == i);

        // transfer unrevealed new deck cards to deck
        for (j = 0; j <= i; j++) {
            expc->deck[player][expc->deckCount[player]++] = newDeck[j];
        }
    
    } else {
        // discard cards revealed from deck [expc->deckCount[player], origTop]
        for (i = origTop; i >= expc->deckCount[player]; i--) {
            expc->discard[player][expc->discardCount[player]++] = expc->deck[player][i];
        }
    }

    // add found treasures to hand and compute total coins in hand
    for (i = 0; i < found; i++) {
        expc->hand[player][expc->handCount[player]++] = treasures[i];
    }
    int totalCoins = 0;
    for (i = 0; i < expc->handCount[player]; i++) {
        if (expc->hand[player][i] >= copper && expc->hand[player][i] <= gold) {
            totalCoins += (expc->hand[player][i] - 3); // treasure card - 3 = its value
        }
    }
    expc->coins = totalCoins;

    // decrement actions
    expc->numActions--;

    // move played adventurer card to played pile
    assert(expc->hand[player][handPos] == adventurer);
    for (i = handPos; i < expc->handCount[player]-1; i++) {
        expc->hand[player][i] = expc->hand[player][i+1];
    }
    expc->handCount[player]--;
    expc->playedCards[expc->playedCardCount++] = adventurer;
}


int main(int argc, char const *argv[]) {
    const int NUM_TEST_CASES = 5000, SHOW_FAIL_DETAILS = 0;
    int i, passed = 0;
    int handPos, c1, c2, c3;
    struct gameState original, expected;

    int shuffleStream = 0, inputStream = 1;
    long shuffleSeed = 1993, inputSeed = 1981;

    // set up random number generator streams
    SelectStream(shuffleStream);
    PutSeed(shuffleSeed);
    SelectStream(inputStream);
    PutSeed(inputSeed);

    // run test cases
    for (i = 0; i < NUM_TEST_CASES; i++) {
        // generate random inputs
        SelectStream(inputStream);
        randomInput(&handPos, &c1, &c2, &c3, &original);
        
        // generate expected output
        SelectStream(shuffleStream);
        testOrcale(handPos, &original, &expected, shuffleSeed);

        // generate result output
        PutSeed(shuffleSeed);
        playCard(handPos, c1, c2, c3, &original);
        
        // print testing information
        printf("Test Case %4d: ", i+1);
        if (memcmp(&expected, &original, sizeof(struct gameState)) == 0) {
            passed++;
            printf("Passed\n");
        } else {
            printf("Failed\n");
            if (SHOW_FAIL_DETAILS) {
                compareStates(&expected, &original, 0, 0);
                printf("\n");
            }
        }

        shuffleSeed++;
    }
    printf("\n");

    printf("%d test cases: %d passed, %d failed\n", NUM_TEST_CASES, passed, NUM_TEST_CASES-passed);

    return 0;
}