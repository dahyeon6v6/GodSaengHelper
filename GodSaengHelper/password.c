#define _CRT_SECURE_NO_WARNINGS
#define DIARYFILE_FORMAT "C:\\Users\\a\\Documents\\Test\\diary_%4d-%02d-%02d.txt" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "functions.h"

bool isPW = false;

// 비밀번호 관리
void passwordManagement() {
    int select = 0;
    char answer;
    printf("\n\t         ◈  비밀번호 관리 ◈\n\n");
    printf("     # 수행할 작업을 선택하세요.\n\n");
    printf("     1 - 비밀번호 설정\n     2 - 비밀번호 삭제\n\n     0 - 이전화면으로 돌아가기\t\t 입력 : ");
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
                printf("\n\n\n     비밀번호가 이미 설정되어있습니다. 수행할 기능을 선택하세요.\n");
                printf("\n     S - 비밀번호 재설정\n     C - 취소\t\t\t\t 입력 : ");
                scanf(" %c", &answer);
                getchar();
                system("cls");

                while (1) {
                    if (answer == 's' || answer == 'S') {
                        printf("\n     ◈ 비밀번호 확인 후 재설정을 진행합니다.◈\n");
                        int exit = checkPassword();
                        if (exit != 1)
                            setPassword();
                        break;
                    }
                    else if (answer == 'c' || answer == 'C') {
                        printf("\n\n   비밀번호 재설정을 취소합니다. 3초 뒤 이전 화면으로 돌아갑니다.");
                        break;
                    }
                    else {
                        printf("\n\n   잘못된 입력입니다. 다시 시도해주세요.\n");
                        printf("\n   S - 비밀번호 재설정\n   C - 취소\t\t\t\t입력 : ");
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
            printf("\n\n   잘못된 입력입니다. 다시 시도해주세요.\n");
            printf("     1 - 비밀번호 설정\n     2 - 비밀번호 삭제\n\n     0 - 달력으로 돌아가기\t\t 입력 : ");
            scanf("%d", &select);
        }
    }
}

// 비밀번호 입력
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

// 비밀번호 확인
int checkPassword() {
    char enteredPassword[5];
    char savedPassword[5];

    printf("\n     # 비밀번호를 입력하세요 : ");
    int attempts = 0;

    while (1) {
        if (attempts > 0) {
            printf("\n     비밀번호가 일치하지 않습니다. 다시 입력하세요.\n");
            printf("\n     0 - 이전 화면으로 돌아가기\t     입력 : ");
            getchar();
        }

        fgets(enteredPassword, sizeof(enteredPassword), stdin);
        attempts++;
        if (strcmp(enteredPassword, "0") == 0)
            return 1;

        FILE* file = fopen("password.txt", "r");
        if (file == NULL) {
            printf("\n\t파일을 열 수 없습니다.\n");
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

// 비밀번호 설정
void setPassword() {
    char password[5];

    FILE* file = fopen("password.txt", "w");
    if (file == NULL) {
        printf("   파일을 열 수 없습니다.\n");
        return;
    }

    printf("\n     # 설정할 비밀번호를 입력하세요. (4자리 숫자): ");
    scanf("%s", password);


    while (1) {
        bool isDigit = false;

        // 입력된 비밀번호가 숫자로만 구성되었는지 확인
        for (int i = 0; i < 4; i++) {
            if (isdigit(password[i]) == false) {
                isDigit = false;
                break;
            }
            else
                isDigit = true;
        }

        if (isDigit == false || strlen(password) != 4) {
            printf("\n     # 비밀번호를 다시 입력하세요. (4자리 숫자): ");
            getchar();
            scanf("%s", password);
        }
        else {
            break;
        }
    }
    fprintf(file, "%s", password);
    fclose(file);

    printf("\n\n     비밀번호가 설정되었습니다. 3초 뒤 이전 화면으로 돌아갑니다.");
    Sleep(3000);

}

// 비밀번호 삭제
void deletePassword() {
    char pFileName[100];
    char answer;

    printf("\n\n\n     # 비밀번호를 정말 삭제하시겠습니까?\n");
    printf("\n     S - 비밀번호 삭제\n\     C - 취소\t\t\t\t입력 : ");
    scanf(" %c", &answer);

    while (1) {
        if (answer == 's' || answer == 'S') {
            system("cls");
            printf("\n\n     비밀번호 확인 후 삭제를 진행합니다.\n");
            getchar();
            checkPassword();

            sprintf(pFileName, "password.txt");
            if (remove(pFileName) != 0) {
                printf("\n\n   파일 삭제에 실패했습니다.\n");
                return;
            }
            printf("\n\n   비밀번호 파일을 삭제합니다. 3초 뒤 이전 화면으로 돌아갑니다.\n");
            Sleep(3000);
            break;
        }
        else if (answer == 'c' || answer == 'C') {
            printf("\n\n   비밀번호 삭제를 취소합니다. 3초 뒤 이전 화면으로 돌아갑니다.");
            Sleep(3000);
            break;
        }
        else {
            printf("\n\n   잘못된 입력입니다. 다시 시도해주세요.\n");
            printf("\n   S - 비밀번호 삭제\n   C - 취소\t\t\t\t입력 : ");
            getchar();
            scanf(" %c", &answer);
        }
    }
}