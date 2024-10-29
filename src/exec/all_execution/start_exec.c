/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:04:23 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/29 06:45:54 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	any_empty_cmd(t_cmd *cmd)
{
	t_arg	*arg;

	while (cmd)
	{
		arg = cmd->args;
		if (arg == NULL)
			return (1);
		while (arg)
		{
			if (arg->content == NULL)
				return (1);
			arg = arg->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	exec_it(t_shell *shell)
{
	if (shell == NULL || shell->cmds == NULL || shell->cmds->args == NULL || any_empty_cmd(shell->cmds))
		return (0);
	if (all_init(shell) == -1) // Un seul appel à all_init
		return (-1);
	if (count_cmd(shell->cmds) == 0)
		return (0);
	handle_here_doc(shell);
	if (shell->nbr_pipes == 0)
	{
		if (starting_one_cmd(shell) == -1)
		{
			clean_up_for_error_init(shell, shell->nbr_pipes);
			// Nettoyage en cas d'erreur
			return (-1);
		}
	}
	else if (shell->nbr_pipes >= 1)
	{
		fork_process(shell);
		wait_and_cleanup(shell);
	}
	ft_printf("shell->nth_here_doc = %d\n", shell->nth_here_doc);
	if (shell->nth_here_doc > 0)
		delete_all_temp_files(shell->nth_here_doc + 1);
	return (0);
}
