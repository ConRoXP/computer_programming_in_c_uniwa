#include <stdio.h>
#include <stdlib.h>
#define comboLength 6

//Most functions don't use all the arguments they have.
//One function calls the next so we have to carry over the arguments that functions
//further down the line will need.
void print_combinations(int* arr, int N, int* combo, int start, int index, int* parametersArray, int* freqCounter, int* counterArray);
void CombinationStart(int* arr, int N,  int* parametersArray, int* freqCounter, int* counterArray);
void comboHandler(int* combo,  int* parametersArray, int* freqCounter, int* counterArray);
void printSorted(int* combo, int* freqCounter);

int main(){

    //Counters used in the comboHandler function are stored in an array
    //to avoid having a larger amount of function arguments
    //[0]-> failX, [1]->failY, [2]-> totalCounter, [3]-> printedCounter
    int* counterArray= (int*)calloc(4, sizeof(int));

    //As above, in order to avoid having an even bigger amount of function arguments
    //being passed around
    //[0]-> X1, [1]->X2, [2]-> Y1, [3]-> Y2
    int* parametersArray= (int*)malloc(4*sizeof(int));

    int N;
    int* arr; //Array holding the user's inputs

    //Frequency of each number in all combinations
    int* freqCounter= (int*)calloc(50, sizeof(int));

    //=========User input=========//
    do{
        printf("Enter total amount of numbers (6 < N ≤ 49): ");
        scanf("%d", &N);
    } while(N<= 6 || N> 49);
    
    arr=(int*)malloc(N*sizeof(int));

    for(int i= 0; i< N; i++){
        int temp;
        int duplicate;
        do{
            duplicate= 0;
            printf("\nEnter number (1 <= number <= 49): ");
            scanf("%d", &temp);
            if(temp< 1 || temp> 49) {
                printf("Invalid number. Try again.\n");
                continue;
            }
            for(int j= 0; j< i; j++) {
                if (arr[j]== temp) {
                    duplicate= 1;
                    printf("Duplicate number. Try again.\n");
                    break;
                }
            }
        } while(duplicate);
        arr[i]= temp;
    }

    printf("Enter range from X1 to X2 (0 ≤ X1 ≤ X2 ≤ 6)\n");
    do{
        printf("X1: ");
        scanf("%d", &parametersArray[0]);
    } while(parametersArray[0]< 0 || parametersArray[0]> 6);

    do{
        printf("X2: ");
        scanf("%d", &parametersArray[1]);
    } while(parametersArray[1]< parametersArray[0] || parametersArray[1]> 6);

    printf("Enter range from Y1 to Y2 (21 ≤ Y1 ≤ Y2 ≤ 279)\n");
    do{
        printf("Y1: ");
        scanf("%d", &parametersArray[2]);
    } while(parametersArray[2]< 21 || parametersArray[2]> 279);

    do{
        printf("Y2: ");
        scanf("%d", &parametersArray[3]);
    } while(parametersArray[3]< parametersArray[2] || parametersArray[3]> 279);
    
    //=========Working on the combinations=========//
    CombinationStart(arr, N, parametersArray, freqCounter, counterArray);

    //=========Printing the results=========//
    printf("Total combinations: %d\n", counterArray[2]);
    printf("Total combinations that did not meet the 1st criteria: %d\n", counterArray[0]);
    printf("Total combinations that did not meet the 2nd criteria: %d\n", counterArray[1]);
    printf("Total combinations printed: %d\n", counterArray[3]);

    for(int i= 0; i< 50; i++){
        if(freqCounter[i]> 0) printf("Number %d found %d times\n", i, freqCounter[i]);
    }

    free(arr);
    free(freqCounter);
    free(counterArray);
    free(parametersArray);
    return 0;
}

void CombinationStart(int* arr, int N, int* parametersArray, int* freqCounter, int* counterArray){
    //An array to store all unique combinations one by one
    int combo[comboLength];

    print_combinations(arr, N, combo, 0, 0, parametersArray, freqCounter, counterArray);
}

void print_combinations(int* arr, int N, int* combo, int start, int index, int* parametersArray, int* freqCounter, int* counterArray){
    if(index == comboLength){
        //2) Now that the combo array is full (chunk of 6 digits= 1 combination),
        // we call the comboHandler func to work with combo's contents.
        //We use tempCombo for the recursive calls, otherwise data handling is wrong and causes duplicates.
        int tempCombo[comboLength]; 
        for (int k= 0; k< comboLength; k++){
            tempCombo[k]= combo[k];
        }
        comboHandler(tempCombo, parametersArray, freqCounter, counterArray);
        return;
    }
    //1) Filling up the combo array (only unique number combinations allowed)
    for(int i= start; i< N  && N-i>= comboLength-index; i++){
        combo[index]= arr[i];
        print_combinations(arr, N, combo, i+1, index+1, parametersArray, freqCounter, counterArray);
    }
}

void comboHandler(int* combo,  int* parametersArray, int* freqCounter, int* counterArray){
    int Ysum= 0; //Sum of a combination's 6 digits (used for the 2nd criteria)
    int Xcount= 0; //Count of a combination's even digits (used for the 1st criteria)

    counterArray[2]= counterArray[2]+ 1; //Total combinations
    for (int i= 0; i< comboLength; i++){
        Ysum= Ysum+ combo[i];
        if(combo[i]%2 == 0) Xcount++;
    }
    //Counting how many combinations failed the 1st criteria
    if(!(Xcount>= parametersArray[0] && Xcount<= parametersArray[1])){
        counterArray[0]= counterArray[0]+ 1;
        return;
    }
    //Counting how many combinations failed the 2nd criteria
    if(!(Ysum>= parametersArray[2] && Ysum<= parametersArray[3])){
        counterArray[1]= counterArray[1]+ 1; 
        return;
    }
    counterArray[3]= counterArray[3]+ 1; //Number of printed combinations
    printSorted(combo, freqCounter);
}

//Sorting and printing
void printSorted(int* combo, int* freqCounter){
    int temp;
    for(int i= 0; i< comboLength-1; i++){
        for(int j= 0; j< comboLength-i-1; j++){
            if(combo[j]> combo[j+1]){
                temp= combo[j];
                combo[j]= combo[j+1];
                combo[j+1]= temp;
            }
        }
    }
    for(int i= 0; i< comboLength; i++){
        printf("%d ", combo[i]);
        freqCounter[combo[i]]= freqCounter[combo[i]]+ 1;
    }
    printf("\n");
}