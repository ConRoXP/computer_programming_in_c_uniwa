/*a) Create a void function that accepts as parameters two arrays of integers and their corresponding sizes.
The function should calculate how many elements of the first array appear three times in the second array.
The function should return (via pointers) their number, as well as the average of the elements of the second array.

b) Write a program that reads 100 integers and stores them in an array.
If the user enters the value -1, the input of values ​​should end.
The same process should be repeated for a second array of 100 integers.
If at least 3 elements have been stored in each array, the program should call the function, otherwise it should end.
If the function is called, the program should display the two return values.*/

#include <stdio.h>

#define SIZE 100

void func(int*, int, int*, int, int*, float*);

int main(){

    int arr1[SIZE], arr2[SIZE], temp, trueSize1= 0, trueSize2= 0, counter1= 0, counter2= 0;
    int funCounter= 0;
    float funAVG= 0;

    //Since the user can quit inputting values before
    //hitting the limit of 100, I use trueSize as a counter
    //for the usable size of the arrays
    printf("Insert numbers for 1st array (-1 to stop): \n");
    for(int i=0; i< SIZE; i++){
        scanf("%d", &temp);
        if(temp== -1){
            trueSize1= i;
            break;
        }
        else{
            arr1[i]= temp;
            counter1++;
            trueSize1= i+1;
        }
    }

    printf("Insert numbers for 2nd array (-1 to stop): \n");
    for(int i=0; i< SIZE; i++){
        scanf("%d", &temp);
        if(temp== -1){
            trueSize2= i;
            break;
        }
        else{
            arr2[i]= temp;
            counter2++;
            trueSize2= i+1;
        }
    }

    if(counter1>= 3 && counter2>= 3){
        func(arr1, trueSize1, arr2, trueSize2, &funCounter, &funAVG);
        printf("Number of arr1 elements that are found at least 3 times in arr2: %d\n", funCounter);
        printf("Avg of arr2's elements: %f", funAVG);
    }
    else{
        printf("Not enough elements, exiting...");
        return 0;
    }

    return 0;
}

/*We are also asked to find the avg of
the second array.

In order to not scan the entire array again,
we count the sum of arr2's elements only in the 1st pass*/

/*If we find the 3 equal elements we are asked to,
we don't need to keep searching thus we can just break
and move on.

However, since we also want the avg, if it's the 1st pass
we don't break and we keep counting to find the sum.
In all other passes we can break.*/

void func(int* arr1, int size1, int* arr2, int size2, int* total, float* avg){
    int counter;

    for(int i=0; i< size1; i++){
        counter= 0;
        for(int j=0; j< size2; j++){
            if(i== 0){
                *avg= *avg+ arr2[j];
                printf("avg= %f\n", *avg);
            }
            if(arr1[i]== arr2[j]){
                counter++;
                if(counter== 3){
                    *total= *total+1;
                    counter= 0;
                    if(i!= 0) break;
                }
            }
        }
    }

    *avg= *avg/ size2;
    return;
}
