#include <stdio.h>
#include <limits.h>
#include <float.h>

void main(void) {
	printf("char \tmin %d, \tmax %d\n", CHAR_MIN, CHAR_MAX);
	printf("signed char \tmin %d, \tmax %d\n", SCHAR_MIN, SCHAR_MAX);
	printf("unsigned char \t\tmax %u\n",UCHAR_MAX);
	printf("int \tmin %d, \tmax %d\n", INT_MIN, INT_MAX);
	printf("signed int \tmin %d, \tmax %d\n", INT_MIN, INT_MAX);
	printf("unsigned int \t\tmax %u\n", UINT_MAX);
	printf("long int \tmin %d \tmax %d\n", LONG_MIN, LONG_MAX);
	printf("unsigned long int \tmax %u\n", ULONG_MAX);
	printf("short int \tmin %d, \tmax %d\n", SHRT_MIN, SHRT_MAX);
	printf("unsigned short int \tmax %u\n", USHRT_MAX); 
	printf("float min: %e max: %e\n", FLT_MIN, FLT_MAX);
	printf("double \tmin: %e \tmax: %e\n", DBL_MIN, DBL_MAX);
	getchar();

}
