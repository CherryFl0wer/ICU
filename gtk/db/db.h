#ifndef DATABASE_H_
#define DATABASE_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Try to avoid stdbool and use int 0 = false 1 = true 


typedef struct Person 	//Have to implement some caracteritic for each
{ 
	 char name[20];
    int nb_pics;
} person;

char** get_pict(char *name);
void add_in_folder(char *path);
void ManageDatabase();
void serialization(person *new, FILE *database);
void deserialization(char *name);
void modify(char *name, char *n);
void remov(char *name);
void print(FILE *f);

#endif
