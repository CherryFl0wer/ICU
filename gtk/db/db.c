#include "db.h"
#include "../../src/SDLPixel.h"

char** get_pict(char *name)
{
  DIR *d = opendir("imagesreco/");
  struct dirent *dir = malloc(sizeof(struct dirent));
  char** names = (char**) malloc(sizeof(char) * (3*20));
  int i = 0;
  int compt = 0;
  DIR *f = opendir("imagesreco/");
  struct dirent *di = malloc(sizeof(struct dirent));
  while((di = readdir(f)))
  {
    compt++;
  }
  while((dir = readdir(d)))
  {
    if (!(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")))
    {
      char *n = malloc(sizeof(char*));
      if(dir->d_name[0] == name[0])
      {
        for (int j = 0; dir->d_name[j] != '1';j++)
        {
          n[j]=dir->d_name[j];
        }
      }
      if (strcmp(n,name) == 0)
      {
        char *str3 = (char *) malloc(1 + strlen(dir->d_name) +  strlen("imagesreco/"));
        strcpy(str3,"imagesreco/");
        strcat(str3,dir->d_name);
        names[i] = str3;
        i++;
      }
    }
  }
  closedir(d);
  closedir(f);
  return names;
}

void add_in_folder(char *path,char *name)
{
  char *way = "imagesreco/";
  const char *a = path;
  int nb = 0;
  int nb2 = 0;
  DIR *d = opendir("imagesreco/");
  struct dirent *dir = malloc(sizeof(struct dirent));
  while((dir = readdir(d)))
  {
    if (!(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")))
    {
      char *n = malloc(sizeof(char*));
      if(dir->d_name[0] == name[0])
      {
        for (int j = 0; dir->d_name[j] != '1';j++)
        {
          n[j]=dir->d_name[j];
          nb2 = j;
        }
        n[nb2+1] = '\0';
      }
      if (strcmp(n,name) == 0)
      {
        nb++;
      }
    }
  }
  closedir(d);
  for (int i=0;i<=nb;i++)
  {  
    strcat(name,"1");
  }
  strcat(name,".jpeg");
  char *str3 = (char *) malloc(1 + strlen(way) +  strlen(name) );
  strcpy(str3, way);
  strcat(str3, name);
  rename(a,str3);
}

void serialization(person *new)
{

  FILE *data = fopen("database.obj","rb+");
  person *answer = calloc(1,sizeof(struct Person));
  char *name_copy = malloc(sizeof(char*));
  strcpy(name_copy,new->name);
  bool find = false;
  while((fread(answer, sizeof(struct Person), 1, data)) && !find)
  {
    if (strcmp(answer->name, new->name)==0)
    {
      find = true;
      printf("%s is already in database\n",answer->name);
    }
  }
  if (!find)
  {
    printf("How many images ?  (Necessarily 3)\n");
    int choice = 0;
    if(!scanf("%d",&choice))
      exit(0);
    int nb1 = choice;
    for (int p = 0;p<nb1;p++)
    {
      printf("Enter the path to picture : \n");
      char pat;
      char *path = &pat;
      if(!scanf("%s",path))
        exit(0);
      strcpy(new->name,name_copy);
      add_in_folder(path,new->name);
    }
    new->nb_pics = 0;
    new->nb_pics = nb1;
    strcpy(new->name,name_copy);
    printf("avtn");
    fwrite(new, sizeof(struct Person), 1, data);
    printf("apres");
  }
  fclose(data);
  printf("Add %s succeed\n",new->name);
}
void print(FILE *f)
{
  int indexer = 0;
  f = fopen("database.obj", "r");
  fseek(f, 0, SEEK_CUR);
  person *a = calloc(1,sizeof(struct Person));
  printf("\n");
  printf("Print database : \n\n");
  printf("  Name                   Nb of pics\n\n");
  while ((!feof(f))&&(fread(a, sizeof(struct Person), 1, f)))
  {
    indexer++;
    printf("%d. %s",indexer, a->name);
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
  person *answer = calloc(1,sizeof(struct Person));
  bool find = false;
  while(fread(answer, sizeof(struct Person), 1, database))
  {
    if (strcmp(answer->name, oldname)==0)
    {
      find = true;
      person *new = calloc(1,sizeof(struct Person));
      *new = *answer;
      strcpy(new->name,n);
      fseek(database, -sizeof(struct Person), SEEK_CUR);
      fwrite(new, sizeof(struct Person), 1, database);
      free(new);
      printf("Modified with success\n");
    }
  }
  if (find)
  {
    DIR *d = opendir("imagesreco/");
    struct dirent *dir = malloc(sizeof(struct dirent));
    // char** names = (char**) malloc(sizeof(char) * (3*20));
    int i = 0;
    int compt = 0;
    DIR *f = opendir("imagesreco/");
    struct dirent *di = malloc(sizeof(struct dirent));
    while((di = readdir(f)))
    {
      compt++;
    }
    while((dir = readdir(d)))
    {
      if (!(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")))
      {
        char *na = malloc(sizeof(char*));
        char *n2 = malloc(sizeof(char*));
        strcpy(n2,n);
        if(dir->d_name[0] == oldname[0])
        {
          i=0;
          for (int j = 0; dir->d_name[j] != '1';j++)
          {
            na[j]=dir->d_name[j];
            i=j;
          }
          i++;
          while(dir->d_name[i] == '1')
          {
            strcat(n2,"1");
            i++;
          }
        }
        if (strcmp(na,oldname) == 0)
        {
          char *str3 = (char *) malloc(1 + strlen(n2) +  strlen("imagesreco/"));
          char *str4 = (char *) malloc(1 + strlen(dir->d_name) +  strlen("imagesreco/"));
          strcpy(str4,"imagesreco/");
          strcat(str4,dir->d_name);
          strcpy(str3,"imagesreco/");
          strcat(n2,".jpeg");
          strcat(str3,n2);
          rename(str4,str3);
        }
      }
    }
    closedir(d);
  }
  free(answer);
}
void remov(char *name)
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
      DIR *d = opendir("imagesreco/");
      struct dirent *dir = malloc(sizeof(struct dirent));
      while((dir = readdir(d)))
      {
        if (!(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")))
        {
          char *na = malloc(sizeof(char*));
          if(dir->d_name[0] == name[0])
          {
            for (int j = 0; dir->d_name[j] != '1';j++)
            {
              na[j]=dir->d_name[j];
            } 
          }
          if (strcmp(na,name) == 0)
          {
            char *str3 = (char *) malloc(1 + strlen(dir->d_name) +  strlen("imagesreco/"));
            strcpy(str3,"imagesreco/");
            strcat(str3,dir->d_name);
            remove(str3); 
          }
        }
      }
      closedir(d);
    }
    else
    {
      fwrite(answer, sizeof(struct Person), 1, ndb);
    }
  }
  //free(answer);
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

int search_in_database(FILE *db, char *name)
{
  db = fopen("database.obj", "r");
  fseek(db, 0, SEEK_CUR);
  person *a = calloc(1,sizeof(struct Person));
  while ((!feof(db))&&(fread(a, sizeof(struct Person), 1, db)))
  {
    if (strcmp(name, a->name) == 0)
    {
      return 1;
    }
  }
  return 0;
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
    printf("5 - Show images of a person\n");
    printf("6 - Quit\n");
    FILE *db;
    if(!scanf("%d",&choice))
      exit(0);
    switch(choice)
    {
      case 1:{
              // db = fopen("database.obj","rb+");
               printf("Enter a name : ");
               person *new = calloc(1,sizeof(struct Person));
               char *name = malloc(sizeof(char*));
               if(!scanf("%s",name))
                 exit(0);
               strcpy(new->name,name);
               //free(name);
               serialization(new);
               //free(new);
              // fclose(db);
               break;}
      case 2:{
               db = fopen("database.obj","r+b");
               printf("Enter a name : ");
               char *name = malloc(sizeof(char*));
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
      case 5:{
               printf("Enter a name : ");
               char *name = malloc(sizeof(char*));
               if(!scanf("%s",name))
                 exit(0);
               db = fopen("database.obj","r+b");
               if (!search_in_database(db,name))
               {
                  printf("No record found");
               }
               else
               {
                 printf("%s",name);
                 char **ways = get_pict(name);
                 for(int e = 0; e<3;e++)
                 {
                   //printf("%s",ways[e]);
                   SDL_Surface *im = loadimg(ways[e]);
                   displayImg(im);
                   SDL_FreeSurface(im);
                 }
               }
               break;
             }
      case 6:
             exit(1);
             break;
      default:
             fputs("Incorrect option\n", stderr);
             exit(-1);
             break;
    }
  }
}
