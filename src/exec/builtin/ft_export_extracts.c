/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_extracts.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:37:13 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/30 17:37:38 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_name(const char *content)
{
	int		len;
	char	*name;
	int		i;

	len = 0;
	while (content[len] && content[len] != '=')
		len++;
	name = malloc(sizeof(char) * (len + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (i < len)
	{
		name[i] = content[i];
		i++;
	}
	name[len] = '\0';
	return (name);
}

char	*extract_value(const char *content)
{
	char	*equal_sign;
	char	*value;

	equal_sign = ft_strchr(content, '=');
	if (!equal_sign)
		return (NULL);
	value = ft_strdup(equal_sign + 1);
	return (value);
}
