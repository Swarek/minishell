/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:57:08 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/28 23:02:34 by dmathis          ###   ########.fr       */
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
		if (current->type && ft_strcmp(current->type, "word") != 0
			&& ft_strcmp(current->type, "pipe") != 0 && ft_strcmp(current->type,
				"command") != 0 && ft_strcmp(current->type, "file") != 0
			&& ft_strcmp(current->type, "redir_right") != 0
			&& ft_strcmp(current->type, "redir_left") != 0)
		{
			free(current->type);
			current->type = NULL;
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
	for (i = 0; i < nbr_pipes; i++)
	{
		ft_safe_free((void **)&(pipes[i]));
	}
	ft_safe_free((void **)&pipes);
}

void	clean_all(t_shell *shell)
{
	char	**ptr;

	if (!shell)
		return ;
	if (shell->child_pids)
	{
		free(shell->child_pids);
		shell->child_pids = NULL;
	}
	// Ne pas nettoyer cmds si déjà NULL
	if (shell->cmds)
	{
		safe_free_cmds(shell->cmds);
		shell->cmds = NULL;
	}
	if (shell->pipes)
	{
		free_pipes(shell->pipes, shell->nbr_pipes);
		shell->pipes = NULL;
	}
	if (shell->envp)
	{
		ptr = shell->envp;
		while (*ptr)
			free(*ptr++);
		free(shell->envp);
		shell->envp = NULL;
	}
	rl_cleanup_after_signal();
	rl_deprep_terminal();
	free(shell);
}
