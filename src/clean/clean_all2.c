/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:57:08 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/30 23:25:11 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_arg_stdin(char **cmd_arg_stdin)
{
	int	i;

	if (!cmd_arg_stdin)
		return ;
	i = 0;
	while (cmd_arg_stdin[i])
	{
		free(cmd_arg_stdin[i]);
		i++;
	}
	free(cmd_arg_stdin);
}

void	free_args(t_arg *args)
{
	t_arg	*current;
	t_arg	*next;

	if (!args)
		return ;
	current = args;
	while (current)
	{
		next = current->next;
		if (current->content)
		{
			free(current->content);
			current->content = NULL;
		}
		free(current);
		current = next;
	}
}

void	safe_free_cmds(t_cmd *cmds)
{
	t_cmd	*current_cmd;
	t_cmd	*next_cmd;

	current_cmd = cmds;
	while (current_cmd)
	{
		next_cmd = current_cmd->next;
		if (current_cmd->args)
			free_args(current_cmd->args);
		if (current_cmd->cmd_arg_stdin)
			safe_free_all_strings(&(current_cmd->cmd_arg_stdin));
		ft_safe_free((void **)&current_cmd);
		current_cmd = next_cmd;
	}
}

void	free_pipes(int **pipes, int nbr_pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < nbr_pipes)
	{
		ft_safe_free((void **)&pipes[i]);
		i++;
	}
	ft_safe_free((void **)&pipes);
}
