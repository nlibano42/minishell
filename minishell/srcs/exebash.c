/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exebash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:33:24 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/15 00:09:34 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_in_child(char *input, t_stack *stack)
{
	t_stack	*node;

	node = stack;
	if (node->next != NULL)
		dup2(node->next->pipe.p[1], 1);
	if (node->prev != NULL)
		dup2(node->pipe.p[0], 0);
	close(node->pipe.p[0]);
	close(node->pipe.p[1]);
	if (is_built(node->pipe.cmd) == 0)
		exit(0);
	if (is_built(node->pipe.cmd) == 1)
	{
		if (launch(input, node) == -1)
		{
			fd_putstr_out("-Minishell: ", node);
			fd_putstr_out(node->pipe.cmd, node);
			fd_putstr_out(": command not found\n", node);
			g_shell.num_quit = 127;
			exit(127);
		}
	}
}

pid_t	child_launch(char *input, t_stack *stack)
{
	pid_t	ch_pid;
	t_stack	*node;

	node = stack;
	g_shell.pid = 1;
	ch_pid = fork();
	if (ch_pid == -1)
		exit(EXIT_FAILURE);
	if (ch_pid == 0)
	{
		rl_catch_signals = 1;
		exec_in_child(input, stack);
	}
	if (ch_pid > 0)
	{
		close(node->pipe.p[1]);
		if (is_built(node->pipe.cmd) == 0)
			if (exec_built_in(input, node) == 1)
				return (ch_pid = 1000, ch_pid);
		close(node->pipe.p[0]);
	}
	waitpid(ch_pid, &g_shell.num_quit, 0);
	get_exit_status();
	return (ch_pid);
}

int	exec_stack(t_stack *stack, char *input)
{
	t_stack	*tmp;
	int		i;

	tmp = stack;
	i = 0;
	if (exit_cmd_in_stack(stack) > 0)
		tmp = reorder_stack(stack);
	while (tmp != NULL)
	{
		if (child_launch(input, tmp) == 1000)
			return (1);
		tmp = tmp->next;
		i++;
	}
	return (0);
}

int	is_built(char *cmd)
{
	int	r;

	cmd = lowercase(cmd);
	r = 1;
	if (str_cmp(cmd, "pwd") == 0)
		r = 0;
	else if (str_cmp(cmd, "echo") == 0)
		r = 0;
	else if (str_cmp(cmd, "cd") == 0)
		r = 0;
	else if (str_cmp(cmd, "export") == 0)
		r = 0;
	else if (str_cmp(cmd, "unset") == 0)
		r = 0;
	else if (str_cmp(cmd, "env") == 0)
		r = 0;
	else if (str_cmp(cmd, "exit") == 0)
		r = 0;
	else if (str_cmp(cmd, "$?") == 0)
		r = 0;
	return (r);
}
