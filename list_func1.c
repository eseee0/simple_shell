#include "shell.h"

/**
 * add_node - to add node to start of list
 * @head: head node pointer address
 * @str: string node field
 * @num: index of node by history
 *
 * Return: list size
 */

list_t *add_node(list_t **head, const char *str, int num)
{
        list_t *new_head;

        if (!head)
                return (NULL);

        new_head = malloc(sizeof(list_t));
        if (!new_head)
                return (NULL);

        new_head->num = num;
        new_head->str = str ? strdup(str) : NULL;
        new_head->next = *head;
        *head = new_head;

        return (new_head);
}

/**
 * add_node_end - to add node to end of list
 * @head: head node pointer address
 * @str: string node field
 * @num: node index by history
 *
 * Return: list size
 */

list_t *add_node_end(list_t **head, char *str, int num)
{
        list_t *node;

	node = malloc(sizeof(list_t));

	if (node == NULL)
		return NULL;
	node->num = num;
	if (str == NULL)
		node->str = NULL;
	else
		node->str = _strdup(str);
	node->next = NULL;

	if (*head == NULL)
		*head = node;
	else
		(*head)->next = node;
	return (node);
	if (node != NULL)
		free(node);
}


/**
 * free_list - to free all nodes of a list
 * @head: head node pointer address
 *
 * Return: null
 */

void free_list(list_t *head)
{
	while (head != NULL)
	{
		list_t *next = head->next;
		free(head);
		head = next;
	}
}

/**
 * print_list_str - to print only str element of list_t linked list
 * @head: first node pointer
 *
 * Return: list size
 */

int print_list_str(list_t *head)
{
	int i = 0;
	while (head != NULL)
	{
		char *str = head->str;
		int len = 0;

		while (str[len] != '\0')
			len++;
		write(1, str, len);
		write(1, "\n", 1);
		i++;
		head = head->next;
	}
	return (i);
}

/**
 * del_node_index - to delete node at given index
 * @head: first node pointer address
 * @index: node index
 *
 * Return: 1 (Success), else 0
 */

int del_node_index(list_t **head, unsigned int index)
{
	list_t *temp;
	list_t *prev;
	unsigned int i;

	if (*head == NULL)
		return (-1);

	temp = *head;
	for (i = 0; i < index - 1 && temp != NULL; i++)
		temp = temp->next;
	if (temp == *head)
		*head = temp->next;
	else
	{
		prev = *head;
		for (i = 0; i < index - 2 && prev != NULL; i++)
			prev = prev->next;
		prev->next = temp->next;
	}
	free(temp);
	return (0);
}
