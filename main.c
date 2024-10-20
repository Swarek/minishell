/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:34:05 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/20 11:41:49 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_d.h"
#include <stdio.h>

void	print_all_commands(t_cmd *cmds)
{
	int	cmd_count;

	cmd_count = 0;
	while (cmds)
	{
		printf("Command %d: ", ++cmd_count);
		print_args(cmds->args);
		printf("\n");
		if (cmds->next)
			printf("| ");
		cmds = cmds->next;
	}
	printf("\n");
}

int	main(void)
{
	t_cmd	*cmds;

	char *test_cases[] = {"echo hello world",
							"echo 'hello world'",
							"echo \"hello world\"",
							"ls -l | grep .c",
							"echo \"quoted string\" unquoted 'single quoted'",
							"cat file.txt > output.txt",
							"echo hello | wc -l > count.txt",
							"echo $HOME | sed 's/home/house/'",
							"ls -l ; echo done",
							"echo 'single | quote' | grep quote",
							"echo \"double | quote\" ; ls",
							"cat < input.txt | sort | uniq > output.txt",
							"echo hello > file1 >> file2 < file3",
							"export VAR=value ; echo $VAR",
							"cd /tmp && ls -la",
							"(echo nested command)",
							"echo \\\"escaped quote\\\"",
							"echo $? # print exit status",
							"echo $USER$HOME$PATH # multiple variables",
							"   echo    multiple     spaces    ",
							"ls -l *.c # wildcard",
							"echo {1..5} # brace expansion",
							"echo $((2 + 3)) # arithmetic expansion",
							"grep 'pat''tern' file.txt # adjacent quotes",
							"echo $'\\x48\\x65\\x6C\\x6C\\x6F' # ANSI-C quoting",
							"command1 2>&1 | command2 # file descriptor manipulation",
							"echo \"Nested ${HOME:+'$HOME'} quotes\"",
							"a=1; b=2; echo $((a+b)) # variable arithmetic",
							NULL};
	for (int i = 0; test_cases[i] != NULL; i++)
	{
		printf("Test case %d: \"%s\"\n", i + 1, test_cases[i]);
		cmds = NULL;
		if (parse_it(test_cases[i], &cmds) == 0)
		{
			print_all_commands(cmds);
		}
		else
		{
			printf("Error parsing command\n");
		}
		printf("----------------------------\n");
		free_cmds(cmds);
	}
	return (0);
}
