#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string
 *@src: the source string
 *@n: the no of characters
 *Return: the destination string
 */
char *_strncpy(char *dest, char *src, int n)
{

	char *s = dest;
	int index = 0, k;

	while (src[index] != '\0' && index < n - 1)
	{
		dest[index] = src[index];
		index++;
	}
	if (index < n)
	{
		k = index;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int index = 0, k = 0;
	char *s = dest;

	while (dest[index] != '\0')
		index++;
	while (src[k] != '\0' && k < n)
	{
		dest[k] = src[k];
		index++;
		k++;
	}
	if (k < n)
		dest[index] = '\0';
	return (s);
}

/**
 **_strchr - search a char in a string
 *@s: the string
 *@c: the character
 *Return: a pointer to the returned string
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
