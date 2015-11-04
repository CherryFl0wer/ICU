#include "db.h"

void serialization(person new, FILE *database) 
{
  person answer;
  bool find = false;
  while((fread(&answer, sizeof(person), 1, database)) && !find)
  {
    if (strcmp(answer.name, new.name)==0)
    {
      find = true;
      printf("%s is already in database\n",answer.name);
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
        strcpy(new.pics[i],path);
        new.nb_pics++;
      }
    }
    fwrite(&new, sizeof(person), 1, database);
    printf("Add %s succeed\n",new.name);
  }
}
void print(FILE *f)
{
  f = fopen("database.obj", "r");
  fseek(f, 0, SEEK_CUR);
  person a;
  printf("\n");
  printf("Print database : \n\n");
  printf(" Name      Nb of pics           Pics\n\n");
  while ((!feof(f))&&(fread(&a, sizeof(person), 1, f))) 
  {
    printf(" %s          %d         ", a.name,a.nb_pics);
    for (int i = 0; i < a.nb_pics;i++)
      printf("%s ",a.pics[i]);
    printf("\n");
  }
  fclose(f);
}
void modify(char oldname[20], char n[20])
{
  FILE *database = fopen("database.obj","r+");
  fseek(database, 0, SEEK_SET);
  person answer;
  while(fread(&answer, sizeof(person), 1, database))
  {
    if (strcmp(answer.name, oldname)==0)
    {
      fseek(database, -sizeof(person), SEEK_CUR);
      person modif;
      strcpy(modif.name,n);

      fwrite(&modif, sizeof(person), 1, database);
      printf("Modified with success\n");
    }
  }
}
void remov(char name[20])
{
  FILE *database, *ndb;
  database = fopen("database.obj", "rb");
  ndb = fopen("temp.obj", "w+b");
  fseek(database, 0, SEEK_SET);
  person answer;
  int found = 0;
  while ((fread(&answer, sizeof(person), 1, database))) 
  {
    
    if (strcmp(name, answer.name) == 0)
    {
      printf("A record with requested name found and deleted.\n");
      found = 1;
    }
    else
    {
      fwrite(&answer, sizeof(person), 1, ndb);
    }
  }
  if (found == 0)
  {
    printf("No record(s) found with the requested name: %s\n", name); //Name doesn't exists in database
  }
  fclose(database);
  fclose(ndb);
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
  FILE *bd = fopen("database.obj","a"); // create database if she doesn't exists
  fclose(bd);

  int choice = 0;
  /*
  char maxou[20] = "Maxime";
  char bapt[20] = "Baptiste";
  char coco[20] = "Corentin";
  char adri[20] = "Adrien"; */
  //  char name[20];
  person new;
  char name[20];
  while(choice != 6)
  {
    printf("\nChoose an option : \n");
    //printf("1 - Initialize with basic person faces\n");
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
               if(!scanf("%s",name))
                 exit(0);
               strcpy(new.name,name);
               serialization(new,db);
               fclose(db);
               break;}
      case 3:{ 
               db = fopen("database.obj","r+b");
               printf("Enter a name : ");
               if(!scanf("%s",name))
                 exit(0);

               remov(name);
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
