/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:35:51 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/14 16:48:06 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_stack *node, char *input)
{
	char	*output;

	(void)input;
	output = node->pipe.parsed_input;
	if (str_cmp(output, "opened quotes in command line") == 0)
		return (1);
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
