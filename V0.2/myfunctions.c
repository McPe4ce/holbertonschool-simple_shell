#include "simple_shell.h"

/**
 * free_args - Frees the arguments of the array one by one before freeing
 * the array
 * @args: Arguments
 */
void free_args(char **args)
{
	int indexor = 0;

	if (!args)
	{
		return;
	}
	while (args[indexor])
	{
		free(args[indexor]);
		indexor++;
	}
	free(args);
}

/**
 * _strlen - returns length of string s
 * @s: input string
 *
 * Return: length
 */
int _strlen(char *s)
{
	int indexor = 0;

	if (!s)
		return (0);
	while (s[indexor])
		indexor++;
	return (indexor);
}

/**
 * _strdup - duplicates a string
 * @s: source string
 *
 * Return: pointer to new string, or NULL on failure
 */
char *_strdup(char *s)
{
	char *dup;
	int len, i;

	if (!s)
		return (NULL);
	len = _strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	for (i = 0; i <= len; i++)
		dup[i] = s[i];
	return (dup);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 if equal, non-zero otherwise
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
