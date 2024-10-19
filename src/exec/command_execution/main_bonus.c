/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 02:51:42 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/19 14:57:13 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_and_cleanup(t_pipex *pipex)
{
	int	i;
	int	status;
	int	exit_code;

	exit_code = 0;
	i = 0;
	while (i < pipex->cmd_count)
	{
		if (waitpid(pipex->child_pids[i], &status, 0) == -1)
		{
			error_msg("Waitpid failed\n");
			exit_code = 1;
		}
		i++;
	}
	cleanup(pipex, NULL, pipex->nbr_pipes);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	exit(exit_code);
}

int	single_cmd(t_shell *shell, int stdin, int stdout)
{
	int	return_value;

	while (ft_strcmp(shell->cmds->args->type, "command") != 0)
		shell->cmds->args = shell->cmds->args->next;
	if (is_built_in(shell->cmds->args))
	{
		return_value = execute_built_in(shell->cmds->args, &shell->envp);
		if (dup2(stdin, STDIN_FILENO) == -1 || dup2(stdout, STDOUT_FILENO) == -1)
			return (ft_printf("Error dup2"), -1);
		return (return_value);
	}
	else
	{
		
		return_value = execute_solo(shell);
		if (dup2(stdin, STDIN_FILENO) == -1 || dup2(stdout, STDOUT_FILENO) == -1)
			return (ft_printf("Error dup2"), -1);
		return (return_value);
	}
}

// Il faut aussi une fonction speciale si len_cmd > 1 mais qu'il n'y a pas de pipe
// Par exemple si on fait ls -l > outfile
int	execution(t_shell *shell)
{
	t_pipex	pipex;
	int stdin;
	int stdout;

	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	pipex.cmd_count = count_real_cmd(shell);
	if (pipex.cmd_count == 0)
		return (ft_printf("Not a cmd\n"), 0);
	try_all_redirection(shell->cmds, &pipex);
	if (len_cmd(shell->cmds) == 1 || count_pipe(shell->cmds) == 0)
		return (single_cmd(shell, stdin, stdout));
	if (all_init(&pipex, shell->envp) == -1)
		return (-1);
	pipex.cmds = shell->cmds;
	fork_process(&pipex);
	wait_and_cleanup(&pipex);
	return (0);
}
// int	main(int argc, char **argv, char **envp)
// {
// 	t_pipex	pipex;

// 	if (argc < 5 || envp == NULL
// 		|| (ft_strcmp(argv[1], "here_doc") == 0 && argc < 6))
// 		return (error_msg("Not enought arguments or envp problem\n"), -1);
// 	if (ft_strcmp(argv[1], "here_doc") == 0 && argc > 5)
// 		if (handle_here_doc(&argc, argv) == -1)
// 			return (-1);
	// if (opening_files(&pipex, argv, argc) == -1)
// 		return (-1);
// 	if (all_init(&pipex, envp, argc, argv) == -1)
// 		return (-1);
// 	fork_process(&pipex);
// 	wait_and_cleanup(&pipex);
// 	return (0);
// }