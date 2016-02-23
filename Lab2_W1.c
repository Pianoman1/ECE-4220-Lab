/*
 * Lab2_W1.c
 *
 *  Created on: Feb 2, 2016
 *      Author: memdm2
 */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

//Create Structures
struct Add {
	int counter;
	int counter2;
	int sizeX1;
	int sizeY1;
	int sizeX2;
	int sizeY2;
	int Arr1[20][20];
	int Arr2[20][20];
	int Result[20][20];
};
struct Mult {
	int counter;
	int counter2;
	int sizeX1;
	int sizeY1;
	int sizeX2;
	int sizeY2;
	int Arr1[20][20];
	int Arr2[20][20];
	int Result[20][20];
};

//Create Global Time Struct Variables
struct timeval itA;
struct timeval otA;
struct timeval itA20;
struct timeval otA20;
struct timeval itA400;
struct timeval otA400;
struct timeval itM;
struct timeval otM;
struct timeval itM20;
struct timeval otM20;
struct timeval itM400;
struct timeval otM400;

//Add matrices one element at a time
void* MatrixAddition400(void* addArr) {
	//printf("Addition Thread Start!\n");
	struct Add *my_Add = (struct Add*) addArr;
	if (((*my_Add).counter == 0) && ((*my_Add).counter2 == 0)) {
		gettimeofday(&itA400, NULL);
	}
	//Counters
	int i = (*my_Add).counter;
	int j = (*my_Add).counter2;
		(*my_Add).Result[i][j] = ((*my_Add).Arr1[i][j]) + ((*my_Add).Arr2[i][j]);
	if (((*my_Add).counter == (*my_Add).sizeX1-1) && ((*my_Add).counter2 == (*my_Add).sizeX2-1)) {
		gettimeofday(&otA400, NULL);
		printf("Addition time (400) = %d microseconds\n", otA400.tv_usec - itA400.tv_usec);
	}
	return 0;
}

//Multiply matrices one element at a time
void* MatrixMultiplication400(void* multArr) {
	//printf("Multiplication Thread Start!\n");
	struct Add *my_Mult = (struct Add*) multArr;
	if ((*my_Mult).counter == 0) {
		gettimeofday(&itM400, NULL);
	}
	//Counters
	int c = 0;
	int d = (*my_Mult).counter2;
	int k = (*my_Mult).counter;
	int sum = 0;
	for (c = 0; c < (*my_Mult).sizeX1; c++) {
		sum = sum + ((*my_Mult).Arr1[c][k] * (*my_Mult).Arr2[k][d]);
		(*my_Mult).Result[c][d] = sum;
		sum = 0;
	}
	if ((*my_Mult).counter == (*my_Mult).sizeX2-1) {
		gettimeofday(&otM400, NULL);
		printf("Multiplication time (20) = %d microseconds\n", otM400.tv_usec - itM400.tv_usec);
	}
	return 0;
}

//Add matrices one row at a time
void* MatrixAddition20(void* addArr) {
	//printf("Addition Thread Start!\n");
	struct Add *my_Add = (struct Add*) addArr;
	if ((*my_Add).counter == 0) {
		gettimeofday(&itA20, NULL);
	}
	//Counters
	int i = 0;
	int j = (*my_Add).counter;
	for (i = 0; i < (*my_Add).sizeX1; i++) {
		(*my_Add).Result[i][j] = ((*my_Add).Arr1[i][j]) + ((*my_Add).Arr2[i][j]);
	}
	if ((*my_Add).counter == (*my_Add).sizeX1-1) {
		gettimeofday(&otA20, NULL);
		printf("Addition time (20) = %d microseconds\n", otA20.tv_usec - itA20.tv_usec);
	}
	return 0;
}

//Multiply Matrices one at a time
void* MatrixMultiplication20(void* multArr) {
	//printf("Multiplication Thread Start!\n");
	struct Add *my_Mult = (struct Add*) multArr;
	if ((*my_Mult).counter == 0) {
		gettimeofday(&itM20, NULL);
	}
	//Counters
	int c = 0;
	int d = 0;
	int k = (*my_Mult).counter;
	int sum = 0;
	for (c = 0; c < (*my_Mult).sizeX1; c++) {
		for (d = 0; d < (*my_Mult).sizeY2; d++) {
			sum = sum + ((*my_Mult).Arr1[c][k] * (*my_Mult).Arr2[k][d]);
			(*my_Mult).Result[c][d] = sum;
			sum = 0;
		}
	}
	if ((*my_Mult).counter == (*my_Mult).sizeX2-1) {
		gettimeofday(&otM20, NULL);
		printf("Multiplication time (20) = %d microseconds\n", otM20.tv_usec - itM20.tv_usec);
	}
	return 0;
}

//Add matrices
void* MatrixAddition(void* addArr) {
	gettimeofday(&itA, NULL);
	//printf("Addition Thread Start!\n");
	struct Add *my_Add = (struct Add*) addArr;
	int i = 0;
	int j = 0;
	for (i = 0; i < (*my_Add).sizeX1; i++) {
		for (j = 0; j < (*my_Add).sizeY1; j++) {
			(*my_Add).Result[i][j] = ((*my_Add).Arr1[i][j]) + ((*my_Add).Arr2[i][j]);
		}
	}
	gettimeofday(&otA, NULL);
	printf("Addition time = %d microseconds\n", otA.tv_usec - itA.tv_usec);
	return 0;
}

//Multiply matrices
void* MatrixMultiplication(void* multArr) {
	gettimeofday(&itM, NULL);
	//printf("Multiplication Thread Start!\n");
	struct Add *my_Mult = (struct Add*) multArr;
	int c = 0;
	int d = 0;
	int k = 0;
	int sum = 0;
	for (c = 0; c < (*my_Mult).sizeX1; c++) {
		for (d = 0; d < (*my_Mult).sizeY2; d++) {
			for (k = 0; k < (*my_Mult).sizeX2; k++) {
				sum = sum + ((*my_Mult).Arr1[c][k] * (*my_Mult).Arr2[k][d]);
			}
			(*my_Mult).Result[c][d] = sum;
			sum = 0;
		}
	}
	gettimeofday(&otM, NULL);
	printf("Multiplication time = %d microseconds\n", otM.tv_usec - itM.tv_usec);
	return 0;
}

int main(void) {

	//Declare add and multiply structure variables
	struct Add Add1;
	struct Mult Mult1;
	int i = 0, j = 0;
	FILE *fp;

//================================================
	fp = fopen("addition.txt","r"); // read mode
	if(fp == NULL)
	{
	   perror("Error while opening the file.\n");
	   return 0;
	}
	fscanf(fp, "%d", &Add1.sizeX1);
	fscanf(fp, "%d", &Add1.sizeY1);

	//int addArr1[sizeX][sizeY];
	for (i = 0; i < Add1.sizeX1; i++) {
		for (j = 0; j < Add1.sizeY1; j++) {
			fscanf(fp, "%d", &Add1.Arr1[i][j]);
		}
	}
	fscanf(fp, "%d", &Add1.sizeX2);
	fscanf(fp, "%d", &Add1.sizeY2);
	//int addArr2[sizeX][sizeY];
	for (i = 0; i < Add1.sizeX2; i++) {
		for (j = 0; j < Add1.sizeY2; j++) {
			fscanf(fp, "%d", &Add1.Arr2[i][j]);
		}
	}
	fclose(fp);
//=================================================
	fp = fopen("multiplication.txt","r"); // read mode
	if(fp == NULL)
	{
	   perror("Error while opening the file.\n");
	   return 0;
	}
	fscanf(fp, "%d", &Mult1.sizeX1);
	fscanf(fp, "%d", &Mult1.sizeY1);
	//int multArr1[sizeX][sizeY];
	for (i = 0; i < Mult1.sizeX1; i++) {
		for (j = 0; j < Mult1.sizeY1; j++) {
			fscanf(fp, "%d", &Mult1.Arr1[i][j]);
		}
	}
	fscanf(fp, "%d", &Mult1.sizeX2);
	fscanf(fp, "%d", &Mult1.sizeY2);
	//int multArr2[sizeX][sizeY];
	for (i = 0; i < Mult1.sizeX2; i++) {
		for (j = 0; j < Mult1.sizeY2; j++) {
			fscanf(fp, "%d", &Mult1.Arr2[i][j]);
		}
	}
	fclose(fp);
//==================================================

	pthread_t pid1;
	pthread_t pid2;

	//Create Threads
	if(pthread_create(&pid1, NULL, MatrixAddition, &Add1)) {
		printf("Error creating thread\n");
		return 1;
	}
	if(pthread_create(&pid2, NULL, MatrixMultiplication, &Mult1)) {
		printf("Error creating thread\n");
		return 1;
	}

	//Join threads
	pthread_join(pid1, NULL);
	pthread_join(pid2, NULL);

	//Print Results
	printf("\nAddition Resulting Matrix: \n");
	for (i = 0; i < Add1.sizeX2; i++) {
		for (j = 0; j < Add1.sizeY2; j++){
			printf("%d ", Add1.Result[i][j]);
		}
		printf("\n");
	}
	printf("\nMultiplication Resulting Matrix: \n");
	for (i = 0; i < Mult1.sizeX1; i++) {
		for (j = 0; j < Mult1.sizeY2; j++){
			printf("%d ", Mult1.Result[i][j]);
		}
		printf("\n");
	}
//*****************************************************************
	Add1.counter = 0;
	for (i = 0; i < Add1.sizeX1; i++) {
		Add1.counter = i;
		if(pthread_create(&pid1, NULL, MatrixAddition20, &Add1)) {
			printf("Error creating thread\n");
			return 1;
		}
	}

	Mult1.counter = 0;
	for (i = 0; i < Mult1.sizeX2; i++) {
		Mult1.counter = i;
		if(pthread_create(&pid1, NULL, MatrixMultiplication20, &Mult1)) {
			printf("Error creating thread\n");
			return 1;
		}
	}
	int k = 0;
	for(k = 0; k < 20; k++) {
		pthread_join(pid1, NULL);
		pthread_join(pid2, NULL);
	}

	//Print Results
	printf("\nAddition Resulting Matrix: \n");
	for (i = 0; i < Add1.sizeX2; i++) {
		for (j = 0; j < Add1.sizeY2; j++){
			printf("%d ", Add1.Result[i][j]);
		}
		printf("\n");
	}
	printf("\nMultiplication Resulting Matrix: \n");
	for (i = 0; i < Mult1.sizeX1; i++) {
		for (j = 0; j < Mult1.sizeY2; j++){
			printf("%d ", Mult1.Result[i][j]);
		}
		printf("\n");
	}

//***********************************************************
	Add1.counter = 0;
	Add1.counter2 = 0;
	for (i = 0; i < Add1.sizeX1; i++) {
		Add1.counter = i;
		for(j = 0; j < Add1.sizeX2; j++) {
			Add1.counter2 = j;
			if(pthread_create(&pid1, NULL, MatrixAddition400, &Add1)) {
				printf("Error creating thread\n");
				return 1;
			}
		}
	}

	Mult1.counter = 0;
	Mult1.counter2 = 0;
	for (i = 0; i < Mult1.sizeX2; i++) {
		Mult1.counter2 = i;
		for(j = 0; j < Mult1.sizeY2; j++) {
			Mult1.counter = j;
			if(pthread_create(&pid1, NULL, MatrixMultiplication400, &Mult1)) {
				printf("Error creating thread\n");
				return 1;
			}
		}
	}

	for(k = 0; k < 400; k++) {
		pthread_join(pid1, NULL);
		pthread_join(pid2, NULL);
	}

	//Print Results
	printf("\nAddition Resulting Matrix: \n");
	for (i = 0; i < Add1.sizeX2; i++) {
		for (j = 0; j < Add1.sizeY2; j++){
			printf("%d ", Add1.Result[i][j]);
		}
		printf("\n");
	}
	printf("\nMultiplication Resulting Matrix: \n");
	for (i = 0; i < Mult1.sizeX1; i++) {
		for (j = 0; j < Mult1.sizeY2; j++){
			printf("%d ", Mult1.Result[i][j]);
		}
		printf("\n");
	}

	return 0;
}
