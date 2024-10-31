/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 05:55:10 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 02:10:16 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *shell)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, shell->outfile);
		ft_putchar_fd('\n', shell->outfile);
		shell->exit_status = 0;
	}
	else
		return (shell->exit_status = 1,
			error_msg("pwd: error retrieving current directory\n"), 0);
	return (0);
}
