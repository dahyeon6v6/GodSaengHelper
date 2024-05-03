#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>

struct todoEach {
    char content[100]; //todo 항목당 내용을 저장하는 변수
    bool complete; //해당 todo의 완료여부를 저장하는 변수
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

// 다이어리 작성
void diaryWrite(int year, int month, int day);
// 다이어리 저장
void diaryFileSave(struct diary* diary, int year, int month, int day);
// 다이어리 파일의 존재 여부 확인
bool diaryFileExists(char dFileName[], int year, int month, int day);
// 다이어리 파일 구조체배열에 불러오기
void diaryFileRead(char dFileName[], int year, int month, int day);
// 다이어리 삭제
void diaryDelete(char dFileName[], struct diary* diary, int year, int month, int day);

// 스트림 버퍼삭제
void clear_stdin();

// 비밀번호 관리
void passwordManagement();
// 비밀번호 입력
void inputPassword(char* dFileName, int year, int month, int day);
// 비밀번호 확인
int checkPassword();
// 비밀번호 설정
void setPassword();
// 비밀번호 삭제
void deletePassword();


#endif // FUNCTIONS_H