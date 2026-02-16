#ifndef MYDATE
#define MYDATE
#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

void cmonth_day(unsigned int year, unsigned int yearday, int *month, int* day) {
		int leap = (year%4 == 0 && year%100 == 0) || year % 400 == 0;
		int i;
		#ifdef PTR_VERSION
		for (i=1; yearday > *(*(daytab + leap) + i); ++i) {
			if (i == 12) {
				printf("Date error: yearday is too large\n");
				return;
			}
			yearday -= *(*(daytab + leap)+i);
		}
		#else
		for (i=1; yearday > daytab[leap][i]; ++i) {
			if (i == 12) {
				printf("ERROR cmonth_day(): yearday is too large\n");
				return;
			}
			yearday -= daytab[leap][i];
		}
		#endif
		*month = i;
		*day = yearday;
}

int cday_of_year(unsigned int year, unsigned int month, unsigned int day) {
	int leap = (year%4 == 0 && year%100 == 0) || year % 400 == 0;

    #ifdef PTR_VERSION

	if (month < 12 && day <= *(*(daytab + leap)+month)) {
		for (int i=1; i < month; ++i) 
			day += *(*(daytab + leap)+month);

		return day;
	}
	else 
		printf("\nERROR cday_of_year(): incorrect date\n");

	#else 

	if (month < 12 && day <= daytab[leap][month]) {
		for (int i=1; i < month; ++i) 
			day += daytab[leap][month];

		return day;
	}
	
	#endif

	return 0;
}
#endif
