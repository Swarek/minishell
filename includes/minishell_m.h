/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_m.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:22:47 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/18 12:18:34 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_M_H
# define MINISHELL_M_H

# include "minishell.h"

# define OUTPUT_REDIRECTION 0
# define APPEND_REDIRECTION 1
typedef struct s_shell
{
	int		last_exit_status;	// To save the exit status ($?) to exit
	int		cmd_count;		// Nbr of cmd in the list
	char	**envp;			// Environnemen
	t_cmd	*cmds;			// List of cmds
	t_arg	*args;			// Liste of args of a cmd (including the cmd)
}	t_shell;

// Build-in functions
int		ft_pwd(void);
int		ft_echo(t_arg *args);
int		ft_cd(t_arg *args);
int		ft_export(t_arg *args, char ***envp);
void	ft_env(char **envp);
void	ft_unset(t_arg *args, char ***env);
int		ft_exit(t_arg *args);

char	*reading_line(int color);
int		ft_echo(t_arg *args);
int		exec_it(t_shell *shell);
int		is_built_in(t_arg *args);
int		execute_built_in(t_arg *args);
int		do_the_execution(t_arg *args, char **envp);
int		execute(t_shell *shell);

#endif