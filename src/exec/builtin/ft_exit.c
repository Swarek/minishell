/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:07:45 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/18 09:25:01 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_arg *args)
{
	int exit_code;
	int	global_last_exit_status;

	global_last_exit_status = 0;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!args->next)
		exit(global_last_exit_status);
	args = args->next;
	if (!is_numeric(args->content))
	{
		ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
		exit(255);
	}
	if (args->next)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	exit_code = ft_atoi(args->content);
	exit(exit_code);
}
