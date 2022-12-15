#include "monty.h"
/*
 * This file contains functions for printing
 * values in the stack.
 *
 * 'line_status' IS A GLOBAL VARIABLE IN 'main.c'!!!
 */

/**
 * pall - print all
 *
 * Print all ints in the stack_t '*stack'.
 *
 * @stack: "global" stack pointer
 * to print all ints from
 * Please don't make it NULL, check 'monty.h'
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
 * pint - Prints top int in the stack 'stack'
 * if the stack is empty, print error message to
 * stderr and sets error code in line_status
 *
 * @stack: stack to print top int of.
 * Please don't make it NULL, check 'monty.h'.
 *
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


