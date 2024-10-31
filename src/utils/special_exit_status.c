/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_exit_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 05:40:32 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 05:42:41 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_exit_status(t_shell *shell)
{
	if (shell != NULL && shell->cmds != NULL && shell->cmds->args != NULL)
	{
		if (ft_strcmp(shell->cmds->args->content, ":") == 0)
			return (shell->exit_status = 0, 1);
		else if (ft_strcmp(shell->cmds->args->content, "!") == 0)
			return (shell->exit_status = 1, 1);
		else if (ft_strcmp(shell->cmds->args->content, "<") == 0)
			return (shell->exit_status = 0, 2);
		else if (ft_strcmp(shell->cmds->args->content, ">") == 0)
			return (shell->exit_status = 0, 2);
		else if (ft_strcmp(shell->cmds->args->content, ">>") == 0)
			return (shell->exit_status = 0, 2);
		else if (ft_strcmp(shell->cmds->args->content, "<<") == 0)
			return (shell->exit_status = 0, 2);
	}
}
