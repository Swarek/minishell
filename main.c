/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:09:52 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/20 16:14:01 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

// Fonction pour afficher le contenu d'une commande parsée
void	print_command(t_cmd *cmd)
{
	t_arg	*arg;

	printf("Command: ");
	arg = cmd->args;
	while (arg)
	{
		printf("[%s (%s)] ", arg->content, arg->type);
		arg = arg->next;
	}
	printf("\n");
}

// Fonction pour afficher toutes les commandes parsées
void	print_all_commands(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		printf("Command %d:\n", i++);
		print_command(cmds);
		cmds = cmds->next;
	}
	printf("\n");
}

int	main(void)
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

	for (int i = 0; test_cases[i] != NULL; i++)
	{
		line = reading_line(color);
		if (parse_it(line, &cmds) != 0)
			return (free(line), -1);
		free(line);
		shell->cmds = cmds;
		print_all_commands(cmds);
		exec_it(shell);
		// free_cmds(cmds);
		// ft_printf("Testttttttt\n");
		cmds = NULL;
		color++;
	}
	return (0);
}
