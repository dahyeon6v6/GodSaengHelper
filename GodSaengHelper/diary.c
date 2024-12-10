#define _CRT_SECURE_NO_WARNINGS
#define DIARYFILE_FORMAT "C:\\Users\\a\\Documents\\Test\\diary_%4d-%02d-%02d.txt" 

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
    strcpy(diary.emotion, "");
    strcpy(diary.content, "");
    
    printf("\n\t\t << %4d-%02d-%02d �ϱ� >>\n\n", year, month, day);

    printf("  �� ���� : ");
    fgets(diary.title, sizeof(diary.title), stdin);
    printf("\n");

    printf("  �� ������ ���� : ");
    fgets(diary.emotion, sizeof(diary.emotion), stdin);
    printf("\n");

    printf("  �� ���� : ");
    fgets(diary.content, sizeof(diary.content), stdin);
    printf("\n");

    diaryFileSave(&diary, year, month, day);
}

// ���̾ ����
void diaryFileSave(struct diary* diary, int year, int month, int day) {
    char answer;
    int valid = 0;

    printf("\n   ������������������������������������������������������������������������������������������������������������������\n\n");
    printf("   �ϱ� �ۼ��� �Ϸ�Ǿ����ϴ�. ������ ����� �����ϼ���.\n");

    while (!valid) {
        printf("\n   S - ���̾ ����\n   C - ���\t\t\t\t�Է� : ");
        scanf(" %c", &answer);

        if (answer == 's' || answer == 'S') {
            valid = 1;
            char dFileName[100];

            sprintf(dFileName, DIARYFILE_FORMAT, year, month, day);

            FILE* fp = fopen(dFileName, "w");

            if (fp == NULL) {
                printf("   ������ �� �� �����ϴ�.\n");
                perror("fopen");
                return;
            }

            fprintf(fp, "%s\n", diary->title);
            fprintf(fp, "%s\n", diary->emotion);
            fprintf(fp, "%s\n", diary->content);

            fclose(fp);

            printf("\n\n   ���̾�� ����Ǿ����ϴ�. 3�� �� ���� ȭ������ ���ư��ϴ�.\n");
            Sleep(3000);
            
        }
        else if (answer == 'c' || answer == 'C') {
            valid = 1;
            printf("\n\n   ���̾ �ۼ��� ����մϴ�. 3�� �� ���� ȭ������ ���ư��ϴ�.");
            Sleep(3000);
        }
        else {
            printf("\n\n   �߸��� �Է��Դϴ�. �ٽ� �õ����ּ���.\n");
            printf("\n   S - ���̾ ����\n   C - ���\t\t\t\t�Է� : ");
            scanf(" %c", &answer);
        }
    }
}

// ���̾ ������ ���� ���� Ȯ��
bool diaryFileExists(char dFileName[], int year, int month, int day) {
    char eFileName[100];

    snprintf(eFileName, sizeof(eFileName), DIARYFILE_FORMAT, year, month, day);
    FILE* file = fopen(dFileName, "r");
    if (file != NULL) {
        fclose(file);
        printf("\n   ����������������������������������  << �� �� >> ������������������������������������\n");
        printf("   ��                                               ��\n");
        printf("   ��                                               ��\n");
        printf("   ��        �ش� ��¥�� �ϱⰡ �����մϴ�.         ��\n");
        printf("   ��                                               ��\n");
        printf("   ��������������������������������������������������������������������������������������������������");

        return true;
    }
    else {
        printf("\n   ����������������������������������  << �� �� >> ������������������������������������\n");
        printf("   ��                                               ��\n");
        printf("   ��                                               ��\n");
        printf("   ��     �ش� ��¥�� �ϱⰡ �������� �ʽ��ϴ�.     ��\n");
        printf("   ��                                               ��\n");
        printf("   ��������������������������������������������������������������������������������������������������");
        return false;
    }
}

// ���̾ ���� ����ü�迭�� �ҷ�����
void diaryFileRead(char dFileName[], int year, int month, int day) {
    struct diary diary;
    strcpy(diary.emotion, "");
    strcpy(diary.title, "");
    strcpy(diary.content, "");
    char eFileName[100];

    FILE* fp = fopen(dFileName, "r");

    if (fp == NULL) {
        printf("   ������ �� �� �����ϴ�.\n");
        return;
    }

    rewind(fp);
    const int max = 100;
    char line[100];
    int lineNumber = 0;
    char tmp[100];

    printf("\n   ��������������������������������  << % d�� %d�� % d�� Diary >> ��������������������������������\n", year, month, day);
    printf("\n");

    while (fgets(line, max, fp) != NULL) {
        if (lineNumber == 0) {
            sscanf(line, "%[^\n]", diary.title);
            printf("      �� ���� : %s\n", diary.title);
            printf("\n");

        }
        else if (lineNumber == 2) {
            sscanf(line, "%[^\n]", diary.emotion);
            printf("      �� ������ ���� : %s\n", diary.emotion);
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
    printf("      �� ���� : ");
    printf("%s\n", diary.content);
    printf("   ��������������������������������������������������������������������������������������������������������������������������������\n");

    fclose(fp);

    printf("\n\n   # ������ ����� �����ϼ���.\n\n");
    printf("   1 - �ϱ� ���ۼ�\n");
    printf("   2 - �ϱ� ����\n\n");
    printf("   0 - ���� ȭ������ �̵�\t\t�Է� : ");

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
            printf("\n\n   # �߸� �Է��ϼ̽��ϴ�. �ٽ� �����ϼ���.\n\n");
            printf("\t\t\t\t\t�Է� : ");
            scanf("%d", &select);
        }
    }
}

// ���̾ ����
void diaryDelete(char dFileName[], struct diary* diary, int year, int month, int day) {
    char eFileName[100];

    sprintf(eFileName, DIARYFILE_FORMAT, year, month, day);

    if (remove(eFileName) != 0) {
        printf("\n\n   ���� ������ �����߽��ϴ�.\n");
        return;
    }

    printf("\n\n   �ϱ� ������ �����մϴ�. 3�� �� ���� ȭ������ ���ư��ϴ�.\n");
    Sleep(3000);
}

// ��Ʈ�� ���ۻ���
void clear_stdin() {
    int ch;
    while ((ch = getchar()) != EOF && ch != '\n') {};
}