#define _CRT_SECURE_NO_WARNINGS
#define TODOFILE_FORMAT "C:\\Users\\a\\Documents\\Test\\todolist_%4d-%02d-%02d.txt"
#define DIARYFILE_FORMAT "C:\\Users\\a\\Documents\\Test\\diary_%4d-%02d-%02d.txt" 
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "functions.h"

void printTodoList(struct todoList* todo) {
    system("cls");
    printf("\n");
    printf("\n   ��������������  << % d�� % d�� % d�� To Do List >> ��������������\n", todo->tYear, todo->tMonth, todo->tDay);
    printf("   ��                                                 ��\n");
    printf("   ��                                                 ��\n");
    if (todo->tCount == 0)//����
        printf("   ��\t        %-19s              ��\n", "��ϵ� todo�� �����ϴ�.");//
    else {//
        for (int i = 0; i < todo->tCount; i++) {
            printf("   ��\t %d) %-19s", i + 1, todo->todoDetail[i].content);
            if (todo->todoDetail[i].complete == true)
                printf("\t\t[\033[1;31mV\033[0m]          ��\n");
            else
                printf("\t\t[ ]          ��\n");
        }
    }//
    printf("   ��                                                 ��\n");
    printf("   ��                                                 ��\n");
    printf("   ������������������������������������������������������������������������������������������������������");
    printf("\n");
    printf("\n");
}

void todoListWrite(char fileName[], struct todoList* todo) {
    
    printf("\n\n   �߰��� To Do �Է� : ");
    if (todo->tCount == 0) {
        FILE* todoFile = fopen(fileName, "w");
        if (todoFile == NULL) {
            printf("   ���� �б⿡ �����߽��ϴ�.\n");
            return -1;
        }
        fputc('0', todoFile);

        char inContent[100];
        getchar();
        scanf("%[^\n]", &inContent);
        fputs(inContent, todoFile);
        fputc('\n', todoFile);

        todo->tCount++;
        getchar();//
        fclose(todoFile);
    }
    else {
        FILE* todoFile = fopen(fileName, "a");
        if (todoFile == NULL) {
            printf("   ���� �б⿡ �����߽��ϴ�.\n");
            return -1;
        }
        fputc('0', todoFile);

        char inContent[100];
        getchar();
        scanf("%[^\n]", &inContent);
        fputs(inContent, todoFile);
        fputc('\n', todoFile);

        todo->tCount++;
        getchar();//
        fclose(todoFile);
    }
}

void todoSimpleRead(struct todoList* todo) {
    char fileName[100];
    snprintf(fileName, sizeof(fileName), TODOFILE_FORMAT, todo->tYear, todo->tMonth, todo->tDay);
    FILE* todoFile = fopen(fileName, "r+");
    if (todoFile == NULL) {
        todoFile = fopen(fileName, "w+");
        if (todoFile == NULL) {
            printf("   ���� ������ �����߽��ϴ�.\n");
            return -1;
        }
    }
    rewind(todoFile);  // ���� �����͸� ������ �������� �̵�
    const int max = 100;
    char line[100];
    int wCount = 0;
    while (fgets(line, max, todoFile) != NULL) {
        char complete;
        char content[100];
        sscanf(line, " %c %[^\n]", &complete, content);
        todo->todoDetail[wCount].complete = (complete == '1');
        strcpy(todo->todoDetail[wCount].content, content);
        wCount++;
    }
    todo->tCount = wCount;
    fclose(todoFile);
    return 0;
}

void completeTodoList(char fileName[], struct todoList* todo) {
    printf("\n\n   �Ϸ� ó���� �׸��� ��ȣ�� �Է����ּ��� : ");
    int selectTodo;
    scanf("%d", &selectTodo);
    selectTodo--;

    if (selectTodo < 0 || selectTodo >= todo->tCount) {
        printf("   �߸��� �Է��Դϴ�.\n");
        return;
    }

    FILE* originalFile = fopen(fileName, "r");
    if (originalFile == NULL) {
        printf("   ���� ���⿡ �����߽��ϴ�.\n");
        return;
    }

    FILE* newFile = fopen("temp.txt", "w");
    if (newFile == NULL) {
        printf("   �� ���� ������ �����߽��ϴ�.\n");
        fclose(originalFile);
    }
    rewind(originalFile);
    char line[100];
    int lineNumber = 0;
    while (fgets(line, sizeof(line), originalFile) != NULL) {
        if (lineNumber != selectTodo)
            fputs(line, newFile);
        else if (lineNumber == selectTodo) {
            line[0] = '1';
            fputs(line, newFile);
        }
        lineNumber++;
    }

    fclose(originalFile);
    fclose(newFile);

    if (remove(fileName) != 0) {
        printf("   ���� ���� ������ �����߽��ϴ�.\n");
        return;
    }
    if (rename("temp.txt", fileName) != 0) {
        printf("   �� ���� �̸� ���濡 �����߽��ϴ�.\n");
        return;
    }
}

void deleteTodoList(char fileName[], struct todoList* todo) {
    printf("\n\n   ������ �׸��� ��ȣ�� �Է����ּ���. : ");
    int selectTodo;
    scanf("%d", &selectTodo);
    selectTodo--;

    if (selectTodo < 0 || selectTodo >= todo->tCount) {
        printf("   ��ȿ���� ���� ��ȣ�Դϴ�.\n");
        return;
    }

    FILE* originalFile = fopen(fileName, "r");
    if (originalFile == NULL) {
        printf("   ���� ���⿡ �����߽��ϴ�.\n");
        return;
    }

    FILE* newFile = fopen("temp.txt", "w");
    if (newFile == NULL) {
        printf("   �� ���� ������ �����߽��ϴ�.\n");
        fclose(originalFile);
        return;
    }

    rewind(originalFile);
    char line[100];
    int lineNumber = 0;


    while (fgets(line, sizeof(line), originalFile) != NULL) {
        if (lineNumber != selectTodo) {
            fputs(line, newFile);
        }
        lineNumber++;
    }
    todo->tCount--;

    fclose(originalFile);
    fclose(newFile);


    if (remove(fileName) != 0) {
        printf("   ���� ���� ������ �����߽��ϴ�.\n");
        return;
    }
    if (rename("temp.txt", fileName) != 0) {
        printf("   �� ���� �̸� ���濡 �����߽��ϴ�.\n");
        return;
    }
}

void todoListDetailRead(struct todoList* todo) {
    int command = 0;

    char fileName[100];
    snprintf(fileName, sizeof(fileName), TODOFILE_FORMAT, todo->tYear, todo->tMonth, todo->tDay);

    while (1) {

        todoSimpleRead(todo);
        printTodoList(todo);

        printf("\n   ������������������������������������������������������������������������������������������������������������������\n\n");
        printf("\n    # ������ �۾��� �������ּ���.\n\n");
        printf("    1 - �� �� �߰�\n");
        printf("    2 - �� �� ����\n");
        printf("    3 - �� �� �Ϸ�\n");
        printf("\n    0 - ���� ȭ������ ���ư���\t\t\t�Է� : ");

        command = getchar();//

        if (command == '0') {//
            break;
        }
        else if (command == '1') {//
            todoListWrite(fileName, &todo);
            printf("\n\n   �ش� �� ���� �߰��մϴ�...");//
            Sleep(2000);//
        }
        else if (command == '2') {//
            if (todo->tCount == 0) {//����
                printf("\n\n    �ػ����� todo�� �����ϴ�.");//
                Sleep(2000);//
            }//
            else {//
                deleteTodoList(fileName, &todo);
                printf("\n\n   �ش� �� ���� �����մϴ�...");//
                Sleep(2000);//
                getchar();
            }//
        }
        else if (command == '3') {//
            if (todo->tCount == 0) {//
                printf("\n\n    �ؿϷ��� todo�� �����ϴ�.");//
                Sleep(2000);//
            }//
            else {//
                completeTodoList(fileName, &todo);
                printf("\n\n   �ش� �� ���� �Ϸ� ó���մϴ�...");//
                Sleep(2000);//
                getchar();
            }//

        }
        else {
            printf("\n\n    ���߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");//
            Sleep(2000);//
        }
    }
}

void choiceDay(int year, int month, int day, struct diary* diary, struct diarydate* date) {
    system("cls");
    struct todoList todo;

    todo.tYear = year;
    todo.tMonth = month;
    todo.tDay = day;

    todo.tCount = 0;

    while (1) { // to do ȭ�� ����
        printf("\n\t         ��  %d�� %d�� %d�� ��\n\n", year, month, day);
        printf("\n   ������������������������������  << ���� �� �� >> ������������������������������\n");
        printf("   ��                                               ��\n");
        printf("   ��                                               ��\n");


        todoSimpleRead(&todo);
        if (todo.tCount == 0)//����
            printf("   ��              %-33s��\n", "���� �� ���� �����ϴ�.");//
        else {//
            bool isEmpty = true;
            for (int i = 0; i < todo.tCount; i++) {
                if (todo.todoDetail[i].complete == false) {
                    printf("   ��    - %-41s��\n", todo.todoDetail[i].content);
                    isEmpty = false;
                }
            }
            if (isEmpty == true)
                printf("   ��              %-33s��\n", "���� �� ���� �����ϴ�.");//
        }//

        printf("   ��                                               ��\n");
        printf("   ��������������������������������������������������������������������������������������������������");
        printf("\n\n");

        char dFileName[50];
        snprintf(dFileName, sizeof(dFileName), DIARYFILE_FORMAT, year, month, day);

        bool isDiary = false;
        isDiary = diaryFileExists(dFileName, year, month, day);

        printf("\n\n   ��������������������������������������������������������������������������������������������������\n\n");
        printf("     # ������ �۾��� �����ϼ���.\n\n");
        printf("     1 - �� �� ����\n     2 - �ϱ� ����\n     3 - ��й�ȣ ����\n\n     0 - �޷����� ���ư���\t\t �Է� : ");

        int select = 0;
        scanf("%d", &select);
        system("cls");

        if (select == 1) {
            getchar();
            todoListDetailRead(&todo);
        }
        else if (select == 2) {
            getchar();
            if (isDiary == false) {
                printf("\n\t   �ۼ��� �ϱⰡ ���� �� �ϱ⸦ �ۼ��մϴ�.\n\n");
                diaryWrite(year, month, day);
            }
            else {
                FILE* file = fopen("password.txt", "r");
                if (file != NULL) {
                    inputPassword(dFileName, year, month, day);
                    fclose(file);
                }
                else {
                    diaryFileRead(dFileName, year, month, day);
                }
            }
        }
        else if (select == 3) {
            passwordManagement();
        }
        else if (select == 0) {
            break;
        }
        else {
            printf("   �߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���. : ");
            scanf("%d", &select);
        }
        system("cls");
    }
}

