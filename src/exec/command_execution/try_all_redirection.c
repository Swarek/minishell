/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_all_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:25:22 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/18 20:47:29 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	try_all_redirection(t_cmd *cmds, t_pipex *pipex)
{
	if (handle_input_redirection(cmds, pipex) == -1)
		return (-1);
	if (handle_output_redirection(cmds, pipex) == -1)
		return (-1);
	if (looking_for_here_doc(cmds, pipex) == -1)
		return (-1);
	if (handle_append_redirection(cmds, pipex) == -1)
		return (-1);
	dup2(pipex->infile, STDIN_FILENO);
	dup2(pipex->outfile, STDOUT_FILENO);
	return (0);
}
