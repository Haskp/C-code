#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция сортировки методом Шелла
void shell_sort(int arr[], int n) {
    int gap, i, j, temp;
    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            temp = arr[i];
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Функция для заполнения массива случайными числами
void fill_random(int arr[], int n) {
    srand(time(NULL)); // инициализация генератора случайных чисел
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000; // случайное число от 0 до 999
    }
}

// Функция для заполнения массива с клавиатуры
void fill_keyboard(int arr[], int n) {
    printf("Введите %d элементов массива:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
}

// Функция для вывода массива на экран
void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Главная функция
int main() {
    int n_values[] = {100, 200, 300, 400, 500};
    int num_values = sizeof(n_values) / sizeof(n_values[0]);
    
    printf("n\tShell Sort\n");

    for (int i = 0; i < num_values; i++) {
        int n = n_values[i];
        int arr[n];
        double time_taken;
        int choice;

        printf("Выберите способ заполнения массива (1 - случайные числа, 2 - ввод с клавиатуры): ");
        scanf("%d", &choice);

        // Заполнение массива в зависимости от выбора пользователя
        switch(choice) {
            case 1:
                fill_random(arr, n);
                break;
            case 2:
                fill_keyboard(arr, n);
                break;
            default:
                printf("Некорректный выбор.\n");
                return 1;
        }

        // Засекаем время перед сортировкой
        clock_t t_start = clock();

        // Выполняем сортировку методом Шелла
        shell_sort(arr, n);

        // Засекаем время после сортировки
        clock_t t_end = clock();

        // Вычисляем затраченное время
        time_taken = ((double)(t_end - t_start)) / CLOCKS_PER_SEC;

        printf("%d\t%f\n", n, time_taken);
    }

    return 0;
}
