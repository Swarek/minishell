/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_d.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:22:47 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/17 22:36:33 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_D_H
# define MINISHELL_D_H

# include "../libft/libft.h"

// Structures

typedef struct s_arg
{
	char			*content;
	char			*type;
	struct s_arg	*next;
}				t_arg;

typedef struct s_cmd
{
	t_arg			*args;
	struct s_cmd	*next;
}	t_cmd;

// 		Parsing

// parsing_main.c

int 	handle_special_char(char *str, int i, t_arg **current_args);
int 	parse_one_command(char *str, int i, t_arg **current_args, t_cmd **cmds);
int 	parse_it(char *str, t_cmd **cmds);

// parsing_save_it.c

int 	save_it_semicolon(int i, t_arg **args);
int 	save_it_redir_right(char *str, int i, t_arg **args);
int 	save_it_redir_left(int i, t_arg **args);
int 	save_it_word(char *str, int i, t_arg **args);
int		save_it_quoted(char *str, int i, t_arg **args);

// parsing_utils.c

t_arg	*create_arg(char *content, char *type);
void	add_arg(t_arg **head, t_arg *new_arg);
void 	free_cmds(t_cmd *cmds);
void add_command(t_cmd **cmds, t_arg **current_args);


#endif
