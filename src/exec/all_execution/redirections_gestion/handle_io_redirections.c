/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_io_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:35:42 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 00:29:10 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*last_redir_left(t_arg *args)
{
	t_arg	*last_redir_left;

	last_redir_left = NULL;
	while (args)
	{
		if (ft_strcmp(args->type, "redir_left") == 0)
			last_redir_left = args;
		if (ft_strcmp(args->type, "double_redir_left") == 0)
			last_redir_left = args;
		args = args->next;
	}
	return (last_redir_left);
}

t_arg	*last_redir_right(t_arg *args)
{
	t_arg	*last_redir_right;

	last_redir_right = NULL;
	while (args)
	{
		if (ft_strcmp(args->type, "redir_right") == 0)
			last_redir_right = args;
		if (ft_strcmp(args->type, "double_redir_right") == 0)
			last_redir_right = args;
		args = args->next;
	}
	return (last_redir_right);
}

static int	handle_input_redirection(t_shell *shell, t_arg *redir_left)
{
	char	*name_file;

	if (redir_left != NULL)
	{
		if (ft_strcmp(redir_left->type, "double_redir_left") == 0)
		{
			name_file = name_files_here_doc(shell->nth_here_doc);
			shell->infile = open(name_file, O_RDONLY);
			free(name_file);
		}
		else
			shell->infile = open(redir_left->next->content, O_RDONLY);
		if (shell->infile < 0)
		{
			shell->exit_status = 1;
			error_msg("Failed to open infile\n");
			return (-1);
		}
	}
	else
	{
		shell->infile = STDIN_FILENO;
	}
	return (0);
}

static int	handle_output_redirection(t_shell *shell, t_arg *redir_right)
{
	if (redir_right != NULL)
	{
		if (ft_strcmp(redir_right->type, "redir_right") == 0)
			shell->outfile = open(redir_right->next->content,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (ft_strcmp(redir_right->type, "double_redir_right") == 0)
			shell->outfile = open(redir_right->next->content,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (shell->outfile < 0)
		{
			shell->exit_status = 1;
			error_msg("Failed to open outfile\n");
			return (-1);
		}
	}
	else
	{
		shell->outfile = STDOUT_FILENO;
	}
	return (0);
}

int	handle_io_redirections(t_shell *shell)
{
	t_arg	*redir_left;
	t_arg	*redir_right;

	redir_left = last_redir_left(shell->cmds->args);
	redir_right = last_redir_right(shell->cmds->args);
	if (handle_input_redirection(shell, redir_left) == -1)
		return (-1);
	if (handle_output_redirection(shell, redir_right) == -1)
	{
		if (redir_left != NULL && shell->infile != STDIN_FILENO)
			close(shell->infile);
		return (-1);
	}
	if (redir_left != NULL)
		shell->there_is_redir_in = 1;
	if (redir_right != NULL)
		shell->there_is_redir_out = 1;
	return (0);
}
