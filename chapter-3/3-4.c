#include <stdio.h>
#include <limits.h>



/* itoa: convert n to characters in s */
void itoa(int in, char s[])
{
	int i, sign;
	unsigned int n = in;
	if ((sign = in) < 0) /* record sign */
		n = (unsigned int)(-in); /* make n positive */
	i = 0;
	do { /* generate digits in reverse order */
		s[i++] = n % 10 + '0'; /* get next digit */
	} while ((n /= 10) > 0); /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}
