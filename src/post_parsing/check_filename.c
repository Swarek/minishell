/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 02:52:31 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/23 03:01:20 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_d.h"

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
	int		i;

	current_cmd = *cmds;
	while (current_cmd)
	{
		current_arg = current_cmd->args;
		while (current_arg)
		{
			i = 0;
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
