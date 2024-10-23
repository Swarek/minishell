/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_add_add_type_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:34:35 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/23 09:52:17 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_arg_add_type_cmd(t_shell *shell, t_arg *args, char **envp)
{
	t_arg	*tmp;

	tmp = args;
	while (tmp)
	{
		if (strcmp(tmp->type, "file") == 0)
		{
			tmp = tmp->next;
			continue;
		}
		if (is_built_in_t_args(tmp) == 1)
		{
			tmp->type = "command";
		}
		else if (is_absolute_or_relative_path(tmp->content))
		{
			if (handle_absolute_or_relative_path(tmp->content) != NULL)
				tmp->type = "command";
		}
		else if (find_command_path(shell, tmp->content, envp) != NULL)
		{
			tmp->type = "command";
		}
		tmp = tmp->next;
	}
}

void	initiates_type_cmd(t_shell *shell)
{
	int		i;
	t_cmd	*tmp;
	
	i = 0;
	if (shell == NULL)
		return ;
	tmp = shell->cmds;
	while (tmp)
	{
		find_arg_add_type_cmd(shell, tmp->args, shell->envp);
		tmp = tmp->next;
	}
	// ft_printf("cmds:\n");
	// print_all_commands(shell->cmds);
	// shell->total_cmd_count = count_cmd(shell->cmds);
}
