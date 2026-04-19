#include "simple_shell.h"

/**
 * split_string - Splits a string and returns an array of each words
 * Short breakdown: Creates first a copy of the string, then cuts it into
 * words with strtok() and checks the size of all those words to creates array
 * Then because strtok modified the string, we copy it a 2nd time
 * and fill the array with the tokens. Tokens here still persist after OG is
 * freed
 *
 * @str: String that has the arguments
 * @delimiters: Where strtok cuts the string each time it gets this symbol
 * Return: array (The string has successfully been put in an array, words
 * cut)
 */
char **split_string(const char *str, const char *delimiters)
{
	char *copy, *token, **array;
	int count = 0, index = 0;
	size_t length, word_length;

	if (!str)
	{
		return (NULL);
	}
	length = 0;
	while (str[length])
	{
		length++;
	}
	copy = malloc(length + 1);
	memcpy(copy, str, length + 1);
	token = strtok(copy, delimiters);
	while (token)
	{
		count++;
		token = strtok(NULL, delimiters);
	}
	free(copy);
	array = malloc((count + 1) * sizeof(char *));
	copy = malloc(length + 1);
	memcpy(copy, str, length + 1);
	token = strtok(copy, delimiters);
	while (token)
	{
		word_length = 0;
		while (token[word_length])
		{
			word_length++;
		}
		array[index] = malloc(word_length + 1);
		memcpy(array[index++], token, word_length + 1);
		token = strtok(NULL, delimiters);
	}
	array[index] = NULL;
	free(copy);
	return (array);
}
