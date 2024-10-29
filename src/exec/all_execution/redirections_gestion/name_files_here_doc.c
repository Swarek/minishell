/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_files_here_doc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 01:46:38 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/29 03:26:26 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_a_here_doc_in_the_cmd(t_cmd *cmd)
{
	t_arg *tmp;

	if (!cmd)
		return (0);
	tmp = cmd->args;
	while (tmp)
	{
		if (tmp)
		{
			if (ft_strcmp(tmp->type, "double_redir_left") == 0)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int count_here_doc_separated_by_pipes(t_cmd *cmd)
{
	int 	count;
	t_arg	*tmp;

	count = 0;
	while (cmd)
	{
		tmp = cmd->args;
		while (tmp)
		{
			if (tmp)
			{
				if (ft_strcmp(tmp->type, "double_redir_left") == 0)
				{
					count++;
					break;
				}
			}
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
	return (count);
}

t_arg	*verif_here_doc_and_find_limiter(t_arg *args)
{
	t_arg	*tmp;
	t_arg	*limiter;

	tmp = args;
	limiter = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, "double_redir_left") == 0)
		{
			tmp = tmp->next;
			limiter = tmp;
		}
		tmp = tmp->next;
	}
	return (limiter);
}

int	handle_here_doc(t_shell *shell)
{
	int		i;
	int		total_here_doc;
	t_arg	*limiter;
	t_cmd	*cmds;

	i = 0;
	cmds = shell->cmds;
	total_here_doc = count_here_doc_separated_by_pipes(shell->cmds);
	while (i < total_here_doc)
	{
		limiter = verif_here_doc_and_find_limiter(cmds->args);
		if (!limiter)
			continue;
		if (here_doc_management(limiter->content, name_files_here_doc(i)) == -1)
			return (-1);
		if (cmds->next)
		{
			cmds = cmds->next;
		}
		while (is_a_here_doc_in_the_cmd(cmds) == 0)
			cmds = cmds->next;
		i++;
	}
	ft_printf("Fin de handle_here_doc\n");
	return (0);
}
// Will return the name of the temp file with the nbr
char	*name_files_here_doc(int nbr)
{
	char	*name;
	char	*nbr_str;

	nbr_str = ft_itoa(nbr);
	if (!nbr_str)
		return (NULL);
	name = ft_strjoin("temp", nbr_str);
	free(nbr_str);
	return (name);
}
