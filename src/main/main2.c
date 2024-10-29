/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:15:49 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/29 23:01:10 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_received_signal_in_main(t_shell *shell)
{
	if (g_received_signal == SIGINT)
		shell->last_exit_status = 130;
	else if (g_received_signal == SIGQUIT)
		shell->last_exit_status = 131;
	g_received_signal = 0;
}

int	main1(char **envp, t_shell **shell)
{
	*shell = init_struct_shell(envp);
	if (!*shell)
		return (-1);
	setup_signals();
	return (0);
}

int	main2(char *line, t_cmd **cmds, t_shell *shell)
{
	if (parse_it(line, cmds) != 0)
	{
		free(line);
		return (1);
	}
	free(line);
	str_arg_in_null(*cmds);
	expand_env_vars_in_cmds_tab(cmds, *shell);
	return (0);
}

int	main3(t_cmd **cmds, t_shell *shell)
{
	if (error_if_subsequent_commands(cmds) == -1
		|| error_if_unclosed_parentheses(cmds) == -1 || error_in_filename(cmds))
	{
		ft_printf("Syntax error\n");
		if (*cmds)
		{
			safe_free_cmds(*cmds);
			*cmds = NULL;
			shell->cmds = NULL;
		}
		// clean_all(shell);
		// return (2);
	}
	return (0);
}
