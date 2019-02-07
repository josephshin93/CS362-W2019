/******************************************************************************
 *       Author: Joseph Shin
 * Date Created: 2019 Feb 06
 *  Description: Declarations of helper functions for testing the dominion 
 *               game code.
 *****************************************************************************/

#ifndef DOMINION_TEST_HELPER
#define DOMINION_TEST_HELPER

#include "dominion.h"


/*  Input: pointer to expected game state
 *         pointer to resulting game state
 * Output: integer reflecting deep comparison of two game states 
 * 
 * This function does a deep comparison of the two given game states.
 */
int compareStates(struct gameState *exp, struct gameState *res);


#endif
