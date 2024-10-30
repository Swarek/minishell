/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 21:22:35 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/30 17:49:05 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	single_cmd(t_shell *shell)
{
	t_arg	*current;

	current = shell->cmds->args;
	while (current && ft_strcmp(current->type, "command") != 0)
		current = current->next;
	if (!current)
		return (execute_solo(shell));
	if (is_built_in(shell->cmds->cmd_arg_stdin))
	{
		shell->exit_status = execute_built_in(shell, shell->cmds->cmd_arg_stdin,
				&shell->envp);
		return (shell->exit_status);
	}
	else
	{
		execute_solo(shell);
		if (shell->infile > STDIN)
			close(shell->infile);
		if (shell->outfile > STDOUT)
			close(shell->outfile);
		return (shell->exit_status);
	}
}

// Iniatiate all needed and call single_cmd to exec
int	starting_one_cmd(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell == NULL || shell->cmds == NULL || shell->cmds->args == NULL)
		return (-1);
	if (handle_io_redirections(shell) == -1)
		return (-1);
	cut_the_cmd_plus_args(shell->cmds);
	if (single_cmd(shell) == -1)
		return (-1);
	return (0);
}
