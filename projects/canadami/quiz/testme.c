#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	char z = ' ';
	//all ASCII values c could be
	int a [9] = {
			91,   // '['
			40,   // '('
			123,  // '{'
			32,   // ' '
			97,   // 'a'
			120,  // 'x'
			125,  // '}'
			41,   // ')'
			93    // ']'
	};	

	//get random value between 0 and 8
	int x = rand() % 9;
	z = a[x];	
	
    return z;
}

char *inputString()
{
	//create string to return
	char *s = malloc(sizeof(char) * 6);

	//terminate string with NULL
	s[5] = '\0';

	//all possible letters of s
	char a [5] = "erst";

	int i, x;
	//create random string from possible letters in s
	for(i = 0; i < 5; i++){
		x = rand() % 5;
		s[i] = a[x];
	}
	
    return s;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error\n");
	  free(s);				//free dynamically allocated s before exit
      exit(200);
    }
	free(s);				//free dynamically allocatd s for each iteration
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
