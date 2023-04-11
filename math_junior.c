#include <stdio.h>

#define SIZE 4

int main();
int solve_cell();
int is_valid(int row, int column, int value);
void print_grid();

int grid[5][5] = {
        { 1, 0, 0,12,31},
		{ 0, 0, 0, 0,27},
		{ 0, 0, 0, 0,29},
		{16, 0, 0,10,49},
		{43,37,23,33, 0} };

int main()
{
    solve_cell();
	return 0;
}

int solve_cell()
{
	for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            /* Find blank cell */
            if (grid[i][j] == 0)
            {
                /* Loop from 1 - 16 */
                for (int n = 1; n < 17; n++)
                {
                    if (is_valid(i, j, n))
                    {
                        grid[i][j] = n;
                        solve_cell();

                        grid[i][j] = 0;
                    }
                    
                }
                return 0;
            }
        }
    }
    static int count;
    printf("id:%d\n", ++count);
    print_grid();
}

int is_valid(int row, int col, int num)
{
    int count;
    // can't repeat
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == num) return 0;            
        }
        
    }
    
    // Check row
    count = 0;
    for (int j = 0; j < SIZE; j++)
        count += grid[row][j];
    count += num;
    if (count > grid[row][4])
        return 0;
    int with_value = 1;
    for (int j = 0; j < SIZE; j++) {
        if (j != col)
            if (grid[row][j] == 0) with_value = 0;
    }
    if (with_value) 
        if (count != grid[row][4]) return 0;

    // Check column
    count = 0;
    for (int i = 0; i < SIZE; i++)
        count += grid[i][col];
    count += num;
    if (count > grid[4][col])
        return 0;
    with_value = 1;
    for (int i = 0; i < SIZE; i++) {
        if (i != row)
            if (grid[i][col] == 0) with_value = 0;
    }
    if (with_value)
        if (count != grid[4][col]) return 0;

    return 1;
}

void print_grid()
{
	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			grid[i][j] != 0 ? printf("%2d ", grid[i][j]) : printf(" . ");
		}
		printf("\n");
	}
}