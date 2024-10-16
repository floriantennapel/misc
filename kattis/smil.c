#include <stdio.h>
#include <string.h>

int main() 
{
   char line[2050];
   fgets(line, 2050, stdin);

   int i = 0;
   for (char* l = line; *l; l++) {
      if (!strncmp(":)", l, 2) || !strncmp(";)", l, 2) || !strncmp(":-)", l, 3) || !strncmp(";-)", l, 3))
         printf("%d\n", i);
      i++;
   }
}
