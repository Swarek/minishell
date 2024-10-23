/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:48:53 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/23 10:36:09 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_solo_in_pipe(t_shell *shell)
{
	// ft_printf("Entree execute_solo_in_pipe\nshell->infile : %d\nshell->outfile : %d\n", shell->infile, shell->outfile);
	// ft_printf("Avant strcmpr\n");
	while (shell->cmds->args != NULL && ft_strcmp(shell->cmds->args->type, "command") != 0)
		shell->cmds->args = shell->cmds->args->next;
	if (shell->cmds->args == NULL)
		exit(127);
	// ft_printf("Apres strcmpr\n");
	if (is_built_in(shell->cmds->cmd_arg_stdin))
	{
		shell->exit_status = execute_built_in(shell, shell->cmds->cmd_arg_stdin, &shell->envp);
		exit(0);
	}
	else
	{
		// ft_printf("\nPassage no built-in\n");
		if (do_the_execution(shell, shell->cmds, shell->envp) == -1)
			exit(1);
	}
	return (0);
}

// int	redir_to_pipe(t_shell *shell)
// {
// 	int	pipe_fd[2];
// 	int	status;

// 	if (pipe(pipe_fd) == -1)
// 		return (error_msg("Pipe failed\n"));
// 	shell->outfile = pipe_fd[1];
// 	status = execute_solo_in_pipe(shell);
// 	close(pipe_fd[1]);
// 	shell->infile = pipe_fd[0];
// 	return (status);
// }
