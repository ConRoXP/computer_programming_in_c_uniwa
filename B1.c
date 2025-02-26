/*Write a program that through appropriate functions:

1) Will read N real numbers within the [A, B] range from the
standard input and will place them in an array of size N.
The numbers N, A and B are also read from the standard input.

2) Will select N/2 random different elements of the array and will double their
values.

3) Will print the elements of the array (after doubling) and the
minimum and maximum values ​​found in it.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* arrayFillUp(int*, int*, int*);
void randDouble(int*, int);
void printMinMax(int*, int);

int main(){
    //RNG seeding
    srand(time(0));

    int N, A, B;
    int* arr;
    //Question 1
    arr= arrayFillUp(&N, &A, &B);
    //Question 2
    randDouble(arr, N);
    //Question 3
    printMinMax(arr, N);

    free(arr);
    return 0;
}

//===========Question 1===========//
int* arrayFillUp(int* n, int* a, int* b){
    int N, A, B;
    int* arr;

    do{
        printf("Enter total amount of numbers to read (>10)\n");
        scanf("%d", &N);
    } while(N<= 10);
    printf("Enter lower limit\n");
    scanf("%d", &A);
    do{
        printf("Enter upper limit (> lower limit)\n");
        scanf("%d", &B);
    } while(B<= A);

    arr= (int*)malloc(N*sizeof(int));
    if(arr== NULL){
        printf("Memory allocation error. Exiting...");
        exit(-1);
    }

    for(int i= 0; i< N; i++){
        printf("Enter number (>=%d & <=%d)\n", A, B);
        scanf("%d", &arr[i]);
        while(arr[i]< A || arr[i]> B){
            printf("Invalid range. Try again:\n");
            scanf("%d", &arr[i]);
        }
    }

    *n= N;
    *a= A;
    *b= B;
    return arr;
}

//===========Question 2===========//
//arr[i] -> 0 <= i <= N-1
//Generate a random number in the range from 0 to N-1
void randDouble(int* arr, int N){
    for(int i= 0; i< N/2; i++){
        int rand_num= (rand() % N);
        arr[rand_num]= arr[rand_num] * 2;
    }
}

//===========Question 3===========//
//We print the array and searh for
//the min and max values in a single loop.
void printMinMax(int* arr, int N){
    int min= arr[0];
    int max= arr[0];
    for(int i= 0; i< N; i++){
        printf("%d ", arr[i]);

        if(arr[i]> max) max= arr[i];
        if(arr[i]< min) min= arr[i];
    }
    printf("\nThe biggest element is: %d\n", max);
    printf("The smallest element is: %d\n", min);
}