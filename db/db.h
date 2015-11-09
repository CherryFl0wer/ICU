#ifndef DATABASE_H_
#define DATABASE_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Try to avoid stdbool and use int 0 = false 1 = true 


typedef struct Person 	//Have to implement some caracteritic for each
{ 
	char name[20];	//name of the person
	int nb_pics;	//number of pictures
	char pics[3][50]; //Paths to images
	//long* vect; //Images to vector
} person;

void ManageDatabase();
void serialization(person *new, FILE *database);
void deserialization(char name[20]);
void modify(char name[20], char *n);
void remov(char name[20]);
void print(FILE *f);

#endif
