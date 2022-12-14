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

/*
void	restore_prompt_c(int sig)
{
	g_shell.num_quit = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	restore_prompt_c_son(int sig)
{
	g_shell.num_quit = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	(void)sig;
}

void	restore_prompt_d(int sig)
{
	g_shell.num_quit = 130;
	rl_replace_line("exit", 0);
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
	printf("\b\bQuit (exit minishell)\n");
	exit(131);
	(void)sig;
}


void	signal_zeta(int sig)
{
	printf("ctrl Ç CAPTURADA\n");
    //printf("MiniShell$> ");
	//rl_redisplay();
	(void) sig;
}

void	son_sig_handler(int sig)
{
	printf("sonPID %d\n", g_shell.pid);
	signal(SIGINT, restore_prompt_c_son);
	signal(SIGQUIT, restore_prompt_d);
	g_shell.pid = 0;
}

void	parent_sig_handler(int sig)
{
	signal(SIGINT, restore_prompt_c);
	signal(SIGQUIT, back_slash);
}

void	both_sig_handler(int sig)
{
	if (g_shell.pid > 0)
		parent_sig_handler(sig);
	if (g_shell.pid == 0)
		son_sig_handler(sig);
}
*/

void    ft_suppress_output(void)
{
    struct termios    config;

    if (tcgetattr(0, &config))
        perror("minishell: tcsetattr");
    config.c_lflag &= ~ECHOCTL;
    if (tcsetattr(0, 0, &config))
        perror("minishell: tcsetattr");
}

void	signal_handler(int sig)
{
	ft_suppress_output();
	if (sig == SIGINT && g_shell.pid == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGINT && g_shell.pid == 1)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		//g_data.sub_pid = 0;
		g_shell.pid = 0;
	}
	//else if (sig == SIGQUIT && g_data.sub_pid);
	else if (sig == SIGQUIT && g_shell.pid == 1)
	{
		printf("Quit: 3\n");
		printf("\n");
		//rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
}
