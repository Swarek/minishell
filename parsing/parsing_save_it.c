#include "damien/minishell_d.h"

int save_it_semicolon(t_arg **args)
{
    add_arg(args, create_arg(";", "separator"));
    return (1);
}

int save_it_redir_right(char *str, int i, t_arg **args)
{
    if (str[i + 1] == '>')
	{
        add_arg(args, create_arg(">>", "append"));
        return (i + 1);
    }
	else
	{
        add_arg(args, create_arg(">", "output"));
        return (i);
    }
}

int save_it_redir_left(t_arg **args)
{
    add_arg(args, create_arg("<", "input"));
    return (1);
}

int save_it_word(char *str, int i, t_arg **args)
{
    int j;
	char *content;
	t_arg *new_arg;

	j = i;
    while (str[j] && !ft_strchr(" \t;><'\"", str[j]))
		j++;
    content = strndup(str + i, j - i);
    new_arg = create_arg(content, "word");
    free(content);
    add_arg(args, new_arg);
    return (j - 1);
}

int	save_it_quoted(char *str, int i, t_arg **args)
{
	int		j;
	t_arg	*arg;
	char 	*to_save;

	j = i + 1;
	while (str[j] && str[j] != str[i])
	{
		j++;
		if (str[j] == '\0')
			return (-1);
	}
	to_save = ft_substr(str, i + 1, j - i - 1);
	arg = create_arg(to_save, "quoted");
	free(to_save);
	add_arg(args, arg);
	return (j);
}