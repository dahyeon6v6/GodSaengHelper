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

	// ** ���� : ��¥ ����ó�� �� ��
	while (1) {
		system("cls");
		showCalender(startDay, inputYear, inputMonth);

		printf("��¥�� �����ϼ���. �ٸ� �޷� �̵��Ϸ��� 0�� �Է��ϼ���. : ");
		scanf("%d", &inputDay);

		printf("\n\n");
		if (inputDay == 0) {
			printf("�̵��� ������ ���� �Է��ϼ���. (�� : 2024 4) : ");
			scanf("%d %d", &inputYear, &inputMonth);
			startDay = startDayOfMonth(inputYear, inputMonth);
			system("cls");
			showCalender(startDay, inputYear, inputMonth);
		}
		else {
			choiceDay(inputYear, inputMonth, inputDay);
		}

	}
	// ȭ�� �� �޿� �ش��ϴ� ��¥�� �̵��ϴ� ��� ���߿� ���� **********************************

}