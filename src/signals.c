/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:24:52 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/30 00:59:12 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum);

void	setup_readline_signals(void)
{
	rl_catch_signals = 0;  // Empêche readline de gérer les signaux
	rl_catch_sigwinch = 1; // Gère les redimensionnements de fenêtre
	signal(SIGINT, sigint_handler);
}

void	sigint_handler(int signum)
{
	g_received_signal = signum;    // Enregistre le signal reçu
	write(STDOUT_FILENO, "\n", 1); // Affiche un retour à la ligne
	// Si readline est en cours d'exécution
	if (rl_line_buffer == NULL) // Si nous sommes dans une commande comme 'cat'
	{
		return ; // Ne rien faire, readline gère l'affichage
	}
	// Si la ligne est vide
	if (*rl_line_buffer == '\0')
	{
		rl_replace_line("", 0); // Remplace la ligne par une ligne vide
		rl_on_new_line();       // Se déplace à la nouvelle ligne
		rl_redisplay();         // Redessine le prompt
	}
	else // Si la ligne contient du texte
	{
		rl_replace_line("", 0); // Efface la ligne courante
		rl_on_new_line();       // Se déplace à la nouvelle ligne
		rl_redisplay();         // Redessine le prompt
	}
}

void	sigquit_handler(int signum)
{
	(void)signum;
	write(1, "Quit: 3\n", 8);
	exit(131);
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_child_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	handle_ctrl_d(char *line, t_shell *shell)
{
	int	exit_status;

	exit_status = shell->last_exit_status;
	if (!line)
	{
		if (shell)
			clean_all(shell);
		write(1, "exit\n", 5);
		exit(exit_status);
	}
}
