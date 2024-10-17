/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:35:19 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/17 23:17:00 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_arg *args)
{
	int	no_newline;
	int	i;

	no_newline = 0;
	i = 1;
	args = args->next;
	if (ft_strcmp(args->content, "-n") == 0)
	{
		no_newline = 1;
		i++;
	}
	if (args->next == NULL)
	{
		ft_putstr("");
		if (!no_newline)
			ft_putchar_fd('\n', 1);
		return (0);
	}
	args = args->next;
	ft_putstr(args->content);
	if (!no_newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
