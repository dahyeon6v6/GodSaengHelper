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
    printf("\t   <%4d년 %2d월 %2d일의 할일 리스트>", todo->tYear, todo->tMonth, todo->tDay);
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
    printf("할일을 입력해주세요\n");
    if (todo->tCount == 0) {
        FILE* todoFile = fopen(fileName, "w");
        if (todoFile == NULL) {
            printf("파일 읽기에 실패했습니다.\n");
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
            printf("파일 읽기에 실패했습니다.\n");
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
            printf("파일 생성에 실패했습니다.\n");
            return -1;
        }
    }
    rewind(todoFile);  // 파일 포인터를 파일의 시작으로 이동
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
    printf("완료 처리할 할일의 번호를 입력해주세요: ");
    int selectTodo;
    scanf("%d", &selectTodo);
    selectTodo--;

    if (selectTodo < 0 || selectTodo >= todo->tCount) {
        printf("잘못된 입력입니다.\n");
        return;
    }

    FILE* originalFile = fopen(fileName, "r");
    if (originalFile == NULL) {
        printf("파일 열기에 실패했습니다.\n");
        return;
    }

    FILE* newFile = fopen("temp.txt", "w");
    if (newFile == NULL) {
        printf("새 파일 생성에 실패했습니다.\n");
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
        printf("기존 파일 삭제에 실패했습니다.\n");
        return;
    }
    if (rename("temp.txt", fileName) != 0) {
        printf("새 파일 이름 변경에 실패했습니다.\n");
        return;
    }
}

void deleteTodoList(char fileName[], struct todoList* todo) {
    printf("삭제할 할일의 번호를 입력해주세요: ");
    int selectTodo;
    scanf("%d", &selectTodo);
    selectTodo--;

    if (selectTodo < 0 || selectTodo >= todo->tCount) {
        printf("유효하지 않은 할일 번호입니다.\n");
        return;
    }

    FILE* originalFile = fopen(fileName, "r");
    if (originalFile == NULL) {
        printf("파일 열기에 실패했습니다.\n");
        return;
    }

    FILE* newFile = fopen("temp.txt", "w");
    if (newFile == NULL) {
        printf("새 파일 생성에 실패했습니다.\n");
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
        printf("기존 파일 삭제에 실패했습니다.\n");
        return;
    }
    if (rename("temp.txt", fileName) != 0) {
        printf("새 파일 이름 변경에 실패했습니다.\n");
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

        printf("\t수행할 작업을 선택해주세요.\n");
        printf("\t0) 이전화면으로 돌아가기\n");
        printf("\t1) 할일 추가\n");
        printf("\t2) 할일 삭제\n");
        printf("\t3) 할일 완료\n");

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
            printf("잘못된 입력입니다.\n");
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

    while (1) { // to do 화면 띄우기
        printf("\n\t▣▣▣ %d년 %d월 %d일 To Do List ▣▣▣\n\n", year, month, day);

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

        printf("\n\n\n\n   1 - To Do List 편집\n   2 - 일기 편집\n");
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
                        printf("비밀번호가 일치하지 않습니다. 다시 입력하세요.\n");
                        printf("0 - 달력으로 돌아가기\n");
                        int tmp;
                        scanf("%d", &tmp);
                        if (tmp == 0)
                            break;

                    }
                }
            }
        }
        else {
            printf("잘못 입력하셨습니다. 다시 입력해주세요. : ");
            scanf("%d", &select);
        }
        system("cls");
    }
}