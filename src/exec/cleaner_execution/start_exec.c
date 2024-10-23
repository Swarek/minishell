/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:04:23 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/23 21:24:16 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_it(t_shell *shell)
{
	if (shell == NULL || shell->cmds == NULL || shell->cmds->args == NULL)
		return (-1);
	all_init(shell);
	if (shell->nbr_pipes == 0)
	{
		if (starting_one_cmd(shell) == -1)
			return (-1);
	}
	else if (shell->nbr_pipes >= 1)
	{
		fork_process(shell);
		wait_and_cleanup(shell);
	}
	return (0);
}
