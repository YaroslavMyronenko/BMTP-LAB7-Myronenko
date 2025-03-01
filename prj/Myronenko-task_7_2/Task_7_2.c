#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>

#define ARRAY_SIZE 9
#define TRUE 1
#define FALSE 0

void showAppInfo() {
    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║                  ІНФОРМАЦІЯ ПРО ПРОГРАМУ                  ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n\n");
    
    printf("📋 Назва: Програма обміну найбільшого та найменшого елементів масиву\n\n");
    
    printf("📝 Опис задачі:\n");
    printf("   Програма приймає масив з 9 натуральних чисел, знаходить найбільший\n");
    printf("   та найменший елементи, міняє їх місцями та виводить модифікований масив.\n\n");
    
    printf("📥 Вхідні дані:\n");
    printf("   - Масив з 9 натуральних чисел (цілі, додатні, більше 0)\n\n");
    
    printf("📤 Вихідні дані:\n");
    printf(" - Початковий масив\n");
    printf(" - Значення та індекси мінімального та максимального елементів\n");
    printf(" - Модифікований масив після обміну\n\n");
    
    printf("👨‍💻 Розробник: Yaroslav_Myronenko\n");
    printf("✉ Контактні дані: jarik2707@gmail.com\n");
    printf("🔄 Версія: 1.0\n");
    printf("📅 Рік розробки: 2025\n\n");
    
    printf("🛠 Технічні деталі:\n");
    printf(" - Мова програмування: C\n");
    printf(" - Кодування інтерфейсу: UTF-8\n");
    printf(" - Використані бібліотеки: stdio.h, stdlib.h, windows.h, locale.h, conio.h\n\n");
    
    printf("💡 Особливості реалізації:\n");
    printf(" - Повна валідація введених даних\n");
    printf(" - Нумерація елементів з одиниці\n");
    printf(" - Візуальне оформлення інтерфейсу\n");
    printf(" - Модульна структура програми\n");
}

//Функція для встановлення украінського інтерфейсу
void setupInterface() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "uk_UA.UTF-8");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

//Функція для введення чисел
void inputArray(int array[], int size) {
    int input;
    int isValid = FALSE;

    printf("╔══════════════════════════════════════╗\n");
    printf("║  ВВЕДЕННЯ МАСИВУ НАТУРАЛЬНИХ ЧИСЕЛ   ║\n");
    printf("╚══════════════════════════════════════╝\n\n");

    for (int i = 0; i < size; i++) {
        isValid = FALSE;

        while (!isValid) {
            printf("► Елемент %d: ", i + 1);

            if (scanf("%d", &input) != 1) {
                while (getchar() != '\n');
                printf("   ⚠ Помилка: Введіть ціле число!\n");
                continue;
            }

            if (input <= 0) {
                printf("   ⚠ Помилка: Введіть натуральне число (більше за 0)!\n");
                continue;
            }
            isValid = TRUE;
        }
        array[i] = input;
    }
    printf("\n");
}


//Функція для виведення масиву
void printArray(int array[], int size, const char* title) {
    printf("%-31s\n", title);
    printf("[ ");
    for (int i = 0; i < size; i++) {
        printf("%d", array[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf(" ]\n\n");
}


//Функція для знаходження індексу мінімального елемента
int findMinIndex(int array[], int size) {
    int minIndex = 0;

    for (int i = 1; i < size; i++) {
        if (array[i] < array[minIndex]) {
            minIndex = i;
        }
    }

    return minIndex;
}


//Функція для знаходження індексу максимального елемента
int findMaxIndex(int array[], int size) {
    int maxIndex = 0;

    for (int i = 1; i < size; i++) {
        if (array[i] > array[maxIndex]) {
            maxIndex = i;
        }
    }

    return maxIndex;
}


//Функція для обміну елементів масиву
void swapElements(int array[], int index1, int index2) {
    int temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}

int main() {
    setupInterface();
    showAppInfo();
    printf("Натисніть будь-яку клавішу, щоб продовжити...");
    getch();
    int array[ARRAY_SIZE];

    system("cls");
    printf("\n");
    printf("╔═════════════════════════════════════════════╗\n");
    printf("║     ПРОГРАМА ДЛЯ ОБМІНУ ЕЛЕМЕНТІВ МАСИВУ    ║\n");
    printf("╚═════════════════════════════════════════════╝\n\n");
    inputArray(array, ARRAY_SIZE);
    printArray(array, ARRAY_SIZE, "Початковий Масив");

    int minIndex = findMinIndex(array, ARRAY_SIZE);
    int maxIndex = findMaxIndex(array, ARRAY_SIZE);

    printf("🔍 Знайдені елементи:\n");
    printf("  • Мінімальний елемент: %d (індекс %d)\n", array[minIndex], minIndex + 1);
    printf("  • Максимальний елемент: %d (індекс %d)\n\n", array[maxIndex], maxIndex + 1);


    swapElements(array, minIndex, maxIndex);

    printArray(array, ARRAY_SIZE, "Модифікований Масив");

    printf("Програма завершила роботу. Натисніть будь-яку клавішу...");
    getch();

    return 0;
}
