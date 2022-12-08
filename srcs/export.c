/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:15:56 by marvin            #+#    #+#             */
/*   Updated: 2022/12/08 02:50:57 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_env	*sort_env(void) //t_env version
{
	t_env	*sort;
	t_env	*iterate;
	t_env	*tmp;

	sort = g_shell.env;
	iterate = g_shell.env;
	while (sort)
	{
		while (iterate)
		{
			if (ft_strncmp(sort->name, iterate->name , ft_strlen(sort->name)) < 0)
			{
				tmp = sort;
				sort =  iterate;
				iterate = tmp;
				
			}
			iterate = iterate->next;
		}
		sort = sort->next;
	}
	return (sort);
}


void	export_no_args(t_stack *node)
{
	t_env	*sort;

	sort = sort_env();
	//sort = g_shell.env;
	while (sort)
		if (ft_strncmp((const char*)sort->name, "_=", 2) != 0)
		{
			fd_putstr_out("declare -x ", node);
			fd_putstr_out(sort->name, node);
			fd_putstr_out("=\"", node);
			fd_putstr_out(sort->val, node);
			fd_putstr_out("\"", node);
			fd_putstr_out("\n", node);
			sort = sort->next;
		}
}

void	export_add(char *vbl)
{
	t_env	*new;
	t_env	**enviroment;
	char	**vble;

	enviroment = &g_shell.env;
	vble = ft_split(vbl, '=');
	new = ft_lstnew(vble[0], vble[1]);
	clear(vble);
    ft_lstadd_back(enviroment, new);
}

void	export(t_stack *node)
{
	int		exist;
	char	**var;
	t_env	*env;

	if (!node->pipe.arg[0])
	{
		export_no_args(node);
		return ;
	}
	//comprobra si hay más de un argumento? cada argumento de node se toma como una variable a trata por export while arg[i]
	var = ft_split(node->pipe.arg[0], '=');
	exist = 0;
	env = g_shell.env;
	while (env)
	{
		if (str_cmp(env->name, var[0]) == 0) 
		{
            env->val = var[0];
			exist = 1;
			break ;
		}
		env = env->next;
	}
	if (exist == 0)
		export_add(node->pipe.arg[0]);
	clear(var);
}
