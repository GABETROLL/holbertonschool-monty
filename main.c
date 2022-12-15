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

	instruction_t instructions[] = {{"push", push}, {"pop", pop},
		{"swap", swap},
		{"add", add},
		{"pall", pall}, {"pint", pint},
		{"nop", nop},
		{NULL, NULL}};

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

