/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:35:51 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/15 00:49:10 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_stack *node, char *input)
{
	int		i;
	int		n;

	(void)input;
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
