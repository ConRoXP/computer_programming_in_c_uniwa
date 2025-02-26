/*a) Create a void function that accepts as parameters an array with product prices,
the number of its elements, and returns (via pointers) how many products
have a price between 10 and 20 euros and how many products have a price between 40 and 50 euros.

b) Write a program that reads the number of products in a store, dynamically allocates memory to store their values,
reads them, and stores them in that memory. If the user enters -1, data input terminates.
Then the program calls the function and displays the two return values.*/

#include <stdio.h>
#include <stdlib.h>

void prodFinder(int*, int*, int*, int*);

int main(){
    int stock, temp, prod12= 0, prod45= 0;
    int* prices;

    printf("Enter total number of products\n");
    scanf("%d", &stock);

    prices= (int*)malloc(stock*sizeof(int));

    for(int i= 0; i< stock; i++){
        printf("Enter price of products in order\n");
        scanf("%d", &temp);
        if(temp== -1){
            //Array size adjustement if
            //user inputs -1
            stock= i-1;
            break;
        }
        else prices[i]= temp;
    }
    prodFinder(prices, &stock, &prod12, &prod45);
    printf("Items between 10 & 20= %d\n", prod12);
    printf("Items between 40 & 50= %d\n", prod45);

    free(prices);
    return 0;
}

//Counters are manipulated via pointers
void prodFinder(int* pr, int* max, int* prod12, int* prod45){
    for(int i=0; i< *max; i++){
        if(pr[i]>= 10 && pr[i]<= 20){
            *prod12= *prod12+1;
        }
        else if(pr[i]>= 40 && pr[i]<= 50){
            *prod45= *prod45+1;
        }
    }
    return;
}
