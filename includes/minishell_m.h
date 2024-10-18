/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_m.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:22:47 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/18 09:34:59 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_M_H
# define MINISHELL_M_H

# include "minishell.h"

typedef struct s_shell
{
	int	last_exit_status;	// Pour sauvegarder l'état de sortie ($?) pour exit
	char	**envp;			// Environnement
	t_cmd	*cmds;			// Liste des commandes
	t_arg	*args;			// Liste des arguments d'une commande
}	t_shell;

// Build-in functions
int		ft_pwd(void);
int		ft_echo(t_arg *args);
int		ft_cd(t_arg *args);
int		ft_export(t_arg *args, char ***envp);
void	ft_env(char **envp);
void	ft_unset(t_arg *args, char ***env);
int		ft_exit(t_arg *args);

char	*reading_line(void);
int		ft_echo(t_arg *args);
int		exec_it(t_cmd *cmds);

#endif