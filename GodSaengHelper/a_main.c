#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>

int main() {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int nowYear = tm.tm_year + 1900;
	int nowMonth = tm.tm_mon + 1;
	int nowDay = tm.tm_mday;
	int inputYear, inputMonth, inputDay;

	int startDay = startDayOfMonth(nowYear, nowMonth);

	inputYear = nowYear;
	inputMonth = nowMonth;

	// ** 수정 : 날짜 예외처리 할 것
	while (1) {
		system("cls");
		showCalender(startDay, inputYear, inputMonth);

		printf("날짜를 선택하세요. 다른 달로 이동하려면 0을 입력하세요. : ");
		scanf("%d", &inputDay);

		printf("\n\n");
		if (inputDay == 0) {
			printf("이동할 연도와 월을 입력하세요. (예 : 2024 4) : ");
			scanf("%d %d", &inputYear, &inputMonth);
			startDay = startDayOfMonth(inputYear, inputMonth);
			system("cls");
			showCalender(startDay, inputYear, inputMonth);
		}
		else {
			choiceDay(inputYear, inputMonth, inputDay);
		}

	}
	// 화면 속 달에 해당하는 날짜로 이동하는 경우 나중에 구현 **********************************

}