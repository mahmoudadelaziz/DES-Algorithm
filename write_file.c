#include <stdio.h>

char * write_file(FILE *fp, char *content)
{
   fp = fopen(".test.txt", "w+");
   fprintf(fp, content);
   fputs(content, fp);
   fclose(fp);
}

int main()
{
   
   printf("What do you want to write?\n");
   char * str;
   scanf("%s", str);
   printf(str);
   write_file(fopen("./newTest.txt", "w+"), str);
}