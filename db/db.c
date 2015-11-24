#include "db.h"

void serialization(person *new, FILE *database) 
{
  person *answer = calloc(1,sizeof(struct Person));
  bool find = false;
  while((fread(answer, sizeof(struct Person), 1, database)) && !find)
  {
    if (strcmp(answer->name, new->name)==0)
    {
      find = true;
      printf("%s is already in database\n",answer->name);
    }
  }
  if (!find)
  {
    printf("How many images ? (max 3)\n");
    int choice = 0;
    if(!scanf("%d",&choice))
      exit(0);
    if (choice > 0)
    {
      int nb = choice;
      char pat;
      char *path = &pat;
      for (int i = 0; i<nb;i++)
      {
        printf("Enter a path: ");
        if(!scanf("%s",path))
          exit(0);
        strcpy(new->pics[i],path);
        new->nb_pics++;
      }
    }
    fwrite(new, sizeof(struct Person), 1, database);
    free(answer);
    printf("Add %s succeed\n",new->name);
  }
}
void print(FILE *f)
{
  f = fopen("database.obj", "r");
  fseek(f, 0, SEEK_CUR);
  person *a = calloc(1,sizeof(struct Person));
  printf("\n");
  printf("Print database : \n\n");
  printf(" Name      Nb of pics           Pics\n\n");
  while ((!feof(f))&&(fread(a, sizeof(struct Person), 1, f))) 
  {
    printf(" %s          %d         ", a->name,a->nb_pics);
    for (int i = 0; i < a->nb_pics;i++)
      printf("%s ",a->pics[i]);
    printf("\n");
  }
  free(a);
  fclose(f);
}
void modify(char oldname[20], char n[20])
{
  FILE *database = fopen("database.obj","r+");
  fseek(database, 0, SEEK_SET);
  person *answer = calloc(1,sizeof(struct Person));
  while(fread(answer, sizeof(struct Person), 1, database))
  {
    if (strcmp(answer->name, oldname)==0)
    {
      person *new = calloc(1,sizeof(struct Person));
      *new = *answer;
      strcpy(new->name,n);
      printf("%s",new->name);
      fseek(database, -sizeof(struct Person), SEEK_CUR);
      fwrite(new, sizeof(struct Person), 1, database);
      free(new);
      printf("Modified with success\n");
    }
  }

  free(answer);
}
void remov(char name[20])
{
  FILE *database, *ndb;
  database = fopen("database.obj", "rb");
  ndb = fopen("temp.obj", "w+b");
  fseek(database, 0, SEEK_SET);
  person *answer = calloc(1,sizeof(struct Person));
  int found = 0;
  while ((fread(answer, sizeof(struct Person), 1, database))) 
  {
    
    if (strcmp(name, answer->name) == 0)
    {
      printf("A record with requested name found and deleted.\n");
      found = 1;
    }
    else
    {
      fwrite(answer, sizeof(struct Person), 1, ndb);
    }
  }

  if (found == 0)
  {
    printf("No record(s) found with the requested name: %s\n", name);
  }

  fclose(database);
  fclose(ndb);
  free(answer);
  remove("database.obj");
  rename("temp.obj", "database.obj");
}
void ergo()
{
  printf("############## ICU ##############\n");
  printf("############ Les pilotes ############");
  printf("\n");
  printf("--------- Facial Recognition ---------\n\n");
}
void ManageDatabase()
{
  FILE *bd = fopen("database.obj","a"); 
  fclose(bd);
  int choice = 0;
  char name[20];
  while(choice != 6)
  {
    printf("\nChoose an option : \n");
    printf("2 - Add a person\n");
    printf("3 - Remove a person\n");
    printf("4 - Modify a person\n");
    printf("5 - Print database\n");
    printf("6 - Quit\n");
    FILE *db;
    if(!scanf("%d",&choice))
      exit(0);

    switch(choice)
    {
      case 2:{ 
               db = fopen("database.obj","r+b");
               printf("Enter a name : ");
	       person *new  = calloc(1,sizeof(struct Person));
               if(!scanf("%s",name))
                 exit(0);
               strcpy(new->name,name);
               serialization(new,db);
  	       free(new);
               fclose(db);
               break;}
      case 3:{ 
               db = fopen("database.obj","r+b");
               printf("Enter a name : ");
               if(!scanf("%s",name))
                 exit(0);

               remov(name);
              // free(new);
               fclose(db);
               break;}
      case 4:{ 
               db = fopen("database.obj","r+b");
               printf("Enter a name to modif : ");
               char namemodif[20];
               if(!scanf("%s",namemodif))
                 exit(0);

               printf("Enter the new name : ");
               char newname[20];
               if(!scanf("%s",newname))
                 exit(0);

               modify(namemodif,newname);
               fclose(db);
               break;}
      case 5:{
             db = fopen("database.obj","r+b");
             print(db);
             break;}
      case 6:
             break;
      default:
             fputs("Incorrect option\n", stderr);
             exit(-1);
             break;
    }
  }
}
