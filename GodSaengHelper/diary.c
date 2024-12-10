#define _CRT_SECURE_NO_WARNINGS
#define DIARYFILE_FORMAT "C:\\Users\\a\\Documents\\Test\\diary_%4d-%02d-%02d.txt" 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "functions.h"

// 다이어리 작성
void diaryWrite(int year, int month, int day) {

    struct diary diary;
    strcpy(diary.title, "");
    strcpy(diary.emotion, "");
    strcpy(diary.content, "");
    
    printf("\n\t\t << %4d-%02d-%02d 일기 >>\n\n", year, month, day);

    printf("  ▶ 제목 : ");
    fgets(diary.title, sizeof(diary.title), stdin);
    printf("\n");

    printf("  ▶ 오늘의 감정 : ");
    fgets(diary.emotion, sizeof(diary.emotion), stdin);
    printf("\n");

    printf("  ▶ 내용 : ");
    fgets(diary.content, sizeof(diary.content), stdin);
    printf("\n");

    diaryFileSave(&diary, year, month, day);
}

// 다이어리 저장
void diaryFileSave(struct diary* diary, int year, int month, int day) {
    char answer;
    int valid = 0;

    printf("\n   ─────────────────────────────────────────────────────────\n\n");
    printf("   일기 작성이 완료되었습니다. 수행할 기능을 선택하세요.\n");

    while (!valid) {
        printf("\n   S - 다이어리 저장\n   C - 취소\t\t\t\t입력 : ");
        scanf(" %c", &answer);

        if (answer == 's' || answer == 'S') {
            valid = 1;
            char dFileName[100];

            sprintf(dFileName, DIARYFILE_FORMAT, year, month, day);

            FILE* fp = fopen(dFileName, "w");

            if (fp == NULL) {
                printf("   파일을 열 수 없습니다.\n");
                perror("fopen");
                return;
            }

            fprintf(fp, "%s\n", diary->title);
            fprintf(fp, "%s\n", diary->emotion);
            fprintf(fp, "%s\n", diary->content);

            fclose(fp);

            printf("\n\n   다이어리가 저장되었습니다. 3초 뒤 이전 화면으로 돌아갑니다.\n");
            Sleep(3000);
            
        }
        else if (answer == 'c' || answer == 'C') {
            valid = 1;
            printf("\n\n   다이어리 작성을 취소합니다. 3초 뒤 이전 화면으로 돌아갑니다.");
            Sleep(3000);
        }
        else {
            printf("\n\n   잘못된 입력입니다. 다시 시도해주세요.\n");
            printf("\n   S - 다이어리 저장\n   C - 취소\t\t\t\t입력 : ");
            scanf(" %c", &answer);
        }
    }
}

// 다이어리 파일의 존재 여부 확인
bool diaryFileExists(char dFileName[], int year, int month, int day) {
    char eFileName[100];

    snprintf(eFileName, sizeof(eFileName), DIARYFILE_FORMAT, year, month, day);
    FILE* file = fopen(dFileName, "r");
    if (file != NULL) {
        fclose(file);
        printf("\n   ┏━━━━━━━━━━━━━━━━  << 일 기 >> ━━━━━━━━━━━━━━━━━┓\n");
        printf("   ┃                                               ┃\n");
        printf("   ┃                                               ┃\n");
        printf("   ┃        해당 날짜에 일기가 존재합니다.         ┃\n");
        printf("   ┃                                               ┃\n");
        printf("   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

        return true;
    }
    else {
        printf("\n   ┏━━━━━━━━━━━━━━━━  << 일 기 >> ━━━━━━━━━━━━━━━━━┓\n");
        printf("   ┃                                               ┃\n");
        printf("   ┃                                               ┃\n");
        printf("   ┃     해당 날짜에 일기가 존재하지 않습니다.     ┃\n");
        printf("   ┃                                               ┃\n");
        printf("   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
        return false;
    }
}

// 다이어리 파일 구조체배열에 불러오기
void diaryFileRead(char dFileName[], int year, int month, int day) {
    struct diary diary;
    strcpy(diary.emotion, "");
    strcpy(diary.title, "");
    strcpy(diary.content, "");
    char eFileName[100];

    FILE* fp = fopen(dFileName, "r");

    if (fp == NULL) {
        printf("   파일을 열 수 없습니다.\n");
        return;
    }

    rewind(fp);
    const int max = 100;
    char line[100];
    int lineNumber = 0;
    char tmp[100];

    printf("\n   ━━━━━━━━━━━━━━━━  << % d년 %d월 % d일 Diary >> ━━━━━━━━━━━━━━━━\n", year, month, day);
    printf("\n");

    while (fgets(line, max, fp) != NULL) {
        if (lineNumber == 0) {
            sscanf(line, "%[^\n]", diary.title);
            printf("      ▶ 제목 : %s\n", diary.title);
            printf("\n");

        }
        else if (lineNumber == 2) {
            sscanf(line, "%[^\n]", diary.emotion);
            printf("      ▶ 오늘의 감정 : %s\n", diary.emotion);
            printf("\n");
        }
        else if (lineNumber == 4) {
            tmp[0] = '\0';
            sscanf(line, "%[^\n]", tmp);
            strcat(diary.content, tmp);
            strcat(diary.content, "\n");
        }
        else if (lineNumber > 4) {
            tmp[0] = '\0';
            sscanf(line, "%[^\n]", tmp);
            strcat(diary.content, "\t");
            strcat(diary.content, tmp);
            strcat(diary.content, "\n");
        }
        lineNumber++;
    }
    printf("      ▶ 내용 : ");
    printf("%s\n", diary.content);
    printf("   ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

    fclose(fp);

    printf("\n\n   # 수행할 기능을 선택하세요.\n\n");
    printf("   1 - 일기 재작성\n");
    printf("   2 - 일기 삭제\n\n");
    printf("   0 - 이전 화면으로 이동\t\t입력 : ");

    int select;
    scanf("%d", &select);

    while (1) {
        if (select == 1) {
            system("cls");
            clear_stdin();
            diaryWrite(year, month, day);
            break;
        }
        if (select == 2) {
            diaryDelete(dFileName, &diary, year, month, day);
            break;
        }
        if (select == 0) {
            break;
        }
        else {
            printf("\n\n   # 잘못 입력하셨습니다. 다시 선택하세요.\n\n");
            printf("\t\t\t\t\t입력 : ");
            scanf("%d", &select);
        }
    }
}

// 다이어리 삭제
void diaryDelete(char dFileName[], struct diary* diary, int year, int month, int day) {
    char eFileName[100];

    sprintf(eFileName, DIARYFILE_FORMAT, year, month, day);

    if (remove(eFileName) != 0) {
        printf("\n\n   파일 삭제에 실패했습니다.\n");
        return;
    }

    printf("\n\n   일기 파일을 삭제합니다. 3초 뒤 이전 화면으로 돌아갑니다.\n");
    Sleep(3000);
}

// 스트림 버퍼삭제
void clear_stdin() {
    int ch;
    while ((ch = getchar()) != EOF && ch != '\n') {};
}