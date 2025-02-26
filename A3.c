/*Define the Product structure with fields: product code and price.

a) Create a function that accepts as parameters an array of such structures,
the number of products stored in the array and the product code.
The function should check if there is a structure in the array with the same code and,
if there is, return a pointer to this structure, otherwise return NULL

b) Write a program that uses this structure to allow the user to enter the details of 100 products.
Products with a price above 20 Euros are stored in an array of such structures.
The program then reads the code of a product, calls the function and,
if the product is registered, uses the return value to display its price.
If it is not registered, the program displays a corresponding message.*/

#include <stdio.h>
#define SIZE 100

typedef struct{
    int price;
    int code;
} Product;

Product* exists(Product*, int, int);

int main(){
    Product prod[SIZE];
    int tempC, tempP, trueSize, counter= 0;
    Product* ptr;

    /*By subtracting the counter from the array's index,
    we save all entries in succession
    without leaving empty slots in the array*/
    for(int i=0; i< SIZE; i++){
        printf("Enter price\n");
        scanf("%d", &tempP);
        if(tempP> 20){
            prod[i-counter].price= tempP;
            printf("Enter code\n");
            scanf("%d", &prod[i-counter].code);
        }
        else{
            counter++;
            printf("Products with prices <=20€ will not be saved\n");
        }
        trueSize= i-counter+1;
    }

    printf("Enter product code to search\n");
    scanf("%d", &tempC);
    ptr= exists(prod, trueSize, tempC);
    
    if(ptr!= NULL){
        printf("Price of requested product= %d", ptr->price);
    }
    else printf("Product not found\n");

    return 0;
}

Product* exists(Product* prod, int size, int code){
    for(int i=0; i< size; i++){
        if(code== prod[i].code) return &prod[i];
    }
    return NULL;
}