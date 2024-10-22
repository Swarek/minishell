/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 06:35:14 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/22 00:48:44 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	find_var_index(char *var, char **envp)
// {
// 	int		i;
// 	int		len;

// 	i = 0;
// 	len = ft_strlen(var);
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

// static void	update_or_add_var(char *var, char ***envp, char *arg)
// {
// 	int		index;
// 	int		i;

// 	index = find_var_index(var, *envp);
// 	if (index >= 0)
// 	{
// 		free((*envp)[index]);
// 		(*envp)[index] = arg;
// 	}
// 	else
// 	{
// 		i = 0;
// 		while ((*envp)[i])
// 			i++;
// 		(*envp)[i] = arg;
// 		(*envp)[i + 1] = NULL;
// 	}
// }

// static char	*parse_var_value(char *arg, char **value)
// {
// 	char	*equal_sign;

// 	equal_sign = strchr(arg, '=');
// 	if (!equal_sign)
// 		return (NULL);
// 	*equal_sign = '\0';
// 	*value = equal_sign + 1;
// 	return (arg);
// }

// int	ft_export(t_arg *args, char ***envp)
// {
// 	char	*value;
// 	char	*var_name;
// 	int		i;

// 	if (!args->next)
// 		return (ft_env(*envp), 0);
// 	i = 1;
// 	args = args->next;
// 	var_name = parse_var_value(args->content, &value);
// 	if (var_name)
// 		update_or_add_var(var_name, envp, args->content);
// 	else
// 		return (ft_printf("export: '%s': not a valid identifier\n", args[i]), -1);
// 	args = args->next;
// 	return (0);
// }

int	ft_export(t_arg *args, char ***envp)
{
	ft_printf("ft_export, args->content : %s\n", args->content);
	ft_printf("envp[0] : %s\n", (*envp)[0]);
	return (0);
}
