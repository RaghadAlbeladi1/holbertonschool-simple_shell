#include "main.h"

/**
 * sigintH - Handles SIGINT (CTRL + C)
 * @signum: Signal number caught by signal, 2 for SIGINIT
 * Return: void
 **/
void sigintH(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\n#(ಠ_ಠ)->$ ", 14);
	}
}

/**
 * str_concat - Concatenate two strings
 * @s1: String 1
 * @s2: String 1
 * Return: Pointer to the concatenated string
 */
char *str_concat(char *s1, char *s2)
{
	char *s;
	unsigned int i;
	unsigned int j;
	unsigned int k;

	if (s1 == NULL)
		s1 = "";

	if (s2 == NULL)
		s2 = "";

	for (i = 0; s1[i] != '\0'; i++)
		continue;

	for (j = 0; s2[j] != '\0'; j++)
		continue;

	j = j + 1;

	s = malloc((i + j) * sizeof(char));

	if (s == NULL)
		return (0);

	for (k = 0; k < (i + j) ; k++)
	{
		if (k < i)
			s[k] = s1[k];
		if (k >= i)
			s[k] = s2[k - i];
	}
	return (s);
}

/**
 * _realloc - Reallocate a memory block
 * @ptr: Pointer to array
 * @old_size: Old size
 * @new_size: New size
 * Return: A pointer to the allocated memory
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *s;
	char *ptr1;
	unsigned int i;

	ptr1 = (char *)ptr;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);

	s = malloc((new_size) * sizeof(char));
	if (s == NULL)
	{
		free(s);
		return (NULL);
	}

	if (new_size > old_size)
	{
		for (i = 0; i < old_size; i++)
			s[i] = ptr1[i];
	}
	if (new_size < old_size)
	{
		for (i = 0; i < new_size; i++)
			s[i] = ptr1[i];
	}
	free(ptr1);
	return (s);
}
