/*
 ============================================================================
 Name        : countpermissions.c
 Author      : sujay
 Version     :
 Copyright   : Your copyright notice
 Description : count the permissions
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>


#include<string.h>
#include<dirent.h>

#include<ctype.h>

struct node
{
   char val[256];
   long int count;
   struct node *lchild;
   struct node *rchild;
};
struct node *root = NULL;


const char inputpath[] = "C:/Users/sujay/Desktop/project/input/";
const char outputfilefullpath[] = "C:/Users/sujay/Desktop/project/output/count.txt";
const char permissionsearchkey[] = "uses-permission: name=";
const size_t searchkeylength=strlen(permissionsearchkey);

void substring(char s[], char sub[], int p, int l);
void touppercase(char * s) ;

int main(void) {

	struct dirent *direntp;
	DIR *folder;
	FILE *inputfile;
	FILE *outfile;

	folder = opendir(inputpath);

	outfile= fopen(outputfilefullpath,"w");
	printf( "size = %u\n", searchkeylength);

	while ((direntp = readdir(folder)) != NULL)
	{
		if ((strcmp(direntp->d_name ,".")==0)||(strcmp(direntp->d_name, "..")==0))
			continue;
		char inputfilepath[500];
		//= malloc(500 * sizeof(char));
		//memset(inputfilepath,'\0',500);
		strcpy(inputfilepath,inputpath);

		strcat(inputfilepath, direntp->d_name);

		printf("file : %s\n",inputfilepath);
		inputfile=fopen(inputfilepath,"r");
		if(inputfile == NULL){
			printf("Could not open the file: %s\n",inputfilepath);
			exit(0);
		}

		char * line = NULL;
		size_t len = 0; ssize_t read;

		puts("---------");
		while ((read = getline(&line, &len, inputfile)) != -1) {
			//printf("Retrieved line of length %d:\t%s", read, line);

			char *permissionline = strstr(line, permissionsearchkey);

			if(permissionline){
				printf(permissionline);
				char permissionname[250];
				substring(permissionline, permissionname, searchkeylength+1,250);
				touppercase(permissionname);
				printf("permission name: %s",permissionname);

				struct node *treenode = NULL;


				treenode = (struct node*)calloc(1,sizeof(struct node));
				treenode->lchild = NULL;
				treenode->rchild = NULL;
				treenode->count = 1;
				strcpy(treenode->val,permissionname);

				if(root == NULL){
					root = treenode;
				}
				else{
					//insert(root,treenode);
					}
			}
		}
		puts("---------");

	}

	closedir(folder);
	return EXIT_SUCCESS;
}


void substring(char s[], char sub[], int p, int l) {
   int c = 0;

   while (c < l) {
      sub[c] = s[p+c-1];
      c++;
   }
   sub[c] = '\0';
}

void touppercase(char * temp) {
  char * name;
  name = strtok(temp,":");

  // Convert to upper case
  char *s = name;
  while (*s) {
    *s = toupper((unsigned char) *s);
    s++;
  }

}
