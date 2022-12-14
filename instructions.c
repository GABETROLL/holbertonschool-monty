#include "monty.h"

/* 'stack' IS A GLOBAL VARIABLE USED IN 'main.c'. */

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
 * pint - Prints top int in the stack 'stack'
 * if the stack is empty, print error message and
 * set error code in line_status
 *
 * @stack: stack to print top int of
 * @line_number: line number of monty file to print
 * if the stack is empty
 *
 * Return: Nothing
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (!*stack)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		line_status = EXIT_FAILURE;
		return;
	}

	printf("%d\n", (**stack).n);
}

