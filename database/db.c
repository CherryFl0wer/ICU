#include "db.h"

int path_in_array(person guy, char *path)
{
	int nb = guy.nb_pics - 1;

	while (nb>=0)
	{
		if(strcmp(guy.pics[nb], path))
		{
			return 1; 
		}
		nb--;
	}

	return 0;
}
/*
	while (nb !=0)
	{
		while (*(guy.pics + i) != '|' && *(path+j) != '\0')
		{
			if (!(*(guy.pics + i) == *(path+j)))
			{
				ret = 0;
			}
			else
			{
				ret =1;
			}
			i++;
			j++;
		}
		if (ret == 1 && *(guy.pics + i) == '|' && *(path+j) == '\0')
		{
			return 1;
		}
		while (*(guy.pics + i) != '|')
		{
			i++;
		}
		ret = 0;
		i++;
		j=0;
		nb--;
	}
}
*/


void add_picture(person new,  int nb)
{
	//char pat = 'l';
	char my_path[] = "";
	for (int i =0; i< nb;i++)
	{
	//	char pat;
	//	char *my_path = &pat;		
//		char *my_path = NULL;

		scanf("%s",my_path);

	//	if(path_in_array(new, my_path))
	//	{
	//		printf("Sorry, this picture already exist\n");
	//	}
	//	else
	//	{
			new.pics[i] = my_path;
			new.nb_pics++;
	//	}
	}
//	free(my_path);
}
/*
		char *output = malloc(strlen(new.pics) + strlen(my_path) + 1);

		if(path_in_array(new, my_path))
		{	
			printf("Sorry, this picture already exist\n");
			return 0;	
		}
		else
		{
			//char *output = malloc(strlen(new.pics) + strlen(my_path) + 1);
				//scanf("%s",path);
		//	char *output = malloc(strlen(new.pics) + strlen(my_path) + 1);
		
			strcpy(output, "");
			unsigned long i = 0;
			while(i < strlen(new.pics))
			{
				*(output + i) = *(new.pics + i);
				i++;
			}
//		i++;
			unsigned long j = 0;
			while(j < strlen(my_path))
			{
				*(output + i + j) = *(my_path + j);
				j++;
			}
			*(output + i + j) = '|';
			strcpy(new.pics, output);
			nb--;
		}
	}
		//printf("\npics = %s\n", output);
//		strcpy(my_path, output); //Here we add the new path to the string of path
		//strcpy(new.pics, output);
		//free(output);
*/

void serialization(char name[20], FILE *database) 
{	
	person answer;
	int find = 0;
	while((fread(&answer, sizeof(person), 1, database)) && !find)
	{
		
		if (strcmp(answer.name, name)==0)
		{
			find = 1;
			printf("%s is already in database\n",name);
		}
	}
	if (!find)
	{
		person *new;
		strcpy(*new.name, name); // Ici que le nom est add
		*new.nb_pics = 0;

		int choice;
		printf("Add picture(s) of %s ?\n", name);
		printf("1. YES\n");
		
		scanf("%d", &choice);

		if (choice == 1)
		{
			int choice_nb_pics = 0;
			printf("How many pictures do you want to add ? : ");
			scanf("%d", &choice_nb_pics);
			
			if(choice_nb_pics >= 1)
			{

				int nb = choice_nb_pics;
				add_picture(new, nb);
					/*
				int nb = choice_nb_pics;
				for(int i = 1; i <= nb; i++)
				{
					char pat;

					char *path = &pat;
		
					printf("Path of the picture : ");
					scanf("%s", path);

					add_picture(new, path);
					new.nb_pics++;
				}*/
			}
			else
			{
				fputs("Incorrect option (How many picture(s))\n", stderr);
				exit(-1);
			}	
		}
		else
		{
			fputs("Incorrect option (Add picture(s))\n", stderr);
			exit(-1);
		}
		
//	 	printf("%10s      %10d     %30s \n\n", new.name, new.nb_pics, new.pics);
//	 	fseek(database, 0, SEEK_END);
		fwrite(&new, sizeof(person), 1, database);
		printf("Add %s succeed\n",name);
		
	}
}

static void print(FILE *f)
{
  f = fopen("database.obj", "r");
 // fseek(f, 0, SEEK_SET);

  person a;
  printf("\nPrint database : \n\n");

  while ((!feof(f))&&(fread(&a, sizeof(person), 1, f)))   
		  //for(int i = 0; i < 4; i++)
  {
    printf("%10s      %10d    ", a.name, a.nb_pics);
	
	int nb = a.nb_pics - 1;
	while(nb>=0)
	{
		printf("%s ", a.pics[nb]);
		nb--;
	}
  }
  printf("\n");

  fclose(f);
}

void modify(char oldname[20], char n[20]) //deserialize database
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

void remov(char name[25])
{
  FILE *database, *ndb;
  database = fopen("database.obj", "rb");
  ndb = fopen("temp.obj", "w+b");
  fseek(database, 0, SEEK_SET);
  person answer;
  int found = 0;
  while ((fread(&answer, sizeof(person), 1, database))) 
		  //While we can read a struct
  {
    //i++;
    if (strcmp(name, answer.name) == 0) 
    {
      printf("A record with requested name found and deleted.\n");
      found = 1;
    } 
    else 
    {
      fwrite(&answer, sizeof(person), 1, ndb); 
	  // Writing struct in the new database ndb
    }
  }
  
  if (found == 0) 
  {
    printf("No record(s) found with the requested name: %s\n", name); 
	//Name doesn't exists in database
  }
  fclose(database);
  fclose(ndb);

  remove("database.obj");
  rename("temp.obj", "database.obj");
}

void ergo()
{
	printf("##############   ICU   ##############\n");
	printf("############ Les pilotes ############");
	printf("\n");
	printf("--------- Facial Recognition ---------\n\n");
}

void ManageDatabase()
{
	int choice = 0;

	char maxou[20] = "Maxime";
	char bapt[20] = "Baptiste";
	char coco[20] = "Corentin";
	char adri[20] = "Adrien";
	char name[20];

	while(choice != 6)
	{
		printf("\nChoose an option : \n");

		printf("1 - Initialize with basic person faces\n");
    	printf("2 - Add a person\n");
		printf("3 - Remove a person\n");
 		printf("4 - Modify a person\n");
		printf("5 - Print database\n");
		printf("6 - Quit\n");

		FILE *db;
		
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:{      			
				db = fopen("database.obj","r+b");
        		serialization(maxou,db);
        		serialization(bapt,db);
        		serialization(coco,db);
        		serialization(adri,db);
        		printf("Serialization: ok\n");
				printf("Init database: ok");
        		fclose(db);
        		print(db);
				break;}

			case 2:{ //Add working good
				db = fopen("database.obj","r+b");
				printf("Enter a name : ");
				scanf("%s", name);
				serialization(name,db);
				fclose(db);
				break;}
				
			case 3: {//Remove working
				db = fopen("database.obj","r+b");
				printf("Enter a name : ");
				scanf("%s",name);
				remov(name);
				fclose(db);
				break;}	
	
			case 4:{ // some problem here but it's basically working or not :p
				db = fopen("database.obj","r+b");
				printf("Enter a name to modif : ");
				char namemodif[20];
				scanf("%s",namemodif);
				printf("Enter the new name : ");
				char newname[20];
				scanf("%s",newname);
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

int main(int argc,char **argv)
{
	(void) argc;
	(void) argv;
	int choice;
	ergo();
	FILE *db = fopen("database.obj","a"); 
	// create database if she doesn't exists
	fclose(db);

	printf("Choose an option : \n");
	printf("1 - Manage database\n");

	scanf("%d",&choice);
	if(choice == 1)
	{
		ManageDatabase();
	}

	return 0;
	
}
