/*Define the structure student with fields: student code and grade.

a) Create a function that accepts as parameters two arrays of such structures and their corresponding sizes.
The function should give a bonus of one grade to those who got a grade in [4, 5). If their new final grade exceeds 5, it becomes equal to 5.
Then, the function should calculate the new percentage of all successful students.
If this is < 70%, the function should return NULL.
Otherwise, for the first student found with a grade of 10, the function should terminate immediately and return a pointer to his structure.
If no such student is found, the function should return NULL

b) Write a program that declares two arrays of Student type structures (e.g. pass and fail) with 100 elements each.
The program reads the data of 100 students and stores in the first array the data of the students who passed the course,
while in the second array the data of the students who failed the course.
Then, the program calls the function and uses the return value to display a corresponding message.*/

#include <stdio.h>
#define SIZE 100

typedef struct{
    int ID;
    int grade;
} Student;

Student* func(Student*, Student*, int, int);

int main(){
    int temp;
    Student pass[SIZE], fail[SIZE];
    Student* result;
    
    int countF= 0, countP= 0;

    /*By subtracting the following counters from the arrays' indexes,
    we add the students in their respective arrays sequencially,
    without leaving empty slots.*/
    
    for(int i= 0; i< SIZE; i++){
        printf("Enter student's grade: ");
        scanf("%d", &temp);
        if(temp< 5){
            countF++;
            fail[i-countP].grade= temp;
            printf("Enter student's ID: ");
            scanf("%d", &fail[i-countP].ID);
        }
        else{
            countP++;
            pass[i-countF].grade= temp;
            printf("Enter student's ID: ");
            scanf("%d", &pass[i-countF].ID);
        }
    }

    result= func(pass, fail, countP, countF);
    if(result== NULL){
        printf("No student with grade= 10 or percentage of passing students < 70\n");
    }
    else printf("ID of student with grade= 10: %d", result->ID);

    return 0;
}

Student* func(Student* pass, Student* fail, int sizeP, int sizeF){
    /*Counter for failing students that
    have a passing grade after adjustment.*/
    int cnt= 0;

    //Percentage of passing students
    float passingPercentage;

    for(int i= 0; i< sizeF; i++){
        if(fail[i].grade>= 4 && fail[i].grade< 5){
            fail[i].grade= fail[i].grade + 1;

            if(fail[i].grade> 5){
                fail[i].grade= 5;
                cnt++;
            }
        }
    }

    passingPercentage= ((sizeP+cnt)* 100)/ (sizeF+sizeP);
    if(passingPercentage < 70){
        return NULL;
    }
    else{
        for(int i= 0; i< sizeP; i++){
            if(pass[i].grade== 10){
                return &pass[i];
            }
        }
        return NULL;
    }
}
