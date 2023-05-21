#include "shell.h"

/**
 * delete_list - frees all nodes of a list
 * @head_ptr: pointer of pointer to head node
 */
void delete_list(link_t **head_ptr)
{
	link_t  *head, *current_node, *next_node;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	current_node = head;
	while (current_node)
	{
		next_node = current_node->next;
		free(current_node->s);
		free(current_node);
		current_node = next_node;
	}
	*head_ptr = NULL;
}
/**
 * write_list_strings - prints list strings
 * @h: pointer to first node
 * Return: length of list
 */
size_t write_list_strings(const link_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->s ? h->s : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_node - deletes node at given index
 * @head: pointer of pointer to first node
 * @index: index
 * Return: 1 on success Or 0 on failure
 */
int delete_node(link_t **head, unsigned int index)
{
	unsigned int i = 0;
	link_t *current_node, *prev_node;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		current_node = *head;
		*head = (*head)->next;
		free(current_node->s);
		free(current_node);
		return (1);
	}
	current_node = *head;
	while (current_node)
	{
		if (i == index)
		{
			prev_node->next = current_node->next;
			free(current_node->s);
			free(current_node);
			return (1);
		}
		i++;
		prev_node = current_node;
		current_node = current_node->next;
	}
	return (0);
}



/**
 * addnode_to_begining - adds a node at the begining to list
 * @head: pointer of pointer to head node
 * @str: string data
 * @index: node index
 * Return: length of list
 */
link_t *addnode_to_begining(link_t **head, const char *str, int index)
{
	link_t *temp_head;

	if (!head)
		return (NULL);
	temp_head = malloc(sizeof(link_t));
	if (!temp_head)
		return (NULL);
	_memset((void *)temp_head, 0, sizeof(link_t));
	temp_head->num = index;
	if (str)
	{
		temp_head->s = _strdup(str);
		if (!temp_head->s)
		{
			free(temp_head);
			return (NULL);
		}
	}
	temp_head->next = *head;
	*head = temp_head;
	return (temp_head);
}

/**
 * addnode_to_end - adds a node to the end
 * @head: pointer of pointer to head
 * @str: input data
 * @index: node index
 * Return: length of list
 */
link_t *addnode_to_end(link_t **head, const char *str, int index)
{
	link_t *temp_node, *node;

	if (!head)
		return (NULL);


	temp_node = malloc(sizeof(link_t));
	node = *head;
	if (!temp_node)
		return (NULL);
	_memset((void *)temp_node, 0, sizeof(link_t));
	if (str)
	{
		temp_node->s = _strdup(str);
		if (!temp_node->s)
		{
			free(temp_node);
			return (NULL);
		}
	}
		temp_node->num = index;

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = temp_node;
	}
	else
		*head = temp_node;
	return (temp_node);
}
