/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:00:16 by nrey              #+#    #+#             */
/*   Updated: 2025/03/11 09:59:12 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	refresh_prompt(int sig)
{
	(void)sig;
	if (write(1, "\n", 1) == -1)
		perror("minishell (refresh_prompt) - write");
	rl_on_new_line();
	rl_replace_line("", 0);
	display_prompt();
	rl_redisplay();
}

/**
 * @brief Sets the current process to SIG_IGN the signal given as argument.
 * 
 * @param signal_id The signal to ignore.
 */
void	ignore_sig(int signal_id)
{
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = SIG_IGN;
	if (sigaction(signal_id, &sig, NULL) == -1)
		perror("minishell (ignores_sig) - sigaction");
}

void	signal_handler(void)
{
	struct sigaction	sig;

	ignore_sig(SIGQUIT);
	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = &refresh_prompt;
	if (sigaction(SIGINT, &sig, NULL) == -1)
		perror("minishell (signal_handler) - sigaction");
}
