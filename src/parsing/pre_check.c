/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 21:25:51 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/28 14:38:43 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	check_pipe_position(char *input)
{
	int		i;

	i = 0;
	if (input[0] && input[0] == '|')
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

int	precheck(char *input)
{
	if (check_pipe_position(input) == -1)
		return (2);
	return (0);
}
