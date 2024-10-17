/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:04:23 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/18 01:53:58 by mblanc           ###   ########.fr       */
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

int	if_built_in_execute(t_arg *args)
{
	if (ft_strcmp(args->content, "echo") == 0)
		return (1);
	return (0);
}

int	exec_it(t_cmd *cmds)
{
	if (cmds == NULL || cmds->args == NULL)
		return (0);
	if (if_built_in_execute(cmds->args) == 1)
	{
		if (ft_strcmp(cmds->args->content, "echo") == 0)
			ft_echo(cmds->args);
	}
	return (0);
}
