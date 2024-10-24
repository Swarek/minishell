/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:09:52 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/24 05:15:06 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

int						g_last_exit_status = 0;
volatile sig_atomic_t	g_sigint_received = 0;

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
	// ft_print_array(cmds->cmd_arg_stdin);
	while (cmds)
	{
		printf("Command %d:\n", i++);
		print_command(cmds);
		cmds = cmds->next;
	}
	printf("\n");
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	free_shell(t_shell *shell)
{
	(void)shell;
}

void	update_exit_status(int status)
{
	if (WIFEXITED(status))
		g_last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_last_exit_status = 128 + WTERMSIG(status);
}

void	sigint_handler(int signum)
{
	(void)signum;
	g_sigint_received = 1;
	g_last_exit_status = 128 + 2;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// clean_all(shell);
	exit(130);
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
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

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->last_exit_status = 0;
	shell->envp = env_copy(envp);
	ft_printf("Test 0 shell->envp[0] = %s\n", shell->envp[0]);
	shell->cmds = NULL;
	// Initialize all other members
	shell->total_cmd_count = 0;
	shell->nbr_pipes = 0;
	shell->infile = 0;
	shell->outfile = 0;
	shell->input_pipe = 0;
	shell->there_is_redir_out = 0;
	shell->n_th_cmd = 0;
	shell->pipes = NULL;
	shell->child_pids = NULL;
	return (shell);
}

int main(int ac, char **av, char **envp)
{
    char    *line;
    t_cmd   *cmds;
    t_shell *shell;
    int     color;

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
        g_sigint_received = 0;
        line = reading_line(color);
        if (!line || g_sigint_received)
		{
			if (line)
				free(line);
            break;
		}
		if (g_sigint_received || parse_it(line, &cmds) != 0)
        {
            free(line);
            continue;
        }
        free(line);
        expand_env_vars_in_cmds_tab(&cmds);
        if (error_if_impair_single_quotes(&cmds) == -1)
        {
            ft_printf("Odd number of single quotes\n");
            clean_all(shell); // Assurer le nettoyage avant de quitter
            return (-1);
        }
        type_to_file_in_args1(&cmds);
        shell->cmds = cmds;
        if (exec_it(shell) == -1)
        {
            clean_all(shell); // Nettoyer en cas d'erreur d'exécution
            return (-1);
        }
        ft_printf("Exit status: %d\n", shell->exit_status);
        cmds = NULL;
        color++;    }
    clean_all(shell);
    return (0);
}


