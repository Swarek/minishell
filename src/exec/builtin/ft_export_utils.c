/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:28:39 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/30 17:41:23 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_env(t_env *env)
{
	t_env	*current;
	int		len;

	len = 0;
	current = env;
	while (current)
	{
		len++;
		current = current->next;
	}
	return (len);
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->name);
		free(temp->value);
		free(temp->line);
		free(temp);
	}
}

t_env	*find_node_by_name(t_env *env, const char *name)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_env	*find_smallest_undeclared(t_env *env)
{
	t_env	*current;
	t_env	*smallest;

	current = env;
	smallest = NULL;
	while (current)
	{
		if (current->declared == 0 && (smallest == NULL
				|| ft_strcmp(current->name, smallest->name) < 0))
			smallest = current;
		current = current->next;
	}
	return (smallest);
}
