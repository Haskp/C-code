#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct student
{
    char name[30];
    char group_number[10];
    int grade[3];
} student;

student* stud_init(char* name, char* group_number)
{
    student* stud = (student*)malloc(sizeof(student));

    strcpy(stud->name, name);

    strcpy(stud->group_number, group_number);

    for(int i = 0; i < 3; i++)
    {
        stud->grade[i] = rand() % 4 + 2;
    }

    return stud;
}

void get_info(student* stud)
{
    printf("Name: %sGroup: %s\nGrade: %d %d %d\n\n",stud->name, stud->group_number, stud->grade[0],stud->grade[1],stud->grade[2]);
}

int main()
{

    srand(time(NULL));

    int count_stud = 10;
    char group[10] = "IA-331";
    char str[20];

    char** names = (char**)malloc(sizeof(char*) * count_stud);

    for(int i = 0; i < count_stud; i++)
    {
        names[i] = (char*)malloc(sizeof(char) * 20);
    }

    int k = 0;

    FILE* file = fopen("name.txt", "r");

    if(file == NULL)
    {
        printf("In %s:%d Error opening file\n", __FILE__, __LINE__);
        exit(1);
    }

    while(fgets(str, 20, file) != NULL && k < count_stud)
    {
        strcpy(names[k++], str);
    }

    fclose(file);

    student* arr[count_stud];

    for(int i  = 0; i < count_stud; i++)
    {
        arr[i] = stud_init(names[i], group);
    }

    for(int i = 0; i < count_stud; i++)
    {
        get_info(arr[i]);
    }

    printf("------------------------------------------------------------------------------------------\n\n");

    FILE* file_b = fopen("vedomost.dat", "wb");

    if(file_b == NULL)
    {
        printf("In %s:%d Error opening file\n", __FILE__, __LINE__);
        exit(1);
    }

    // for(int i = 0; i < count_stud; i++)
    // {
        fwrite(arr[0], sizeof(student), count_stud,file_b);
    // }

    fclose(file_b);

    FILE* file_br = fopen("vedomost.dat", "rb");

    student* new_arr = (student*)malloc(sizeof(student) * count_stud);

    for(int i = 0; i < count_stud; i++)
    {
        fread(&new_arr[i], sizeof(student), 1,file_br);
    }

    for(int i = 0; i < count_stud; i++)
    {
        double grade = (new_arr[i].grade[0] + new_arr[i].grade[1] + new_arr[i].grade[2])/3;
        if(grade < 4)
        {
            get_info(&new_arr[i]);
        }
    }
    
    
    return 0;
}