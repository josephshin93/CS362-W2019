#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

// return random integer within range [lowerLimit, upperLimit]
// random number generator should be seeded before this -> run srand()
int randInt(int lowerLimit, int upperLimit) {
  return (rand() % (upperLimit - lowerLimit + 1)) + lowerLimit;
}

// shuffling an array based on the fisher-yates technqiue
// based on pseudo-code from: https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
void fyShuffle(int *arr, int len) {
  int i, j, temp;
  for (i = 0; i < len-1; i++) {
    j = randInt(i, len-1);
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
}

char inputChar()
{
    char *choices = "[({ ax})]";
    int index = randInt(0, strlen(choices)-1);
    // printf("index = %d\n", index);
    return choices[index];
}

char *inputString()
{
    int i;
    char *word = "reset";
    int len = strlen(word);

    int *indices = malloc(sizeof(int) * len);
    for (i = 0; i < len; i++) indices[i] = i;

    char *shuffledWord = malloc(sizeof(char) * len+1);
    memset(shuffledWord, 0, len+1);

    fyShuffle(indices, len);

    for (i = 0; i < len; i++) shuffledWord[i] = word[indices[i]];
    // printf("shuffled word = \"%s\"\n", shuffledWord);

    free(indices);
    
    return shuffledWord;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }

    free(s);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
