/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:42:26 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/14 10:42:26 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_prompt_c(int sig)
{
	g_shell.num_quit = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	restore_prompt_d(int sig)
{
	g_shell.num_quit = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	//rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	ctrl_c(int sig)
{
	g_shell.num_quit = 130;
	write(1, "\b\b\b\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	back_slash(int sig)
{
	g_shell.num_quit = 131;
	printf("Quit (core dumped)\n");
	exit(131);
	(void)sig;
}

void	sig_handler(int sig)
{
	printf("\b\b  \b\b");
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt_c);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	if (sig == 3)
	{
		rl_on_new_line();
		printf("\b\b\b\b\b\b\b\b\\b\b\b\bexit\n");
		exit(0);
	}
}
void	signal_zeta()
{
    printf("ctrl Ç CAPTURADA\n");
    //printf("MiniShell$> ");
	//rl_redisplay();
}

void	son_sig_handler()
{
	printf("\b\b  \b\b");
	signal(SIGINT, restore_prompt_c); //SIGN INT ctrl C
	//signal(SIGQUIT, SIG_IGN);      //SIGQUIT  Ctrl Ç señal 3
	signal(SIGQUIT, restore_prompt_d);
	signal(3, signal_zeta);    //SIGTSTP Ctrl Z Ctrl Ç

}

void	parent_sig_handler()
{
	printf("\b\b  \b\b");
	//signal(SIGINT, ctrl_c);
	signal(SIGINT, restore_prompt_c);
	signal(SIGQUIT, back_slash);
	signal(SIGSTOP, restore_prompt_d);
	//exit(0);
}
