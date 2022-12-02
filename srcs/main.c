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

void	sighandler(int sig)
{
	if (sig == SIGQUIT)
		g_shell.quit = 4;
	if (sig == SIGINT)
		g_shell.quit = 1;
}

/*void	wait_signal(t_shell **shell)
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
}*/

/*void	init_env(t_shell **shell, char **env)
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
*/
int	main(int argc, char **argv, char **env)
{
	char			*input;
	char			**tokens;
	t_stack	*stack;
//	t_shell			*shell;

	(void)argc;
	(void)argv;
	//init_env(&shell, env);
//	stack->pipe.quit = 0;
	//wait_signal(&shell);
	signal(SIGQUIT, sighandler);
	signal(SIGINT, sighandler);
	while (1)
	{
		input = readline("MiniShell $> ");
		add_history(input);
		if (ft_strlen(input) > 0)
		{
			tokens = ft_split(input, ' '); //aqui iria el lexer. crear los tokens o en pipe stack
			if (str_cmp(tokens[0], "exit") == 0 || str_cmp(tokens[0], "EXIT") == 0)
			{
				deleteAllNodes(stack);
				free(tokens);
				free(input);
				break ;
			}
			stack = pipe_stack(input, env); //crear la pila de ejecución
			//redirect_pipes(stack); //cambiar el orden de la pila, redireccionar los pipes
			exec_stack(stack); //ejecutar la pila
		}
		deleteAllNodes(stack);
		free(input);
		free(tokens);
	}

	return (0);
}
