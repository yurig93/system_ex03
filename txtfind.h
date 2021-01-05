//
// Created by Yuri Grigorian on 05/01/2021.
//

#ifndef SYSTEM_EX03_TXTFIND_H
#define SYSTEM_EX03_TXTFIND_H

#define LEN_LINE 256
#define LEN_WORD 30
#define NUM_LINES 250
#define NUM_ALLOWED_CHAR_PENALTY 1
#define OP_PRINT_CONTAINING_LINES 'a'
#define OP_PRINT_SIMILAR_WORDS 'b'


// There are two function here one check if a string is a substring and the second checks if a word is a substring.

int is_substring(char *str1, char *str2);

int is_substring_by_word(char *str1, char *str2);

int is_similar(char *s, char *t, int iAllowedPenalty);

void print_lines(char *cpLines, int iNumLines, int iLineLen, char *targetStr);

void print_similar_words(char *cpLines, int iNumLines, int iLineLen, char *targetStr, int iAllowedPenalty);

#endif //SYSTEM_EX03_TXTFIND_H
