#pragma once

// Macro/Constant defines
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define NULL 0L

// String conversion
double 			atof(const char *str);
int				atoi(const char *str);
long int			atol(const char *str);
double 			strtod(const char *str, char **endptr);
long int 		strtol(const char *str, char **endptr, int base);
unsigned int 	strtoul(const char *str, char **endptr, int base);

// Pseudo-random sequence generation

// Dynamic memory management
void 				*calloc(size_t n, size_t size);
void 				free(void *ptr);
void 				*malloc(size_t size);
void 				*realloc(void *ptr, size_t size);

// Environment

// Searching and sorting

// Integer arithmetics

// Multibyte characters

// Multibyte strings
