/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 21:25:51 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/28 18:19:10 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_position(char *input)
{
	int	i;

	if (!input || !*input)
		return (0);
	if (input[0] == '|')
		return (-1);
	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (i == 0 || (input[i - 1] != ' ' && input[i - 1] != '\t'))
				return (-1);
			if (!input[i + 1])
				return (-1);
		}
		i++;
	}
	return (0);
}

int	precheck(char *input)
{
	if (check_pipe_position(input) == -1)
		return (2);
	return (0);
}
