#include "db.h"

void serialization(char name[20], FILE *database) // Vu qu'il ya eu une modif de la structure Person ici il n'y a que le nom de pris en compte => il faudrait rajouter des argument pour prendre en compte le nb image ect .. mais je suis fatiguer on verra se demain :p
{	
	person answer;
	bool find = false;
	while((fread(&answer, sizeof(person), 1, database)) && !find)
	{
		
		if (strcmp(answer.name, name)==0)
		{
			find = true;
			printf("%s is already in database\n",name);
		}
	}
	if (!find)
	{
		person new;
		strcpy(new.name,name); // Ici que le nom est add
		fwrite(&new, sizeof(person), 1, database);
		printf("Add %s succeed\n",name);
		
	}
}

static void print(FILE *f)
{
  f = fopen("database.obj", "r");
  fseek(f, 0, SEEK_CUR);

  person a;
  printf("\n");
  printf("Print database : \n\n");

  while ((!feof(f))&&(fread(&a, sizeof(person), 1, f)))   //for(int i = 0; i < 4; i++)
  {
    printf("%s\n", a.name);
  }

  fclose(f);
}

void modify(char oldname[20], char n[20]) //deserialize database
{
  FILE *database = fopen("database.obj","r+");
  fseek(database, 0, SEEK_SET);
  person answer;
  int c = 0;

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
  while ((fread(&answer, sizeof(person), 1, database))) //While we can read a struct
  {
    //i++;
    if (strcmp(name, answer.name) == 0) 
    {
      printf("A record with requested name found and deleted.\n");
      found = 1;
    } 
    else 
    {
      fwrite(&answer, sizeof(person), 1, ndb); // Writing struct in the new database ndb
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
				scanf("%s",name);
				serialization(name,db);
				fclose(db);
				break;}
				
			case 3:{ //Remove working
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
			case 5:
				print(db);
				break;

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
	int choice;
	ergo();
	FILE *db = fopen("database.obj","w"); // create database if she doesn't exists
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
