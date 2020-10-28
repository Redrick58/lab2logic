#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "header.h"

#define LENGTH 7560

void shell(int *items, int count)
{

  int i, j, gap, k;
  int x, a[5];

  a[0]=9; a[1]=5; a[2]=3; a[3]=2; a[4]=1;

  for(k=0; k < 5; k++) {
    gap = a[k];
    for(i=gap; i < count; ++i) {
      x = items[i];
      for(j=i-gap; (x < items[j]) && (j >= 0); j=j-gap)
        items[j+gap] = items[j];
      items[j+gap] = x;
    }
  }
}

void qs(int *items, int left, int right) //вызов функции: qs(items, 0, count-1);
{
  int i, j;
  int x, y;

  i = left; j = right;

  /* выбор компаранда */
  x = items[(left+right)/2];
  
  do {
    while((items[i] < x) && (i < right)) i++;
    while((x < items[j]) && (j > left)) j--;

    if(i <= j) {
      y = items[i];
      items[i] = items[j];
      items[j] = y;
      i++; j--;
    }
  } while(i <= j);

  if(left < j) qs(items, left, j);
  if(i < right) qs(items, i, right);
}

int fillrand(int* mas, int length) {
	srand(time(0));
	for (int i=0; i < length; i++) {
		mas[i] = rand() % 100001;
	}
	return 0;
}

int fillincr(int* mas, int length) {

	for (int i = 0; i < length; i++) {
		mas[i] = i;
	}
	return 0;
}

int filldecr(int* mas, int length) {

	for (int i = 1; i <= length; i++) {
		mas[i-1] = length - i;
	}
	return 0;
}

int fillincdecr(int* mas, int length) {

	for (int i = 0; i < length / 2; i++) {
		mas[i] = i;
	}

	for (int i = length / 2; i < length; i++) {
		mas[i] = length - i;
	}
	return 0;
}


int comp (const int *i, const int *j)
{
return *i - *j;
}

int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FILE *fp;
  char name[] = "moo.txt";
  if ((fp = fopen(name, "w")) == NULL)
  {
    fprintf(fp, "Не удалось открыть файл");
    getchar();
  }
	matrix(100, fp);
	matrix(200, fp);
	matrix(400, fp);
	matrix(1000, fp);
	matrix(2000, fp);
	matrix(4000, fp);
	matrix(10000, fp);
	int* to_sort_random = (int*)malloc(LENGTH * sizeof(int));
	int* to_sort_random_cpy = (int*)malloc(LENGTH * sizeof(int));
	fillrand(to_sort_random, LENGTH);
	fprintf(fp, "Распределение\tqs\tШелл\tqsort\n");
	/*for (int i=0; i < LENGTH; i++) {
			fprintf(fp, "%d ", to_sort_random[i]);
	}*/
	clock_t start, end;
	memcpy(to_sort_random_cpy, to_sort_random, LENGTH * sizeof(int));
	start = clock();
	qs(to_sort_random_cpy, 0, LENGTH - 1);
	end = clock();
	start = difftime(end, start);
	/*for (int i=0; i < LENGTH; i++) {
			fprintf(fp, "%d ", to_sort_random_cpy[i]);
	}*/
	fprintf(fp, "псевдослучайное\t%d\t", start);
	memcpy(to_sort_random_cpy, to_sort_random, LENGTH * sizeof(int));
	start = clock();
	shell(to_sort_random_cpy, LENGTH);
	end = clock();
	start = difftime(end, start);
	/*for (int i=0; i < LENGTH; i++) {
			fprintf(fp, "%d ", to_sort_random_cpy[i]);
	}*/
	fprintf(fp, "%d\t", start);
	memcpy(to_sort_random_cpy, to_sort_random, LENGTH * sizeof(int));
	start = clock();
	qsort(to_sort_random_cpy, LENGTH, sizeof(int), (int(*) (const void *, const void *)) comp);
	end = clock();
	start = difftime(end, start);
	/*for (int i=0; i < LENGTH; i++) {
			fprintf(fp, "%d ", to_sort_random_cpy[i]);
	}*/
	fprintf(fp, "%d\n", start);

	int* to_sort_inc = (int*)malloc(LENGTH * sizeof(int));
	int* to_sort_inc_cpy = (int*)malloc(LENGTH * sizeof(int));
	fillincr(to_sort_inc, LENGTH);
	/*for (int i=0; i < LENGTH; i++) {
			fprintf(fp, "%d ", to_sort_inc[i]);
	}*/
	memcpy(to_sort_inc_cpy, to_sort_inc, LENGTH * sizeof(int));
	start = clock();
	qs(to_sort_inc_cpy, 0, LENGTH - 1);
	end = clock();
	start = difftime(end, start);
	/*for (int i=0; i < LENGTH; i++) {
			fprintf(fp, "%d ", to_sort_inc_cpy[i]);
	}*/
	fprintf(fp, "возрастающее\t%d\t", start);
	memcpy(to_sort_inc_cpy, to_sort_inc, LENGTH * sizeof(int));
	start = clock();
	shell(to_sort_inc_cpy, LENGTH);
	end = clock();
	start = difftime(end, start);
	/*for (int i=0; i < LENGTH; i++) {
			fprintf(fp, "%d ", to_sort_inc_cpy[i]);
	}*/
	fprintf(fp, "%d\t", start);
	memcpy(to_sort_inc_cpy, to_sort_inc, LENGTH * sizeof(int));
	start = clock();
	qsort(to_sort_inc_cpy, LENGTH, sizeof(int), (int(*) (const void*, const void*)) comp);
	end = clock();
	start = difftime(end, start);
	/*for (int i=0; i < LENGTH; i++) {
			fprintf(fp, "%d ", to_sort_inc_cpy[i]);
	}*/
	fprintf(fp, "%d\t", start);

	int* to_sort_dec = (int*)malloc(LENGTH * sizeof(int));
	int* to_sort_dec_cpy = (int*)malloc(LENGTH * sizeof(int));
	filldecr(to_sort_dec, LENGTH);
	/*for (int i=0; i < LENGTH; i++) {
			fprintf(fp, "%d ", to_sort_dec[i]);
	}*/
	memcpy(to_sort_dec_cpy, to_sort_dec, LENGTH * sizeof(int));
	fprintf(fp, "\n");
	start = clock();
	qs(to_sort_dec_cpy, 0, LENGTH - 1);
	end = clock();
	start = difftime(end, start);
	/*for (int i=0; i < LENGTH; i++) {
			fprintf(fp, "%d ", to_sort_dec_cpy[i]);
	}*/
	fprintf(fp, "убывающее\t%d\t", start);
	memcpy(to_sort_dec_cpy, to_sort_dec, LENGTH * sizeof(int));
	start = clock();
	shell(to_sort_dec_cpy, LENGTH);
	end = clock();
	start = difftime(end, start);
	/*for (int i=0; i < LENGTH; i++) {
			fprintf(fp, "%d ", to_sort_dec_cpy[i]);
	}*/
	fprintf(fp, "%d\t", start);
	memcpy(to_sort_dec_cpy, to_sort_dec, LENGTH * sizeof(int));
	start = clock();
	qsort(to_sort_dec_cpy, LENGTH, sizeof(int), (int(*) (const void*, const void*)) comp);
	end = clock();
	start = difftime(end, start);
	/*for (int i=0; i < LENGTH; i++) {
			fprintf(fp, "%d ", to_sort_dec_cpy[i]);
	}*/
	fprintf(fp, "%d\t\n", start);

	int* to_sort_incdec = (int*)malloc(LENGTH * sizeof(int));
	int* to_sort_incdec_cpy = (int*)malloc(LENGTH * sizeof(int));
	fillincdecr(to_sort_incdec, LENGTH);
	/*for (int i=0; i < LENGTH; i++) {
			fprintf(fp, "%d ", to_sort_incdec[i]);
	}*/
	memcpy(to_sort_incdec_cpy, to_sort_incdec, LENGTH * sizeof(int));
	start = clock();
	qs(to_sort_incdec_cpy, 0, LENGTH - 1);
	end = clock();
	start = difftime(end, start);
	/*for (int i=0; i < LENGTH; i++) {
			fprintf(fp, "%d ", to_sort_incdec_cpy[i]);
	}*/
	fprintf(fp, "возр.-убыв.\t%d\t", start);
	memcpy(to_sort_incdec_cpy, to_sort_incdec, LENGTH * sizeof(int));
	start = clock();
	shell(to_sort_incdec_cpy, LENGTH);
	end = clock();
	start = difftime(end, start);
	/*for (int i=0; i < LENGTH; i++) {
			fprintf(fp, "%d ", to_sort_incdec_cpy[i]);
	}*/
	fprintf(fp, "%d\t", start);
	memcpy(to_sort_incdec_cpy, to_sort_incdec, LENGTH * sizeof(int));
	start = clock();
	qsort(to_sort_incdec_cpy, LENGTH, sizeof(int), (int(*) (const void*, const void*)) comp);
	end = clock();
	start = difftime(end, start);
	/*for (int i=0; i < LENGTH; i++) {
			fprintf(fp, "%d ", to_sort_incdec_cpy[i]);
	}*/
	fprintf(fp, "%d\t", start);
	fclose(fp);
}