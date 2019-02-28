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



// generate random values used to play adventure card
void randomInput(int *handPos, int *c1, int *c2, int *c3, struct gameState *state) {
    // random choice
    *c1 = floor(Random() * 2);
    *c2 = floor(Random() * 2);
    *c3 = floor(Random() * 2);

    // random game state
    randomizeGameState(state);

    // hand position
    *handPos = floor(Random() * state->handCount[state->whoseTurn]);

    // place adventurer card in hand
    // TODO: not random enough
    state->hand[state->whoseTurn][*handPos] = adventurer;
}

// compute expected state from original state
void oracle(struct gameState *orig, struct gameState *expc, long seed) {
    memcpy(expc, orig, sizeof(struct gameState));

    // check if card can be played can be done
    if (expc->phase != ACTION_PHASE || expc->numActions < 1) return;
    
    int i, j, card;
    int player = expc->whoseTurn;
    int origTop = expc->deckCount[player] - 1;
    int found = 0;
    int treasures[2] = {0, 0};

    int newDeck[MAX_DECK];
    int newDeckCount = 0;
    
    
    // add treasures from deck
    while (expc->deckCount[player] > 0 && found < 2) {
        card = expc->deck[player][expc->deckCount[player-1]];
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

        // NOTE: following the code for dominion.c shuffle function
        // sort card in deck to ensure determinism
        qsort((void*)(expc->discard[player]), 
              expc->discardCount[player], 
              sizeof(int), 
              compare);
        // randomly choose each card to get shuffled order
        while (expc->discardCount[player] > 0) {
            card = floor(Random() * expc->discardCount[player]);
            newDeck[newDeckCount++] = expc->discard[player][card];
            for (i = card; i < expc->discardCount[player]-1; i++) {
                expc->discard[player][i] = expc->discard[player][i+1];
            }
            expc->discardCount[player]--;
        }
        
        // add treasures from new deck
        for (i = newDeckCount-1; i >= 0 && found < 2; i--) {
            card = newDeck[i];
            if (card == copper || card == silver || card == gold) {
                treasures[found++] = card;
                for (j = i; j < newDeckCount-1; j++) newDeck[j] = newDeck[j+1];
                newDeckCount--;
            }
        }

        // now, all of deck needs to go into discard and [i+1, newDeckCount] of 
        // newDeck needs to go into the discard pile as well
        if (expc->deckCount[player] + (newDeckCount - i + 1) > MAX_DECK) 
            printf("ERROR: seg fault imminent\n");
        
        while (expc->deckCount[player] > 0 && expc->discardCount[player] < MAX_DECK) {
            expc->discard[player][expc->discardCount[player]++] = expc->deck[player][--expc->deckCount[player]];
        }
        assert(expc->deckCount[player] == 0);
        for (j = i+1; j < newDeckCount && expc->discardCount[player] < MAX_DECK; j++) {
            expc->discard[player][expc->discardCount[player]++] = newDeck[j];
        }

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


    // add found treasures to hand
    for (i = 0; i < found; i++) {
        expc->hand[player][expc->handCount[player]++] = treasures[i];
        expc->coins += treasures[i] - 3; // treasure card - 3 = its coin value
    }
    
}

int main(int argc, char const *argv[]) {
    
    const int NUM_TEST_CASES = 2;
    int i;
    int handPos, c1, c2, c3;
    struct gameState original, expected;

    long seed = 1993;

    for (i = 0; i < NUM_TEST_CASES; i++) {
        randomInput(&handPos, &c1, &c2, &c3, &original);
        oracle(&original, &expected, seed);

        PutSeed(seed);
        playCard(handPos, c1, c2, c3, &original);
        
        compareStates(&expected, &original, 1, 100);
    }
    

    return 0;
}