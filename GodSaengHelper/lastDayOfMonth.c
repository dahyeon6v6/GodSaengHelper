//�ش� ������ ���� ������ ��¥�� int������ return
int lastDayOfMonth(int year, int month) {
	int lastDay;
	int leapYear;
	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 4: case 6: case 9: case 11:
		return  30;
	case 2:
		leapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		return  28 + leapYear; //�ش� ������ 2���� �������� �ƴ��� Ȯ���� ������ 28+1�� return
	default:
		return 0;
	}
}