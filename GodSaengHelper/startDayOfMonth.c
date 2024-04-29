int startDayOfMonth(int year, int month) {
	int startDay;

	if (month <= 2) {
		year--;
		month += 12;
	}

	startDay = ((21 * (year / 100) / 4) + (5 * (year % 100) / 4) + (26 * (month + 1) / 10)) % 7;

	// 일요일 0, 월요일 1, 화요일 2, 수요일 3, 목요일 4, 금요일 5, 토요일 6 return
	return startDay;
}