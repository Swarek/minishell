/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:04:23 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/17 23:26:57 by mblanc           ###   ########.fr       */
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

int	is_built_in(t_arg *args)
{
	if (ft_strcmp(args->content, "echo") == 0)
		return (1);
	return (0);
}

int	exec_it(t_cmd *cmds)
{
	my_print_command(cmds->args);
	if (is_built_in(cmds->args) == 1)
	{
		if (ft_strcmp(cmds->args->content, "echo") == 0)
			ft_echo(cmds->args);
	}
	return (0);
}
