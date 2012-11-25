/**
 * 2012 OpenSARM
 * Avtor: Urban Bevc <pi.pawr666@gmail.com>
 *
 */

#include "rtc.h"
#include "lpc214x.h"
#include "io.h"

void rtc_init(void)
{
	CCR = 0;
	CCR |= CLKSRC;  //izbran zunanji oscilator
	CCR |= CLKEN;	//števci omogočeni
	CCR |= CTCRST;  //reset "generatorja" sekund - (clock tock counter) - baje uporabno
	CCR &= ~CTCRST;  //konec reseta
	CIIR &= ~0xff;  //prekinitve ob povečanju števcev onemogočene
	AMR &= ~0xff;	//onemogočeni alarmi
	//ILR = ILR_RTCCIF; //pobrisana zastavica prekinitev incr.
	ILR = 3;			//pobrisani zastavici prekinitev
	return;
}

void set_time(unsigned int h, unsigned int m, unsigned int s)
{
	if (h > 23 || m > 59 || s > 59)
		return;

	CCR &= ~CLKEN;
	HOUR = h;
	MIN = m;
	SEC = s;
	CCR |= CLKEN;

	return;
}

void set_date(unsigned int d, unsigned int m, unsigned int y)
{
	if (d > days_of_month(m, y) || m > 12 || y > 4095)
		return;

	CCR &= ~CLKEN;
	DOM = d;
	MONTH = m;
	YEAR = y;
	DOW = d_o_w(y, m, d);
	CCR |= CLKEN;

	return;
}

void set_alarm(unsigned int h, unsigned int m)
{
	ALHOUR = h;
	ALMIN = m;

	return;
}

void start_alarm(void)
{
	AMR = 0x06;
	/*INTWAKE |= 0x8000;*/
	return;
}

void stop_alarm(void)
{
	AMR &= ~0xff;
	/*INTWAKE &= 0X8000;*/
	return;
}

int get_hours(void)
{
	return HOUR;
}

int get_minutes(void)
{
	return MIN;
}

int get_seconds(void)
{
	return SEC;
}

int get_day(void)
{
	return DOM;
}

int get_month(void)
{
	return MONTH;
}

int get_year(void)
{
	return YEAR;
}

int d_o_w(int y, int m, int d)
{
	static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
	y -= m < 3;
	return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

void rtc_increase_hours()
{
	CCR &= ~CLKEN;
	HOUR++;
	if (HOUR > 23)
		HOUR = 23;

	CCR |= CLKEN;
}

void rtc_decrease_hours()
{
	CCR &= ~CLKEN;
	HOUR--;
	if (HOUR < 0)
		HOUR = 0;

	CCR |= CLKEN;
}

void rtc_increase_minutes()
{
	CCR &= ~CLKEN;
	MIN++;
	if (MIN > 59)
		MIN = 59;

	CCR |= CLKEN;
}

void rtc_decrease_minutes()
{
	CCR &= ~CLKEN;
	MIN--;
	if (MIN < 0)
		MIN = 0;

	CCR |= CLKEN;
}

void rtc_increase_seconds()
{
	CCR &= ~CLKEN;
	SEC++;
	if (SEC > 59)
		SEC = 59;

	CCR |= CLKEN;
}

void rtc_decrease_seconds()
{
	CCR &= ~CLKEN;
	SEC--;
	if (SEC < 0)
		SEC = 0;

	CCR |= CLKEN;
}

void rtc_increase_days()
{
	CCR &= ~CLKEN;
	DOM++;
	if (DOM > days_of_month(get_month(), get_year()))
		DOM = days_of_month(get_month(), get_year());

	CCR |= CLKEN;
}

void rtc_decrease_days()
{
	CCR &= ~CLKEN;
	DOM--;
	if (DOM < 0)
		DOM = 0;
	CCR |= CLKEN;
}

void rtc_increase_months()
{
	CCR &= ~CLKEN;
	MONTH++;
	if (MONTH > 12)
		MONTH = 12;

	CCR |= CLKEN;
}

void rtc_decrease_months()
{
	CCR &= ~CLKEN;
	MONTH--;
	if (MONTH < 0)
		MONTH = 0;

	CCR |= CLKEN;
}

void rtc_increase_years()
{
	CCR &= ~CLKEN;
	YEAR++;
	if (YEAR > 4095)
		YEAR = 4095;

	CCR |= CLKEN;
}

void rtc_decrease_years()
{
	CCR &= ~CLKEN;
	YEAR--;
	if (YEAR < 0)
		YEAR = 0;

	CCR |= CLKEN;
}

int days_of_month(unsigned int month, unsigned int year)
{
	int leap = is_leap(year);
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		return 31;
	else if (!leap && (month == 2))
		return 28;
	else if ((month == 2) && leap)
		return 29;
	else
		return 30;
}

int is_leap(unsigned int year)
{
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
		return 1;
	else
		return 0;
}
