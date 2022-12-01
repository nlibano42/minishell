/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:33:47 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/01 11:24:03 by nlibano-         ###   ########.fr       */
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

void	wait_signal(t_shell **shell)
{
	while (1)
	{
		signal(SIGQUIT, sighandler);
		signal(SIGINT, sighandler);
		if ((*shell)->quit == 0)
			printf("Minishell> ");
		(*shell)->quit = 0;
		(*shell)->fork = 0;
		if (
	}
}

void	init_env(t_shell **shell, char **env)
{
	int		i;
	char	*split;
	t_shell	*new;

	i = -1;
	while (env[++i])
	{
		split = ft_split(env[i], '=');
		new = ft_lstnew(env[0], env[1]);
		ft_lstadd_back((*shell)->env, new);
	}
}

int	main(int argc, char **argv, char **env)
{
//	char			*input;
//	char			**tokens;
//	char			**envi;
//	struct t_stack	*stack;
	t_shell			*shell;

	(void)argc;
	(void)argv;
	init_env(&shell, env);
	shell->quit = 0;
	wait_signal(&shell);




/*
	while (1)
	{
		input = readline("MiniShell: ");
		add_history(input);
		if (ft_strlen(input) > 0)
		{
			tokens = ft_split(input, ' '); //aqui iria el lexer. crear los tokens o en pipe stack
			if (str_cmp(tokens[0], "exit") == 0 || str_cmp(tokens[0], "EXIT") == 0)
			{
				//deleteAllNodes(stack);
				clear(tokens);
				free(input);
				break ;
			}
//			stack = pipe_stack(input, envi); //crear la pila de ejecución
			stack = pipe_stack(input, env); //crear la pila de ejecución
			//redirect_pipes(stack); //cambiar el orden de la pila, redireccionar los pipes
			exec_stack(stack); //ejecutar la pila
		}
		deleteAllNodes(stack);
		free(input);
		clear(tokens);
	}
*/
	return (0);
}
