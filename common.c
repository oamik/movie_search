#include "common.h"

void get_column(char *line, char *dest, int ncol)
{
	int iStart, iEnd, len;
	char *p = line;
	iStart = 0;
	iEnd = 0;
	len = 0;

	for(int i = 0; p; i++, p++)
	{
		if (*p == '\t' || *p == '\n')
		{
			ncol--;
			if ( ncol == 1 )
			{
				iStart = i + 1;
			}
			else if( ncol == 0)
			{
				iEnd = i;
				break;
			}
		}
	}
	len = iEnd - iStart;
	strncpy(dest, line + iStart, len);
	dest[len] = '\0';
}

void reverse(char *str)
{
	char temp;
	int n = strlen(str);

	for (int i = 0; i < n/2 ; ++i)
	{
		temp = str[i];
		str[i] = str[n - 1 - i];
		str[n - 1 - i] = temp;
	}
}

