/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_de_damien.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 06:04:18 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/29 06:34:07 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_in_here_doc16(const char *str, size_t start)
{
    size_t len;

    len = 0;
    while (str[start + len] && ((str[start + len] >= 'A' && str[start + len] <= 'Z') || 
           (str[start + len] >= 'a' && str[start + len] <= 'z') || 
           (str[start + len] >= '0' && str[start + len] <= '9') || 
           str[start + len] == '_'))
        len++;
    return (len);
}

char *expand_in_here_doc15(const char *str, size_t start, size_t var_len)
{
    char *var_name;
    char *env_value;

    var_name = malloc(var_len + 1);
    if (!var_name)
        return (NULL);
    ft_memcpy(var_name, str + start, var_len);
    var_name[var_len] = '\0';
    env_value = getenv(var_name);
    free(var_name);
    return (env_value);
}

size_t expand_in_here_doc14(int n)
{
    size_t len;

    len = 1;
    if (n < 0)
        len++;
    while (n / 10)
    {
        len++;
        n /= 10;
    }
    return (len);
}

void expand_in_here_doc13(char *str, int n, size_t len)
{
    int digit;

    str[len] = '\0';
    if (n == 0)
    {
        str[0] = '0';
        return;
    }
    if (n < 0)
        str[0] = '-';
    while (n)
    {
        len--;
        digit = n % 10;
        if (digit < 0)
            digit = -digit;
        str[len] = digit + '0';
        n /= 10;
    }
}

char *expand_in_here_doc12(int n)
{
    char *result;
    size_t len;

    len = expand_in_here_doc14(n);
    result = malloc(len + 1);
    if (!result)
        return (NULL);
    expand_in_here_doc13(result, n, len);
    return (result);
}

size_t expand_in_here_doc11(int last_exit_status)
{
    char *exit_str;
    size_t len;

    exit_str = expand_in_here_doc12(last_exit_status);
    if (!exit_str)
        return (0);
    len = ft_strlen(exit_str);
    free(exit_str);
    return (len);
}

size_t expand_in_here_doc10(const char *str, size_t start, size_t var_len)
{
    char *env_value;
    size_t len;

    env_value = expand_in_here_doc15(str, start, var_len);
    if (!env_value)
        return (0);
    len = ft_strlen(env_value);
    return (len);
}

size_t expand_in_here_doc9(const char *str, size_t *i, int last_exit_status)
{
    size_t new_len;
    size_t var_len;

    new_len = 0;
    if (str[*i + 1] == '?') {
        new_len = expand_in_here_doc11(last_exit_status);
        *i += 2;
    } else {
        var_len = expand_in_here_doc16(str, *i + 1);
        if (var_len) {
            new_len = expand_in_here_doc10(str, *i + 1, var_len);
            *i += var_len + 1;
        } else {
            new_len = 1;
            (*i)++;
        }
    }
    return (new_len);
}

size_t expand_in_here_doc8(const char *str, int last_exit_status)
{
    size_t i;
    size_t new_len;
    size_t len;

    i = 0;
    new_len = 0;
    len = ft_strlen(str);
    while (i < len) {
        if (str[i] == '$' && str[i + 1])
            new_len += expand_in_here_doc9(str, &i, last_exit_status);
        else {
            new_len++;
            i++;
        }
    }
    return (new_len);
}

void expand_in_here_doc7(char *new_str, size_t *new_i, size_t *i, int last_exit_status)
{
    char *exit_str;
    size_t len;

    exit_str = expand_in_here_doc12(last_exit_status);
    if (!exit_str)
        return;
    len = ft_strlen(exit_str);
    ft_strlcpy(new_str + *new_i, exit_str, len + 1);
    *new_i += len;
    *i += 2;
    free(exit_str);
}

int expand_in_here_doc6(char *new_str, size_t *new_i, size_t *i, const char *str)
{
    size_t var_len;
    char *env_value;
    size_t len;

    var_len = expand_in_here_doc16(str, *i + 1);
    if (!var_len)
        return (0);
    env_value = expand_in_here_doc15(str, *i + 1, var_len);
    if (env_value) {
        len = ft_strlen(env_value);
        ft_strlcpy(new_str + *new_i, env_value, len + 1);
        *new_i += len;
    }
    *i += var_len + 1;
    return (1);
}

char *expand_in_here_doc5(const char *str, int last_exit_status)
{
    size_t len;
    size_t new_len;
    char *new_str;
    size_t i;
    size_t new_i;

    if (!str)
        return (NULL);
    len = ft_strlen(str);
    new_len = expand_in_here_doc8(str, last_exit_status);
    new_str = malloc(new_len + 1);
    if (!new_str)
        return (NULL);
    i = 0;
    new_i = 0;
    while (i < len) {
        if (str[i] == '$' && str[i + 1]) {
            if (str[i + 1] == '?')
                expand_in_here_doc7(new_str, &new_i, &i, last_exit_status);
            else if (!expand_in_here_doc6(new_str, &new_i, &i, str))
                new_str[new_i++] = str[i++];
        } else
            new_str[new_i++] = str[i++];
    }
    new_str[new_i] = '\0';
    return (new_str);
}

void expand_in_here_doc4(char **array)
{
    size_t i;

    i = 0;
    while (array[i])
        free(array[i++]);
    free(array);
}

size_t expand_in_here_doc2(char **array)
{
    size_t size;

    size = 0;
    while (array[size])
        size++;
    return (size);
}

char **expand_in_here_doc(char **array, int last_exit_status)
{
    size_t size;
    char **new_array;
    size_t i;

    if (!array)
        return (NULL);
    size = expand_in_here_doc2(array);
    new_array = malloc(sizeof(char *) * (size + 1));
    if (!new_array)
        return (NULL);
    i = 0;
    while (array[i]) {
        new_array[i] = expand_in_here_doc5(array[i], last_exit_status);
        if (!new_array[i])
		{
            while (i > 0)
                free(new_array[--i]);
            free(new_array);
            return (NULL);
        }
        i++;
    }
    new_array[i] = NULL;
    expand_in_here_doc4(array);
    return (new_array);
}

static char	**append_line(char **array, char *line, int size)
{
	char	**new_array;
	int		i;

	new_array = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_array[i] = array[i];
		i++;
	}
	new_array[i] = line;
	new_array[i + 1] = NULL;
	free(array);
	return (new_array);
}

static char	**read_file_to_array(int fd)
{
	char	**array;
	char	*line;
	int		size;

	array = NULL;
	size = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		array = append_line(array, line, size);
		if (!array)
		{
			free(line);
			return (NULL);
		}
		size++;
	}
	return (array);
}

static void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static int	write_array_to_file(int fd, char **array)
{
	int		i;
	ssize_t	wr;

	i = 0;
	while (array[i])
	{
		wr = write(fd, array[i], ft_strlen(array[i]));
		if (wr == -1)
			return (-1);
		wr = write(fd, "\n", 1);
		if (wr == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	expand_in_here_doc25(char *file_name, int last_exit_status)
{
	int		fd;
	char	**array;
	char	**new_array;
	int		ret;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	array = read_file_to_array(fd);
	close(fd);
	if (!array)
		return (-1);
	new_array = expand_in_here_doc(array, last_exit_status);
	if (!new_array)
	{
		free_array(array);
		return (-1);
	}
	free_array(array);
	fd = open(file_name, O_WRONLY | O_TRUNC);
	if (fd == -1)
	{
		free_array(new_array);
		return (-1);
	}
	ret = write_array_to_file(fd, new_array);
	close(fd);
	free_array(new_array);
	return (ret);
}
