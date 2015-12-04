#include "db.h"

void serialization(person *new, FILE *database) 
{
  person *answer = malloc(sizeof(new));
  answer->name = malloc(sizeof(new->name));
  answer->nb_pics = 0;
  printf("On init");
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
    //Here we add image in a folder. Coming soon Inshallah
    new->nb_pics = choice;
    fwrite(new, sizeof(struct Person), 1, database);
  }
  free(answer);
  printf("Add %s succeed\n",new->name);
}

void print(FILE *f)
{
  int indexer = 0;
  f = fopen("database.obj", "r");
  fseek(f, 0, SEEK_CUR);
  person *a = malloc(sizeof(struct Person));
  a->name = malloc(sizeof(char*));
  a->nb_pics = 0;
  printf("\n");
  printf("Print database : \n\n");
  printf("      Name              Nb of pics\n\n");
  while ((!feof(f))&&(fread(a, sizeof(struct Person), 1, f))) 
  {
    indexer++;
    printf("%d.  %s",indexer, a->name);
    for (int i = (25-strlen(a->name)); i>0;i--)
      printf(" ");
    printf("%d",a->nb_pics);
    printf("\n");
  }
  printf("\n");
  free(a);
  fclose(f);
}
void modify(char *oldname, char *n)
{
  FILE *database = fopen("database.obj","r+");
  fseek(database, 0, SEEK_SET);
  person *answer = malloc(sizeof(struct Person));
  answer->name = malloc(sizeof(char*));
  answer->nb_pics = 0;
  while(fread(answer, sizeof(struct Person), 1, database))
  {
    if (strcmp(answer->name, oldname)==0)
    {
      person *new = malloc(sizeof(struct Person));
      new->name = malloc(sizeof(char*));
      new->nb_pics = 0;
      *new = *answer;
      strcpy(new->name,n);
      fseek(database, -sizeof(struct Person), SEEK_CUR);
      fwrite(new, sizeof(struct Person), 1, database);
      free(new);
      printf("Modified with success\n");
    }
  }
  free(answer);
}
void remov(char *name)
{
  FILE *database, *ndb;
  database = fopen("database.obj", "rb");
  ndb = fopen("temp.obj", "w+b");
  fseek(database, 0, SEEK_SET);
  person *answer = malloc(sizeof(struct Person));
  answer->name = malloc(sizeof(char*));
  answer->nb_pics = 0;
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
  FILE *bd = fopen("database.obj","a"); //create db if it doesn't exist 
  fclose(bd);
  int choice = 0;
  while(choice != 5)
  {
    printf("\nChoose an option : \n\n");
    printf("1 - Add a person\n");
    printf("2 - Remove a person\n");
    printf("3 - Modify a person\n");
    printf("4 - Print database\n");
    printf("5 - Quit\n");
    FILE *db;
    if(!scanf("%d",&choice))
      exit(0);

    switch(choice)
    {
      case 1:{ 
               db = fopen("database.obj","r+b");
               printf("Enter a name : ");
	           person *new  = malloc(sizeof(struct Person));
               char *name = malloc(sizeof(char*));
               if(!scanf("%s",name))
                 exit(0);
               printf("name dans name");
               new->name = malloc(sizeof(char*));
               new->nb_pics = 0;
               strcpy(new->name,name);
               //new->name = name
               printf("free");
               free(name);
               serialization(new,db);
  	           free(new);
               fclose(db);
               break;}
      case 2:{ 
               db = fopen("database.obj","r+b");
               printf("Enter a name : ");
               char *name = calloc(1,sizeof(char*));
               if(!scanf("%s",name))
                 exit(0);

               remov(name);
               free(name);
               fclose(db);
               break;}
      case 3:{ 
               db = fopen("database.obj","r+b");
               printf("Enter a name to modif : ");
               char *namemodif = calloc(1,sizeof(char*));
               if(!scanf("%s",namemodif))
                 exit(0);

               printf("Enter the new name : ");
               char *newname = calloc(1,sizeof(char*));
               if(!scanf("%s",newname))
                 exit(0);

               modify(namemodif,newname);
               free(namemodif);
               free(newname);
               fclose(db);
               break;}
      case 4:{
             db = fopen("database.obj","r+b");
             print(db);
             break;}
      case 5:
             break;
      default:
             fputs("Incorrect option\n", stderr);
             exit(-1);
             break;
    }
  }
}
