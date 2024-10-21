/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_escape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:50:50 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/20 21:04:31 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calc_len(int start, int end, t_exclude *excl)
{
	int	len;
	int	i;

	len = end - start + 1;
	i = 0;
	while (i < excl->count)
	{
		if (excl->indices[i] >= start && excl->indices[i] <= end)
		{
			len--;
		}
		i++;
	}
	return (len);
}

int	should_skip(int idx, t_exclude *excl)
{
	int	i;

	i = 0;
	while (i < excl->count)
	{
		if (idx == excl->indices[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*copy_string_exclude(const char *source, int start, int end,
		t_exclude *excl)
{
	int		length;
	char	*result;
	int		i;
	int		j;

	if (start == end)
		return (strdup(""));
	length = calc_len(start, end, excl);
	result = (char *)malloc((length + 1) * sizeof(char));
	if (!result)
	{
		return (NULL);
	}
	i = start;
	j = 0;
	while (i <= end)
	{
		if (!should_skip(i, excl))
		{
			result[j++] = source[i];
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}
