#define _CRT_SECURE_NO_WARNINGS
#define DIARYFILE_FORMAT "C:\\Users\\a\\Documents\\Test\\diary_%4d-%02d-%02d.txt" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "functions.h"

bool isPW = false;

// ��й�ȣ ����
void passwordManagement() {
    int select = 0;
    char answer;
    printf("\n\t         ��  ��й�ȣ ���� ��\n\n");
    printf("     # ������ �۾��� �����ϼ���.\n\n");
    printf("     1 - ��й�ȣ ����\n     2 - ��й�ȣ ����\n\n     0 - ����ȭ������ ���ư���\t\t �Է� : ");
    scanf("%d", &select);

    FILE* file = fopen("password.txt", "r");
    if (file != NULL) {
        isPW = true;
        fclose(file);
    }

    while (1) {
        if (select == 0)
            break;
        else if (select == 1) {
            if (isPW == true) {
                printf("\n\n\n     ��й�ȣ�� �̹� �����Ǿ��ֽ��ϴ�. ������ ����� �����ϼ���.\n");
                printf("\n     S - ��й�ȣ �缳��\n     C - ���\t\t\t\t �Է� : ");
                scanf(" %c", &answer);
                getchar();
                system("cls");

                while (1) {
                    if (answer == 's' || answer == 'S') {
                        printf("\n     �� ��й�ȣ Ȯ�� �� �缳���� �����մϴ�.��\n");
                        int exit = checkPassword();
                        if (exit != 1)
                            setPassword();
                        break;
                    }
                    else if (answer == 'c' || answer == 'C') {
                        printf("\n\n   ��й�ȣ �缳���� ����մϴ�. 3�� �� ���� ȭ������ ���ư��ϴ�.");
                        break;
                    }
                    else {
                        printf("\n\n   �߸��� �Է��Դϴ�. �ٽ� �õ����ּ���.\n");
                        printf("\n   S - ��й�ȣ �缳��\n   C - ���\t\t\t\t�Է� : ");
                        while (getchar() != '\n');
                        scanf("%c", &answer);
                    }
                }
                break;
            }
            else {
                setPassword();
                break;
            }
        }
        else if (select == 2) {
            deletePassword();
            break;
        }
        else {
            printf("\n\n   �߸��� �Է��Դϴ�. �ٽ� �õ����ּ���.\n");
            printf("     1 - ��й�ȣ ����\n     2 - ��й�ȣ ����\n\n     0 - �޷����� ���ư���\t\t �Է� : ");
            scanf("%d", &select);
        }
    }
}

// ��й�ȣ �Է�
void inputPassword(char* dFileName, int year, int month, int day) {
    bool isPWentered = false;

    while (!isPWentered) {
        checkPassword();
        if (isPW) {
            diaryFileRead(dFileName, year, month, day);
            isPWentered = true;
        }
    }
}

// ��й�ȣ Ȯ��
int checkPassword() {
    char enteredPassword[5];
    char savedPassword[5];

    printf("\n     # ��й�ȣ�� �Է��ϼ��� : ");
    int attempts = 0;

    while (1) {
        if (attempts > 0) {
            printf("\n     ��й�ȣ�� ��ġ���� �ʽ��ϴ�. �ٽ� �Է��ϼ���.\n");
            printf("\n     0 - ���� ȭ������ ���ư���\t     �Է� : ");
            getchar();
        }

        fgets(enteredPassword, sizeof(enteredPassword), stdin);
        attempts++;
        if (strcmp(enteredPassword, "0") == 0)
            return 1;

        FILE* file = fopen("password.txt", "r");
        if (file == NULL) {
            printf("\n\t������ �� �� �����ϴ�.\n");
            return;
        }
        rewind(file);
        fscanf(file, "%s", savedPassword);
        fclose(file);

        if (strcmp(enteredPassword, savedPassword) == 0) {
            isPW = true;
            break;
        }
    }
}

// ��й�ȣ ����
void setPassword() {
    char password[5];

    FILE* file = fopen("password.txt", "w");
    if (file == NULL) {
        printf("   ������ �� �� �����ϴ�.\n");
        return;
    }

    printf("\n     # ������ ��й�ȣ�� �Է��ϼ���. (4�ڸ� ����): ");
    scanf("%s", password);


    while (1) {
        bool isDigit = false;

        // �Էµ� ��й�ȣ�� ���ڷθ� �����Ǿ����� Ȯ��
        for (int i = 0; i < 4; i++) {
            if (isdigit(password[i]) == false) {
                isDigit = false;
                break;
            }
            else
                isDigit = true;
        }

        if (isDigit == false || strlen(password) != 4) {
            printf("\n     # ��й�ȣ�� �ٽ� �Է��ϼ���. (4�ڸ� ����): ");
            getchar();
            scanf("%s", password);
        }
        else {
            break;
        }
    }
    fprintf(file, "%s", password);
    fclose(file);

    printf("\n\n     ��й�ȣ�� �����Ǿ����ϴ�. 3�� �� ���� ȭ������ ���ư��ϴ�.");
    Sleep(3000);

}

// ��й�ȣ ����
void deletePassword() {
    char pFileName[100];
    char answer;

    printf("\n\n\n     # ��й�ȣ�� ���� �����Ͻðڽ��ϱ�?\n");
    printf("\n     S - ��й�ȣ ����\n\     C - ���\t\t\t\t�Է� : ");
    scanf(" %c", &answer);

    while (1) {
        if (answer == 's' || answer == 'S') {
            system("cls");
            printf("\n\n     ��й�ȣ Ȯ�� �� ������ �����մϴ�.\n");
            getchar();
            checkPassword();

            sprintf(pFileName, "password.txt");
            if (remove(pFileName) != 0) {
                printf("\n\n   ���� ������ �����߽��ϴ�.\n");
                return;
            }
            printf("\n\n   ��й�ȣ ������ �����մϴ�. 3�� �� ���� ȭ������ ���ư��ϴ�.\n");
            Sleep(3000);
            break;
        }
        else if (answer == 'c' || answer == 'C') {
            printf("\n\n   ��й�ȣ ������ ����մϴ�. 3�� �� ���� ȭ������ ���ư��ϴ�.");
            Sleep(3000);
            break;
        }
        else {
            printf("\n\n   �߸��� �Է��Դϴ�. �ٽ� �õ����ּ���.\n");
            printf("\n   S - ��й�ȣ ����\n   C - ���\t\t\t\t�Է� : ");
            getchar();
            scanf(" %c", &answer);
        }
    }
}