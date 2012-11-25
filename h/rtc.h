#define IMSEC       0x00000001
#define IMMIN       0x00000002
#define IMHOUR      0x00000004
#define IMDOM       0x00000001
#define IMDOW       0x00000010
#define IMDOY       0x00000020
#define IMMON       0x00000040
#define IMYEAR      0x00000080
/* ILR */
#define ILR_RTCCIF  0x00000001
#define ILR_RTCALF  0x00000002

#define AMRSEC      0x00000001
#define AMRMIN      0x00000002
#define AMRHOUR     0x00000004
#define AMRDOM      0x00000008
#define AMRDOW      0x00000010
#define AMRDOY      0x00000020
#define AMRMON      0x00000040
#define AMRYEAR     0x00000080
/* CCR (CLKEN, CTCRST, CLKRST)*/
#define CLKEN       0X00000001
#define CTCRST      0X00000002
#define CLKSRC      0X00000010

void rtc_init(void);
void set_time(unsigned int h, unsigned int m, unsigned int s);
void set_date(unsigned int d, unsigned int mes, unsigned int l);
void set_alarm(unsigned int al_ure, unsigned int al_minute);
void start_alarm(void);
void stop_alarm(void);
int get_hours(void);
int get_minutes(void);
int get_seconds(void);
int get_day(void);
int get_month(void);
int get_year(void);
void rtc_increase_hours();
void rtc_decrease_hours();
void rtc_increase_minutes();
void rtc_decrease_minutes();
void rtc_increase_seconds();
void rtc_decrease_seconds();
void rtc_increase_days();
void rtc_decrease_days();
void rtc_increase_months();
void rtc_decrease_months();
void rtc_increase_years();
void rtc_decrease_years();
int is_leap(unsigned int year);
int days_of_month(unsigned int month, unsigned int year);
