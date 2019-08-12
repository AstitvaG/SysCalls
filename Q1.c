// C program to illustrate close system Call 
#include<stdio.h> 
#include <fcntl.h> 
#include <limits.h>
#include <string.h>
#define buff_size 1000000

long long int counter=0,current=0;
int pf=-1;
char a[6];

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

void convert(int curr)
{
  for (int i = 0; i < 5; ++i)
  {
    a[i]=' ';
  }
  a[0]='\r';
  a[5]='%';
  int i=0;
  while(curr)
  {
    char c_temp = (char)(curr%10+48);
    a[3-i]=c_temp;
    i++;
    curr/=10;
  }
}

/*void reverse(int fileIn, int fileOut) {
  char data;
  char x[] = "\r                ";
  if (read(fileIn, &data, 1) == 1) {
    reverse(fileIn, fileOut);
    current++;
    convert((current*100)/counter);
    write(1,&x,strlen(x));   
    write(1,&a,strlen(a)); 
    fflush(stdout);
    write(fileOut, &data, 1);
  }
}*/

void reverse_multiple(int fileIn, int fileOut) {
  char *data = (char *) calloc(buff_size,sizeof(char));
  int temp = read(fileIn, data, buff_size) ;
  if (temp > 0) {
    reverse_multiple(fileIn, fileOut);
    current+=temp;
    int pr = (current*100)/counter;
    if(pf<=pr)
    {
      pf = pr;
      convert(pr);
      write(1,&a,strlen(a)); 
      fflush(stdout);
    }
    data = strrev(data);
    write(fileOut, data, temp);
  }
}

int main(int argc, char* argv[]) {

  char str[100000],str1[100000];
  strcpy(str,argv[1]);
  int init_size = strlen(str);
  char delim[] = "/";

  char *ptr = strtok(str, delim);

  while(ptr != NULL)
  {
    strcpy(str1,ptr);
    ptr = strtok(NULL, delim);
  }

  int dir = mkdir("Assignment",S_IRWXU);

  char str_t[] = "Assignment/";
  strcat(str_t,str1);

  int fileOut = open(str_t, O_WRONLY | O_CREAT, 0600);
  int fileIn = open(argv[1], O_RDONLY);
  
  int fileTemp = open(argv[1], O_RDONLY);
  counter = lseek(fileTemp,0,SEEK_END);
  close(fileTemp);

  if (fileOut<0 || fileIn<0){ 
    perror("c1"); 
    exit(1); 
  }
  write(1,"  0 % completed",sizeof("      completed"));
  reverse_multiple(fileIn, fileOut);
  close(fileIn);
  close(fileOut);
  write(1,"\nDone\n",sizeof("\nDone\n"));
  return 0;
}