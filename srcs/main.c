/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:33:47 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/02 02:09:05 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear(char **intro)
{
	int	i;

	i = 0;
	while (intro[i])
	{
		free(intro[i]);
		i++;
	}
	free (intro);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	**tokens;
	char	**envi;
	t_stack	*stack;
	struct sigaction	s_sigaction;

	(void)argc;
	(void)argv;
	envi = env;
	s_sigaction.sa_sigaction = sig_handler;
	s_sigaction.sa_flags = 0;
	sigaction(SIGINT, &s_sigaction, 0);
	sigaction(SIGTSTP, &s_sigaction, 0);
	while (1)
	{
		input = readline("MiniShell: ");
		add_history(input);
		if (ft_strlen(input) > 0)
		{
			tokens = ft_split(input, ' ');
			if (str_cmp(tokens[0], "exit") == 0 || str_cmp(tokens[0], "EXIT") == 0)
			{
				clear(tokens);
				free(input);
				break ;
			}
			stack = pipe_stack(input, envi);
			exec_stack(stack);
		}
		deleteAllNodes(stack);
		free(input);
		clear(tokens);
	}
	return (0);
}
