/******************************************************************************
 *       Author: Joseph Shin
 * Date Created: 2019 Mar 2
 *  Description: Unit test for effect of smithy card. A random testing 
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



// generate random values used to play smithy card
void randomInput(struct cardPlayInput *input) {
    int i;
    
    // random choice
    input->c1 = randValInRange(0, 2);
    input->c2 = randValInRange(0, 2);
    input->c3 = randValInRange(0, 2);

    // random game state
    struct gameState *state = &input->state;
    randomizeGameState(state);

    // random pile counts
    state->handCount[state->whoseTurn] = randValInRange(3, 8);
    state->deckCount[state->whoseTurn] = randValInRange(0, 6); // 50% chance of shuffling 
    state->discardCount[state->whoseTurn] = randValInRange(4, 10); 

    // place smithy card in random spot of hand
    input->handPos = randValInRange(0, state->handCount[state->whoseTurn]);

    // ~86% that card will be played
    // NOTE: in the event that the card in handPos is not an smithy, it 
    //       must either be < 7 or > 26 or else another action card is 
    //       played with the this input, which could lead to infinite loops
    //       or the program crashing
    if (chanced(95)) state->hand[state->whoseTurn][input->handPos] = smithy;
    else state->hand[state->whoseTurn][input->handPos] = 0; 
    if (chanced(95)) state->phase = 0;
    if (chanced(95) && state->numActions < 0) state->numActions *= -1;
}


// compute expected state from original state
void testOrcale(struct cardPlayInput *input, struct gameState *expc, long seed) {
    struct gameState *orig = &input->state;

    memcpy(expc, orig, sizeof(struct gameState));

    const int MAX_DRAW = 3;
    int i, j, card, drawn = 0, totalCoins = 0;
    int player = expc->whoseTurn;
    int drawnCards[MAX_DRAW];

    // check if card can be played can be done
    if (expc->phase != ACTION_PHASE || 
        expc->numActions < 1 || 
        expc->hand[player][input->handPos] != smithy) return;

    // draw from deck
    for (; expc->deckCount[player] > 0 && drawn < MAX_DRAW; expc->deckCount[player]--) {
        drawnCards[drawn++] = expc->deck[player][expc->deckCount[player]-1];
        // expc->hand[player][expc->handCount[player]++] = expc->deck[player][expc->deckCount[player]-1];
        // drawn++;
    }

    // shuffle discard and add to deck if not enough has been drawn
    if (drawn < MAX_DRAW) {
        assert(expc->deckCount[player] == 0);
        
        PutSeed(seed);
        
        // NOTE: the following code is from the dominion.c shuffle function
        // sort card in deck to ensure determinism
        qsort((void*)(expc->discard[player]), 
              expc->discardCount[player], 
              sizeof(int), 
              compareInts);
        // randomly choose each card to get shuffled order and immediately add
        while (expc->discardCount[player] > 0) {
            card = floor(Random() * expc->discardCount[player]);
            expc->deck[player][expc->deckCount[player]++] = expc->discard[player][card];
            for (i = card; i < expc->discardCount[player]-1; i++) {
                expc->discard[player][i] = expc->discard[player][i+1];
            }
            expc->discardCount[player]--;
            // NOTE: seems like whatever helper function smithy used to shuffle and 
            //       move to deck casues any removed cards to be -1, does not seem 
            //       to be incorrect behavior
            expc->discard[player][expc->discardCount[player]] = -1;
        }
        assert(expc->discardCount[player] == 0);
        
        // draw from new deck
        for (; expc->deckCount[player] > 0 && drawn < 3; expc->deckCount[player]--) {
            drawnCards[drawn++] = expc->deck[player][expc->deckCount[player]-1];
            // expc->hand[player][expc->handCount[player]++] = expc->deck[player][expc->deckCount[player]-1];
            // drawn++;
        }
    }

    // move played smithy card to played pile
    // NOTE: seems that smithy is supposed to draw 2 cards and then the final drawn 
    //       card goes into the spot that the smithy card is
    assert(input->handPos >= 0 && input->handPos < expc->handCount[player]);
    assert(expc->hand[player][input->handPos] == smithy);
    for (i = 0; i < drawn-1; i++) {
        expc->hand[player][expc->handCount[player]++] = drawnCards[i];
    }
    expc->hand[player][input->handPos] = drawnCards[drawn-1];
    // for (i = input->handPos; i < expc->handCount[player]-1; i++) {
    //     expc->hand[player][i] = expc->hand[player][i+1];
    // }
    // expc->handCount[player]--;
    expc->playedCards[expc->playedCardCount++] = smithy;

    // update the coins
    for (i = 0; i < expc->handCount[player]; i++) {
        if (expc->hand[player][i] >= copper && expc->hand[player][i] <= gold) {
            totalCoins += (expc->hand[player][i] - 3); // treasure card - 3 = its value
        }
    }
    expc->coins = totalCoins;

    // decrement actions
    expc->numActions--;
}


int main(int argc, char const *argv[]) {
    const int NUM_TEST_CASES = 5000, SHOW_FAIL_DETAILS = 1;
    int i, j, passed = 0;
    struct cardPlayInput input;
    struct gameState expected;

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
        randomInput(&input);

        // generate expected output
        SelectStream(shuffleStream);
        testOrcale(&input, &expected, shuffleSeed);

        // generate result output
        PutSeed(shuffleSeed);
        playCard(input.handPos, input.c1, input.c2, input.c3, &input.state);
        
        // print testing information
        printf("Test Case %4d: ", i+1);
        if (memcmp(&expected, &input.state, sizeof(struct gameState)) == 0) {
            passed++;
            printf("Passed\n");
        } else {
            printf("Failed\n");
            if (SHOW_FAIL_DETAILS) {
                compareStates(&expected, &input.state, 0, 0);
                printf("\n");
            }
        }

        shuffleSeed++;
    }
    printf("\n");

    printf("%d test cases: %d passed, %d failed\n", NUM_TEST_CASES, passed, NUM_TEST_CASES-passed);

    return 0;
}