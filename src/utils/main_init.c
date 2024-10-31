/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:38:17 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/31 05:24:49 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_copy(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	if (!env || !env[0])
		return (NULL);
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			while (i >= 0)
				free(new_env[i--]);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

t_shell	*init_struct_shell(char **envp)
{
	t_shell	*shell;

	(void)envp;
	shell = ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		return (NULL);
	shell->exit_status = 0;
	shell->envp = env_copy(envp);
	if (!shell->envp)
		create_basic_env(shell);
	shlvl_incrementation(shell);
	shell->cmds = NULL;
	shell->total_cmd_count = 0;
	shell->nbr_pipes = 0;
	shell->infile = 0;
	shell->outfile = 0;
	shell->input_pipe = 0;
	shell->there_is_redir_out = 0;
	shell->n_th_cmd = 0;
	shell->pipes = NULL;
	shell->child_pids = NULL;
	shell->in_child_process = 0;
	return (shell);
}
