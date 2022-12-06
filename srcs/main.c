/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:33:47 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/02 23:07:07 by nlibano-         ###   ########.fr       */
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

/*VARIABLES GLOBALES*/
//t_env	*envir;
int	g_num_quit;

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	**tokens;
	char	**envi;
	t_stack	*stack;
	

	(void)argc;
	(void)argv;
	stack = NULL;
	envi = env;
	sig_handler(1);
	//envir = set_envi(env);

	while (1)
	{
		input = readline("MiniShell $> ");
		add_history(input);
		if (!input)
			sig_handler(3);
		if (ft_strlen(input) > 0)
		{
			tokens = ft_split(input, ' ');
			if (str_cmp(tokens[0], "exit") == 0)
			{
				clear(tokens);
				free(input);
				break ;
			}
			stack = pipe_stack(input, envi);
			exec_stack(stack, input);
		}
		deleteAllNodes(stack);
		free(input);
		clear(tokens);
	}
	return (0);
}
