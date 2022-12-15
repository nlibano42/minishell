/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:33:47 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/14 10:16:11 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_exit_status(void)
{
	int	temp_status;

	temp_status = g_shell.num_quit;
	if (WIFEXITED(temp_status))
		g_shell.num_quit = WEXITSTATUS(temp_status);
	if (WIFSIGNALED(temp_status))
	{
		if (WTERMSIG(temp_status) == 2)
			g_shell.num_quit = 130;
		else if ((WTERMSIG(temp_status) == 3))
			g_shell.num_quit = 131;
	}
}

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
	g_shell.pid = 0;
	g_shell.env = NULL;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	set_envi(&(g_shell.env), env);
	while (1)
	{
		input = readline("MiniShell $> ");
		if (!input)
			exit(0);
		if (!input[0])
			continue ;
		g_shell.input = input;
		add_history(input);
		if (input == NULL)
		{
			printf("exit\n");
			exit(g_shell.num_quit);
		}
		if (ft_strlen(input) > 0)
		{
			stack = pipe_stack(input);
			if (!stack)
				continue ;
			if (exec_stack(stack, input) == 1)
				continue ;
		}
		free_all_params(&stack, &input, &tokens);
	}
	ft_lstclear(&g_shell.env);
	return (g_shell.num_quit);
}

/*
void	executor(char **input, char ***tokens, t_stack **stack)
{
	if (!input)
		exit(0);
	if (ft_strlen(input) > 0)
	{
		tokens = ft_split(input, ' ');
		if (str_cmp(tokens[0], "exit") == 0)
			exit(g_shell.num_quit);
		stack = pipe_stack(input);
		exec_stack(stack, input);
	}
	free_all_params(&stack, &input, &tokens);
}
*/
void	free_all_params(t_stack **stack, char **input, char ***tokens)
{
	if (*stack)
	{
		delete_all_nodes(*stack);
		stack = NULL;
	}
	if (*input)
	{
		free(*input);
		input = NULL;
	}
	if (*tokens)
	{
		clear(*tokens);
		tokens = NULL;
	}
}
