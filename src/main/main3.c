/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:19:31 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/29 23:43:47 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main4(t_cmd **cmds, t_shell *shell)
{
	type_to_file_in_args1(cmds);
	replace_exit_status_in_cmds_tab(cmds, shell);
	shell->cmds = *cmds;
	if (exec_it(shell) == -1)
	{
		if (*cmds)
		{
			safe_free_cmds(*cmds);
			*cmds = NULL;
			shell->cmds = NULL;
		}
		clean_all(shell);
		return (-1);
	}
	return (0);
}

void	main5(t_cmd **cmds, t_shell *shell)
{
	if (*cmds)
	{
		safe_free_cmds(*cmds);
		*cmds = NULL;
		shell->cmds = NULL;
	}
}

int	main6(char **line, t_shell *shell, int color)
{
	initialize_shell_values(shell);
	if (g_received_signal)
		handle_received_signal_in_main(shell);
	*line = reading_line(color);
	handle_ctrl_d(*line, shell);
	if (!*line)
		return (1);
	return (0);
}

int	main7(char *line, t_cmd **cmds, t_shell *shell, int *color)
{
	int	ret;

	ret = main2(line, cmds, shell);
	if (ret != 0)
		return (0);
	ret = main3(cmds, shell);
	if (ret != 0)
		return (ret);
	ret = main4(cmds, shell);
	if (ret != 0)
		return (ret);
	(*color)++;
	main5(cmds, shell);
	return (0);
}
