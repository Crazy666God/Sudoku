#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ZERO 0
#define THREE 3
#define NINE 9
#define TEN 10
#define MAX_VALUE 81

void print_int(int **agr)
{
  int **arr = agr;
  for(int i = 0; i < 9; ++i)
  {
    for(int j = 0; j < 9; ++j)
      printf("%d", arr[i][j]);
    putchar('\n');
  }
}

char **ft_read(FILE *pointer)
{
  char **massiv = (char**)malloc(sizeof(char*) * NINE + 1);
  for(int i = 0; i < NINE; ++i)
  {
    massiv[i] = (char*)malloc(sizeof(char) * NINE);
    fread(massiv[i], 1, NINE + 1, pointer);
  }
  massiv[NINE] = NULL;
  return massiv;
}

int **char_v_int(char **sudoku)
{
  int **arr = (int**)malloc(sizeof(int*) * 9);
  for(int row = 0; row < 9; ++row)
  {
    arr[row] = (int*)malloc(sizeof(int) * 9);
    for(int column = 0; column < 9; ++column)
    {
      if(sudoku[row][column] == '.')
        arr[row][column] = 0;
      else
        arr[row][column] = sudoku[row][column] - '0';
    }
  }
  return arr;
}

void ft_free(char **str)
{
  char **p = str;
  while(*p)
  {
    free(*p);
    *(++p);
  }
  free(str);
}

void ft_print(char **str)
{
  for(int i = 0; i < NINE; ++i)
  {
    for(int j = 0; j < NINE; ++j)
      printf("%c", str[i][j]);
    putchar('\n');
  }
}

bool cheking_for_a_match(int **sudoku, int row, int column, int number)
{
  for(int i = 0; i < NINE; ++i)
    if(sudoku[i][column] == number || sudoku[row][i] == number)
      return false;
  for(int i = 0; i < THREE; ++i)
    for(int j = 0; j < THREE; ++j)
      if(sudoku[(row - (row % THREE)) + i][(column - (column % THREE)) + j] == number)
        return false;
  return true;
}

bool ft_decision(int **sudoku, int value)
{
  int row = value / NINE; 
  int column = value % NINE;
  if(value >= MAX_VALUE)
    return true;
  if(sudoku[row][column])
    return ft_decision(sudoku, ++value);
  for(int i = 1; i < TEN; ++i)
  {
    if(cheking_for_a_match(sudoku, row, column, i))
    {
      sudoku[row][column] = i;
      if(ft_decision(sudoku, ++value))
        return true;
      else
      {
        sudoku[row][column] = 0;
	--value;
      }
    }
  }
  return false;
}

int main(void)
{
  FILE *source_data = fopen("sudoku", "rb");
  char **sudoku = ft_read(source_data);
  fclose(source_data);
  int **arr = char_v_int(sudoku);
  int res = ft_decision(arr, ZERO);
  if(res)
  {
     print_int(arr);
//     ft_print(sudoku);
  }
  else
    printf("Нет решения\n");
  ft_free(sudoku);
  return 0;
}
