/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_d.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:22:47 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/21 02:36:56 by dmathis          ###   ########.fr       */
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
}					t_arg;

typedef struct s_cmd
{
	t_arg			*args;
	char			**only_cmd_and_args;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_exclude
{
	int	indices[1000];
	int	count;
	int	start;
	int	end;
}		t_exclude;

// 		Parsing

/*

Si c'est un pipe ça sera une commande de type = "pipe" et de content "|"
Si c'est un double pipe ça sera une commande de type = "double_pipe" et de content "||"
Si c'est une ">" ça sera une commande de type = "redir_right" et de content = ">"
Si c'est une ">>" ça sera une commande de type = "double_redir_right" et de content = ">>"
Si c'est une "<" ça sera une commande de type = "redir_left" et de content = "<"
Si c'est un ";" ça sera une commande de type = "semicolon" et de content = ";"

Pour les arguments les types sont :

"single_quoted" : Contenu entre single quotes
"double_quoted" : Contenu entre double quotes
"unfinished single_quoted" : Contenu placé après une seule single quote jamais fermée
"unfinished double_quoted" : Contenu placé après une seule double quote jamais fermée
"word" : le reste,
		séparés par des espaces,	c'est à dire une suite de caractères qui ne contient pas de tout ça ; > < ' " |

*/

// parsing_main.c

int					handle_special_char(char *str, int i, t_arg **current_args);
int					parse_one_command(char *str, int i, t_arg **current_args,
						t_cmd **cmds);
int					parse_it(char *str, t_cmd **cmds);

// parsing_save_it.c

int					save_it_redir_right(char *str, int i, t_arg **args);
int					save_it_redir_left(char *str, int i, t_arg **args);
int					save_it_word(char *str, int i, t_arg **args);
int					save_it_quoted(char *str, int i, t_arg **args);
int					save_it_unfinished(char *str, int i, t_arg **args);

// parsing_utils.c

t_arg				*create_arg(char *content, char *type);
void				add_arg(t_arg **head, t_arg *new_arg);
void				free_cmds(t_cmd *cmds);
void				add_command(t_cmd **cmds, t_arg **current_args);

void				print_args(t_arg *args);

void				expand_env_vars_in_cmds_tab(t_cmd **cmds);
void				expand_env_vars(t_arg *current_arg);
void				replace_env_var(t_arg *current_arg, int start, int end,
						const char *value);

char				*copy_string_exclude(const char *source, int start, int end, t_exclude *excl);
int					should_skip(int idx, t_exclude *excl);
int					calc_len(int start, int end, t_exclude *excl);

void				remove_backslashs_in_cmds_tab(t_cmd **cmds);
void				remove_backslashs_in_cmds_tab2(t_arg *current_arg);
void				remove_backslashs_in_cmds_tab3(char **str, int index);

void				remove_backslashs_in_words(t_cmd **cmds);
void				remove_backslashs_in_words2(t_arg *current_arg);
void				remove_backslashs_in_words3(char **str, int index);
#endif
