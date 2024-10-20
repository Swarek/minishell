/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_save_it.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:53:29 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/20 22:11:58 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_it_word(char *str, int i, t_arg **args)
{
	int		j;
	char	*to_save;
	t_arg	*new_arg;

	j = i;
	while (str[j] && !ft_strchr(" ;><'\"", str[j]))
		j++;
	to_save = ft_substr(str, i, j - i);
	new_arg = create_arg(to_save, "word");
	free(to_save);
	add_arg(args, new_arg);
	return (j - 1);
}

int	save_it_quoted(char *str, int i, t_arg **args)
{
	int			j;
	t_arg		*arg;
	char		*to_save;
	t_exclude	exclude;

	j = i + 1;
	exclude.count = 0;
	while (str[j])
	{
		if (str[j] == str[i] && str[j - 1] != '\\')
			break ;
		if (str[j] == str[i] && str[j - 1] == '\\')
		{
			exclude.indices[exclude.count] = j - 1;
			exclude.count++;
		}
		j++;
	}
	to_save = copy_string_exclude(str, i + 1, j - 1, &exclude);
	if (str[i] == '"')
		arg = create_arg(to_save, "double_quoted");
	else
		arg = create_arg(to_save, "single_quoted");
	free(to_save);
	add_arg(args, arg);
	return (j);
}

int	save_it_unfinished(char *str, int i, t_arg **args)
{
	int		j;
	t_arg	*arg;
	char	*to_save;

	j = i + 1;
	while (str[j])
		j++;
	to_save = ft_substr(str, i + 1, j - i);
	if (str[i] == '"')
		arg = create_arg(to_save, "unfinished_double_quoted");
	else
		arg = create_arg(to_save, "unfinished_single_quoted");
	free(to_save);
	add_arg(args, arg);
	return (j);
}

int	save_it_redir_right(char *str, int i, t_arg **args)
{
	if (str[i] && str[i + 1] == '>')
	{
		add_arg(args, create_arg(">>", "double_redir_right"));
		return (i + 1);
	}
	else
	{
		add_arg(args, create_arg(">", "redir_right"));
		return (i);
	}
}

int	save_it_redir_left(char *str, int i, t_arg **args)
{
	if (str[i] && str[i + 1] == '<')
	{
		add_arg(args, create_arg("<<", "double_redir_left"));
		return (i + 1);
	}
	else
	{
		add_arg(args, create_arg("<", "redir_left"));
		return (i);
	}
}
