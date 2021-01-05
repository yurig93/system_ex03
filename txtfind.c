//
// Created by Yuri Grigorian on 05/01/2021.
//

#include <stdio.h>
#include <string.h>
#include "txtfind.h"

/// Gets a memory address by line num.
/// \param cpLines Pointer to 2D char array.
/// \param iNumLine Number of lines in array.
/// \param iLenLine Length of each line.
/// \return
char *get_address_by_line(char *cpLines, int iLineNum, int iLineLen) {
    return (cpLines + iLineNum * iLineLen);
}

/// Init array with a given char.
/// \param cpLines Pointer to 2D char array.
/// \param iNumLine Number of lines in array.
/// \param iLenLine Length of each line.
/// \param initChar Init char.
void init_array(char *cpLines, int iNumLine, int iLenLine, char initChar) {
    // Can use memset too.
    for (int i = 0; i < iNumLine; i++) {
        for (int j = 0; j < iLenLine; j++) {
            *(get_address_by_line(cpLines, i, iLenLine) + j) = initChar;
        }
    }
}

char *get_line(char *cpLineBuffer, int iLenLine) {
    return fgets(cpLineBuffer, iLenLine, stdin);
}

/// Checks if str2 in str1.
/// \param str1 First string.
/// \param str2 Second String.
/// \return 1 if true else 0.
int is_substring(char *str1, char *str2) {
    char *cpFoundString = strstr(str1, str2);
    return cpFoundString != NULL ? 1 : 0;
}

/// Checks if word str2 in str1.
/// \param str1 First string.
/// \param str2 Second String.
/// \return 1 if true else 0.
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

/// Checks is s is similar to t up to iAllowedPenalty mistakes.
/// \param s Source string.
/// \param t Target string.
/// \param iAllowedPenalty Allowed mistakes in word.
/// \return 1 if yes else 0.
int is_similar(char *s, char *t, int iAllowedPenalty) {
    char *cpSource = s;
    char *cpTarget = t;

    int iCharPenalty = 0;
    while (iCharPenalty <= iAllowedPenalty && *cpSource != '\0') {
        if (*cpSource != *cpTarget) {
            ++iCharPenalty;
        } else {
            if (*cpTarget != '\0') { ++cpTarget; }
        }
        ++cpSource;
    }

    if (iCharPenalty > iAllowedPenalty || *cpSource != '\0' || *cpTarget != '\0') {
        return 0;
    }
    return 1;
}

/// Prints lines containing targetStr.
/// \param cpLines Pointer to 2D char array.
/// \param iNumLine Number of lines in array.
/// \param iLenLine Length of each line.
/// \param targetStr Word to search.
void print_lines(char *cpLines, int iNumLines, int iLenLine, char *targetStr) {
    for (int iNumLine = 0; iNumLine < iNumLines; ++iNumLine) {
        char *scannedLine = get_address_by_line(cpLines, iNumLine, iLenLine);
        unsigned long iScannedLineLen = strlen(scannedLine) + 1;
        char tmp[iScannedLineLen];
        strncpy(tmp, scannedLine, iScannedLineLen);
        if (is_substring_by_word(tmp, targetStr) > 0) {
            printf("%s", scannedLine);
        }
    }
}

/// Prints similar words up to iAllowedPenalty mistakes.
/// \param cpLines Pointer to 2D char array.
/// \param iNumLine Number of lines in array.
/// \param iLenLine Length of each line.
/// \param targetStr Word to search.
/// \param iAllowedPenalty Allowed mistakes.
void print_similar_words(char *cpLines, int iNumLines, int iLenLine, char *targetStr, int iAllowedPenalty) {
    const char *tokens = " \t\n\r";
    char *word = NULL;

    for (int iNumLine = 0; iNumLine < iNumLines; ++iNumLine) {
        char *scannedLine = get_address_by_line(cpLines, iNumLine, iLenLine);

        // Copy string
        unsigned long iScannedLineLen = strlen(scannedLine) + 1;
        char tmp[iScannedLineLen];
        strncpy(tmp, scannedLine, iScannedLineLen);

        word = strtok(tmp, tokens);
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

    // Read text lines
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