/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_d.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:22:47 by dmathis           #+#    #+#             */
/*   Updated: 2024/09/14 15:51:44 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_D_H
# define MINISHELL_D_H

# include "../libft/libft.h"

// Structures

typedef struct s_arg
{
	char		*content;
	char		*type;
	struct s_arg *next;
}				t_arg;

typedef struct s_cmd
{
    t_arg *args;
    struct s_cmd *next;
} t_cmd;

// 		Parsing

/*

Si c'est un pipe ça sera une commande de type = "pipe" et de content "|"
Si c'est une ">" ça sera une commande de type = "redir_right" et de content =">"
Si c'est une ">>" ça sera une commande de type = "double_redir_right" et de content =">>"
Si c'est une "<" ça sera une commande de type = "redir_left" et de content ="<"

Si nous sommes dans un argument,
Les trois types sont : quoted - semicolon - word 
Quoted correspond aux caractères placés entre " " ou ' '
semicolon correspond à une ;
word correspond à tout le reste, c'est à dire une suite de caractères qui ne contient pas de tout ça ; > < ' " |

*/

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
void 	add_command(t_cmd **cmds, t_arg **current_args);


#endif
