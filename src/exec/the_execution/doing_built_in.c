/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doing_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 01:59:53 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/20 02:00:02 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_in(t_arg *args)
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

int	execute_built_in(t_arg *args, char ***envp)
{
	if (ft_strcmp(args->content, "echo") == 0)
		return (ft_echo(args));
	if (ft_strcmp(args->content, "cd") == 0)
		return (ft_cd(args));
	if (ft_strcmp(args->content, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(args->content, "export") == 0)
		return (ft_export(args, envp));
	if (ft_strcmp(args->content, "env") == 0)
		return (ft_env(*envp), 0);
	if (ft_strcmp(args->content, "unset") == 0)
		return (ft_unset(args, envp), 0);
	if (ft_strcmp(args->content, "exit") == 0)
		return (ft_exit(args));
	return (-1);
}
