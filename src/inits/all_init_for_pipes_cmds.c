/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_init_for_pipes_cmds.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 03:06:09 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 03:46:10 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_up_for_error_init(t_shell *shell, int pipe_count)
{
	int	i;

	if (shell->pipes)
	{
		i = 0;
		while (i < pipe_count)
		{
			if (shell->pipes[i])
				free(shell->pipes[i]);
			i++;
		}
		free(shell->pipes);
		shell->pipes = NULL;
	}
	if (shell->child_pids)
	{
		free(shell->child_pids);
		shell->child_pids = NULL;
	}
}

static int	init_pipes(t_shell *shell)
{
	int	i;

	if (shell->nbr_pipes <= 0)
		return (shell->pipes = NULL, 0);
	shell->pipes = malloc(sizeof(int *) * shell->nbr_pipes);
	if (!shell->pipes)
		return (error_msg("Memory allocation failed\n"), -1);
	i = 0;
	while (i < shell->nbr_pipes)
	{
		shell->pipes[i] = malloc(2 * sizeof(int));
		if (!shell->pipes[i])
		{
			clean_up_for_error_init(shell, i);
			return (error_msg("Memory allocation failed\n"), -1);
		}
		if (pipe(shell->pipes[i]) == -1)
		{
			clean_up_for_error_init(shell, i);
			return (error_msg("Pipe creation failed\n"), -1);
		}
		i++;
	}
	return (0);
}

static int	init_child_pids(t_shell *shell)
{
	if (shell->total_cmd_count <= 0)
	{
		shell->child_pids = NULL;
		return (0);
	}
	shell->child_pids = malloc(sizeof(pid_t) * shell->total_cmd_count);
	if (!shell->child_pids)
	{
		clean_up_for_error_init(shell, shell->nbr_pipes);
		return (error_msg("Memory allocation failed\n"), -1);
	}
	return (0);
}

static void	initiates_type_cmd(t_shell *shell)
{
	t_cmd	*tmp;

	if (shell == NULL)
		return ;
	tmp = shell->cmds;
	while (tmp)
	{
		find_arg_add_type_cmd(shell, tmp->args);
		tmp = tmp->next;
	}
}

int	all_init_for_pipes_cmds(t_shell *shell)
{
	if (shell->pipes)
	{
		free_pipes(shell->pipes, shell->nbr_pipes);
		shell->pipes = NULL;
	}
	if (shell->child_pids)
	{
		free(shell->child_pids);
		shell->child_pids = NULL;
	}
	shell->nbr_pipes = count_pipe(shell->cmds);
	shell->total_cmd_count = shell->nbr_pipes + 1;
	shell->there_is_redir_out = 0;
	shell->n_th_cmd = 0;
	if (init_pipes(shell) == -1)
		return (clean_up_for_error_init(shell, 0), -1);
	if (init_child_pids(shell) == -1)
	{
		clean_up_for_error_init(shell, shell->nbr_pipes);
		return (-1);
	}
	initiates_type_cmd(shell);
	return (0);
}
