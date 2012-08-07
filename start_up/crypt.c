/*!
 * \file	crypt.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-07-07 16:50:28
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

/* copied from passwd.c in busybox */
static int i64c(int i)
{
	if (i <= 0)
		return ('.');
	if (i == 1)
		return ('/');
	if (i >= 2 && i < 12)
		return ('0' - 2 + i);
	if (i >= 12 && i < 38)
		return ('A' - 12 + i);
	if (i >= 38 && i < 63)
		return ('a' - 38 + i);
	return ('z');
}

static char *crypt_make_salt(void)
{
	time_t now;
	static unsigned long x;
	static char result[7];

	time(&now);
	x += now + getpid() + clock();
	strcpy(&(result[0]), "$1$");
	result[3] = i64c(((x >> 18) ^ (x >> 6)) & 077);
	result[4] = i64c(((x >> 12) ^ x) & 077);
	result[5] = '$';
	result[6] = '\0';
	return result;
}

int main(int argc, char* argv[])
{
    char *salt;
    salt = crypt_make_salt();
    printf("%s\n",salt); 
    return 0;
}

