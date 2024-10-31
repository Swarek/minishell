/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:38:24 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 02:05:22 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_d(char *line, t_shell *shell)
{
	int	exit_status;

	exit_status = shell->exit_status;
	if (!line)
	{
		if (shell)
			clean_all(shell);
		write(1, "exit\n", 5);
		exit(exit_status);
	}
}
