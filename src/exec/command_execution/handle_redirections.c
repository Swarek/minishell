/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:07:29 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/18 20:45:12 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	opening_files(t_pipex *pipex, char *infile, char *outfile, int output_mode)
{
	if (infile != NULL)
		pipex->infile = open(infile, O_RDONLY);
	if (outfile != NULL)
	{
		if (output_mode == OUTPUT_REDIRECTION)
			pipex->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (output_mode == APPEND_REDIRECTION)
			pipex->outfile = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (pipex->outfile < 0 && pipex->infile < 0)
		return (error_msg("Problem with infile and outfile\n"));
	else if (pipex->infile < 0)
		return (close(pipex->infile), error_msg("Failed to open infile\n"));
	if (pipex->outfile < 0)
		return (close(pipex->infile), error_msg("Failed to open outfile\n"));
	return (0);
}

int	handle_input_redirection(t_cmd *cmds, t_pipex *pipex)
{
	while (cmds)
	{
		if (ft_strcmp(cmds->args->type, "input") == 0
			|| ft_strcmp (cmds->args->content, "<") == 0)
		{
			if (opening_files(pipex, cmds->next->args->content, NULL, 0) == -1)
				return (-1);
		}
		cmds = cmds->next;
	}
	return (0);
}

int handle_output_redirection(t_cmd *cmds, t_pipex *pipex)
{
	while (cmds)
	{
		if (ft_strcmp(cmds->args->type, "redir_right") == 0
			|| ft_strcmp (cmds->args->content, ">") == 0)
		{
			if (opening_files(pipex, NULL, cmds->next->args->content, OUTPUT_REDIRECTION) == -1)
				return (-1);
		}
		cmds = cmds->next;
	}
	return (0);
}

int handle_append_redirection(t_cmd *cmds, t_pipex *pipex)
{
	while (cmds)
	{
		if (ft_strcmp(cmds->args->type, "append") == 0
			|| ft_strcmp (cmds->args->content, ">>") == 0)
		{
			if (opening_files(pipex, NULL, cmds->next->args->content, APPEND_REDIRECTION) == -1)
				return (-1);
		}
		cmds = cmds->next;
	}
	return (0);
}

int	looking_for_here_doc(t_cmd *cmds, t_pipex *pipex)
{
	while (cmds)
	{
		if (ft_strcmp(cmds->args->type, "here_doc") == 0
			|| ft_strcmp (cmds->args->content, "<<") == 0)
		{
			if (here_doc_management(cmds->next->args->content) == -1)
				return (-1);
			if (opening_files(pipex, "temp.txt", NULL, 0) == -1)
				return (-1);
		}
		cmds = cmds->next;
	}
	return (0);
}
