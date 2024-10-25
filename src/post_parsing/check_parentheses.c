/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parentheses.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 02:24:00 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/25 02:33:39 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_if_unclosed_parentheses(t_cmd **cmds)
{
	t_cmd	*current_cmd;
	t_arg	*current_arg;
	int		open_parentheses;
	int		i;

	open_parentheses = 0;
	current_cmd = *cmds;
	while (current_cmd)
	{
		current_arg = current_cmd->args;
		while (current_arg)
		{
			i = 0;
			if (ft_strncmp(current_arg->type, "word", 4) == 0)
			{
				while (current_arg->content[i])
				{
					if (current_arg->content[i] == '(')
						open_parentheses++;
					else if (current_arg->content[i] == ')')
					{
						open_parentheses--;
						if (open_parentheses < 0)
							return (-1);
					}
					i++;
				}
			}
			current_arg = current_arg->next;
		}
		current_cmd = current_cmd->next;
	}
	if (open_parentheses != 0)
		return (-1);
	return (0);
}
