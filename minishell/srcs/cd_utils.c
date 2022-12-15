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

void	update_pwd(t_stack *node)
{
	t_env	*env;

	env = g_shell.env;
	if (access((const char *)node->pipe.arg[0], F_OK) == -1)
	{
		printf("-Minishell: cd: ");
		printf("%s: No such file or directory\n", node->pipe.arg[0]);
		g_shell.num_quit = 1;
		return ;
	}
	while (env)
	{
		if (str_cmp(env->name, "PWD") == 0)
		{
			env->val = node->pipe.arg[0];
			chdir((const char *)node->pipe.arg[0]);
			break ;
		}
		env = env->next;
	}
}

void	update_oldpwd(char *old_dir)
{
	t_env	*env;

	env = g_shell.env;
	while (env)
	{
		if (str_cmp(env->name, "OLDPWD") == 0)
		{
			env->val = old_dir;
			break ;
		}
		env = env->next;
	}
}

void	expand_relative(t_stack *node)
{
	char	*exp_dir;

	exp_dir = active_dir();
	node->pipe.arg[0]++;
	exp_dir = stradd(exp_dir, node->pipe.arg[0]);
	node->pipe.arg[0] = exp_dir;
}

void	expand_relative2(t_stack *node)
{
	char	*exp_dir;
	char	*tmp;
	int		i;

	exp_dir = active_dir();
	i = ft_strlen(exp_dir);
	while (exp_dir[i] != '/')
		i--;
	tmp = (char *)malloc(sizeof(char) * (i + 2));
	tmp[i + 1] = '\0';
	while (i >= 0)
	{
		tmp[i] = exp_dir[i];
		i--;
	}
	node->pipe.arg[0]++;
	node->pipe.arg[0]++;
	node->pipe.arg[0]++;
	exp_dir = tmp;
	exp_dir = stradd(exp_dir, node->pipe.arg[0]);
	node->pipe.arg[0] = exp_dir;
}

char	*active_dir(void)
{
	t_env	*env;

	env = g_shell.env;
	while (env)
	{
		if (str_cmp(env->name, "PWD") == 0)
			return (env->val);
		env = env->next;
	}
	return (env->val);
}
