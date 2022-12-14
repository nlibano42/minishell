/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:42:57 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/14 10:42:57 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*home_dir(void)
{
	t_env	*env;

	env = g_shell.env;
	while (env)
	{
		if (str_cmp(env->name, "HOME") == 0)
			return (env->val);
		env = env->next;
	}
	return (env->val);
}

char	*old_dir(void)
{
	t_env	*env;

	env = g_shell.env;
	while (env)
	{
		if (str_cmp(env->name, "OLDPWD") == 0)
			return (env->val);
		env = env->next;
	}
	return (env->val);
}

int	init_cd_one_arg(t_stack *node)
{
	char	*val;

	if (node->pipe.arg[0][0] == '.' && node->pipe.arg[0][1] == '/')
		expand_relative(node);
	else if (node->pipe.arg[0][0] == '.' && node->pipe.arg[0][1] == '.' && \
			node->pipe.arg[0][2] == '/')
		expand_relative2(node);
	else if (strcmp(node->pipe.arg[0], "-") == 0 && !node->pipe.arg[1])
	{
		val = ft_lstfind_val(g_shell.env, "OLDPWD");
		if (val == NULL)
		{
			printf("Minishell: cd: OLDPWD not set\n");
			return (1);
		}
		else
		{
			free (node->pipe.arg[0]);
			node->pipe.arg[0] = ft_strdup(val);
		}
	}
	else if (strcmp(node->pipe.arg[0], "~") == 0 && !node->pipe.arg[1])
		node->pipe.arg[0] = ft_strdup(home_dir());
	return (0);
}

int	init_cd(char *input, t_stack *node)
{
	(void) input;
	if (node->pipe.arg == NULL)
	{
		node->pipe.arg = (char **)malloc(sizeof(char *) * 2 + 1);
		if (!(node->pipe.arg))
			return (-1);
		node->pipe.arg[0] = ft_strdup(home_dir());
		node->pipe.arg[1] = NULL;
	}
	else if (node->pipe.arg[0])
	{
		if (init_cd_one_arg(node) == 1)
			return (1);
	}
	else if (node->pipe.arg[2] != NULL)
	{
		fd_putstr_out("-Minishell: cd: too many arguments\n", node);
		g_shell.num_quit = 1;
		return (1);
	}
	return (0);
}

void	cd(char *input, t_stack *node)
{
	t_env	*env;
	char	*old_dir;

	env = g_shell.env;
	old_dir = NULL;
	while (env)
	{
		if (str_cmp(env->name, "PWD") == 0)
		{
			old_dir = ft_strdup(env->val);
			break ;
		}
		env = env->next;
	}
	if (init_cd(input, node) == 0)
		update_pwd(node);
	update_oldpwd(old_dir);
	if (old_dir)
		free(old_dir);
}
