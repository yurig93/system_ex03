//
// Created by Yuri Grigorian on 05/01/2021.
//

#include <stdio.h>
#include <string.h>
#include "txtfind.h"


char *get_address_by_line(char *dpLines, int iLineNum, int iLineLen) {
    return (dpLines + iLineNum * iLineLen);
}

void init_array(char *dpLines, int iNumLine, int iLenLine, char initChar) {
    // Can use memset too.
    for (int i = 0; i < iNumLine; i++) {
        for (int j = 0; j < iLenLine; j++) {
            *(get_address_by_line(dpLines, i, iLenLine) + j) = initChar;
        }
    }
}

char *get_line(char *cpLineBuffer, int iLenLine) {
    return fgets(cpLineBuffer, iLenLine, stdin);
}

int is_substring(char *str1, char *str2) {
    char *cpFoundString = strstr(str1, str2);
    return cpFoundString != NULL ? 1 : 0;
}

int is_substring_by_word(char *str1, char *str2) {
    const char *tokens = " \t\n\r";
    char *word = NULL;
    char *scannedLine = str1;

    word = strtok(scannedLine, tokens);
    while (word != NULL) {
        char *tmpWord = word;
        if (is_similar(tmpWord, str2, 0) > 0) {
            return 1;
        }
        word = strtok(NULL, tokens);
    }
    return 0;
}

int is_similar(char *s, char *t, int n) {
    char *cpSource = s;
    char *cpTarget = t;

    int iCharPenalty = 0;
    while (iCharPenalty <= n && *cpSource != '\0') {
        if (*cpSource != *cpTarget) {
            ++iCharPenalty;
        } else {
            if (*cpTarget != '\0') { ++cpTarget; }
        }
        ++cpSource;
    }

    if (iCharPenalty > n || *cpSource != '\0' || *cpTarget != '\0') {
        return 0;
    }
    return 1;
}

void print_lines(char *dpLines, int iNumLines, int iLenLine, char *targetStr) {
    for (int iNumLine = 0; iNumLine < iNumLines; ++iNumLine) {
        char *scannedLine = get_address_by_line(dpLines, iNumLine, iLenLine);
        if (is_substring(scannedLine, targetStr) > 0) {
            printf("%s", scannedLine);
        }
    }
}

void print_similar_words(char *dpLines, int iNumLines, int iLenLine, char *targetStr, int iAllowedPenalty) {
    const char *tokens = " \t\n\r";
    char *word = NULL;

    for (int iNumLine = 0; iNumLine < iNumLines; ++iNumLine) {
        char *scannedLine = get_address_by_line(dpLines, iNumLine, iLenLine);

        word = strtok(scannedLine, tokens);
        while (word != NULL) {
            char *tmpWord = word;
            if (is_similar(tmpWord, targetStr, iAllowedPenalty) > 0) {
                printf("%s\n", tmpWord);
            }
            word = strtok(NULL, tokens);
        }
    }
}


int main() {
    char lines[NUM_LINES][LEN_LINE];
    char targetWord[LEN_WORD] = {'\0'};
    char targetOperation = '\0';

    init_array((char *) lines, NUM_LINES, LEN_LINE, '\0');

    // Get word and operation
    scanf("%29s %c\n\n", targetWord, &targetOperation);

    int readCount = 0;
    while (get_line(lines[readCount], LEN_LINE) != NULL && readCount < NUM_LINES) {
        if (strcmp(lines[readCount], "\n") == 0) {
            break;
        }
        ++readCount;
    }

    switch (targetOperation) {
        case OP_PRINT_CONTAINING_LINES:
            print_lines((char *) lines, NUM_LINES, LEN_LINE, targetWord);
            break;
        case OP_PRINT_SIMILAR_WORDS:
            print_similar_words((char *) lines, NUM_LINES, LEN_LINE, targetWord, NUM_ALLOWED_CHAR_PENALTY);
            break;
        default:
            printf("Unknown operation %c", targetOperation);
            return 1;
    }

    return 0;
}