/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 03:06:09 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/24 05:05:45 by mblanc           ###   ########.fr       */
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

int init_pipes(t_shell *shell)
{
    int i;

    // Vérifier si le nombre de pipes est supérieur à 0
    if (shell->nbr_pipes <= 0)
    {
        shell->pipes = NULL;
        return (0);
    }

    shell->pipes = malloc(sizeof(int *) * shell->nbr_pipes);
    if (!shell->pipes)
        return (error_msg("Memory allocation failed\n"), -1);
    i = 0;
    while (i < shell->nbr_pipes)
    {
        shell->pipes[i] = malloc(2 * sizeof(int));
        if (!shell->pipes[i])
        {
            clean_up_for_error_init(shell, i);  // Nettoyer les pipes alloués partiellement
            return (error_msg("Memory allocation failed\n"), -1);
        }
        if (pipe(shell->pipes[i]) == -1)
        {
            clean_up_for_error_init(shell, i);  // Nettoyer les pipes alloués partiellement
            return (error_msg("Pipe creation failed\n"), -1);
        }
        i++;
    }
    return (0);
}

int init_child_pids(t_shell *shell)
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
		find_arg_add_type_cmd(shell, tmp->args);
		tmp = tmp->next;
	}
}

int	all_init(t_shell *shell)
{
	shell->nbr_pipes = count_pipe(shell->cmds);
	shell->total_cmd_count = shell->nbr_pipes + 1;
	shell->pipes = NULL;
	shell->child_pids = NULL;
	shell->there_is_redir_out = 0;
	shell->n_th_cmd = 0;
	if (init_pipes(shell) == -1)
		return (-1);
	if (init_child_pids(shell) == -1)
		return (-1);
	initiates_type_cmd(shell);
	return (0);
}
