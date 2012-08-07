#include "stdio.h"
#include <fcntl.h>

int strrindex(char *string, char letter);

char *reverse(char string[]);

char *strcpy(char *destination, char *source);

char *strncpy(char *destination, const char *source, size_t num);

char * strcat ( char * destination, const char * source );

char * strncat ( char * destination, const char * source, size_t num);

int strcmp(const char *str1, const char *str2);

int strncmp(const char *str1, const char *str2, size_t num);

char *strstr ( char * str1, const char * str2 );

int strstr_nocase(const char * str1, char* str2 );
