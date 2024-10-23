/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:22:47 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/23 01:36:46 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>

# include "libft.h"
# include "minishell_d.h"
# include "pipex.h"
# include "minishell_m.h"

# define STDIN 0
# define STDOUT 1
// Utils
void	print_command(t_cmd *cmd);
void	print_all_commands(t_cmd *cmds);
void	my_print_command(t_arg *args);
void	free_cmd(t_cmd *cmd);
int		len_cmd(t_cmd *cmd);
int		count_cmd(t_cmd *cmd);
int		count_arguments(char **args);
int		count_arguments_for_t_arg(t_arg *args);
char	**convert_args_to_argv(t_arg *args);
void	print_args(t_arg *args);
void	find_and_add_type_cmd(t_arg *args, char **envp);


#endif
