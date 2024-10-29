/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:09:52 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/29 05:42:01 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

volatile sig_atomic_t	g_received_signal = 0;

void	print_command(t_cmd *cmd)
{
	t_arg	*arg;

	printf("Command: ");
	arg = cmd->args;
	while (arg)
	{
		printf("[%s (%s)] ", arg->content, arg->type);
		arg = arg->next;
	}
	printf("\n");
}

void	print_all_commands(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		printf("Command %d:\n", i++);
		print_command(cmds);
		cmds = cmds->next;
	}
	printf("\n");
}

void	sigint_handler(int signum)
{
	g_received_signal = signum;
	write(1, "\n", 1);
	// Si on était en train de lire une ligne (pas dans une commande)
	if (rl_line_buffer && !*rl_line_buffer)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		rl_replace_line("", 1);
		rl_on_new_line();
	}
}

void	sigquit_handler(int signum)
{
	(void)signum;
	write(1, "Quit: 3\n", 8); // Mimics default behavior of quit signal
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
	int exit_status;

	exit_status = shell->last_exit_status;
	if (!line) // rl_gets returns NULL if ctrl+d is received
	{
		if (shell)
			clean_all(shell); // Free memory properly
		write(1, "exit\n", 5);
		exit(exit_status); // Exit with the last status
	}
}

char	**env_copy(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			while (i >= 0)
				free(new_env[i--]);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

t_shell	*init_struct_shell(char **envp)
{
	t_shell	*shell;

	(void) envp;
	shell = ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		return (NULL);
	shell->last_exit_status = 0;
	shell->envp = env_copy(envp);
	shell->cmds = NULL;
	shell->total_cmd_count = 0;
	shell->nbr_pipes = 0;
	shell->infile = 0;
	shell->outfile = 0;
	shell->input_pipe = 0;
	shell->there_is_redir_out = 0;
	shell->n_th_cmd = 0;
	shell->pipes = NULL;
	shell->child_pids = NULL;
	shell->in_child_process = 0;
	return (shell);
}

void	str_arg_in_null(t_cmd *cmd)
{
	while (cmd)
	{
		cmd->cmd_arg_stdin = NULL;
		cmd = cmd->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_cmd	*cmds;
	t_shell	*shell;
	int		color;

	(void)ac;
	(void)av;
	line = NULL;
	cmds = NULL;
	shell = init_struct_shell(envp);
	if (!shell)
		return (-1);
	cmds = NULL;
	color = 0;
	setup_signals();
	while (1)
	{
		shell->nth_here_doc = 0;
		shell->there_is_redir_in = 0;
		shell->there_is_redir_out = 0;
		if (g_received_signal)
		{
			if (g_received_signal == SIGINT)
				shell->last_exit_status = 130; // 128 + 2 (SIGINT)
			else if (g_received_signal == SIGQUIT)
				shell->last_exit_status = 131; // 128 + 3 (SIGQUIT)
			g_received_signal = 0;
			// Réinitialiser pour le prochain signal
		}
		line = reading_line(color);
		handle_ctrl_d(line, shell);
		if (!line)
			break ;
		if (parse_it(line, &cmds) != 0)
		{
			free(line);
			continue ;
		}
		free(line);
		str_arg_in_null(cmds);
		expand_env_vars_in_cmds_tab(&cmds, *shell);
		if (error_if_subsequent_commands(&cmds) == -1
			|| error_if_unclosed_parentheses(&cmds) == -1
			|| error_in_filename(&cmds))
		{
			ft_printf("Syntax error\n");
			if (cmds)
			{
				safe_free_cmds(cmds);
				cmds = NULL;
				shell->cmds = NULL;
			}
			clean_all(shell);
			return (-1);
		}
		type_to_file_in_args1(&cmds);
		replace_exit_status_in_cmds_tab(&cmds, shell);
		shell->cmds = cmds;
		// print_all_commands(cmds);
		if (exec_it(shell) == -1)
		{
			if (cmds)
			{
				safe_free_cmds(cmds);
				cmds = NULL;
				shell->cmds = NULL;
			}
			clean_all(shell);
			return (-1);
		}
		color++;
		if (cmds)
		{
			safe_free_cmds(cmds);
			cmds = NULL;
			shell->cmds = NULL;
		}
	}
	clean_all(shell);
	return (0);
}
