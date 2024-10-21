/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 21:25:51 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/21 21:39:47 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_parentheses(const char *input)
{
	int	parentheses_count;
	int	i;

	parentheses_count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '(')
			parentheses_count++;
		else if (input[i] == ')')
			parentheses_count--;
		if (parentheses_count < 0)
			return (true);
		i++;
	}
	return (parentheses_count != 0);
}

bool	check_pipe_position(const char *input)
{
	int		i;
	bool	found_a_space;

	i = 0;
	found_a_space = false;
	while (input[i])
	{
		if (input[i] == ' ' && input[i] == '\t')
			found_a_space = true;
		if (input[i] == '|')
		{
			if (!found_a_space || input[i + 1] == '\0')
				return (true);
			found_a_space = false;
		}
		i++;
	}
	return (false);
}

int	precheck(const char *input)
{
	if (check_parentheses(input))
		return (1);
	if (check_pipe_position(input))
		return (2);
	return (0);
}
