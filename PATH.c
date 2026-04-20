#include "simple_shell.h"

/**
 *_getenv - Function that gets an environnement variable
 * @name: Name of the variable to get
 * Return: NULL (value)
 */

char *_getenv(const char *name)
{
	int DAname = strlen(name);
	char **env = environ;

	if (name == NULL || *name == '\0')
	{
		return (NULL);
	}

	while (*env)
	{
		if (strncmp(*env, name, DAname) == 0 && (*env)[DAname] == '=')
		{
			return (*env + DAname + 1);
		}
		env++;
	}
	return (NULL);
}

/**
 * pathfinder - searches for cmd in each directory of PATH
 * @cmd: command name to look for
 *
 * Return: full path (caller must free), or NULL if not found
 */

char *pathfinder(char *cmd)
{
	char *path_env, *path_copy, *dir, *full_path;
	struct stat st;
	int len;

	if (strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == 0 && (st.st_mode & S_IXUSR))
			return (_strdup(cmd));
		return (NULL);
	}

	path_env = _getenv("PATH");
	if (!path_env || path_env[0] == '\0')
		return (NULL);

	path_copy = _strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		len = _strlen(dir) + _strlen(cmd) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, cmd);
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
