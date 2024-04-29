#define _CRT_SECURE_NO_WARNINGS
#define TODOFILE_FORMAT "C:\\Users\\User\\Documents\\Test\\todolist_%4d-%02d-%02d.txt"
#define DIARYFILE_FORMAT "C:\\Users\\User\\Documents\\Test\\diary_%4d-%02d-%02d.txt"  
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "functions.h"

bool isPW;

void printTodoList(struct todoList* todo) {
    system("cls");
    printf("\n");
    printf("\t   <%4d�� %2d�� %2d���� ���� ����Ʈ>", todo->tYear, todo->tMonth, todo->tDay);
    printf("\n\n");

    for (int i = 0; i < todo->tCount; i++) {
        printf("\t%d) %-20s", i + 1, todo->todoDetail[i].content);
        if (todo->todoDetail[i].complete == true)
            printf("\t\t[\033[1;31mV\033[0m]\n");
        else
            printf("\t\t[ ]\n");
    }
    printf("\n");
    printf("\n");
}

void todoListWrite(char fileName[], struct todoList* todo) {
    printf("������ �Է����ּ���\n");
    if (todo->tCount == 0) {
        FILE* todoFile = fopen(fileName, "w");
        if (todoFile == NULL) {
            printf("���� �б⿡ �����߽��ϴ�.\n");
            return -1;
        }
        fputc('0', todoFile);

        char inContent[100];
        getchar();
        scanf("%[^\n]", &inContent);
        fputs(inContent, todoFile);
        fputc('\n', todoFile);

        todo->tCount++;
        fclose(todoFile);
    }
    else {
        FILE* todoFile = fopen(fileName, "a");
        if (todoFile == NULL) {
            printf("���� �б⿡ �����߽��ϴ�.\n");
            return -1;
        }
        fputc('0', todoFile);

        char inContent[100];
        getchar();
        scanf("%[^\n]", &inContent);
        fputs(inContent, todoFile);
        fputc('\n', todoFile);

        todo->tCount++;
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
            printf("���� ������ �����߽��ϴ�.\n");
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
    printf("�Ϸ� ó���� ������ ��ȣ�� �Է����ּ���: ");
    int selectTodo;
    scanf("%d", &selectTodo);
    selectTodo--;

    if (selectTodo < 0 || selectTodo >= todo->tCount) {
        printf("�߸��� �Է��Դϴ�.\n");
        return;
    }

    FILE* originalFile = fopen(fileName, "r");
    if (originalFile == NULL) {
        printf("���� ���⿡ �����߽��ϴ�.\n");
        return;
    }

    FILE* newFile = fopen("temp.txt", "w");
    if (newFile == NULL) {
        printf("�� ���� ������ �����߽��ϴ�.\n");
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
        printf("���� ���� ������ �����߽��ϴ�.\n");
        return;
    }
    if (rename("temp.txt", fileName) != 0) {
        printf("�� ���� �̸� ���濡 �����߽��ϴ�.\n");
        return;
    }
}

void deleteTodoList(char fileName[], struct todoList* todo) {
    printf("������ ������ ��ȣ�� �Է����ּ���: ");
    int selectTodo;
    scanf("%d", &selectTodo);
    selectTodo--;

    if (selectTodo < 0 || selectTodo >= todo->tCount) {
        printf("��ȿ���� ���� ���� ��ȣ�Դϴ�.\n");
        return;
    }

    FILE* originalFile = fopen(fileName, "r");
    if (originalFile == NULL) {
        printf("���� ���⿡ �����߽��ϴ�.\n");
        return;
    }

    FILE* newFile = fopen("temp.txt", "w");
    if (newFile == NULL) {
        printf("�� ���� ������ �����߽��ϴ�.\n");
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
        printf("���� ���� ������ �����߽��ϴ�.\n");
        return;
    }
    if (rename("temp.txt", fileName) != 0) {
        printf("�� ���� �̸� ���濡 �����߽��ϴ�.\n");
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

        printf("\t������ �۾��� �������ּ���.\n");
        printf("\t0) ����ȭ������ ���ư���\n");
        printf("\t1) ���� �߰�\n");
        printf("\t2) ���� ����\n");
        printf("\t3) ���� �Ϸ�\n");

        scanf("%d", &command);
        if (command == 0) {
            break;
        }
        else if (command == 1) {
            todoListWrite(fileName, &todo);
        }
        else if (command == 2) {
            deleteTodoList(fileName, &todo);
        }
        else if (command == 3) {
            completeTodoList(fileName, &todo);
        }
        else
            printf("�߸��� �Է��Դϴ�.\n");
    }
}

void choiceDay(int year, int month, int day, struct diary* diary, struct diarydate* date) {
    system("cls");

    //strcpy(diary->title, "");
    //strcpy(diary->content, "");
    //strcpy(diary->emotion, "");

    struct todoList todo;

    todo.tYear = year;
    todo.tMonth = month;
    todo.tDay = day;

    todo.tCount = 0;

    while (1) { // to do ȭ�� ����
        printf("\n\t�ââ� %d�� %d�� %d�� To Do List �ââ�\n\n", year, month, day);

        todoSimpleRead(&todo);

        for (int i = 0; i < todo.tCount; i++) {
            if (todo.todoDetail[i].complete == false)
                printf("%s\n", todo.todoDetail[i].content);
        }

        printf("\n\n");

        char dFileName[50];
        snprintf(dFileName, sizeof(dFileName), DIARYFILE_FORMAT, year, month, day);

        bool isDiary = false;
        isDiary = diaryFileExists(dFileName, year, month, day);

        printf("\n\n\n\n   1 - To Do List ����\n   2 - �ϱ� ����\n");
        int select = 0;
        scanf("%d", &select);
        getchar();
        system("cls");

        if (select == 1) {
            todoListDetailRead(&todo);
        }
        else if (select == 2) {
            system("cls");

            if (isDiary == false) {
                diaryWrite(year, month, day);
            }
            else {
                while (1) {
                    checkPassword();
                    if (isPW == true) {
                        //printf("%s", dFileName);
                        //printf("%s", diary->title);
                        //printf("%s", diary->content);
                        //printf("%s", diary->emotion);
                        //printf("%d", year);
                        //int n;
                        //scanf("%d", &n);
                        diaryFileRead(dFileName, year, month, day);
                        break;
                    }
                    else {
                        printf("��й�ȣ�� ��ġ���� �ʽ��ϴ�. �ٽ� �Է��ϼ���.\n");
                        printf("0 - �޷����� ���ư���\n");
                        int tmp;
                        scanf("%d", &tmp);
                        if (tmp == 0)
                            break;

                    }
                }
            }
        }
        else {
            printf("�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���. : ");
            scanf("%d", &select);
        }
        system("cls");
    }
}