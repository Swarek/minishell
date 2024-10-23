/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 21:25:51 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/23 00:59:50 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


bool	check_parentheses(char *input)
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

int	check_pipe_position(char *input)
{
	int		i;

	i = 0;
	if (input[0] == '|')
		return (-1);
	i++;
	while (input[i])
	{
		if (input[i] == '|' && (input[i - 1] != ' ' && input[i - 1] != '\t'))
			return (-1);
		if (input[i] == '|' && input[i + 1] == '\0')
			return (-1);
		i++;
	}
	return (0);
}

int	is_valid_char(char str)
{
	if (!((str >= 65 && str <= 90) || (str >= 97 && str <= 122) || (str >= 48
				&& str <= 57) || str == 95 || str == 46 || str == 45))
	{
		return (-1);
	}
	return (1);
}

int	check_file_name(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>')
		{
			i++;
			while (input[i] == ' ' || input[i] == '\t')
				i++;
			if (input[i] == '\0')
				return (-1);
			while (input[i] && input[i] != ' ' && input[i] != '\t')
			{
				if (is_valid_char(input[i]) == -1)
					return (-1);
				i++;
			}
		}
		else
			i++;
	}
	return (0);
}

int	precheck(char *input)
{
	if (check_parentheses(input))
		return (1);
	if (check_pipe_position(input) == -1)
		return (2);
	if (check_file_name(input) == -1)
		return (3);
	return (0);
}
