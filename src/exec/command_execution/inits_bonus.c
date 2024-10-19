/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 03:06:09 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/19 14:52:33 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->pipes = malloc(sizeof(int *) * (pipex->nbr_pipes));
	if (!pipex->pipes)
		return (error_msg("Memory allocation failed 1\n"));
	while (i < pipex->nbr_pipes)
	{
		pipex->pipes[i] = malloc(2 * sizeof(int));
		if (!pipex->pipes[i])
		{
			cleanup(pipex, NULL, i);
			return (error_msg("Memory allocation failed 2\n"));
		}
		if (pipe(pipex->pipes[i]) == -1)
		{
			cleanup(pipex, NULL, i);
			return (error_msg("Pipe creation failed 3\n"));
		}
		i++;
	}
	return (0);
}

int	init_child_pids(t_pipex *pipex)
{
	pipex->child_pids = malloc(sizeof(pid_t) * pipex->cmd_count);
	if (!pipex->child_pids)
	{
		cleanup(pipex, NULL, pipex->nbr_pipes);
		return (error_msg("Memory allocation failed\n"));
	}
	return (0);
}

int	init_pipex_structure(t_pipex *pipex, char **env)
{
	pipex->pipes = NULL;
	pipex->nbr_pipes = pipex->cmd_count - 1;
	pipex->child_pids = NULL;
	pipex->envp = env;
	return (0);
}

int	all_init(t_pipex *pipex, char **env)
{
	if (init_pipex_structure(pipex, env) == -1)
		return (-1);
	if (init_pipes(pipex) == -1)
		return (-1);
	if (init_child_pids(pipex) == -1)
		return (-1);
	return (0);
}
