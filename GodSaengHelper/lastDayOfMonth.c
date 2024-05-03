//해당 연도와 달의 마지막 날짜를 int값으로 return
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
		return  28 + leapYear; //해당 연도 윤년 확인 -> 맞으면 28+1로 return
	default:
		return 0;
	}
}