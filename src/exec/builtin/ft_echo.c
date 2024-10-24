/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:35:19 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/23 02:38:55 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Return 0 if iarg_stdin[1] is not a -n(n xtimes)
// Return 1 if iarg_stdin[1] is a -n(n xtimes)
int	handle_multiple_n_echo(t_shell *shell)
{
	int	i;

	i = 2;
	if (!(shell->cmds->cmd_arg_stdin[1][0] == '-')
		|| !(shell->cmds->cmd_arg_stdin[1][1] == 'n'))
		return (0);
	while (shell->cmds->cmd_arg_stdin[1][i] != '\0'
		&& shell->cmds->cmd_arg_stdin[1][i] == 'n')
		i++;
	if (shell->cmds->cmd_arg_stdin[1][i] == '\0')
		return (1);
	return (0);
}

int	ft_echo(t_shell *shell)
{
	int	no_newline;
	int	i;

	no_newline = 0;
	i = 1;
	if (!shell->cmds->cmd_arg_stdin[1])
		return (ft_putchar_fd('\n', shell->outfile), 0);
	if (handle_multiple_n_echo(shell) == 1)
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

// int	ft_echo(t_shell *shell)
// {
// 	int	no_newline;
// 	int	i;

// 	no_newline = 0;
// 	i = 1;
// 	if (shell->cmds->cmd_arg_stdin[1] != NULL
// 		&& ft_strcmp(shell->cmds->cmd_arg_stdin[1], "-n") == 0) // piege quand en parametre -nnnnnnn
// 	{
// 		no_newline = 1;
// 		i = 2;
// 	}
// 	else
// 		i = 1;
// 	while (shell->cmds->cmd_arg_stdin[i] != NULL)
// 	{
// 		ft_putstr_fd(shell->cmds->cmd_arg_stdin[i], shell->outfile);
// 		if (shell->cmds->cmd_arg_stdin[i + 1] != NULL)
// 			ft_putchar_fd(' ', shell->outfile);
// 		i++;
// 	}
// 	if (!no_newline)
// 		ft_putchar_fd('\n', shell->outfile);
// 	return (0);
// }
