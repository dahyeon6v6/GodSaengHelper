#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>

struct todoEach {
    char content[100]; //todo �׸�� ������ �����ϴ� ����
    bool complete; //�ش� todo�� �ϷῩ�θ� �����ϴ� ����
};
struct todoList {
    int tYear;
    int tMonth;
    int tDay;
    int tCount;

    struct todoEach todoDetail[100];
};
struct diary {
    char title[100];
    char content[1000];
    char emotion[50];
};

bool isPW;

void printTodoList(struct todoList* todo);
void todoListWrite(char fileName[], struct todoList* todo);
void todoSimpleRead(struct todoList* todo);
void completeTodoList(char fileName[], struct todoList* todo);
void deleteTodoList(char fileName[], struct todoList* todo);
void todoListDetailRead(struct todoList* todo);
void choiceDay(int year, int month, int day);

// ���̾ �ۼ�
void diaryWrite( int year, int month, int day);
// ���̾ ����
void diaryFileSave(struct diary* diary, int year, int month, int day);
// ���̾ ������ ���� ���� Ȯ��
bool diaryFileExists(char dFileName[], int year, int month, int day);
// ���̾ ���� ����ü�迭�� �ҷ�����
void diaryFileRead(char dFileName[], int year, int month, int day);
// ���̾ ����
void diaryEdit(char dFileName[], struct diary* diary, int year, int month, int day);
// ���̾ ����
void diaryDelete(char dFileName[], struct diary* diary, int year, int month, int day);

// ��й�ȣ ����
void setPassword();
// ��й�ȣ Ȯ��
void checkPassword();

// ��Ʈ�� ���ۻ���
void clear_stdin();

#endif // FUNCTIONS_H