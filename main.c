#include "monty.h"

stack_t *stack = NULL;

/**
 * pall - print all
 *
 * Print all ints in the stack_t '*stack'.
 *
 * Return: Nothing
 */
void pall(void)
{
	stack_t *node = stack;

	while (node)
	{
		printf("%d\n", node->n);
		node = node->prev;
	}
}

/**
 * push - Try to push new value 'value' onto
 * the stack_t 'stack'.
 *
 * THE NEW NODE IS THE NEW HEAD OF THE STACK.
 * THE NEW HEAD'S 'PREV' ATTRIBUTE BECOMES
 * THE STACK'S OLD HEAD, AND THE STACK'S
 * OLD HEAD'S 'NEXT' ATTRIBUTE BECOMES THE
 * NEW HEAD.
 *
 * The new node with 'value' is stored in
 * the heap and must be freed.
 *
 * If there's no 'stack' or if malloc fails,
 * return -1.
 *
 * If '*stack' is NULL, the new node becomes
 * the head.
 *
 * @value: value to put into new node
 *
 * Return: 1 if successful, -1 otherwise
 */
int push(int value)
{
	stack_t *new_head = malloc(sizeof(stack_t));

	if (!new_head)
	{
		fputs("Error: malloc failed", stderr);
		return (-1);
	}

	new_head->n = value;
	new_head->prev = stack;
	new_head->next = NULL;

	if (stack)
		stack->next = new_head;
	stack = new_head;

	return (1);
}

/**
 * parse_command - Parse command line as tokens
 * separated by spaces and new lines.
 *
 * @line: line to parse
 * @line_number: to print line number in error
 * messages
 *
 * Return: 1 if successful, 0 if no line was
 * fed, -1 if error
 */
int parse_command(char *line, int line_number)
{
	char *token = strtok(line, " \n");

	if (!token)
		return (0);

	if (strcmp(token, "push") == 0)
	{
		int value;

		token = strtok(NULL, " \n");
		if (token)
		{
			value = atoi(token);

			if (value || strcmp(token, "0") == 0)
			{
				push(value);
				return (1);
			}
		}
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
	}
	else if (strcmp(token, "pall") == 0)
	{
		pall();
		return (1);
	}
	else
		fprintf(stderr, "L%d: unknown instruction %s\n", line_number, token);

	return (-1);
}

/**
 * free_stack - Frees all nodes in stack 'stack'
 * Return: nothing
 */
void free_stack(void)
{
	stack_t *a = stack;
	stack_t *b;

	while (a)
	{
		b = a->prev;
		free(a);
		a = b;
	}
}

/**
 * main - Parse monty file from shell argument 1
 *
 * @argc: shell argument count
 * @argv: shell arguments
 *
 * Return: EXIT_SUCCESS if interpreting the monty
 * file was successful (including the arguments
 * being 2 and the file existing), otherwise EXIT_FAILURE
 */
int main(int argc, char **argv)
{
	FILE *fp;

	size_t line_buffer_size = 0;
	char *line = NULL;
	int line_index = 1;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: %s file\n", argv[0]);
		return (EXIT_FAILURE);
	}

	fp = fopen(argv[1], "r");

	if (!fp)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}

	while (getline(&line, &line_buffer_size, fp) != -1)
	{
		int line_result = parse_command(line, line_index);

		if (line_result == -1)
		{
			free_stack();
			free(line);
			fclose(fp);
			return (EXIT_FAILURE);
		}

		line_index++;
	}
	free_stack();
	free(line);
	fclose(fp);

	return (EXIT_SUCCESS);
}

