/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 21:22:35 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/24 03:43:45 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// After variables are set, we will call this function to execute the command
// This function will check if the command is a built-in, and execute it if it is
// If it is not, it will execute the command with execve
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
		shell->exit_status = execute_built_in(shell, shell->cmds->cmd_arg_stdin, &shell->envp);
		return (shell->exit_status);
	}
	else
	{
		execute_solo(shell);
		return (shell->exit_status);
	}
}

// Iniatiate all needed and call single_cmd to exec
int starting_one_cmd(t_shell *shell)
{
    int i;

    i = 0;
    if (shell == NULL || shell->cmds == NULL || shell->cmds->args == NULL)
        return (-1);
    if (handle_io_redirections(shell) == -1)
        return (-1);
    if (all_init(shell) == -1)
    {
        shell->exit_status = 1;
        clean_all(shell); // Nettoyer en cas d'échec d'initialisation
        return (-1);
    }
    // print_all_commands(shell->cmds);
    cut_the_cmd_plus_args(shell->cmds);
    if (single_cmd(shell) == -1)
    {
        clean_all(shell); // Nettoyer en cas d'erreur dans single_cmd
        return (-1);
    }
    return (0);
}

