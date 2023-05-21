#include "shell.h"
/**
 * node_index - gets the index of a node
 * @head: pointer to head
 * @current_node: pointer to the node
 * Return: index of the node
 */
ssize_t node_index(link_t *head, link_t *current_node)
{
	size_t i = 0;

	while (head)
	{
		if (head == current_node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

/**
 * print_list - prints all elements of alist
 * @head: pointer to first node
 * Return: length of list
 */
size_t print_list(const link_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(num_converter(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->s ? head->s : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return (count);
}
/**
 * list_length - get length of linked list
 * @h: pointer to first node
 * Return: length of list
 */
size_t list_length(const link_t *h)
{
	size_t size = 0;

	while (h)
	{
		h = h->next;
		size++;
	}
	return (size);
}

/**
 * str_list - returns an array of strings
 * @head: pointer to first node
 * Return: array of strings
 */
char **str_list(link_t *head)
{
	link_t *current_node = head;
	size_t i = list_length(head);
size_t j;
	char **str_arr;
	char *str;

	if (!head || !i)
		return (NULL);
	str_arr = malloc(sizeof(char *) * (i + 1));
	if (!str_arr)
		return (NULL);
	for (i = 0; current_node; current_node = current_node->next, i++)
	{
		str = malloc(_strlen(current_node->s) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(str_arr[j]);
			free(str_arr);
			return (NULL);
		}

		str = _strcpy(str, current_node->s);
		str_arr[i] = str;
	}
	str_arr[i] = NULL;
	return (str_arr);
}



/**
 * begain_with_node - search for anode with the prefix inputg
 * @node: pointer to list head
 * @prefix: string to match
 * @nextchar: the next character after prefix to match
 * Return: matched node
 */
link_t *begain_with_node(link_t *node, char *prefix, char nextchar)
{
	char *temp = NULL;

	while (node)
	{
		temp = begain_with(node->s, prefix);
		if (temp && ((nextchar == -1) || (*temp == nextchar)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
