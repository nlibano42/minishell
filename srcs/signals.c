/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:56:10 by marvin            #+#    #+#             */
/*   Updated: 2022/12/07 22:32:27 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	sig_int(int code)
{
	(void)code;
	if (g_sig.pid == 0)
	{
		ft_putstr_out("\b\b  ", STDERR);
		ft_putstr_out("\n", STDERR);
		ft_putstr_out("\033[0;36m\033[1m🤬 minishell ▸ \033[0m", STDERR);
		g_shell.num_quit = 1;
	}
	else
	{
		ft_putstr_out("\n", STDERR);
		g_shell.num_quit = 130;
	}
	g_sig.sigint = 1;
}

void	sig_quit(int code)
{
	char	*nbr;

	nbr = ft_itoa(code);
	if (g_sig.pid != 0)
	{
		ft_putstr_out("Quit: ", STDERR);
		ft_putendl_out(nbr, STDERR); //end of line?
		g_shell.num_quit = 131;
		g_sig.sigquit = 1; //
	}
	else
		ft_putstr_out("\b\b  \b\b", STDERR);
	ft_memdel(nbr);
}

void	sig_init(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_sig.exit_status = 0;
}

*/


void	restore_prompt(int sig)
{
	g_shell.num_quit = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	ctrl_c(int sig)
{
	g_shell.num_quit = 130;
	write(1, "\b\b\b\n", 1);
	(void)sig;
}

void	back_slash(int sig)
{
	g_shell.num_quit = 131;
	printf("Quit (core dumped)\n");
	(void)sig;
}

void	sig_handler(int sig)
{
	printf("\b\b  \b\b");
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	if (sig == 3)
	{
		printf("\b\b\b\b\b\b\b\b\bexit\n");
		exit(0);
	}
}
void	signal_zeta()
{
    //printf("SEÃ‘AL ctrl D CAPTURADA\n");
    printf("MiniShell$> ");
}


void	new_sig_handler()
{
	printf("\b\b  \b\b");
	if(g_shell.pid == 0) //proceso padre
	{
		signal(SIGINT, restore_prompt); //SIGN INT ctrl C
		signal(SIGQUIT, SIG_IGN);      //SIGQUIT  Ctrl D
		signal(SIGTSTP, signal_zeta);    //SIGTSTP Ctrl Z
		//signal(SIGTERM, back_slash);
	}
	if(g_shell.pid > 0) //proceso hijo
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
		signal(SIGTSTP, ctrl_c);
		//signal(SIGTERM, back_slash);
	}
	/*
	if (sig == 3)
	{
		printf("\b\b\b\b\b\b\b\b\bexit\n");
		exit(0);
	}
	*/
}