/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:33:56 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/30 18:35:03 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_child_pids(t_shell *shell)
{
	if (shell->child_pids)
	{
		free(shell->child_pids);
		shell->child_pids = NULL;
	}
}

void	clean_cmds(t_shell *shell)
{
	if (shell->cmds)
	{
		safe_free_cmds(shell->cmds);
		shell->cmds = NULL;
	}
}

void	clean_pipes(t_shell *shell)
{
	if (shell->pipes)
	{
		free_pipes(shell->pipes, shell->nbr_pipes);
		shell->pipes = NULL;
	}
}

void	clean_envp(t_shell *shell)
{
	char	**ptr;

	if (shell->envp)
	{
		ptr = shell->envp;
		while (*ptr)
			free(*ptr++);
		free(shell->envp);
		shell->envp = NULL;
	}
}

void	clean_all(t_shell *shell)
{
	if (!shell)
		return ;
	clean_child_pids(shell);
	clean_cmds(shell);
	clean_pipes(shell);
	clean_envp(shell);
	rl_cleanup_after_signal();
	rl_deprep_terminal();
	free(shell);
}
