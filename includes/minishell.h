/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:22:47 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/20 11:33:14 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "minishell_d.h"
# include "pipex.h"
# include "minishell_m.h"

// Utils
void	print_command(t_cmd *cmd);
void	print_all_commands(t_cmd *cmds);
void	my_print_command(t_arg *args);
void	free_cmd(t_cmd *cmd);
int		len_cmd(t_cmd *cmd);
int		count_cmd(t_cmd *cmd);
int		count_arguments(t_arg *args);
char	**convert_args_to_argv(t_arg *args);
void	print_args(t_arg *args);
void	find_and_add_type_cmd(t_arg *args, char **envp);

int	looking_for_here_doc(t_cmd *cmds, t_pipex *pipex);
int handle_output_redirection(t_cmd *cmds, t_pipex *pipex);
int handle_append_redirection(t_cmd *cmds, t_pipex *pipex);
int	handle_input_redirection(t_cmd *cmds, t_pipex *pipex);

#endif