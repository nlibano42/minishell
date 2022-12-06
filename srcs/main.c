/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:33:47 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/06 10:09:12 by nlibano-         ###   ########.fr       */
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
	t_stack	*stack;

	(void)argc;
	(void)argv;
	stack = NULL;
	tokens = NULL;
	sig_handler(1);
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
			stack = pipe_stack(input, env);
			exec_stack(stack);
		}
		if (stack)
			deleteAllNodes(stack);
		free(input);
		if (tokens)
			clear(tokens);
	}
	return (0);
}
