// C program to illustrate close system Call 
#include<stdio.h> 
#include <fcntl.h> 
#include <limits.h>
#include <string.h>
#define buff_size 1000000

int pf=0,fileIn_original;

char *strrev(char *str)
{
	char *p1, *p2;

	if (! str || ! *str)
		return str;
	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
	{
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}
	return str;
}

void revcheck_multiple(int fileIn) {
	char *data = (char *) calloc(buff_size,sizeof(char));
	int temp = read(fileIn, data, buff_size) ;
	if (temp > 0) {
		if(pf==0)
			revcheck_multiple(fileIn);
		if(pf==-1) return 0;
		data = strrev(data);
		char *data2 = (char *) calloc(buff_size,sizeof(char));
		int temp2 = read(fileIn_original, data2, temp);
		if(strcmp(data,data2)!=0)
			pf = -1;
	}
}

char owner[100]="User has ", perm[100]="read",
txt[]=" permission on ",fil[100] ="newfile",retStr[500]="";

void concat(int j)
{
	memset(retStr, 0, strlen(retStr));
	strcpy(retStr,owner);
	strcat(retStr,perm);
	strcat(retStr,txt);
	strcat(retStr,fil);
	if(j==1) strcat(retStr,": YES\n");
	else strcat(retStr,": NO\n");
!	write(1,retStr,sizeof(retStr));
}

void permissions(char *file,char * strx){
	struct stat st;
	if(stat(file, &st) == 0){
		mode_t permis = st.st_mode;
		strcpy(fil,strx);
		strcpy(owner,"User has ");
		strcpy(perm,"read");
		(permis & S_IRUSR) ? concat(1) : concat(0);
		strcpy(owner,"User has ");
		strcpy(perm,"write");
		(permis & S_IWUSR) ? concat(1) : concat(0);
		strcpy(owner,"User has ");
		strcpy(perm,"execute");
		(permis & S_IXUSR) ? concat(1) : concat(0);
		write(1,"\n",sizeof("\n"));
		strcpy(owner,"Group has ");
		strcpy(perm,"read");
		(permis & S_IRGRP) ? concat(1) : concat(0);
		strcpy(owner,"Group has ");
		strcpy(perm,"write");
		(permis & S_IWGRP) ? concat(1) : concat(0);
		strcpy(owner,"Group has ");
		strcpy(perm,"execute");
		(permis & S_IXGRP) ? concat(1) : concat(0);
		write(1,"\n",sizeof("\n"));
		strcpy(owner,"Others have ");
		strcpy(perm,"read");
		(permis & S_IROTH) ? concat(1) : concat(0);
		strcpy(owner,"Others have ");
		strcpy(perm,"write");
		(permis & S_IWOTH) ? concat(1) : concat(0);
		strcpy(owner,"Others have ");
		strcpy(perm,"execute");
		(permis & S_IXOTH) ? concat(1) : concat(0);
		write(1,"\n",sizeof("\n"));
	}
}

int main(int argc, char* argv[]) 
{

	int fileIn = open(argv[2], O_RDONLY);
	int fileIn_t = open(argv[2], O_RDONLY);
	
	fileIn_original = open(argv[1], O_RDONLY);
	int fileIn_original_t = open(argv[1], O_RDONLY);

	if (fileIn<0 || fileIn_original<0){ 
		perror("c1"); 
		exit(1);
	}

	char str[100] = "Directory is created: ";
	if (!opendir(argv[3]))
	{
		strcat(str,"NO\n");
		// perror("c1");
		write(1,str,sizeof(str));
		fflush(stdout);
		exit(0);
	}
	else
	{
		strcat(str,"YES\n");
		write(1,str,sizeof(str));
		fflush(stdout);
	}

	int size1 = lseek(fileIn_t,0,SEEK_END);
	int size2 = lseek(fileIn_original_t,0,SEEK_END);
	close(fileIn_t);close(fileIn_original_t);

	if(size1!=size2) pf=-1;
	else {write(1,"Checking\r",sizeof("Checking\r"));revcheck_multiple(fileIn);}
	
	close(fileIn);
	strcpy(str,"Whether file contents are reversed in newfile: ");

	if(pf==-1) 
	{
		strcat(str,"NO\n");
		write(1,str,sizeof(str));
		fflush(stdout);
		exit(0);
	}
	else
	{
		strcat(str,"YES\n\n");
		write(1,str,sizeof(str));
		fflush(stdout);
	}


	permissions(argv[1],"New file");
	fflush(stdout);

	permissions(argv[2],"Old file");
	fflush(stdout);

	permissions(argv[3],"Directory");
	fflush(stdout);
}