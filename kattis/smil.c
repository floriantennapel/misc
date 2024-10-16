#include <stdio.h>
#include <string.h>

int main() 
{
   char line[2050];
   fgets(line, 2050, stdin);

   int i = 0;
   for (char* c = line; *c; c++) {
      if (*c == ':' || *c == ';') {
         if (*(c+1) == ')' || !strncmp("-)", c+1, 2))
            printf("%d\n", i);
      }
      i++;
   }
}
