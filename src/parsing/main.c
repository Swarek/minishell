/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:21:11 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/18 20:38:35 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_d.h"
#include <stdio.h>

// Fonction pour afficher le contenu d'une commande parsée
void print_command(t_cmd *cmd) 
{
    printf("Command: ");
    t_arg *arg = cmd->args;
    while (arg) {
        printf("[%s (%s)] ", arg->content, arg->type);
        arg = arg->next;
    }
    printf("\n");
}

// Fonction pour afficher toutes les commandes parsées
void print_all_commands(t_cmd *cmds)
{
    int i = 0;
    while (cmds) {
        printf("Command %d:\n", i++);
        print_command(cmds);
        cmds = cmds->next;
    }
    printf("\n");
}

// int main() 
// {
//     char *test_cases[] = {
//         "echo 'hello world'",
//         "ls -l | grep .c",
//         "echo \"quoted string\" unquoted 'single quoted'",
//         "cat file.txt > output.txt",
//         "echo hello | wc -l > count.txt",
//         "echo $HOME | sed 's/home/house/'",
//         "ls -l ; echo done",
//         "echo 'single | quote' | grep quote",
//         "echo \"double | quote\" ; ls",
//         "cat<input.txt|sort|uniq>output.txt",
//         NULL
//     };

//     for (int i = 0; test_cases[i] != NULL; i++) {
//         printf("Test case %d: \"%s\"\n", i + 1, test_cases[i]);
//         t_cmd *cmds = NULL;
//         if (parse_it(test_cases[i], &cmds) == 0) 
//         {
//             print_all_commands(cmds);
//         } 
//         else {
//             printf("Error parsing command\n");
//         }
//         printf("----------------------------\n");
//         free_cmds(cmds);
//     }

//     return 0;
// }
