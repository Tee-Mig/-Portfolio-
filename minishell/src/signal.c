/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:39:53 by naben-za          #+#    #+#             */
/*   Updated: 2022/06/03 12:44:00 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler(int sig, siginfo_t *info, void *unused)
{
	(void)unused;
	(void)info;
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	sig_init(void)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) == -1
		|| sigaddset(&sa.sa_mask, SIGINT) == -1)
		printf("Sigset error\n");
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_handler2(int sig, siginfo_t *info, void *unused)
{
	(void)unused;
	(void)info;
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		g_exit_status = 130;
	}
	if (sig == SIGQUIT)
	{
		write(1, "Quit (core dumped)", 18);
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		g_exit_status = 131;
	}
}

void	sig_init2(void)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) == -1
		|| sigaddset(&sa.sa_mask, SIGINT) == -1)
		printf("Sigset error\n");
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler2;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
