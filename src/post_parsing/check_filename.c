/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 02:52:31 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/31 03:45:12 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (is_valid_char(input[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	error_in_filename(t_cmd **cmds)
{
	t_cmd	*current_cmd;
	t_arg	*current_arg;

	current_cmd = *cmds;
	while (current_cmd)
	{
		current_arg = current_cmd->args;
		while (current_arg)
		{
			if (ft_strncmp(current_arg->type, "file", 4) == 0)
			{
				if (check_file_name(current_arg->content) == -1)
					return (-1);
			}
			current_arg = current_arg->next;
		}
		current_cmd = current_cmd->next;
	}
	return (0);
}
