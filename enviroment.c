#include "shell.h"

/**
* domain - print current environment
* @data: pointer
* Return: 0
*/

int domain(inputs_t *data)
{
	list_str(data->env);
	return (0);
}

/**
* new_envioremt - make new environment variable
* @data: pointer
* Return: 0
*/

int new_envioremt(inputs_t *data)
{
	if (data->ac != 3)
	{
		puts_str("arguments are incorrect \n");
		return (1);
	}
	if (_setenv(data, data->av[1], data->av[2]))
		return (0);
	return (1);
}

/**
 * remove_domain - Remove an environment variable
 * @data: pointer
 * Return: Always 0
 */

int remove_domain(inputs_t *data)
{
	int envr;

	if (data->ac == 1)
	{
		puts_str("need more arguments\n");
		return (1);
	}

	for (envr = 1; envr <= data->ac; envr++)
		_unsetenv(data, data->av[envr]);
	return (0);
}
