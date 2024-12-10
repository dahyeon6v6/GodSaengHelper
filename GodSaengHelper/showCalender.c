#define TODOFILE_FORMAT "C:\\Users\\a\\Documents\\Test\\todolist_%4d-%02d-%02d.txt"
#define DIARYFILE_FORMAT "C:\\Users\\a\\Documents\\Test\\diary_%4d-%02d-%02d.txt"  
#include <stdbool.h>
#include <stdio.h>

bool toDo(int year, int month, int day) {
    char tFileName[100];
    snprintf(tFileName, sizeof(tFileName), TODOFILE_FORMAT, year, month, day);
    FILE* file = fopen(tFileName, "r");
    if (file != NULL) {
        char c = fgetc(file);
        fclose(file);
        if (c == '0' || c == '1')
            return true;
        else
            return false;
    }
    else {
        return false;
    }
}

bool writeDiary(int year, int month, int day) {
    char dFileName[50];
    snprintf(dFileName, sizeof(dFileName), DIARYFILE_FORMAT, year, month, day);
    FILE* file = fopen(dFileName, "r");
    if (file != NULL) {
        fclose(file);
        return true;
    }
    else {
        return false;
    }
}

void showCalender(int startDay, int nowYear, int nowMonth) {
    int totalDay = lastDayOfMonth(nowYear, nowMonth);

    printf("\n\t\t\t\t      \033[1;33m\u250f\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2513\033[0m");
    printf("\n\t\033[1;33m      ≡≡≡≡≡≡≡≡≡≡≡≡\u2503 %d년 %02d월\u2503≡≡≡≡≡≡≡≡≡≡≡≡\033[0m\n", nowYear, nowMonth);
    printf("\t\t\t\t      \033[1;33m\u2517\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u251b\n\n\033[0m");
    printf("\t    \u250f\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2513\n");
    printf("\t    \u2503   \033[1;31m일\033[0m   \u2503   월   \u2503   화   \u2503   수   \u2503   목   \u2503   금   \u2503   \033[1;34m토\033[0m   \u2503\n");
    printf("\t    \u2523\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254b\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254b\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254b\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254b\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254b\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254b\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u252b\n");
    printf("\t    ");
    for (int i = 0; i < startDay; i++)
        printf("\u2503        ");
    int count = startDay;
    for (int i = 1; i <= totalDay; i++) {
        if (count == 7) {    // 요일별로 출력되도록 줄바꿈
            printf("\u2503\n\t    \u2503        \u2503        \u2503        \u2503        \u2503        \u2503        \u2503        \u2503\n\t    \u2503\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254b\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254b\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254b\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254b\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254b\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254b\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u252b\n\t    ");
            count = 0;
        }
        // 조건에 따라 기호를 선택하여 출력
        if (toDo(nowYear, nowMonth, i) == true && writeDiary(nowYear, nowMonth, i) == true) {
            if (count == 6) {
                printf("\u2503 \033[1;34m%2d\033[0m \033[1;35m♥\033[0m\033[1;32m★\033[0m", i);
            }
            else if (count == 0) {
                printf("\u2503 \033[1;31m%2d\033[0m \033[1;35m♥\033[0m\033[1;32m★\033[0m", i);
            }
            else {
                printf("\u2503 %2d \033[1;35m♥\033[0m\033[1;32m★\033[0m", i);
            }
        }
        else if (toDo(nowYear, nowMonth, i) == true) {
            if (count == 6) {
                printf("\u2503 \033[1;34m%2d\033[0m \033[1;35m♥\033[0m  ", i);
            }
            else if (count == 0) {
                printf("\u2503 \033[1;31m%2d\033[0m \033[1;35m♥\033[0m  ", i);
            }
            else {
                printf("\u2503 %2d \033[1;35m♥\033[0m  ", i);
            }
        }
        else if (writeDiary(nowYear, nowMonth, i) == true) {
            if (count == 6) {
                printf("\u2503 \033[1;34m%2d\033[0m  \033[1;32m★\033[0m ", i);
            }
            else if (count == 0) {
                printf("\u2503 \033[1;31m%2d\033[0m  \033[1;32m★\033[0m ", i);
            }
            else {
                printf("\u2503 %2d  \033[1;32m★\033[0m ", i);
            }
        }
        else {
            if (count == 6) {
                printf("\u2503 \033[1;34m%2d\033[0m     ", i);
            }
            else if (count == 0) {
                printf("\u2503 \033[1;31m%2d\033[0m     ", i);
            }
            else {
                printf("\u2503 %2d     ", i);
            }
        }
        count++;
    }
    for (int i = count; i < 7; i++) // 마지막 주의 나머지 날짜에 공백 출력
        printf("\u2503        ");
    printf("\u2503\n\t    \u2503        \u2503        \u2503        \u2503        \u2503        \u2503        \u2503        \u2503\n    ");
    printf("\t    \u2517\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u253b\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u253b\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u253b\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u253b\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u253b\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u253b\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u251b\n");
}