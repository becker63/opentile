/* C uses "", C++ uses <> */
#include "string.h" /* C++: #include<cstring> */
#include "stdio.h" /* C++: #include<cstdio> */

/* don't do "int function(void)", do "int function()" instead */
int main()
{
  char *text = "Hello World."; /* string length 12, array size 13 */

  /* size of these has to accomodate the terminating null */
  char one[6];
  char two[3];
  char three[6];

  /* copy two characters, starting at index 5 */
  strncpy(two, &text[5], 2);

  /* for three, we don't have to do &text[0], because it is at the beginning of the string */
  strncpy(three, text, 5);

  /* we can do strcpy if we're at the end of the string.  It will stop when it hits '\0' */
  strcpy(one, &text[7]);

  /* note that we still have to null-terminate the strings when we use strncpy */
  two[2] = '\0';
  three[5] = '\0';

  /* but we don't have to null-terminate when we use strcpy */
  /* so we can comment this out: one[5] = '\0'; */

  printf("%s\n", one);
  printf("%s\n", two);
  printf("%s\n", three);

  return 0; /* returns 0, since no errors occurred */
}