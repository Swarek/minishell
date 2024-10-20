/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doing_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 01:59:53 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/20 21:04:57 by mblanc           ###   ########.fr       */
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

int	execute_built_in(t_shell *shell, char **cmd_arg_stdin, char ***envp)
{
	if (ft_strcmp(cmd_arg_stdin[0], "echo") == 0)
		return (ft_echo(shell));
	if (ft_strcmp(cmd_arg_stdin[0], "cd") == 0)
		return (ft_cd(shell));
	if (ft_strcmp(cmd_arg_stdin[0], "pwd") == 0)
		return (ft_pwd(shell));
	if (ft_strcmp(cmd_arg_stdin[0], "export") == 0)
		return (ft_export(shell->cmds->args, envp)); 		// A bien faire a la fin
	if (ft_strcmp(cmd_arg_stdin[0], "env") == 0)
		return (ft_env(*envp, shell), 0);
	if (ft_strcmp(cmd_arg_stdin[0], "unset") == 0)			// A bien faire a la fin
		return (ft_unset(shell->cmds->args, envp), 0);
	if (ft_strcmp(cmd_arg_stdin[0], "exit") == 0)
		return (ft_exit(shell, shell->cmds->args));
	return (-1);
}
