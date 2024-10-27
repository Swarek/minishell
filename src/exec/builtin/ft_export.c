/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 06:35:14 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/27 18:58:52 by mblanc           ###   ########.fr       */
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
			if (current->declared == 0 && (smallest == NULL || ft_strcmp(current->name, smallest->name) < 0))
				smallest = current;
			current = current->next;
		}
		if (smallest)
		{
			smallest->declared = 1;
			ft_printf("declare -x %s=\"%s\"\n", smallest->name, smallest->value);
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
		if (!(*envp)[i]) {
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

// A chaque passage dans le main il faudra mettre a jour char **envp a partir de t_env
int	ft_export(t_arg *args, char ***envp)
{
	t_env	*env;

	env = create_t_env(*envp);
	if (!env)
		return (1);
	if (count_arguments_for_t_arg(args) == 1)
		return (declare_and_sort(env), 0);
	args = args->next;
	edit_args_for_export(args);
	while (args)
	{
		if (is_valid_identifier(args->content) && ft_strchr(args->content, '='))
			env = add_node(env, create_node(args->content));
		else
			error_msg("export: not a valid identifier\n");
		args = args->next;
	}
	safe_free_all_strings(envp);
	if (t_env_to_array(env, envp) != 0)
		return (1);
	return (0);
}
