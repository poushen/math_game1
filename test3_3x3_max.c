// C program to print all permutations with duplicates allowed
#include <stdio.h>
#include <string.h>
#include <time.h>

/*
  A simple math game
   ?  ?  ? | 9   (A1)
   ?  ?  ? | 16   (A2)
   ?  ?  ? | 20   (A3)
  ---------+
  14 18 13 
  
  B1 B2 B3
  
  This is a 3 x 3 matrix, permute from 1 to 9.
  We know each row count (list on the righ side of each row) and column count (list under each column).
  The question is what is the ? number are? 
*/

typedef unsigned char BYTE;

#define TOTAL_TRIES 362		// 9! / 1000, that's the times we need to try
#define A1 11					// sum of row 1
#define A2 18					// sum of row 2
#define A3 16					// sum of row 3

#define B1 11					// sum of column 1
#define B2 16					// sum of column 2
#define B3 18					// sum of column 3


int match_number = 0;

// print progress
void print_progress(void)
{
	static int cumulate = 0;
	cumulate++;
	
	printf("- %.1f%% -\r", (float)cumulate/TOTAL_TRIES * 100);
}

// print out whole array
void print_array(BYTE* array, int len)
{
	printf("%2d %2d %2d \n", array[0], array[1], array[2]);
	printf("%2d %2d %2d \n", array[3], array[4], array[5]);
	printf("%2d %2d %2d \n", array[6], array[7], array[8]);
	printf("----------   \n\n");
}

//function to convert string to byte array
void string2ByteArray(char* input, BYTE* output)
{
    int loop;
    int i;

    loop = 0;
    i = 0;

    while(input[loop] != '\0')
    {
        output[i++] = input[loop++] - 64;
    }
}

/* Function to swap values at two pointers */
void swap(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/* Function to print permutations of string
This function takes three parameters:
1. String
2. Starting index of the string
3. Ending index of the string. */
void permute(char *a, int l, int r)
{
int i;
if (l == r)
{
	static int index = 0;
	index++;
	if (index >= 1000) index = 0;
	// if (index == 0) print_progress();	// print search progress every 100 tries.
	
    // printf("%s\n", a);
    int len = strlen(a);
    BYTE arr[len];

    //converting string to BYTE[]
    string2ByteArray(a, arr);

	
	int a1, a2, a3, b1, b2, b3;
	a1 = arr[0] + arr[1] + arr[2];
	a2 = arr[3] + arr[4] + arr[5];
	a3 = arr[6] + arr[7] + arr[8];
	b1 = arr[0] + arr[3] + arr[6];
	b2 = arr[1] + arr[4] + arr[7];
	b3 = arr[2] + arr[5] + arr[8];
	printf("%d,%d,%d,%d,%d,%d\n",a1,a2,a3,b1,b2,b3);
}
else
{
    for (i = l; i <= r; i++)
    {
        swap((a+l), (a+i));
        permute(a, l+1, r);
        swap((a+l), (a+i)); //backtrack
    }
}
}

/* Driver program to test above functions */
int main()
{
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	
	// map A to 1, B to 2, C to 3, ...
	// just list what we want to permute
	//
	// A B C D E F G H I  J  K  L  M  N  O  P
	// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
	//

    	char str[] = "ABCDEFGHI";
    	int n = strlen(str);
    	permute(str, 0, n-1);
	
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("It took %.2f seconds, find %d matchs \n", cpu_time_used, match_number);
    return 0;
}
