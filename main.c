/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:09:52 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/22 17:05:50 by mblanc           ###   ########.fr       */
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
t_shell	*init_struct_shell(char **envp)
{
	t_shell *shell;
	
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->last_exit_status = 0;
	shell->envp = env_copy(envp);
	shell->cmds = NULL;
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