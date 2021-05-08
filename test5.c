// C program to print all permutations with duplicates allowed
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*
  A simple math game
   1  ?  ? 12  | 31  , ? + ? = 18 (A1)
   ?  ?  ?  ?  | 27               (A2)
   ?  ?  ?  ?  | 29               (A3)
  16  ?  ? 10  | 49  , ? + ? = 23 (A4)
  -------------+
  43 37 23 33
  
  26       11  <=  ? + ?
  B1 B2 B3 B4
  
  This is a 4 x 4 matrix, permute from 1 to 16.
  We know each row count (list on the righ side of each row) and column count (list under each column).
  There are 4 number already know, at the 4 corner.
  The question is what is the ? number are? 
*/

typedef unsigned char BYTE;

#define NUM_THREADS 12

#define TOTAL_TRIES 4790		// 12! / 100000, that's the times we need to try
#define A1 18					// sum of row 1
#define A2 27					// sum of row 2
#define A3 29					// sum of row 3
#define A4 23					// sum of row 4
#define B1 26					// sum of column 1
#define B2 37					// sum of column 2
#define B3 23					// sum of column 3
#define B4 11					// sum of column 4

int match_number = 0;


// print index
void print_progress(void)
{
	static int cumulate = 0;
	cumulate++;
	
    // int i;
	// for (i=0; i<index; i++)
	// printf(".");
	printf("- %.1f%% -\r", (float)cumulate/TOTAL_TRIES * 100);
}

// print out whole array
void print_array(BYTE* array, int len)
{
    // int i;
    // for (i=0; i<len; i++)
    // printf("%d,", array[i]);
    // printf("\n");
	printf("%2d %2d %2d %2d         \n", 1, array[0], array[1], 12);
	printf("%2d %2d %2d %2d\n", array[2], array[3], array[4], array[5]);
	printf("%2d %2d %2d %2d\n", array[6], array[7], array[8], array[9]);
	printf("%2d %2d %2d %2d\n", 16, array[10], array[11], 10);
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
	if (index >= 100000) index = 0;
	if (index == 0) print_progress();	// print search progress every 100 tries.
	
	// printf("%s\n", a);
	int len = strlen(a);
	//printf("len: %d \n", len);
	BYTE arr[len];

    	//converting string to BYTE[]
    	string2ByteArray(a, arr);

	// selection criteria list here
    if (  ((arr[0] + arr[1]) == A1) && 
          ((arr[2] + arr[3] + arr[4] + arr[5]) == A2) &&
          ((arr[6] + arr[7] + arr[8] + arr[9]) == A3) &&
          ((arr[10] + arr[11]) == A4) &&
          ((arr[2] + arr[6]) == B1) && 
          ((arr[0] + arr[3] + arr[7] + arr[10]) == B2) &&
          ((arr[1] + arr[4] + arr[8] + arr[11]) == B3) &&
          ((arr[5] + arr[9]) == B4) )
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

void *thread_1(void* param)
{
	char* str_a = (char*)param;
	
	char str[13];
	strcpy(str, str_a);
	
    	int n = strlen(str);
    	printf("string: %s, len: %d\n", str, n);
    	permute(str, 1, n-1);
    	
	pthread_exit(NULL);
}

/* Driver program to test above functions */
int main()
{
	pthread_t threads[NUM_THREADS];
	
	struct timespec begin, end;
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC, &begin);
	
	// map A to 1, B to 2, C to 3, ...
	// just list what we want to permute
	//
	// A B C D E F G H I  J  K  L  M  N  O  P
	// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
	//
	// in this case, 1 10 12 16 should be skip, therefor
	// A  J  L  P will be delete from the str[] array
	
	char* str[] = {
		"BCDEFGHIKMNO", "CBDEFGHIKMNO", "DBCEFGHIKMNO",
		"EBCDFGHIKMNO", "FBCDEGHIKMNO", "GBCDEFHIKMNO",
		"HBCDEFGIKMNO", "IBCDEFGHKMNO", "KBCDEFGHIMNO",
		"MBCDEFGHIKNO", "NBCDEFGHIKMO", "OBCDEFGHIKMN",
	}; 
	
	int rc;
	for(int i = 0; i < NUM_THREADS; i++ ) {
		//printf("%s\n", str[i]);	
		rc = pthread_create(&threads[i], NULL, thread_1, (void*)str[i]);
	}
	
	for (int i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);
	
	clock_gettime(CLOCK_MONOTONIC, &end);
	elapsed = end.tv_sec - begin.tv_sec;
	elapsed += (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
	
	printf("It took %.2f seconds, find %d matchs \n", elapsed, match_number);
	
    	pthread_exit(NULL);
}
