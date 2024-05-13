#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct student {
    char name[30];              // Имя студента
    char group_number[10];      // Номер группы студента
    int grade[3];               // Оценки студента по трем предметам
} student;

// Функция для инициализации структуры "студент"
student* stud_init(char* name, char* group_number) {
    // Выделение памяти для структуры "студент"
    student* stud = (student*)malloc(sizeof(student));
    if (stud == NULL) {
        printf("Выделение памяти не удалось\n");
        exit(1);
    }

    // Копирование имени студента в структуру
    strcpy(stud->name, name);

    // Копирование номера группы студента в структуру
    strcpy(stud->group_number, group_number);
    
    // Генерация случайных оценок студента по трем предметам
    for(int i = 0; i < 3; i++) {
        stud->grade[i] = rand() % 4 + 2; // Оценка генерируется в диапазоне от 2 до 5
    }

    return stud; // Возврат указателя на созданную структуру
}

// Функция для вывода информации о студенте
void get_info(student* stud) {
    printf("Имя: %s\nГруппа: %s\nОценки: %d %d %d\n\n", stud->name, stud->group_number, stud->grade[0], stud->grade[1], stud->grade[2]);
}

// Главная функция программы
int main() {
    srand(time(NULL));

    int count_stud = 3;            // Количество студентов
    char group[10] = "IA-331";      // Номер группы для всех студентов
    char str[30];                   // Строка для временного хранения имени студента
    char** names = (char**)malloc(sizeof(char*) * count_stud); // Выделение памяти для массива указателей на имена студентов
    if (names == NULL) {
        printf("Выделение памяти не удалось\n");
        exit(1);
    }

    FILE* file = fopen("name.txt", "r"); // Открытие файла для чтения
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        exit(1);
    }

    int k = 0;
    // Считывание имен студентов из файла
    while (fgets(str, sizeof(str), file) != NULL && k < count_stud) {
        str[strcspn(str, "\n")] = 0; // Удаление конечного символа новой строки
        names[k] = strdup(str); // Копирование имени в массив
        if (names[k] == NULL) {
            printf("Выделение памяти не удалось\n");
            exit(1);
        }
        k++;
    }
    fclose(file); // Закрытие файла

    student* arr[count_stud]; // Создание массива структур "студент"

    // Инициализация структур "студент" и добавление их в массив
    for (int i  = 0; i < count_stud; i++) {
        arr[i] = stud_init(names[i], group); // Инициализация структуры и добавление ее в массив
    }

    // Вывод информации о каждом студенте
    for (int i = 0; i < count_stud; i++) {
        get_info(arr[i]); // Вывод информации о студенте
    }

    FILE* file_b = fopen("vedomost.dat", "wb"); // Открытие файла для записи
    if (file_b == NULL) {
        printf("Ошибка открытия файла\n");
        exit(1);
    }

    // Запись данных о студентах в файл
    for (int i = 0; i < count_stud; i++) {
        fwrite(arr[i], sizeof(student), count_stud, file_b);
    }
    fclose(file_b); // Закрытие файла

    FILE* file_br = fopen("vedomost.dat", "rb"); // Открытие файла для чтения
    if (file_br == NULL) {
        printf("Ошибка открытия файла\n");
        exit(1);
    }

    student* new_arr[count_stud]; // Выделение памяти для нового массива структур "студент"

    // Считывание данных о студентах из файла
    for (int i = 0; i < count_stud; i++) {
        new_arr[i] = (student*)malloc(sizeof(student)); // Выделение памяти для структуры в новом массиве
        if (new_arr[i] == NULL) {
            printf("Выделение памяти не удалось\n");
            exit(1);
        }
        fread(new_arr[i], sizeof(student), 1, file_br); // Считывание данных из файла в структуры
    }
    fclose(file_br); // Закрытие файла

    // Вывод информации о студентах с низким средним баллом
    for (int i = 0; i < count_stud; i++) {
        double grade = (double)(new_arr[i]->grade[0] + new_arr[i]->grade[1] + new_arr[i]->grade[2]) / 3.0; // Расчет среднего балла
        if (grade < 4) {
            get_info(new_arr[i]); // Вывод информации о студенте
        }
    }
    
    return 0; // Возврат из главной функции с кодом успешного завершения
}
