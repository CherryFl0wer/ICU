#include <dirent.h>
#include "db.h"


int number_of_file(char *directory)
{
  int nb_file = 0;
  DIR * rep = opendir(directory);

  if(rep != NULL)
  {
    struct dirent * ent;

    while ((ent = readdir(rep)) != NULL)
    {
      if((strcmp(".", ent->d_name)) && (strcmp("..", 
              ent->d_name)))
      {
        nb_file++;
      }
    }
    closedir(rep);
  }
  return nb_file;
}

char* concat_string(char *str1, char *str2)
{
  char *output = malloc(strlen(str1) + strlen(str2) + 1);

  unsigned long i = 0;

  while(i < strlen(str1))
  {
    output[i] = str1[i];
    i++;
  }
  output[i] = '/';
  i++;
  unsigned long j = 0;

  while(j < strlen(str2))
  {
    output[i + j] = str2[j];
    j++;
  }

  return output;	
  free(output);
}

void search_dir(char *directory,FILE *db)
{
  DIR * rep = opendir(directory); 
  db = fopen("database.obj","r+b");
  if (rep != NULL) 
  { 
    struct dirent * ent; 

    while ((ent = readdir(rep)) != NULL) 
    { 
      if((strcmp(".", ent->d_name)) && (strcmp("..", 
              ent->d_name)))
      {
        person my_guy;
        strcpy(my_guy.name, ent->d_name);
        printf("\n%s\t", my_guy.name);

        my_guy.nb_pics = number_of_file(concat_string
            (directory, my_guy.name));
        printf("%d", my_guy.nb_pics);
        fwrite(&my_guy, sizeof(person), 1, db);

      }
    } 

    closedir(rep); 
  } 

}

/*int main (int argc, char *argv[])
{
  argc = 0;
  argv = NULL;
  //search_dir("my_dir");

  return 0;
}*/
