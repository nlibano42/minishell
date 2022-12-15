/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:35:51 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/14 21:46:51 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_stack *node, char *input)
{
	char	*output;

	(void)input;
	output = node->pipe.parsed_input;
	if (node->pipe.arg == NULL)
	{
		fd_putstr_out("\n", node);
		return (0);
	}
	if (str_cmp(node->pipe.arg[0], "-n") == 0)
		fd_putstr_out(&output[8], node);
	else
	{
		fd_putstr_out(&output[5], node);
		fd_putstr_out("\n", node);
	}
	return (0);
}

/*

int	arg_echo(t_stack *node, char *input)
{
	//char	*output;
	int		i;
	int		n;

	(void)input;
	//output = node->pipe.parsed_input;
	i = -1;
	n = 0;
	if (node->pipe.arg[0] == NULL)
	{
		fd_putstr_out("\n", node);
		return (0);
	}
	if (strcmp(node->pipe.arg[0], "-n"))
	{
		n = 1;
		i++;
	}
	if (node->pipe.arg[0] == NULL)
	{
		fd_putstr_out("\n", node);
		return (0);
	}
	while (node->pipe.arg[i])
	{
		fd_putstr_out(node->pipe.arg[i], node);
		fd_putstr_out(" ", node);
		i++;
	}
	if (n == 1)
		fd_putstr_out("\n", node);
	return (0);
}

*/
