#include "monty.h"

/**
 * add - Adds the 'n' attribute of the
 * top node in the stack 'stack'
 * to the 'n' attribute of the
 * node previous to the top node,
 * then pops the top node,
 * if there are
 * at least two nodes in the stack.
 *
 * If there aren't, 'add' just prints an error
 * message and sets 'line_status' to
 * EXIT_FALURE.
 *
 * @stack: stack to add its top value to its
 * next-to-top value from
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

/**
 * sub - Subtracts the 'n' attribute of the
 * top node in the stack 'stack'
 * from the stack's next-to-top node's value,
 * then pops the top node,
 * if there are
 * at least two nodes in the stack.
 *
 * If there aren't, 'sub' just prints an error
 * message and sets 'line_status' to
 * EXIT_FALURE.
 *
 * @stack: stack to subtract its top value
 * from its next-top-top value from
 * Please don't make it NULL, check monty.h
 *
 * @line_number: line currently being read from
 * monty file; to print which line caused an
 * error if this function causes it
 *
 * Return: nothing
 */
void sub(stack_t **stack, unsigned int line_number)
{
	stack_t *top = *stack;
	stack_t *prev = NULL;

	if (top)
		prev = top->prev;

	if (!top || !prev)
	{
		fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
		line_status = EXIT_FAILURE;
		return;
	}

	prev->n -= top->n;
	pop(stack, line_number);
}

/**
 * div_ - Tries to divide the 'n' attribute of the
 * node previous to the top node in the stack 'stack'
 * by the stack's top node,
 * then pop the top node.
 *
 * If there aren't at least two nodes in the stack,
 * 'div_' just prints an error message and
 * sets 'line_status' to EXIT_FALURE.
 *
 * If the top value is 0, 'div_' just prints
 * "division by zero" and sets 'line_status' to
 * EXIT_FAILURE.
 *
 * @stack: stack to divide its next-to-top
 * value by its top value from
 * Please don't make it NULL, check monty.h
 *
 * @line_number: line currently being read from
 * monty file; to print which line caused an
 * error if this function causes it
 *
 * Return: nothing
 */
void div_(stack_t **stack, unsigned int line_number)
{
	stack_t *top = *stack;
	stack_t *prev = NULL;

	if (top)
		prev = top->prev;

	if (!top || !prev)
	{
		fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
		line_status = EXIT_FAILURE;
		return;
	}

	if (top->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		line_status = EXIT_FAILURE;
		return;
	}

	prev->n /= top->n;
	pop(stack, line_number);
}

/**
 * mul - Multiplies the 'n' attribute of
 * the next-to-top node in the stack 'stack'
 * by the stack's top node's value,
 * then pops the top node,
 * if there are
 * at least two nodes in the stack.
 *
 * If there aren't, 'mul' just prints an error
 * message and sets 'line_status' to
 * EXIT_FALURE.
 *
 * @stack: stack to multiply its next-to-top value
 * by its top value from
 * Please don't make it NULL, check monty.h
 *
 * @line_number: line currently being read from
 * monty file; to print which line caused an
 * error if this function causes it
 *
 * Return: nothing
 */
void mul(stack_t **stack, unsigned int line_number)
{
	stack_t *top = *stack;
	stack_t *prev = NULL;

	if (top)
		prev = top->prev;

	if (!top || !prev)
	{
		fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
		line_status = EXIT_FAILURE;
		return;
	}

	prev->n *= top->n;
	pop(stack, line_number);
}

/**
 * mod - Tries to make the stack 'stack's next-to-top
 * value be the remainder of the division
 * of the next-to-top value by the top value,
 * then pop the top node.
 *
 * If there aren't, 'mod' just prints an error
 * message and sets 'line_status' to
 * EXIT_FAILURE.
 *
 * If the top value is 0, 'mod' just prints
 * "division by zero" and sets 'line_status' to
 * EXIT_FAILURE.
 *
 * @stack: stack to make its next-to-top value
 * be the remainder of the division of its
 * next-to-top value by its top value from
 * Please don't make it NULL, check monty.h
 *
 * @line_number: line currently being read from
 * monty file; to print which line caused an
 * error if this function causes it
 *
 * Return: nothing
 */
void mod(stack_t **stack, unsigned int line_number)
{
	stack_t *top = *stack;
	stack_t *prev = NULL;

	if (top)
		prev = top->prev;

	if (!top || !prev)
	{
		fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
		line_status = EXIT_FAILURE;
		return;
	}

	if (top->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		line_status = EXIT_FAILURE;
		return;
	}

	prev->n %= top->n;
	pop(stack, line_number);
}

