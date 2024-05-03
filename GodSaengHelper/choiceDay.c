#define _CRT_SECURE_NO_WARNINGS
#define TODOFILE_FORMAT "C:\\Users\\User\\Documents\\Test\\todolist_%4d-%02d-%02d.txt"
#define DIARYFILE_FORMAT "C:\\Users\\User\\Documents\\Test\\diary_%4d-%02d-%02d.txt" 
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "functions.h"

void printTodoList(struct todoList* todo) {
    system("cls");
    printf("\n");
    printf("\n   ┏━━━━━━  << % d년 % d월 % d일 To Do List >> ━━━━━━┓\n", todo->tYear, todo->tMonth, todo->tDay);
    printf("   ┃                                                 ┃\n");
    printf("   ┃                                                 ┃\n");
    if (todo->tCount == 0)//수정
        printf("   ┃\t        %-19s              ┃\n", "등록된 todo가 없습니다.");//
    else {//
        for (int i = 0; i < todo->tCount; i++) {
            printf("   ┃\t %d) %-19s", i + 1, todo->todoDetail[i].content);
            if (todo->todoDetail[i].complete == true)
                printf("\t\t[\033[1;31mV\033[0m]          ┃\n");
            else
                printf("\t\t[ ]          ┃\n");
        }
    }//
    printf("   ┃                                                 ┃\n");
    printf("   ┃                                                 ┃\n");
    printf("   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
    printf("\n");
    printf("\n");
}

void todoListWrite(char fileName[], struct todoList* todo) {
    
    printf("\n\n   추가할 To Do 입력 : ");
    if (todo->tCount == 0) {
        FILE* todoFile = fopen(fileName, "w");
        if (todoFile == NULL) {
            printf("   파일 읽기에 실패했습니다.\n");
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
            printf("   파일 읽기에 실패했습니다.\n");
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
            printf("   파일 생성에 실패했습니다.\n");
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
    printf("\n\n   완료 처리할 항목의 번호를 입력해주세요 : ");
    int selectTodo;
    scanf("%d", &selectTodo);
    selectTodo--;

    if (selectTodo < 0 || selectTodo >= todo->tCount) {
        printf("   잘못된 입력입니다.\n");
        return;
    }

    FILE* originalFile = fopen(fileName, "r");
    if (originalFile == NULL) {
        printf("   파일 열기에 실패했습니다.\n");
        return;
    }

    FILE* newFile = fopen("temp.txt", "w");
    if (newFile == NULL) {
        printf("   새 파일 생성에 실패했습니다.\n");
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
        printf("   기존 파일 삭제에 실패했습니다.\n");
        return;
    }
    if (rename("temp.txt", fileName) != 0) {
        printf("   새 파일 이름 변경에 실패했습니다.\n");
        return;
    }
}

void deleteTodoList(char fileName[], struct todoList* todo) {
    printf("\n\n   삭제할 항목의 번호를 입력해주세요. : ");
    int selectTodo;
    scanf("%d", &selectTodo);
    selectTodo--;

    if (selectTodo < 0 || selectTodo >= todo->tCount) {
        printf("   유효하지 않은 번호입니다.\n");
        return;
    }

    FILE* originalFile = fopen(fileName, "r");
    if (originalFile == NULL) {
        printf("   파일 열기에 실패했습니다.\n");
        return;
    }

    FILE* newFile = fopen("temp.txt", "w");
    if (newFile == NULL) {
        printf("   새 파일 생성에 실패했습니다.\n");
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
        printf("   기존 파일 삭제에 실패했습니다.\n");
        return;
    }
    if (rename("temp.txt", fileName) != 0) {
        printf("   새 파일 이름 변경에 실패했습니다.\n");
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

        printf("\n   ─────────────────────────────────────────────────────────\n\n");
        printf("\n    # 수행할 작업을 선택해주세요.\n\n");
        printf("    1 - 할 일 추가\n");
        printf("    2 - 할 일 삭제\n");
        printf("    3 - 할 일 완료\n");
        printf("\n    0 - 이전 화면으로 돌아가기\t\t\t입력 : ");

        command = getchar();//

        if (command == '0') {//
            break;
        }
        else if (command == '1') {//
            todoListWrite(fileName, &todo);
            printf("\n\n   해당 할 일을 추가합니다...");//
            Sleep(2000);//
        }
        else if (command == '2') {//
            if (todo->tCount == 0) {//수정
                printf("\n\n    ※삭제할 todo가 없습니다.");//
                Sleep(2000);//
            }//
            else {//
                deleteTodoList(fileName, &todo);
                printf("\n\n   해당 할 일을 삭제합니다...");//
                Sleep(2000);//
                getchar();
            }//
        }
        else if (command == '3') {//
            if (todo->tCount == 0) {//
                printf("\n\n    ※완료할 todo가 없습니다.");//
                Sleep(2000);//
            }//
            else {//
                completeTodoList(fileName, &todo);
                printf("\n\n   해당 할 일을 완료 처리합니다...");//
                Sleep(2000);//
                getchar();
            }//

        }
        else {
            printf("\n\n    ※잘못된 입력입니다. 다시 입력해주세요.");//
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

    while (1) { // to do 화면 띄우기
        printf("\n\t         ◈  %d년 %d월 %d일 ◈\n\n", year, month, day);
        printf("\n   ┏━━━━━━━━━━━━━━  << 남은 할 일 >> ━━━━━━━━━━━━━━┓\n");
        printf("   ┃                                               ┃\n");
        printf("   ┃                                               ┃\n");


        todoSimpleRead(&todo);
        if (todo.tCount == 0)//수정
            printf("   ┃              %-33s┃\n", "남은 할 일이 없습니다.");//
        else {//
            bool isEmpty = true;
            for (int i = 0; i < todo.tCount; i++) {
                if (todo.todoDetail[i].complete == false) {
                    printf("   ┃    - %-41s┃\n", todo.todoDetail[i].content);
                    isEmpty = false;
                }
            }
            if (isEmpty == true)
                printf("   ┃              %-33s┃\n", "남은 할 일이 없습니다.");//
        }//

        printf("   ┃                                               ┃\n");
        printf("   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
        printf("\n\n");

        char dFileName[50];
        snprintf(dFileName, sizeof(dFileName), DIARYFILE_FORMAT, year, month, day);

        bool isDiary = false;
        isDiary = diaryFileExists(dFileName, year, month, day);

        printf("\n\n   ─────────────────────────────────────────────────\n\n");
        printf("     # 수행할 작업을 선택하세요.\n\n");
        printf("     1 - 할 일 편집\n     2 - 일기 편집\n     3 - 비밀번호 관리\n\n     0 - 달력으로 돌아가기\t\t 입력 : ");

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
                printf("\n\t   작성된 일기가 없어 새 일기를 작성합니다.\n\n");
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
            printf("   잘못 입력하셨습니다. 다시 입력해주세요. : ");
            scanf("%d", &select);
        }
        system("cls");
    }
}

