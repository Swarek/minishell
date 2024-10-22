/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_real_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:35:09 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/22 18:43:54 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_type_cmd(t_cmd *cmds)
{
	cmds->args->type = "command";
	return (1);
}

int	count_real_cmd(t_shell *shell)
{
	int		nbr_cmds;
	t_cmd	*tmp;

	nbr_cmds = 0;
	tmp = shell->cmds;
	while (tmp)
	{
		if (is_built_in(tmp->cmd_arg_stdin) == 1)
			nbr_cmds += add_type_cmd(tmp);
		else if (is_absolute_or_relative_path(tmp->args->content))
		{
			if (handle_absolute_or_relative_path(tmp->args->content) != NULL)
				nbr_cmds += add_type_cmd(tmp);
		}
		else if (find_command_path(shell, tmp->args->content, shell->envp) != NULL)
			nbr_cmds += add_type_cmd(tmp);
		
		tmp = tmp->next;
	}
	return (nbr_cmds);
}
