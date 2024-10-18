/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:04:23 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/18 09:35:30 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_print_command(t_arg *args)
{
	ft_printf("Command: %s\n", args->content);
	args = args->next;
	while (args)
	{
		ft_printf("Content : %s, Type : %s ", args->content, args->type);
		args = args->next;
	}
	ft_printf("\n");
}

static int	is_built_in(t_arg *args)
{
	if (ft_strcmp(args->content, "echo") == 0)
		return (1);
	if (ft_strcmp(args->content, "cd") == 0)
		return (1);
	if (ft_strcmp(args->content, "pwd") == 0)
		return (1);
	if (ft_strcmp(args->content, "export") == 0)
		return (1);
	if (ft_strcmp(args->content, "env") == 0)
		return (1);
	if (ft_strcmp(args->content, "unset") == 0)
		return (1);
	if (ft_strcmp(args->content, "exit") == 0)
		return (1);
	return (0);
}

static int	execute_built_in(t_arg *args)
{
	if (ft_strcmp(args->content, "echo") == 0)
		return (ft_echo(args));
	if (ft_strcmp(args->content, "cd") == 0)
		return (ft_cd(args));
	if (ft_strcmp(args->content, "pwd") == 0)
		return (ft_pwd());
	// if (ft_strcmp(args->content, "export") == 0)
		// return (ft_export(args, &g_shell.envp));
	// if (ft_strcmp(args->content, "env") == 0)
	// 	return (ft_env(g_shell.envp), 0);
	// if (ft_strcmp(args->content, "unset") == 0)
	// 	return (ft_unset(args, &g_shell.envp), 0);
	if (ft_strcmp(args->content, "exit") == 0)
		return (ft_exit(args));
	return (-1);
}

int	how_much_pipes(t_arg *cmds)
{
	int		count;

	count = 0;
	while (cmds)
	{
		if (ft_strcmp(cmds->type, "pipe") == 0)
			count++;
		cmds = cmds->next;
	}
	return (count);
}

int	exec_it(t_cmd *cmds)
{
	int	nb_pipes;

	if (cmds == NULL || cmds->args == NULL)
		return (0);
	nb_pipes = how_much_pipes(cmds->args);
	if (is_built_in(cmds->args))
	{
		if (execute_built_in(cmds->args) == -1)
			return (-1);
	}
	return (0);
}
