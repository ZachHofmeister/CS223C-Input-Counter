#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAX_WORD_LEN 25

int words[MAX_WORD_LEN];
char wordbuf[50];
int wordIndex = 0;

void addWord() {
    ++words[wordIndex];
    wordbuf[0] = wordbuf[wordIndex];
    wordIndex = 0;
}

void countWords() {
    long newChar, newLine, newWord;
    int c, state = OUT;
    newChar = newLine = newWord = 0;
    memset(words, 0, sizeof(words));

    //Used to store the current word
        //Clear the current word buffer

    while ((c=getchar()) != EOF) {
        ++newChar;
        if (isalpha(c) || c == '-') wordbuf[wordIndex++] = c;

        if (c == '\n') ++newLine;

        if (isspace(c)) state = OUT;
        else if (state == OUT) {
            state = IN;
            if (newWord > 0) addWord();
            ++newWord;
        }
    }

    if (wordIndex > 0) {
        ++wordIndex;
        addWord();
    }

    printf("%ld chars, %ld words, and %ld lines.\n", newChar, newWord, newLine);
}

void printHistVertical() {
    //Find the length of word that is most common
    int max = 1; //Tracks the index/word length that is the most common
    for (int i = 1; i < MAX_WORD_LEN; ++i) {
        if (words[i] > words[max]) {
            max = i;
        }
    } //words[max] is the largest amount of words of any length
    printf("%d letter words are the most common (%d).\n", max, words[max]);

    printf("=========================================================================================================================\n");
    for (int j = 1; j < MAX_WORD_LEN; ++j) { //x direction of histogram for header
        printf(" %3d:", j);
    }        
    printf("\n=========================================================================================================================\n");

    for (int i = 0; i < words[max]; ++i) { //y direction of histogram
        if (i % 5 == 0 && i != 0) printf("-------------------------------------------------------------------------------------------------------------------------\n");
        for (int j = 1; j < MAX_WORD_LEN; ++j) { //x direction of histogram for body
            if (words[j] > i) printf(" %4c", '*');
            else printf(" %4c", '\'');
        }
        printf("\n");
    }
}

int main(int argc, const char * argv[]) {
    countWords();
    printHistVertical();
    // for (int i = 0; i < MAX_WORD_LEN; ++i) printf("There are %d %d-letter words.\n", words[i], i);
    // return 0;
}
//TODO histogram
