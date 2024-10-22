/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_pipe_is_coming.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:41:49 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/22 05:30:31 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return 1 if a pipe is coming, 0 otherwise
int	is_there_a_pipes_coming(t_shell *shell)
{
	t_cmd	*tmp;

	tmp = shell->cmds;
	while (tmp && ft_strcmp(tmp->args->type, "semicolon") != 0)
	{
		if (ft_strcmp(tmp->args->type, "pipe") == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
