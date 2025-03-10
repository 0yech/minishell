/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:00:16 by nrey              #+#    #+#             */
/*   Updated: 2025/03/10 11:13:34 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	refresh_prompt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	display_prompt();
	rl_redisplay();
}

void	ignore_sig(void)
{
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig, NULL);
}

void	signal_handler(void)
{
	struct sigaction	sig;

	ignore_sig();
	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = &refresh_prompt;
	sigaction(SIGINT, &sig, NULL);
}
