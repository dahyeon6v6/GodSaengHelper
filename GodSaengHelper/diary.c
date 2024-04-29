#define _CRT_SECURE_NO_WARNINGS
#define DIARYFILE_FORMAT "C:\\Users\\User\\Documents\\Test\\diary_%4d-%02d-%02d.txt"
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
    strcpy(diary.content, "");
    strcpy(diary.emotion, "");

    printf("%4d-%02d-%02d\n", year, month, day);

    printf("제목을 입력하세요.\n");
    fgets(diary.title, sizeof(diary.title), stdin);

    printf("내용을 입력하세요.\n");
    fgets(diary.content, sizeof(diary.content), stdin);


    printf("오늘의 감정을 입력하세요.\n");
    fgets(diary.emotion, sizeof(diary.emotion), stdin);

    system("cls");

    printf("▣▣▣ %d년 %d월 %d일 Diary ▣▣▣\n", year, month, day);
    printf("%s\n", diary.title);
    printf("%s\n", diary.content);
    printf("%s\n", diary.emotion);
    
    diaryFileSave(&diary, year, month, day);
    
}

// 다이어리 저장
void diaryFileSave(struct diary* diary, int year, int month, int day) {
    char answer;

    printf("\n작성된 다이어리를 저장하시겠습니까? 취소하시겠습니까? (S: 저장, C: 취소): ");
    scanf(" %c", &answer);

    if (answer == 's' || answer == 'S') {
        char dFileName[100];

        sprintf(dFileName, DIARYFILE_FORMAT, year, month, day);

        FILE* fp = fopen(dFileName, "w");

        if (fp == NULL) {
            printf("파일을 열 수 없습니다.\n");
            perror("fopen");
            return;
        }
      
        printf("%s\n", diary->title);
        printf("%s\n", diary->content);
        printf("%s\n", diary->emotion);

        fprintf(fp, "%s\n", diary->emotion);
        fprintf(fp, "%s\n", diary->title);
        fprintf(fp, "%s\n", diary->content);

        fclose(fp);
        printf("다이어리가 저장되었습니다.\n");


    }
    else if (answer == 'c' || answer == 'C') {
     
    }
    else {
        printf("잘못된 입력입니다. 다시 시도해주세요.\n");
        scanf("%c", &answer);
    }
}


// 다이어리 파일의 존재 여부 확인
bool diaryFileExists(char dFileName[], int year, int month, int day) {
    char eFileName[100];

    snprintf(eFileName, sizeof(eFileName), DIARYFILE_FORMAT, year, month, day);
    FILE* file = fopen(dFileName, "r");
    if (file != NULL) {
        fclose(file);
        printf("해당 날짜에 일기가 존재합니다.");
        return true;
    }
    else {
        printf("해당 날짜에 일기가 존재하지 않습니다.");
        return false;
    }
}

// 다이어리 파일 구조체배열에 불러오기
void diaryFileRead(char dFileName[], int year, int month, int day) {
    struct diary diary;
    strcpy(diary.title, "");
    strcpy(diary.content, "");
    strcpy(diary.emotion, "");
    char eFileName[100];

    FILE* fp = fopen(dFileName, "r");

    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    rewind(fp);
    const int max = 100;
    char line[100];
    int lineNumber = 0;
    char tmp[100];

    printf("▣▣▣ %d년 %d월 %d일 Diary ▣▣▣\n", year, month, day);

    while (fgets(line, max, fp) != NULL) {
        if (lineNumber == 0) {
            sscanf(line, "%[^\n]", diary.emotion);
            printf("%s\n", diary.emotion);
        }
        else if (lineNumber == 1) {
            sscanf(line, "%[^\n]", diary.title);
            printf("%s\n", diary.title);
        }
        else if (lineNumber == 2) {
            tmp[0] = '\0';
            sscanf(line, "%[^\n]", tmp);
            strcpy(diary.content, tmp);
            strcat(diary.content, "\n");
        }
        else {
            tmp[0] = '\0';
            sscanf(line, "%[^\n]", tmp);
            strcat(diary.content, tmp);
            strcat(diary.content, "\n");
        }
        lineNumber++;
    }

    printf("%s\n", diary.content);


    fclose(fp);

    printf("1. 다이어리 편집하기\n");
    printf("2. 다이어리 삭제하기\n");
    printf("3. To Do 리스트 편집창으로 이동\n");

    int select;
    scanf("%d",&select );
     
    while (1) {
        if (select == 1) {
            diaryEdit(dFileName, &diary, year, month, day);
            break;
        }
        if (select == 2) {
            diaryDelete(dFileName, &diary, year, month, day);
            break;
        }
        if (select == 3) {
            break;
        }
        else {
            printf("잘못 입력하셨습니다. 다시 입력해주세요. : ");
            scanf("%d", &select);
        }
    }
}

// 다이어리 수정
void diaryEdit(char dFileName[], struct diary* diary, int year, int month, int day) {
    char eFileName[100];

    printf("수정 할 내용을 입력하세요.\n");

    printf("%4d-%02d-%02d\n", year, month, day);

    clear_stdin();
    printf("제목을 입력하세요.\n");
    fgets(diary->title, sizeof(diary->title), stdin);

    printf("내용을 입력하세요.\n");
    fgets(diary->content, sizeof(diary->content), stdin);

    printf("오늘의 감정을 입력하세요.\n");
    fgets(diary->emotion, sizeof(diary->emotion), stdin);

    system("cls");

    printf("▣▣▣ %d년 %d월 %d일 Diary ▣▣▣\n", year, month, day);
    printf("%s\n", diary->title);
    printf("%s\n", diary->content);
    printf("%s\n", diary->emotion);

    diaryFileSave(diary, year, month, day);
}

// 다이어리 삭제
void diaryDelete(char dFileName[], struct diary* diary, int year, int month, int day) {
    char eFileName[100];

    sprintf(eFileName, DIARYFILE_FORMAT, year, month, day);

    if (remove(eFileName) != 0) {
        printf("파일 삭제에 실패했습니다.\n");
        return;
    }

    printf("파일을 성공적으로 삭제했습니다.\n");

}

// 비밀번호 설정
void setPassword() {

    FILE* file = fopen("password.txt", "r");
    if (file == NULL) {
        char password[5];

        while (1) {
            printf("설정 할 비밀번호 4자리를 입력해주세요: ");
            scanf("%s", password);

            if (strlen(password) != 4) {
                printf("4자리로 다시 설정해 주세요.\n");
                continue;
            }

            file = fopen("password.txt", "a");
            if (file == NULL) {
                printf("파일을 열 수 없습니다.\n");
                return;
            }

            fprintf(file, "%s", password);
            fclose(file);

            printf("비밀번호가 설정되었습니다.\n");
            break;
        }
    }
    else {
        fclose(file);
    }
}

// 비밀번호 확인
void checkPassword() {
    char enteredPassword[5];
    char savedPassword[5];
    setPassword();

    printf("비밀번호를 입력하세요: ");
    scanf("%4s", enteredPassword);

    FILE* file = fopen("password.txt", "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    fscanf(file, "%s", savedPassword);
    fclose(file);

    if (strcmp(enteredPassword, savedPassword) == 0) {
        isPW = true;
    }
    else {
        isPW = false;
    }

    system("cls");
}

// 스트림 버퍼삭제
void clear_stdin() {
    int ch;
    while ((ch = getchar()) != EOF && ch != '\n') {};
}