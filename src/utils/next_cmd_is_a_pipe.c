/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_cmd_is_a_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 04:58:44 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/22 05:13:35 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	next_cmd_is_a_pipe(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->cmds && ft_strcmp(shell->cmds->args->type, "pipe") != 0
		&& ft_strcmp(shell->cmds->args->type, "semicolon") != 0)
		shell->cmds = shell->cmds->next;
	if (shell->cmds && ft_strcmp(shell->cmds->args->type, "pipe") == 0)
		return (1);
	return (0);
}
