#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define SIZE 10
#define subs 3
#define grads 3

typedef unsigned char uint8;
int num;
uint8 Course_ID[subs];
uint8 Course_GRADE[grads];
void fun(int num);
bool res;
uint8 Used_Size;
uint8 ID;
uint8 YEAR =0;
uint8 Count_ID;
uint8* list;
uint8 arr[3];
typedef struct student{
uint8 ID;
uint8 YEAR;
uint8 course_1_ID;
uint8 course_1;
uint8 course_2_ID;
uint8 course_2;
uint8 course_3_ID;
uint8 course_3;
struct student *next;
}Node;
uint8 ids[10];

Node* first = NULL;

bool SDB_IsFull(void);
uint8 SDB_GetUsedSize(void);
bool SDB_AddEntry(uint8 id,uint8 year,uint8* subjects,uint8* grades);
void SDB_DeleteEntry(uint8 id);
bool SDB_ReadEntry(uint8 id,uint8* year,uint8* subjects,uint8* grades);
bool SDB_IsIdExist(uint8 ID);
int main()
{
    while(1) {
        printf("############################################\n");
        printf("Hello this is the amazing student database:\n");
        printf("please enter the number of the process you want:\n");
        printf("1.Check if database is full\n");
        printf("2.Get the used size of the database\n");
        printf("3.Add Student\n");
        printf("4.Delete student\n");
        printf("5.Read the data of a student\n");
        printf("6.Get List of student ID\n");
        printf("7.Check if a student with ID exists\n");
        scanf("%d",&num);
        fun(num);
    }
    return 0;
}
void fun(int num)
{
    switch(num)
    {
       case 1:
           res = SDB_IsFull();
           if (res == 1)
            printf("The database is full :( you can't add more entries\n");
           else
            printf("The database is not full :) you can add more entries\n");
           break;
       case 2:
           Used_Size = SDB_GetUsedSize();
           printf("The number of entries is: %d\n",Used_Size);
           break;
       case 3:
           printf("Now we are adding a new student:\n");
           printf("Please enter the student (ID):\n");
           scanf("%s",arr);
           ID=atoi(arr);
           printf("please enter the student (YEAR):\n");
           scanf("%s",arr);
           YEAR=atoi(arr);
           for (int j=0;j<3;j++){
                printf("Please enter the ID of subject %d:\n",j+1);
                scanf("%s",arr);
                Course_ID[j]=atoi(arr);
                printf("Please enter the Grade of subject %d:\n",j+1);
                scanf("%s",arr);
                Course_GRADE[j]=atoi(arr);
           }
           res = SDB_AddEntry(ID,YEAR,Course_ID,Course_GRADE);
           break;

       case 4:
           printf("Please enter the ID of the student you want to delete from the database:\n");
           scanf("%s",arr);
           ID=atoi(arr);
           SDB_DeleteEntry(ID);
           break;
       case 5:
           printf("Please enter the ID of the student you want to read data from the database:\n");
           scanf("%s",arr);
           ID=atoi(arr);
           res = SDB_ReadEntry(ID,&YEAR,Course_ID,Course_GRADE);
           if(res == 1) {
                printf("Here is the data found for the student ID:\n");
               printf("Year:%c\n",YEAR);
               for (int i=0 ; i<3 ; i++) {
                    printf("Course_%d_ID:%c\n",i+1,Course_ID[i]);
                    printf("Course_%d_GRADE:%c\n",i+1,Course_GRADE[i]);
               }
           }

           break;
       case 6:
           SDB_GetIdList(&Count_ID, &list);
           printf("The number of Students exist is:%d\n",Count_ID);
           printf("Here is the list of ids\n[");
           for (int j=0;j<Count_ID;j++)
           {
                printf(" %c\t",ids[j]);
           }
           printf("]\n");
           break;
       case 7:
           printf("please Enter the ID of student you want to check:\n");
           scanf("%s",arr);
           ID=atoi(arr);
           res = SDB_IsIdExist(ID);
           switch(res)
           {
            case 0:
                printf("Sorry the student ID does not exist :( \n");
                break;
            case 1:
                printf("The student ID exists :) \n");
                break;
           }
           break;
       default:
           printf("Please enter a valid number :)\n");
    }

}

Node* SDB_GetLast(void)
{
    Node* temp = first;

    while(temp->next != NULL) {
        temp = temp->next;
    }

    return temp;
}

Node* SDB_GetByID(uint8 id) {
    Node* current = first;
    while (current != NULL)
    {
        if (current->ID == id){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

bool SDB_AddEntry(uint8 id,uint8 year,uint8* subjects,uint8* grades)
{
    if (SDB_IsFull()) {
        printf("Sorry the database is full. \n");
        return 0;
    }

    Node *student = (Node*) malloc(sizeof(Node));
    student->ID = id;
    student->YEAR = year;
    student->course_1_ID = subjects[0];
    student->course_2_ID = subjects[1];
    student->course_3_ID = subjects[2];
    student->course_1 = grades[0];
    student->course_2 = grades[1];
    student->course_3 = grades[2];

    if(first == NULL) {
        first = student;
    } else {
        Node* last = SDB_GetLast();
        last->next = student;
    }

    return 1;

}

bool SDB_IsFull(void)
{
   uint8 count = 0;
   Node* current = first;
   while (current != NULL)
    {
        count++;
        current = current->next;

        if(count >=10)
            return 1;
    }
    return 0;
}

uint8 SDB_GetUsedSize(void)
{
    uint8 count = 0;
    Node* current = first;
    while (current != NULL)
    {
        count++;
        current = current->next;

    }
    return count;
}

void SDB_DeleteEntry(uint8 id)
{
    if(first == NULL) {
        printf("There is no data to delete \n");
        return;
    }

    Node* tail = first;
    Node* head = first->next;

    if(head == NULL && tail->ID == id) {
        free(tail);
        first = NULL;
        printf("The student is successfully deleted:)\n");
    }

    while (head != NULL)
    {
        if (head->ID == id){
            tail->next = head->next;
            free(head);
            printf("The student is successfully deleted:)\n");
            return;
        }
        tail = tail->next;
        head = head->next;
    }
    printf("The student doesn't exist in the database\n");
}

bool SDB_ReadEntry(uint8 id,uint8* year,uint8* subjects,uint8* grades)
{
    Node* current = SDB_GetByID(id);
    if(current == NULL) {
        printf("The student doesn't exist in the database\n");
        return 0;
    }

    *year = current->YEAR;
    subjects[0] = current->course_1_ID;
    subjects[1] = current->course_2_ID;
    subjects[2] = current->course_3_ID;
    grades[0] = current->course_1;
    grades[1] = current->course_2;
    grades[2] = current->course_3;
    return 1;
}
void SDB_GetIdList(uint8* count, uint8* list)
{
    uint8 curSize = SDB_GetUsedSize();
    *count = curSize;
    Node* current = first;
    int i = 0;
    while (current != NULL)
    {
        ids[i] = current->ID;
        i++;
        current = current->next;
    }
    list = ids;
}

bool SDB_IsIdExist(uint8 id)
{
   return SDB_GetByID(id);
}
