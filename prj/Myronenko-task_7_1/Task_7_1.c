#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>

#define MAX_SENTENCE_LENGTH 1024
#define TRUE 1
#define FALSE 0

// Функція для відображення інформації про програму
void showAppInfo() {
    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║                  ІНФОРМАЦІЯ ПРО ПРОГРАМУ                  ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n\n");
   
    printf("📋 Програма аналізу речення та обробки символів\n\n");
   
    printf("📝 Опис задачі:\n");
    printf(" Програма приймає речення українською або англійською мовою, яке\n");
    printf(" закінчується символом '!' або '?'. Підраховує кількість літер 'д'\n");
    printf(" у введеному реченні. Якщо символ 'д' відсутній, перетворює і виводить\n");
    printf(" речення, у якому літери 'а' та 'я' замінюються на заголовкові ('А', 'Я').\n\n");
   
    printf("📥 Вхідні дані:\n");
    printf(" - Речення українською або англійською мовою\n");
    printf(" - Речення має закінчуватись символом '!' або '?'\n\n");
   
    printf("📤 Вихідні дані:\n");
    printf(" - Кількість літер 'д' у реченні, якщо вони присутні\n");
    printf(" - Або модифіковане речення з заголовковими літерами 'А' та 'Я'\n\n");
   
    printf("👨‍💻 Розробник: Yaroslav_Myronenko\n");
    printf("✉ Контактні дані: jarik2707@gmail.com\n");
    printf("🔄 Версія: 1.1\n");
    printf("📅 Рік розробки: 2025\n\n");
   
    printf("🛠 Технічні деталі:\n");
    printf(" - Мова програмування: C\n");
    printf(" - Кодування інтерфейсу: UTF-8\n");
    printf(" - Підтримка кирилиці та латиниці\n");
    printf(" - Використані бібліотеки: stdio.h, stdlib.h, windows.h, locale.h, string.h, conio.h\n\n");
}

void setupInterface() {
    SetConsoleCP(65001);     
    SetConsoleOutputCP(65001); 
    setlocale(LC_ALL, "uk_UA.UTF-8");
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

int is_cyrillic_d(unsigned char first, unsigned char second) {
    return (first == 0xD0 && (second == 0xB4 || second == 0x94));
}

int count_d(const char *sentence) {
    int count = 0;
    int i = 0;
    
    while (sentence[i] != '\0') {
        if ((unsigned char)sentence[i] == 0xD0 && is_cyrillic_d((unsigned char)sentence[i], (unsigned char)sentence[i + 1])) {
            count++;
            i += 2; 
        }
        else if (sentence[i] == 'd' || sentence[i] == 'D') {
            count++;
            i++;
        }
        else {
            i++;
        }
    }
    
    return count;
}

void toggle_a_ya(char *sentence) {
    int i = 0;
    
    while (sentence[i] != '\0') {
        if ((unsigned char)sentence[i] == 0xD0 && (unsigned char)sentence[i + 1] == 0xB0) {
            sentence[i + 1] = 0x90;
            i += 2;
        }
        else if ((unsigned char)sentence[i] == 0xD0 && (unsigned char)sentence[i + 1] == 0x90) {
            i += 2;
        }
        else if ((unsigned char)sentence[i] == 0xD1 && (unsigned char)sentence[i + 1] == 0x8F) {
            sentence[i] = 0xD0;
            sentence[i + 1] = 0xAF;
            i += 2;
        }
        else if ((unsigned char)sentence[i] == 0xD0 && (unsigned char)sentence[i + 1] == 0xAF) {
            i += 2;
        }
        else if (sentence[i] == 'a') {
            sentence[i] = 'A';
            i++;
        }
        else if (sentence[i] == 'A') {
            i++;
        }
        else {
            i++;
        }
    }
}

// Функція для валідації речення
int validateSentence(const char *sentence) {
    int length = strlen(sentence);
    
    if (length == 0) {
        printf("⚠ Помилка: Речення не може бути порожнім.\n");
        return FALSE;
    }
    
    if (length > MAX_SENTENCE_LENGTH - 1) {
        printf("⚠ Помилка: Речення занадто довге (максимум %d символів).\n", MAX_SENTENCE_LENGTH - 1);
        return FALSE;
    }
    
    char last_char = sentence[length - 1];
    if (last_char != '!' && last_char != '?' && last_char != '.') {
        printf("⚠ Помилка: Речення повинно закінчуватися символом '!', '?' або '.'.\n");
        return FALSE;
    } 
    return TRUE;
}

// Функція для отримання речення від користувача
void getSentence(char *sentence, int max_length) {
    int isValid = FALSE;
    
    while (!isValid) {
        printf("Введіть речення (закінчується на '!', '?' або '.'): ");
        fgets(sentence, max_length, stdin);
        
        sentence[strcspn(sentence, "\n")] = '\0';
        
        isValid = validateSentence(sentence);
    }
}

int main() {
    setupInterface();
    showAppInfo();
    printf("Натисніть будь-яку клавішу, щоб продовжити...");
    getch();
    system("cls");
    
    printf("╔═════════════════════════════════════════════╗\n");
    printf("║     ПРОГРАМА АНАЛІЗУ РЕЧЕННЯ                ║\n");
    printf("╚═════════════════════════════════════════════╝\n\n");
    
    char sentence[MAX_SENTENCE_LENGTH];
    
    getSentence(sentence, MAX_SENTENCE_LENGTH);
    
    int d_count = count_d(sentence);
    
    printf("\n📊 Результат обробки:\n");
    
    if (d_count > 0) {
        printf("► Кількість літер 'д' та 'd' у реченні: %d\n", d_count);
    } else {
        printf("► Літери 'д' та 'd' відсутні у реченні.\n");
        printf("► Перетворюємо літери 'а', 'я', 'a' на заголовкові...\n\n");
        
        char original[MAX_SENTENCE_LENGTH];
        strcpy(original, sentence);
        
        toggle_a_ya(sentence);
        
        printf("Початкове речення: %s\n", original);
        printf("Перетворене речення: %s\n", sentence);
    }
    
    printf("\nПрограма завершила роботу. Натисніть будь-яку клавішу...");
    getch();
    
    return 0;
}