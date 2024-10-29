/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:24:52 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/30 00:25:23 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigint_handler(int signum)
{
    g_received_signal = signum;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 1);
    rl_redisplay();
}

void	sigquit_handler(int signum)
{
	(void)signum;
	write(1, "Quit: 3\n", 8);
	exit(131);
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_child_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	handle_ctrl_d(char *line, t_shell *shell)
{
	int	exit_status;

	exit_status = shell->last_exit_status;
	if (!line)
	{
		if (shell)
			clean_all(shell);
		write(1, "exit\n", 5);
		exit(exit_status);
	}
}
