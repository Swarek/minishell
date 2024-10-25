/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsequent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 01:06:59 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/25 02:33:55 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect_or_pipe(char *type)
{
	return (ft_strncmp(type, "pipe", 4) == 0 || ft_strncmp(type, "redir_left",
			10) == 0 || ft_strncmp(type, "redir_right", 11) == 0
		|| ft_strncmp(type, "double_redir_left", 16) == 0 || ft_strncmp(type,
			"double_redir_right", 17) == 0);
}

int	error_if_subsequent_commands(t_cmd **cmds)
{
	t_cmd	*current_cmd;
	t_arg	*current_arg;
	t_arg	*next_arg;

	current_cmd = *cmds;
	while (current_cmd)
	{
		current_arg = current_cmd->args;
		while (current_arg && current_arg->next)
		{
			next_arg = current_arg->next;
			if (is_redirect_or_pipe(current_arg->type)
				&& is_redirect_or_pipe(next_arg->type))
				return (-1);
			current_arg = current_arg->next;
		}
		current_cmd = current_cmd->next;
	}
	return (0);
}
