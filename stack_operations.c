#include "monty.h"

/* 'line_status' IS A GLOBAL VARIABLE USED IN 'main.c'. */

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
 * Please don't make it NULL, check 'monty.h'
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
 * pop - If the stack isn't empty, pop "pops"
 * and frees the top node of the stack.
 *
 * If the stack is empty, it prints an error message
 * to stderr and sets 'line_status' to 'EXIT_FAILURE'.
 *
 * @stack: stack to pop from.
 * Please don't make it NULL, check monty.h
 *
 * @line_number: line currently being read from
 * monty file; to print which line caused an error
 * if this function causes it
 *
 * Return: nothing
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *head;

	if (!*stack)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		line_status = EXIT_FAILURE;
		return;
	}

	head = *stack;
	*stack = head->prev;
	free(head);
}

/**
 * swap - If the stack contains at least 2
 * elements, 'swap' will swap the top 2
 * 'n' values of the top two nodes,
 * NOT THE NODES THEMSELVES!!!
 *
 * If the stack doesn't have at least two
 * nodes to swap, it will
 * print an error message to stderr and set
 * line_status to EXIT_FAILURE.
 *
 * @stack: stack to swap two values from its
 * top.
 * Please don't make it NULL, check monty.h
 *
 * @line_number: line currently being read from
 * monty file; to print which line caused an
 * error if this function causes it
 *
 * Return: nothing
 */
void swap(stack_t **stack, unsigned int line_number)
{
	/* to get the top and prev to top nodes */
	stack_t *top = *stack;
	stack_t *prev = NULL;
	/* to swap their two 'n' attributes */
	int temp;

	if (top)
		prev = top->prev;

	/* if the stack doesn't have two top nodes: */
	if (!top || !prev)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		line_status = EXIT_FAILURE;
		return;
	}

	temp = top->n;
	top->n = prev->n;
	prev->n = temp;
}

/**
 * add - Adds the 'n' attributes of the
 * top two nodes in the stack 'stack'
 * to the node previous to the top node,
 * then pops the top node, if there are
 * at least two nodes in the stack.
 *
 * If there aren't, 'add' just prints an error
 * message and sets 'line_status' to
 * EXIT_FALURE.
 *
 * @stack: stack to add two values from its
 * top.
 * Please don't make it NULL, check monty.h
 *
 * @line_number: line currently being read from
 * monty file; to print which line caused an
 * error if this function causes it
 *
 * Return: nothing
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *top = *stack;
	stack_t *prev = NULL;

	if (top)
		prev = top->prev;

	if (!top || !prev)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		line_status = EXIT_FAILURE;
		return;
	}

	prev->n += top->n;
	pop(stack, line_number);
}

