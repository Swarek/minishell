/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:04:23 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/25 03:10:42 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	exec_it(t_shell *shell)
{
	if (shell == NULL || shell->cmds == NULL || shell->cmds->args == NULL)
		return (-1);
	if (all_init(shell) == -1) // Un seul appel à all_init
		return (-1);
	if (shell->nbr_pipes == 0)
	{
		if (starting_one_cmd(shell) == -1)
		{
			clean_up_for_error_init(shell, shell->nbr_pipes);
			// Nettoyage en cas d'erreur
			return (-1);
		}
	}
	else if (shell->nbr_pipes >= 1)
	{
		fork_process(shell);
		wait_and_cleanup(shell);
	}
	return (0);
}
