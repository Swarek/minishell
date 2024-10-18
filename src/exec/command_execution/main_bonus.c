/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 02:51:42 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/18 12:25:14 by mblanc           ###   ########.fr       */
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

int	execution(t_shell *shell)
{
	t_pipex	pipex;

	if (len_cmd(shell->cmds) == 1)
	{
		if (is_built_in(shell->cmds->args))
			return (execute_built_in(shell->cmds->args));
		else
			return (execute(shell));
	}
	pipex.cmd_count = count_cmd(shell->cmds);
	if (all_init(&pipex, envp, argv) == -1)
		return (-1);
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