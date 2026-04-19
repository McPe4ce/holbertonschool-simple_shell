#include "simple_shell.h"

/**
 * free_args - frees a NULL-terminated array of strings (not the strings)
 * @args: the array to free
 */
void free_args(char **args)
{
	if (args)
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
 * _strcat_new - allocates a new string = s1 + s2
 * @s1: first string
 * @s2: second string
 *
 * Return: new concatenated string (caller must free), or NULL on failure
 */
char *_strcat_new(char *s1, char *s2)
{
	char *result;
	int len1, len2, i, j;

	len1 = _strlen(s1);
	len2 = _strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	for (i = 0; i < len1; i++)
		result[i] = s1[i];
	for (j = 0; j < len2; j++)
		result[len1 + j] = s2[j];
	result[len1 + len2] = '\0';
	return (result);
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
