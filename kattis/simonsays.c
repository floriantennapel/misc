#include <stdio.h>
#include <string.h>

int main()
{
   int n;
   scanf("%d\n", &n);

   char buf[102];
   for (int i = 0; i < n; i++) {
      fgets(buf, 102, stdin);
      if (!strncmp("Simon says", buf, 10)) {
         printf("%s", buf+10);
      }
   }
}
