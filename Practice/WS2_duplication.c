/* For this exercise you are required to complete the string_dupe() 
   function call such that a passed string s as input is copied into
   a new string str and returned. 
   
   Chitrarth Lav, 27 July 2017 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define NULL_BYTE '\0'

char* string_dupe(const char* s)
{
    // (0) validate input
    if (s == NULL) {
        printf("error string_dupe: input ptr is NULL.\n");
        exit(EXIT_FAILURE);
    }

    // (1) determine length
    int stringLength = 0;
    while (s[stringLength] != NULL_BYTE) {
        stringLength++;
    }

    // (2) allocate len + one extra for the 0 byte
    char * newStr = (char*)malloc(sizeof(char)*(stringLength+1));

    // (3) copy data
    int i=0;
    for (i=0; i<stringLength; i++) {
        newStr[i] = s[i];
    }

    // (4) terminate the new string with 0
    newStr[stringLength] = NULL_BYTE;

    return newStr;
}

int main(int argc, char const* argv[])
{
    char* str = string_dupe("test 1234");

    int rcmp = strcmp(str, "test 1234");
    if (rcmp != 0) {
        printf("strings are not equal!\n");
        exit(EXIT_FAILURE);
    }
    else {
        printf("string copy ok!\n");
    }

    free(str);
    return 0;
}
