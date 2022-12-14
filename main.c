#include "monty.h"

/*
 * turns into EXIT_FAILURE when a line causes an error
 * keeps track of a line being successful or not
 * if it's EXIT_FAILURE, it should be used to exit
 * this program.
 */
int line_status = EXIT_SUCCESS;

/**
 * free_stack - Frees all nodes in stack 'stack'
 *
 * @stack: "global" stack pointer
 * Please don't make it NULL.
 *
 * Return: nothing
 */
void free_stack(stack_t **stack)
{
	stack_t *a = *stack;
	stack_t *b;

	while (a)
	{
		b = a->prev;
		free(a);
		a = b;
	}
}

/**
 * pall - print all
 *
 * Print all ints in the stack_t '*stack'.
 *
 * @stack: "global" stack pointer
 * to print all ints from
 * Please don't make it NULL.
 *
 * @line_number: line number in monty file
 * to print in case something goes wrong
 *
 * Return: Nothing
 */
void pall(stack_t **stack, __attribute__((unused)) unsigned int line_number)
{
	stack_t *node = *stack;

	while (node)
	{
		printf("%d\n", node->n);
		node = node->prev;
	}
}

/**
 * push - Try to push new value saved in
 * function 'strtok' onto the stack_t 'stack'.
 *
 * The value SHOULD come from the read line
 * in the monty input file of this program,
 * currently one token after the start of it.
 * that token SHOULD be "push".
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
 * If malloc fails or the next token
 * was invalid, it prints message
 * describing the error to stderr, sets
 * line_status to EXIT_FAILURE and returns.
 *
 * If '*stack' is NULL, the new node becomes
 * the head.
 *
 * @stack: "global" stack to push number to
 * Please don't make it NULL.
 *
 * @line_number: line number in monty file we're
 * currently trying to execute in case
 * something goes wrong
 *
 * Return: Nothing
 */
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *new_head;
	char *next_token;
	int value;

	next_token = strtok(NULL, " \n");
	if (!next_token)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		line_status = EXIT_FAILURE;
		return;
	}
	value = atoi(next_token);
	/*
	 * atoi returns 0 when next_token isn't a valid number,
	 * as well as when the number was a valid 0.
	 * So, we have to check for the "0" edge case.
	 * If it wasn't "0", we'll assume it's wrong,
	 * for now...
	 */
	if (!value && strcmp("0", next_token) != 0)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		line_status = EXIT_FAILURE;
		return;
	}
	new_head = malloc(sizeof(stack_t));
	if (!new_head)
	{
		fputs("Error: malloc failed", stderr);
		line_status = EXIT_FAILURE;
		return;
	}
	new_head->n = value;
	new_head->prev = *stack;
	new_head->next = NULL;

	if (*stack)
		(**stack).next = new_head;

	*stack = new_head;
}

/**
 * parse_command - Parse command line as tokens
 * separated by spaces and new lines.
 *
 * @stack: "global" stack pointer
 * Please don't make it NULL.
 *
 * @line: line to parse
 * @line_number: to print line number when error occurs
 * messages
 * @instructions: an array of structs containing
 * each monty opcode and its corresponding
 * function
 *
 * Return: Nothing
 */
void parse_command(stack_t **stack,
		char *line, unsigned int line_number,
		instruction_t *instructions)
{
	char *token = strtok(line, " \n");
	int index = 0;

	if (!token)
		return;

	for (index = 0; instructions[index].opcode; index++)
	{
		if (strcmp(token, instructions[index].opcode) == 0)
		{
			instructions[index].f(stack, line_number);

			if (line_status == EXIT_SUCCESS)
				return;
		}
	}

	/*
	 * if the opcode was valid, then failed,
	 * its corresponding function should've
	 * already printed an error message, so
	 * we should only print it line_status is
	 * still EXIT_SUCCESS and hasn't been
	 * affected by any function, to prevent more
	 * than one error message
	 */
	if (line_status == EXIT_SUCCESS)
	{
		fprintf(stderr, "L%u: unknown instruction %s\n", line_number, token);
		line_status = EXIT_FAILURE;
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

	char *line = NULL;
	size_t line_buffer_size = 0;
	unsigned int line_number = 1;

	instruction_t instructions[] = {{"pall", pall}, {"push", push}, {NULL, NULL}};

	stack_t *stack = NULL;

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

	while (line_status == EXIT_SUCCESS
			&& getline(&line, &line_buffer_size, fp) != -1)
	{
		parse_command(&stack, line, line_number, instructions);
		line_number++;
	}

	free_stack(&stack);
	free(line);
	fclose(fp);

	return (line_status);
}

