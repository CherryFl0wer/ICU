#ifndef DATABASE_H_
#define DATABASE_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <libgen.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdbool.h>


typedef struct Person 	
{ 
    char name[20];
    int nb_pics;

} person;

int search_in_database(FILE *db, char *name);
char** get_pict(char *name);
void add_in_folder(char *path,char *name);
void ManageDatabase();
void serialization(person *new, FILE *database);
void deserialization(char *name);
void modify(char *name, char *n);
void remov(char *name);
void print(FILE *f);

#endif
