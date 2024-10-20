/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:04:23 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/20 11:35:45 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	how_much_pipes(t_arg *cmds)
{
	int		count;

	count = 0;
	while (cmds)
	{
		if (ft_strcmp(cmds->type, "pipe") == 0)
			count++;
		cmds = cmds->next;
	}
	return (count);
}

// int	exec_it(t_shell *shell)
// {
// 	if (shell == NULL || shell->cmds == NULL || shell->cmds->args == NULL)
// 		return (0);
// 	shell->args = shell->cmds->args;
// 	execution(shell);
// 	// execute_solo(shell);
// 	// if (is_built_in(shell->args))
// 	// {
// 	// 	if (execute_built_in(shell->args) == -1)
// 	// 		return (-1);
// 	// }
// 	return (0);
// }
