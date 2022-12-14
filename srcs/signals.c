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

void	ft_suppress_output(void)
{
	struct termios	config;

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
		g_shell.pid = 0;
	}
	else if (sig == SIGQUIT && g_shell.pid == 1)
	{
		printf("Quit: 3\n");
		printf("\n");
		rl_redisplay();
	}
}
