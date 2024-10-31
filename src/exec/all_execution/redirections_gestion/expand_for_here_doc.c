/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_for_here_doc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 00:02:41 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 00:32:28 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_var_len(char *str, int *i, t_shell *shell)
{
	char	var[1024];
	char	*value;
	int		j;

	j = 0;
	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strlen(ft_itoa(shell->exit_status)));
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		var[j++] = str[(*i)++];
	var[j] = '\0';
	value = getenv(var);
	if (value)
		return (ft_strlen(value));
	return (0);
}

char	*get_var_value(char *str, int *i, t_shell *shell)
{
	char	var[1024];
	char	*value;
	int		j;

	j = 0;
	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->exit_status));
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		var[j++] = str[(*i)++];
	var[j] = '\0';
	value = getenv(var);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

size_t	get_final_len(char *str, t_shell *shell)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
			len += get_var_len(str, &i, shell);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*replace_in_charstar(char **str, t_shell *shell)
{
	char	*new;
	char	*var_value;
	int		i;
	int		j;

	new = malloc(sizeof(char) * (get_final_len(*str, shell) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && (*str)[i + 1])
		{
			var_value = get_var_value(*str, &i, shell);
			if (var_value == NULL)
				return (free(new), NULL);
			ft_strlcpy(new + j, var_value, ft_strlen(var_value) + 1);
			j += ft_strlen(var_value);
			free(var_value);
		}
		else
			new[j++] = (*str)[i++];
	}
	return (new[j] = '\0', free(*str), new);
}
