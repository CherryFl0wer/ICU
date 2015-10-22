
#ifndef DATABASE_H_
#define DATABASE_H_
#include <stdio.h>

void serialization(char name[20], FILE *database);
void deserialization(char name[20]);
void modify(char name[20], char *n);
void remov(char name[20]);
static void print(FILE *f);

#endif
