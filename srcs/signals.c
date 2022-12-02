/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:56:10 by marvin            #+#    #+#             */
/*   Updated: 2022/12/01 12:56:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
    (void)info;
	if (signum == SIGINT) //ctrl+C
    {
		printf("SEÑAL ctrl C Exit status 130\n");
        printf("MiniShell: "); //si estamos en un cat sobra
    }
	if (signum == SIGTSTP) /*ctrl+\ */
    {
        printf("SEÑAL ctrl D CAPTURADA\n");
        printf("MiniShell: ");
    }
	//kill(info->si_pid, SIGUSR1); ejemplo. con kill y pid del hijo matariamos el proceso
}
