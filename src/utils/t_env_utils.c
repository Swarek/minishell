/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:18:27 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 12:48:52 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_name(char *env_line)
{
	int		i;
	char	*name;
	int		j;

	i = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	name = (char *)malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	j = 0;
	while (j < i)
	{
		name[j] = env_line[j];
		j++;
	}
	name[j] = '\0';
	return (name);
}

char	*get_env_value(char *env_line)
{
	int		i;
	char	*value;

	i = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	if (env_line[i] == '\0')
		return (NULL);
	value = ft_strdup(env_line + i + 1);
	return (value);
}

t_env	*create_node(char *env_line)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->line = ft_strdup(env_line);
	if (!node->line)
		return (free(node), NULL);
	node->name = get_env_name(env_line);
	if (!node->name)
		return (free(node->line), free(node), NULL);
	node->value = get_env_value(env_line);
	if (!node->value && ft_strchr(env_line, '=') != NULL)
		return (free(node->name), free(node->line), free(node), NULL);
	node->next = NULL;
	return (node);
}

t_env	*add_node(t_env *head, t_env *new_node)
{
	t_env	*current;

	if (!head)
		return (new_node);
	current = head;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (head);
}

t_env	*create_t_env(char **envp)
{
	t_env	*head;
	t_env	*new_node;
	int		i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = create_node(envp[i]);
		if (!new_node)
			return (NULL);
		head = add_node(head, new_node);
		i++;
	}
	return (head);
}
