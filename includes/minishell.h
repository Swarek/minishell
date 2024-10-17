/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:22:47 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/18 00:48:08 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../Libft/includes/libft.h"
# include "minishell_d.h"
# include "minishell_m.h"

void	print_command(t_cmd *cmd);
void	print_all_commands(t_cmd *cmds);
void	my_print_command(t_arg *args);
void	free_cmd(t_cmd *cmd);

#endif