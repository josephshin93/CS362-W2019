/******************************************************************************
 *       Author: Joseph Shin
 * Date Created: 2019 Mar 2
 *  Description: Unit test for effect of minion card. A random testing 
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
void randomInput(struct cardPlayInput *input) {
    int i;
    
    // random choice
    if (chanced(60)) {
        input->c1 = 0;
        input->c2 = 1;
    } else {
        input->c1 = 1;
        input->c2 = 0;
    }
    input->c3 = floor(Random() * 2);

    // random game state
    struct gameState *state = &input->state;
    randomizeGameState(state);

    // keep player number 2-4
    state->numPlayers = randomRangeVal(2, 3);
    state->whoseTurn = randomRangeVal(0, state->numPlayers);

    // for all, keep hand counts 3-7 (60% of hand count >= 5)
    for (i = 0; i < state->numPlayers; i++) {
        state->handCount[i] = randomRangeVal(3, 5); // 60% chance of hand count >= 5
        state->deckCount[i] = randomRangeVal(4, 10); // keep deck >= 4 to avoid shuffling
        state->discardCount[i] = randomRangeVal(4, 10);
    }

    // hand position
    input->handPos = floor(Random() * state->handCount[state->whoseTurn]);

    // ~90% that card will be played
    state->hand[state->whoseTurn][input->handPos] = minion;
    if (chanced(95)) state->phase = 0;
    if (chanced(95) && state->numActions < 0) state->numActions *= -1;
}


// compute expected state from original state
void testOrcale(struct cardPlayInput *input, struct gameState *expc) {
    struct gameState *orig = &input->state;
    memcpy(expc, orig, sizeof(struct gameState));

    // check if card can be played can be done
    if (expc->phase != ACTION_PHASE || expc->numActions < 1) return;

    const int C1_BONUS = 2;
    int i, j, card, totalCoins = 0;
    int player = expc->whoseTurn;
    
    // check for second choice
    if (input->c2) {
        for (i = 0; i < expc->numPlayers; i++) {
            if (i == player || expc->handCount[i] >= 5) {
                // discard hands of current player and any other player with 5 or more cards
                for (; expc->handCount[i] > 0; expc->handCount[i]--) {
                    expc->discard[i][expc->discardCount[i]++] = expc->hand[i][expc->handCount[i]-1];
                }
                assert(expc->handCount[i] == 0);
   
                // those same people now draw 4 cards from their deck
                int origDeckCount = expc->deckCount[i];
                for (j = 0; j < 4; j++) {
                    expc->hand[i][expc->handCount[i]++] = expc->deck[i][--expc->deckCount[i]];
                }
                assert(expc->handCount[i] == 4);
                assert(expc->deckCount[i] == origDeckCount-4);
            }
        }
    }

    // update coins
    for (i = 0; i < expc->handCount[player]; i++) {
        if (expc->hand[player][i] >= copper && expc->hand[player][i] <= gold) {
            totalCoins += (expc->hand[player][i] - 3); // treasure card - 3 = its value
        }
    }
    expc->coins = totalCoins;

    // check for first choice
    if (input->c1) expc->coins += C1_BONUS;

    // actions - 1 + 1; so don't change

    // TODO: move minion card to played pile?
}


int main(int argc, char const *argv[]) {
    const int NUM_TEST_CASES = 5000, SHOW_FAIL_DETAILS = 1;
    int i, j, passed = 0;
    struct cardPlayInput input;
    struct gameState expected;

    int inputStream = 1;
    long inputSeed = 1981;

    // set up random number generator streams
    SelectStream(inputStream);
    PutSeed(inputSeed);

    // run test cases
    for (i = 0; i < NUM_TEST_CASES; i++) {
        // generate random inputs
        randomInput(&input);

        // generate expected output
        testOrcale(&input, &expected);

        // generate result output
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
    }
    printf("\n");

    printf("%d test cases: %d passed, %d failed\n", NUM_TEST_CASES, passed, NUM_TEST_CASES-passed);

    return 0;
}