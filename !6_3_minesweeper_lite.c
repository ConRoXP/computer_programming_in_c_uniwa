#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

char** createMinefield(int*, int*, int*);
void addMines(char**, int, int, int);
void calculateProx(char**, int, int);
void printMinefield(char**, int, int, int);

int main(){
    int M, N, K;
    char** minefield;
    //RNG seeding
    srand(time(0));

    //Minefield M x N with K mines
    minefield= createMinefield(&M, &N, &K);
    addMines(minefield, M, N, K);
    calculateProx(minefield, M, N);
    printMinefield(minefield, M, N, K);

    for(int i= 0; i< M; i++){
        free(minefield[i]);
    }
    free(minefield);
    return 0;
}

char** createMinefield(int* M, int* N, int* K){
    int i, j;
    int m, n, k;
    int rec, recMax;
    char** minefield;

    printf("Enter minefield dimensions (M x N)\n");
    printf("M: ");
    scanf("%d", M);
    printf("N: ");
    scanf("%d", N);
    m= *M;
    n= *N;

    //Recommended mine values
    rec= rintf((0.2*(m*n)));
    recMax= rintf((0.3*(m*n)));

    printf("\nRecommended for desired board size: %d\n", rec);
    printf("Recommended maximum for desired board size: %d\n", recMax);
    do{
    printf("Allowed maximum: %d\n", m*n);
    printf("Enter number of mines: ");
    scanf("%d", K);
    k= *K;
    } while(k> m*n);
    printf("\n");

    //Minefield allocation and initialization
    minefield= (char**)malloc(m*sizeof(char*));
    for(i= 0; i< m; i++){
        minefield[i]= (char*)malloc(n*sizeof(char));
    }

    for(i= 0; i< m; i++){
        for(j= 0; j< n; j++){
            minefield[i][j]= '-';
        }
    }

    return minefield;
}

void addMines(char** minefield, int M, int N, int K){
    int random_M, random_N;

    for(int i= 0; i< K; i++){
        random_M= rand() % M;
        random_N= rand() % N;
        minefield[random_M][random_N]= '*';
    }
}

void calculateProx(char** minefield, int M, int N){
    for(int i= 0; i< M; i++){
        for(int j= 0; j< N; j++){
            int counter= 0;

            //The following logic takes into account all coordinates located
            //in the minefield's borders so that we don't check out of bounds.
            if(minefield[i][j]== '*') continue;
            if(i< M-1) if(minefield[i+1][j]== '*') counter++;
            if(i> 0) if(minefield[i-1][j]== '*') counter++;

            if(i> 0 && j>0) if(minefield[i-1][j-1]== '*') counter++;
            if(j> 0){
                if(i< M-1) if(minefield[i+1][j-1]== '*') counter++;
                if(minefield[i][j-1]== '*') counter++;
            }

            if(j< N-1){
                if(i> 0) if(minefield[i-1][j+1]== '*') counter++;
                if(i< M-1) if(minefield[i+1][j+1]== '*') counter++;
                if(minefield[i][j+1]== '*') counter++;
            }

            if(counter== 0) continue;
            minefield[i][j]= counter+ '0';
        }
    }
}

void printMinefield(char** minefield, int M, int N, int K){
    FILE *fptr;
    fptr= fopen("Minesweeper_Lite.txt", "w");
    if(fptr== NULL) printf("Error saving to file.\n");

    printf("Size: %d x %d\nMines: %d\n", M, N, K);
    fprintf(fptr, "Size: %d x %d\nMines: %d\n", M, N, K);
    for(int i= 0; i< M; i++){
        for(int j= 0; j< N; j++){
            printf(" %c ", minefield[i][j]);
            fprintf(fptr, " %c ", minefield[i][j]);
        }
        printf("\n");
        fprintf(fptr, "\n");
    }
    fclose(fptr);
    printf("\nSuccessfully saved to file \"Minesweeper_Lite.txt\"");
}
