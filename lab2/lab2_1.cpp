#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>



int matrix(int SIDE)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	clock_t start, end; // объявляем переменные для определения времени выполнения

	int i=0, j=0, r;
	int elem_c;
	int** a = (int**)malloc(SIDE * sizeof(int*));
	for (int i = 0; i < SIDE; i++)
	{
		a[i] = (int*)malloc(SIDE * sizeof(int));
	}

	int** b = (int**)malloc(SIDE * sizeof(int*));
	for (int i = 0; i < SIDE; i++)
	{
		b[i] = (int*)malloc(SIDE * sizeof(int));
	}

	int** c = (int**)malloc(SIDE * sizeof(int*));
	for (int i = 0; i < SIDE; i++)
	{
		c[i] = (int*)malloc(SIDE * sizeof(int));
	}

	srand(time(NULL)); // инициализируем параметры генератора случайных чисел
	while(i<SIDE)
	{
		while(j<SIDE)
		{
			a[i][j]=rand()% 100 + 1; // заполняем массив случайными числами
			j++;
		}
		i++;
	}
	srand(time(NULL)); // инициализируем параметры генератора случайных чисел
	i=0; j=0;
	while(i<SIDE)
	{
		while(j<SIDE)
		{
			b[i][j]=rand()% 100 + 1; // заполняем массив случайными числами
			j++;
		}
		i++;
	}

	start = clock();

	for(i=0;i<SIDE;i++)
	{
		for(j=0;j<SIDE;j++)
		{
			elem_c=0;
			for(r=0;r<SIDE;r++)
			{
				elem_c=elem_c+a[i][r]*b[r][j];
				c[i][j]=elem_c;
			}
		}
	}

	end = clock();
	start = difftime(end, start);
	printf("Время выполнения всей программы %d тиков. Размер %d\n", end, SIDE);
	printf("Время перемножения матриц %d тиков. Размер %d\n", start, SIDE);
	return(0);
}
