/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:35:19 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/29 22:42:20 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_flag_echo(char *flag)
{
	int	i;

	i = 1;
	if (flag == NULL)
		return (0);
	if (!(flag[0] == '-'))
		return (0);
	while (flag[i] && flag[i] == 'n')
		i++;
	if (flag[i] == '\0')
		return (1);
	return (0);
}

// Return 0 if iarg_stdin[1] is not a -n(n xtimes)
// Return x as the index of the first arg which is not a flag.
int	handle_multiple_n_echo(t_shell *shell)
{
	int	i;

	i = 1;
	while (shell->cmds->cmd_arg_stdin[i] != NULL)
	{
		if (!(is_flag_echo(shell->cmds->cmd_arg_stdin[i])))
			return (i);
		i++;
	}
	if (is_flag_echo(shell->cmds->cmd_arg_stdin[i - 1]))
		return (-2);
	return (1);
}

int	ft_echo(t_shell *shell)
{
	int	no_newline;
	int	i;

	no_newline = 0;
	i = 1;
	if (!shell->cmds->cmd_arg_stdin[1])
		return (ft_putchar_fd('\n', shell->outfile), 0);
	i = handle_multiple_n_echo(shell);
	if (i > 1 || i == -2)
		no_newline = 1;
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
