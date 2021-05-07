// C program to print all permutations with duplicates allowed
#include <stdio.h>
#include <string.h>
#include <time.h>

/*
  A simple math game
   1  ?  ? 11  | 31
   ?  ?  ?  ?  | 27
   ?  ?  ?  ?  | 29
  15  ?  ? 10  | 49
  -------------+
  43 37 23 33
  
  This is a 4 x 4 matrix, permute from 1 to 16.
  We know each row count (list on the righ side of each row) and column count (list under each column).
  There are 4 number already know, at the 4 corner.
  The question is what is the ? number are? 
*/

typedef unsigned char BYTE;

#define TOTAL_TRIES 4790016		// 12! / 100, that's the times we need to try
int match_number = 0;

// print index
void print_progress(int index)
{
	static int cumulate = 0;
	cumulate++;
	
    // int i;
	// for (i=0; i<index; i++)
	// printf(".");
	printf("-- %d, %.1f%% --\r", cumulate, (float)cumulate/TOTAL_TRIES * 100);
}

// print out whole array
void print_array(BYTE* array, int len)
{
    // int i;
    // for (i=0; i<len; i++)
    // printf("%d,", array[i]);
    // printf("\n");
	printf("%2d %2d %2d %2d         \n", 0, array[0], array[1], 0);
	printf("%2d %2d %2d %2d\n", array[2], array[3], array[4], array[5]);
	printf("%2d %2d %2d %2d\n", array[6], array[7], array[8], array[9]);
	printf("%2d %2d %2d %2d\n", 0, array[10], array[11], 0);
	printf("------------\n\n");
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
	if (index >= 100) index = 0;
	if (index == 0) print_progress(10);	// print search progress every 100 tries.
	
    // printf("%s\n", a);
    int len = strlen(a);
    BYTE arr[len];

    //converting string to BYTE[]
    string2ByteArray(a, arr);

	// selection criteria list here
    if (  ((arr[0] + arr[1]) == 19) && 
          ((arr[2] + arr[3] + arr[4] + arr[5]) == 27) &&
          ((arr[6] + arr[7] + arr[8] + arr[9]) == 29) &&
          ((arr[10] + arr[11]) == 24) &&
          ((arr[2] + arr[6]) == 27) && 
          ((arr[0] + arr[3] + arr[7] + arr[10]) == 37) &&
          ((arr[1] + arr[4] + arr[8] + arr[11]) == 23) &&
          ((arr[5] + arr[9]) == 12) )
		  {
			  print_array(arr, len);
			  match_number++;
		  }
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
    char str[] = "BCDEFGHILMNP";
    int n = strlen(str);
    permute(str, 0, n-1);
	
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("It took %.2f seconds, find %d matchs \n", cpu_time_used, match_number);
    return 0;
}
