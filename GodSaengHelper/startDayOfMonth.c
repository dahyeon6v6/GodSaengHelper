int startDayOfMonth(int year, int month) {
	int startDay;

	if (month <= 2) {
		year--;
		month += 12;
	}

	startDay = ((21 * (year / 100) / 4) + (5 * (year % 100) / 4) + (26 * (month + 1) / 10)) % 7;

	// �Ͽ��� 0, ������ 1, ȭ���� 2, ������ 3, ����� 4, �ݿ��� 5, ����� 6 return
	return startDay;
}