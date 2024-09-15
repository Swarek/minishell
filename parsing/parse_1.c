/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:34:51 by dmathis           #+#    #+#             */
/*   Updated: 2024/09/14 15:51:56 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_d.h"

int	save_it_quoted(char *str, int i)
{
	int		j;
	t_arg	arg;

	j = i + 1;
	while (str[j] && str[j] != str[i])
	{
		j++;
		if (str[j] == '\0')
			return ;
	}
	arg.arg = ft_substr(str, i + 1, j - i - 1);
	arg.type = ft_strdup("quoted");
}

int	parse_it(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str [i] == '\t')
			i++;
		else if (str[i] == '\'' || str[i] == '\"')
		{
			if (save_it_quoted(str, i) == -1)
				return (-1);
		}
		else if (str[i] == '|')
			save_it_pipe(str, i);
		else if (str[i] == ';')
			save_it_semicolon(str, i);
		else if (str[i] == '>')
			save_it_redir_right(str, i);
		else if (str[i] == '<')
			save_it_redir_left(str, i);
		else
			save_it_word(str, i);
		i++;
	}
}
