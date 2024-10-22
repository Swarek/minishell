/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:35:19 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/21 23:35:56 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_shell *shell)
{
	int	no_newline;
	int	i;

	no_newline = 0;
	i = 1;
	if (shell->cmds->cmd_arg_stdin[1] != NULL
		&& ft_strcmp(shell->cmds->cmd_arg_stdin[1], "-n") == 0) // piege quand en parametre -nnnnnnn
	{
		no_newline = 1;
		i = 2;
	}
	else
		i = 1;
	while (shell->cmds->cmd_arg_stdin[i] != NULL)
	{
		ft_putstr_fd(shell->cmds->cmd_arg_stdin[i], shell->outfile);
		if (shell->cmds->cmd_arg_stdin[i + 1] != NULL)
			ft_putchar_fd(' ', shell->outfile);
		i++;
	}
	if (!no_newline)
		ft_putchar_fd('\n', shell->outfile);
	return (0);
}
