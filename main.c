/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:09:52 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/22 18:07:10 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char	**env_copy(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
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
			while(i >= 0)
				free(new_env[i--]);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

t_shell *init_struct_shell(char **envp)
{
    t_shell *shell;

    shell = malloc(sizeof(t_shell));
    if (!shell)
        return (NULL);
    shell->last_exit_status = 0;
    shell->envp = env_copy(envp);
    shell->cmds = NULL;
    // Initialize all other members
    shell->total_cmd_count = 0;
    shell->nbr_pipes = 0;
    shell->infile = 0;
    shell->outfile = 0;
    shell->input_pipe = 0;
    shell->there_is_redir_out = 0;
    shell->n_th_cmd = 0;
    shell->pipes = NULL;
    shell->child_pids = NULL;
    return (shell);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_cmd	*cmds;
	t_shell	*shell;
	int		color;

	(void)ac;
	(void)av;
	line = NULL;
	cmds = NULL;
	shell = init_struct_shell(envp);
	if (!shell)
		return (-1);
	cmds = NULL;
	color = 0;
	while (1)
	{
		line = reading_line(color);
		if (parse_it(line, &cmds) != 0)
			return (free(line), -1);
		free(line);
		shell->cmds = cmds;
		// initiates_type_cmd(shell);
		// print_all_commands(cmds);
		exec_it(shell);
		// free_cmds(cmds);
		// ft_printf("Testttttttt\n");
		cmds = NULL;
		color++;
	}
	return (0);
}
