#ifndef DATABASE_H_
#define DATABASE_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Try to avoid stdbool and use int 0 = false 1 = true 

void serialization(char name[20], FILE *database);
void deserialization(char name[20]);
void modify(char name[20], char *n);
void remov(char name[20]);
static void print(FILE *f);

#endif
