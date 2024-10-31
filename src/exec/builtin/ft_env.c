/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:06:09 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 02:11:15 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **envp, t_shell *shell)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], shell->outfile);
		ft_putchar_fd('\n', shell->outfile);
		i++;
	}
	shell->exit_status = 0;
}
