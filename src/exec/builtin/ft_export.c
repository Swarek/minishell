/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 06:35:14 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/30 19:03:48 by dmathis          ###   ########.fr       */
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

int	declare_and_sort(t_env *env)
{
	t_env	*current;
	t_env	*smallest;
	int		len;

	current = env;
	while (current)
	{
		current->declared = 0;
		current = current->next;
	}
	len = len_env(env);
	while (len-- > 0)
	{
		current = env;
		smallest = NULL;
		while (current)
		{
			if (current->declared == 0 && (smallest == NULL
					|| ft_strcmp(current->name, smallest->name) < 0))
				smallest = current;
			current = current->next;
		}
		if (smallest)
		{
			smallest->declared = 1;
			ft_printf("declare -x %s=\"%s\"\n", smallest->name,
				smallest->value);
		}
	}
	return (0);
}

int	print_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		ft_printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (0);
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

int	t_env_to_array(t_env *env, char ***envp)
{
	t_env	*current;
	int		i;

	*envp = malloc(sizeof(char *) * (len_env(env) + 1));
	if (!*envp)
		return (1);
	i = 0;
	current = env;
	while (current)
	{
		(*envp)[i] = ft_strdup(current->line);
		if (!(*envp)[i])
		{
			while (i-- > 0)
				free((*envp)[i]);
			free(*envp);
			return (1);
		}
		i++;
		current = current->next;
	}
	(*envp)[i] = NULL;
	return (0);
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

void	free_env_list(t_env *env)
{
	t_env	*current;
	t_env	*next;

	current = env;
	while (current)
	{
		next = current->next;
		if (current->line)
			free(current->line);
		if (current->name)
			free(current->name);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

int	ft_export(t_arg *args, char ***envp)
{
	t_env	*env;
	t_env	*existing_node;
	char	*name;
	char	*value;
	int		ret;
	char	*new_line;
	t_env	*new_node;

	env = create_t_env(*envp);
	if (!env)
		return (1);
	if (count_arguments_for_t_arg(args) == 1)
	{
		ret = declare_and_sort(env);
		free_env_list(env);
		return (ret);
	}
	args = args->next;
	edit_args_for_export(args);
	while (args)
	{
		if (is_valid_identifier(args->content) && ft_strchr(args->content, '='))
		{
			name = extract_name(args->content);
			if (!name)
			{
				free_env_list(env);
				return (1);
			}
			value = extract_value(args->content);
			if (!value)
			{
				free(name);
				free_env_list(env);
				return (1);
			}
			existing_node = find_node_by_name(env, name);
			if (existing_node)
			{
				new_line = ft_strdup(args->content);
				if (!new_line)
				{
					free(name);
					free(value);
					free_env_list(env);
					return (1);
				}
				// Libérer l'ancienne mémoire
				free(existing_node->line);
				free(existing_node->value);
				// Mettre à jour avec les nouvelles valeurs
				existing_node->line = new_line;
				existing_node->value = value;
			}
			else
			{
				new_node = create_node(args->content);
				if (!new_node)
				{
					free(name);
					free(value);
					free_env_list(env);
					return (1);
				}
				env = add_node(env, new_node);
			}
			free(name);
			if (!existing_node)
				// On libère value seulement si on n'a pas trouvé de node existant
				free(value);
		}
		else
			error_msg("export: not a valid identifier\n");
		args = args->next;
	}
	safe_free_all_strings(envp);
	ret = t_env_to_array(env, envp);
	free_env_list(env);
	return (ret);
}
