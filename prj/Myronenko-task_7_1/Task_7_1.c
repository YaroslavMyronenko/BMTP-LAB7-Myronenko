#include <stdio.h>
#include <string.h>
#include <locale.h>

// Функція для підрахунку кількості літер 'д' у реченні
int count_d(const char *sentence) {
    int count = 0;
    for (int i = 0; sentence[i] != '\0'; i++) {
        if ((unsigned char)sentence[i] == 0xD0 && (unsigned char)sentence[i + 1] == 0xB4) {  
            count++;
            i++; 
        } else if ((unsigned char)sentence[i] == 0xD0 && (unsigned char)sentence[i + 1] == 0x94) {  
            count++;
            i++;
        }
    }
    return count;
}

// Функція для перетворення літер 'а' та 'я' на заголовковi
void toggle_a_ya(char *sentence) {
    for (int i = 0; sentence[i] != '\0'; i++) {
        if ((unsigned char)sentence[i] == 0xD0 && (unsigned char)sentence[i + 1] == 0xB0) { 
            sentence[i + 1] = 0x90;  
        } else if ((unsigned char)sentence[i] == 0xD0 && (unsigned char)sentence[i + 1] == 0x90) { 
            sentence[i + 1] = 0xB0; 
        } else if ((unsigned char)sentence[i] == 0xD1 && (unsigned char)sentence[i + 1] == 0x8F) { 
            sentence[i] = 0xD0;      
            sentence[i + 1] = 0xAF;  
        } else if ((unsigned char)sentence[i] == 0xD0 && (unsigned char)sentence[i + 1] == 0xAF) { 
            sentence[i] = 0xD1;      
            sentence[i + 1] = 0x8F; 
        }
    }
}

int main() {
    setlocale(LC_ALL, "uk_UA.UTF-8");

    char sentence[256];
    printf("Введіть речення (закінчується на '!', '?' або '.'): ");
    fgets(sentence, sizeof(sentence), stdin);

    sentence[strcspn(sentence, "\n")] = '\0';

    char last_char = sentence[strlen(sentence) - 1];
    if (last_char != '!' && last_char != '?' && last_char != '.') {
        printf("Речення не закінчується на '!', '?' або '.'.\n");
        return 1;
    }

    int d_count = count_d(sentence);

    if (d_count > 0) {
        printf("Кількість літер 'д' у реченні: %d\n", d_count);
    } else {
        toggle_a_ya(sentence);
        printf("Перетворене речення: %s\n", sentence);
    }

    return 0;
}
