/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 10:40:03 by marvin            #+#    #+#             */
/*   Updated: 2022/12/02 01:26:36 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_stack *node, char* input)
{
	char *output;

	if (node->pipe.arg[0] == NULL)
	{
		fd_putstr_out("\n", node);
		return (0);
	}
	output = parse(input);
	if (str_cmp(node->pipe.arg[0], "-n") == 0)
		fd_putstr_out(&output[8], node);
	else
	{
		fd_putstr_out(&output[5], node);
		fd_putstr_out("\n", node);
	}
	
	return (0);
}

void	env(char **envi, t_stack *node)
{
	int	i;

	i = 0;
	while (envi[i])
	{
		fd_putstr_out(envi[i++], node);
		fd_putstr_out("\n", node);
	}
}

void	pwd(char **envi, t_stack *node)
{
	int		i;
	char	**var;

	i = 0;
	while (envi[i])
	{
		var = ft_split(envi[i], '=');
		if (str_cmp(var[0], "PWD") == 0)
		{
			fd_putstr_out(var[1], node);
			fd_putstr_out("\n", node);
			clear (var);
			break;
		}
		i++;
		clear (var);
	}
}

void	unset(char *input, char **envi)
{
	int		i;
	char	**var;
	char	**arguments;

	i = 0;
	arguments = ft_split(input, ' ');
	if (!arguments[1])
		return ;
	while (envi[i])
	{
		var = ft_split(envi[i], '=');
		if (str_cmp(var[0], arguments[1]) == 0)
		{
			while(envi[i + 1])
			{
				envi[i] = envi[i + 1];
				i++;
			}
//			envi[i] = '\0';
			envi[i] = NULL;
			clear(var);
			return ;
		}
		i++;
	}
	clear(var);
	return ;
}

void	exit_kill(t_stack *node) 
{
	//kill(node->pipe.node_pid, SIGKILL);
	deleteAllNodes(node);
	exit(0);
}

int	exec_built_in(char *input, char **envi, t_stack *node)
{
	if (str_cmp(node->pipe.cmd, "echo") == 0)
		echo(node, input);
	else if (str_cmp(node->pipe.cmd, "pwd") == 0)
		pwd(envi, node);
	else if (str_cmp(node->pipe.cmd, "cd") == 0)
		cd(input, envi, node);
	else if (str_cmp(node->pipe.cmd, "export") == 0)
		export(input, envi, node);
	else if (str_cmp(node->pipe.cmd, "unset") == 0)
		unset(input, envi);
	else if (str_cmp(node->pipe.cmd, "env") == 0)
		env(envi, node);
	else if (str_cmp(node->pipe.cmd, "exit") == 0)
	{
		printf("cucu exit\n");
		exit_kill(node);
	}
	g_num_quit = 0; //status a 0.
	return (0);
}
