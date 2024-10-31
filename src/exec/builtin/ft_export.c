/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 06:35:14 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 02:16:56 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		smallest = find_smallest_undeclared(env);
		if (smallest)
		{
			smallest->declared = 1;
			ft_printf("declare -x %s=\"%s\"\n", smallest->name,
				smallest->value);
		}
	}
	return (0);
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
			{
				free((*envp)[i]);
				free(*envp);
				return (1);
			}
		}
		i++;
		current = current->next;
	}
	(*envp)[i] = NULL;
	return (0);
}

int	update_existing_node(t_env *existing_node, char *name, char *value)
{
	char	*temp_line;
	char	*temp;

	free(existing_node->value);
	existing_node->value = ft_strdup(value);
	free(existing_node->line);
	temp_line = ft_strjoin(name, "=");
	if (!temp_line)
		return (1);
	temp = ft_strjoin(temp_line, value);
	free(temp_line);
	if (!temp)
		return (1);
	existing_node->line = temp;
	return (0);
}

int	process_arg(t_arg *arg, t_env **env, t_shell *shell)
{
	t_env	*existing_node;
	char	*name;
	char	*value;

	if (is_valid_identifier(arg->content) && ft_strchr(arg->content, '='))
	{
		name = extract_name(arg->content);
		value = extract_value(arg->content);
		existing_node = find_no_na(*env, name);
		if (existing_node)
		{
			if (update_existing_node(existing_node, name, value) != 0)
				return (free(name), free(value), 1);
		}
		else
			*env = add_node(*env, create_node(arg->content));
		free(name);
		free(value);
	}
	else
		return (error_msg("export: not a valid identifier\n"),
			shell->exit_status = 1, 1);
	return (0);
}

int	ft_export(t_arg *args, char ***envp, t_shell *shell)
{
	t_env	*env;
	int		error_flag;

	env = create_t_env(*envp);
	if (!env)
	{
		shell->exit_status = 1;
		return (1);
	}
	if (count_arguments_for_t_arg(args) == 1)
		return (declare_and_sort(env), free_env(env),
			shell->exit_status = 0, 0);
	args = args->next;
	edit_args_for_export(args);
	error_flag = 0;
	while (args)
	{
		if (process_arg(args, &env, shell) != 0)
			error_flag = 1;
		args = args->next;
	}
	safe_free_all_strings(envp);
	if (t_env_to_array(env, envp) != 0)
		return (free_env(env), shell->exit_status = 1, 1);
	return (free_env(env), shell->exit_status = error_flag, shell->exit_status);
}
