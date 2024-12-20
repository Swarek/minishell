/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doing_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 01:59:53 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 02:18:25 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_in(char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (1);
	if (ft_strcmp(args[0], "cd") == 0)
		return (1);
	if (ft_strcmp(args[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(args[0], "export") == 0)
		return (1);
	if (ft_strcmp(args[0], "env") == 0)
		return (1);
	if (ft_strcmp(args[0], "unset") == 0)
		return (1);
	if (ft_strcmp(args[0], "exit") == 0)
		return (1);
	return (0);
}

int	is_built_in_t_args(t_arg *args)
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

int	execute_built_in(t_shell *shell, char **cmd_arg_stdin, char ***envp)
{
	if (ft_strcmp(cmd_arg_stdin[0], "echo") == 0)
		return (ft_echo(shell), shell->exit_status);
	if (ft_strcmp(cmd_arg_stdin[0], "cd") == 0)
		return (ft_cd(shell));
	if (ft_strcmp(cmd_arg_stdin[0], "pwd") == 0)
		return (ft_pwd(shell));
	if (ft_strcmp(cmd_arg_stdin[0], "export") == 0)
		return (ft_export(shell->cmds->args, envp, shell));
	if (ft_strcmp(cmd_arg_stdin[0], "env") == 0)
		return (ft_env(*envp, shell), 0);
	if (ft_strcmp(cmd_arg_stdin[0], "unset") == 0)
		return (ft_unset(shell->cmds->args, envp, shell), shell->exit_status);
	if (ft_strcmp(cmd_arg_stdin[0], "exit") == 0)
		return (ft_exit(shell, shell->cmds->args));
	return (127);
}
