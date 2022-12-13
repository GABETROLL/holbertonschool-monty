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
 */
int push(int value)
{
	stack_t *new_head = malloc(sizeof(stack_t));

	if (!new_head)
		return (-1);

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
		printf("L%d: usage: push integer\n", line_number);
	}
	else if (strcmp(token, "pall") == 0)
	{
		pall();
		return (1);
	}

	return (-1);
}

int main(int argc, char **argv)
{
	FILE *fp;

	size_t line_buffer_size = 0;
	char *line = NULL;
	int line_index = 0;

	if (argc != 2)
	{
		printf("USAGE: %s file\n", argv[0]);
		return (EXIT_FAILURE);
	}

	fp = fopen(argv[1], "r");

	if (!fp)
	{
		printf("Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}

	while (getline(&line, &line_buffer_size, fp) != -1)
	{
		int line_result = parse_command(line, line_index);

		/* reset loop */
		free(line);
		line_buffer_size = 0;
		line = NULL;

		if (line_result == -1)
			return (EXIT_FAILURE);

		line_index++;
	}

	return (EXIT_SUCCESS);
}

