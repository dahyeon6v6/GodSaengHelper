#define _CRT_SECURE_NO_WARNINGS
#define DIARYFILE_FORMAT "C:\\Users\\User\\Documents\\Test\\diary_%4d-%02d-%02d.txt"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "functions.h"

// ���̾ �ۼ�
void diaryWrite(int year, int month, int day) {

    struct diary diary;
    strcpy(diary.title, "");
    strcpy(diary.content, "");
    strcpy(diary.emotion, "");

    printf("%4d-%02d-%02d\n", year, month, day);

    printf("������ �Է��ϼ���.\n");
    fgets(diary.title, sizeof(diary.title), stdin);

    printf("������ �Է��ϼ���.\n");
    fgets(diary.content, sizeof(diary.content), stdin);


    printf("������ ������ �Է��ϼ���.\n");
    fgets(diary.emotion, sizeof(diary.emotion), stdin);

    system("cls");

    printf("�ââ� %d�� %d�� %d�� Diary �ââ�\n", year, month, day);
    printf("%s\n", diary.title);
    printf("%s\n", diary.content);
    printf("%s\n", diary.emotion);
    
    diaryFileSave(&diary, year, month, day);
    
}

// ���̾ ����
void diaryFileSave(struct diary* diary, int year, int month, int day) {
    char answer;

    printf("\n�ۼ��� ���̾�� �����Ͻðڽ��ϱ�? ����Ͻðڽ��ϱ�? (S: ����, C: ���): ");
    scanf(" %c", &answer);

    if (answer == 's' || answer == 'S') {
        char dFileName[100];

        sprintf(dFileName, DIARYFILE_FORMAT, year, month, day);

        FILE* fp = fopen(dFileName, "w");

        if (fp == NULL) {
            printf("������ �� �� �����ϴ�.\n");
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
        printf("���̾�� ����Ǿ����ϴ�.\n");


    }
    else if (answer == 'c' || answer == 'C') {
     
    }
    else {
        printf("�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���.\n");
        scanf("%c", &answer);
    }
}


// ���̾ ������ ���� ���� Ȯ��
bool diaryFileExists(char dFileName[], int year, int month, int day) {
    char eFileName[100];

    snprintf(eFileName, sizeof(eFileName), DIARYFILE_FORMAT, year, month, day);
    FILE* file = fopen(dFileName, "r");
    if (file != NULL) {
        fclose(file);
        printf("�ش� ��¥�� �ϱⰡ �����մϴ�.");
        return true;
    }
    else {
        printf("�ش� ��¥�� �ϱⰡ �������� �ʽ��ϴ�.");
        return false;
    }
}

// ���̾ ���� ����ü�迭�� �ҷ�����
void diaryFileRead(char dFileName[], int year, int month, int day) {
    struct diary diary;
    strcpy(diary.title, "");
    strcpy(diary.content, "");
    strcpy(diary.emotion, "");
    char eFileName[100];

    FILE* fp = fopen(dFileName, "r");

    if (fp == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    rewind(fp);
    const int max = 100;
    char line[100];
    int lineNumber = 0;
    char tmp[100];

    printf("�ââ� %d�� %d�� %d�� Diary �ââ�\n", year, month, day);

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

    printf("1. ���̾ �����ϱ�\n");
    printf("2. ���̾ �����ϱ�\n");
    printf("3. To Do ����Ʈ ����â���� �̵�\n");

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
            printf("�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���. : ");
            scanf("%d", &select);
        }
    }
}

// ���̾ ����
void diaryEdit(char dFileName[], struct diary* diary, int year, int month, int day) {
    char eFileName[100];

    printf("���� �� ������ �Է��ϼ���.\n");

    printf("%4d-%02d-%02d\n", year, month, day);

    clear_stdin();
    printf("������ �Է��ϼ���.\n");
    fgets(diary->title, sizeof(diary->title), stdin);

    printf("������ �Է��ϼ���.\n");
    fgets(diary->content, sizeof(diary->content), stdin);

    printf("������ ������ �Է��ϼ���.\n");
    fgets(diary->emotion, sizeof(diary->emotion), stdin);

    system("cls");

    printf("�ââ� %d�� %d�� %d�� Diary �ââ�\n", year, month, day);
    printf("%s\n", diary->title);
    printf("%s\n", diary->content);
    printf("%s\n", diary->emotion);

    diaryFileSave(diary, year, month, day);
}

// ���̾ ����
void diaryDelete(char dFileName[], struct diary* diary, int year, int month, int day) {
    char eFileName[100];

    sprintf(eFileName, DIARYFILE_FORMAT, year, month, day);

    if (remove(eFileName) != 0) {
        printf("���� ������ �����߽��ϴ�.\n");
        return;
    }

    printf("������ ���������� �����߽��ϴ�.\n");

}

// ��й�ȣ ����
void setPassword() {

    FILE* file = fopen("password.txt", "r");
    if (file == NULL) {
        char password[5];

        while (1) {
            printf("���� �� ��й�ȣ 4�ڸ��� �Է����ּ���: ");
            scanf("%s", password);

            if (strlen(password) != 4) {
                printf("4�ڸ��� �ٽ� ������ �ּ���.\n");
                continue;
            }

            file = fopen("password.txt", "a");
            if (file == NULL) {
                printf("������ �� �� �����ϴ�.\n");
                return;
            }

            fprintf(file, "%s", password);
            fclose(file);

            printf("��й�ȣ�� �����Ǿ����ϴ�.\n");
            break;
        }
    }
    else {
        fclose(file);
    }
}

// ��й�ȣ Ȯ��
void checkPassword() {
    char enteredPassword[5];
    char savedPassword[5];
    setPassword();

    printf("��й�ȣ�� �Է��ϼ���: ");
    scanf("%4s", enteredPassword);

    FILE* file = fopen("password.txt", "r");
    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
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

// ��Ʈ�� ���ۻ���
void clear_stdin() {
    int ch;
    while ((ch = getchar()) != EOF && ch != '\n') {};
}