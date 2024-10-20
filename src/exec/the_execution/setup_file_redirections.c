/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_file_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:35:42 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/20 11:49:10 by mblanc           ###   ########.fr       */
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

int	setup_file_redirections(t_shell *shell)
{
	t_arg	*redir_left;
	t_arg	*redir_right;

	shell->infile = STDIN_FILENO;
	shell->outfile = STDOUT_FILENO;
	redir_left = last_redir_left(shell->cmds->args);
	redir_right = last_redir_right(shell->cmds->args);
	print_all_commands(shell->cmds);
	// ft_printf("Voici redir_right : %s\n", redir_right->content);
	if (redir_left != NULL)
	{
		shell->infile = open(redir_left->next->content, O_RDONLY);
		if (shell->infile < 0)
			return (error_msg("Failed to open infile\n"));
	}
	if (redir_right != NULL)
	{
		if (ft_strcmp(redir_right->type, "redir_right") == 0)
			shell->outfile = open(redir_right->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (ft_strcmp(redir_right->type, "double_redir_right") == 0)
			shell->outfile = open(redir_right->next->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (shell->outfile < 0 && redir_left != NULL)
			return (close(shell->infile), error_msg("Failed to open outfile\n"));
		else if (shell->outfile < 0)
			return (error_msg("Failed to open outfile\n"));
	}
	return (0);
}

