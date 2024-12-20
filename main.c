/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:09:52 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 13:46:29 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

volatile sig_atomic_t	g_received_signal = 0;

void	initialize_shell_values(t_shell *shell)
{
	shell->nth_here_doc = 0;
	shell->there_is_redir_in = 0;
	shell->there_is_redir_out = 0;
}

void	print_command(t_cmd *cmd)
{
	t_arg	*arg;

	ft_printf("Command: ");
	arg = cmd->args;
	while (arg)
	{
		ft_printf("[%s (%s)] ", arg->content, arg->type);
		arg = arg->next;
	}
	ft_printf("\n");
}

void	print_all_commands(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		ft_printf("Command %d:\n", i++);
		print_command(cmds);
		cmds = cmds->next;
	}
	ft_printf("\n");
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_cmd	*cmds;
	t_shell	*shell;
	int		color;
	int		ret;

	(void)ac;
	(void)av;
	line = NULL;
	cmds = NULL;
	color = 0;
	if (main1(envp, &shell) == -1)
		return (-1);
	while (1)
	{
		if (main6(&line, shell, color))
			break ;
		ret = main7(line, &cmds, shell, &color);
		g_received_signal = 0;
		ft_printf(" status: %d\n", shell->exit_status);
	}
	clean_all(shell);
	return (0);
}
