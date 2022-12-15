/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:44:11 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/14 17:59:53 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_size(void)
{
	t_env	*env;
	int		i;

	env = g_shell.env;
	i = 1;
	while (env)
	{
		i++;
		env = env ->next;
	}
	return (i);
}

char	**tab_env(void)
{
	t_env	*env;
	char	**tab;
	int		i;
	char	*s;
	char	*s1;

	env = g_shell.env;
	i = env_size();
	tab = malloc(sizeof(char *) * i + 1);
	if (!tab)
		return (NULL);
	env = g_shell.env;
	i = -1;
	while (env)
	{
		s = ft_strjoin(env->name, "=");
		s1 = ft_strjoin(s, env->val);
		tab[++i] = ft_strdup(s1);
		free (s);
		free (s1);
		env = env->next;
	}
	tab[i + 1] = NULL;
	return (tab);
}

void	path_in_enviroment(t_stack *node)
{
	t_env	*env;

	env = g_shell.env;
	while (env)
	{
		if (strcmp(env->name, "PATH") == 0)
			return ;
		env = env ->next;
	}
	g_shell.num_quit = 127;
	fd_putstr_out(" -Minshell: ", node);
	fd_putstr_out(node->pipe.cmd, node);
	fd_putstr_out(": command not found\n", node);
	exit(127);
}

int	launch(char *intro, t_stack *node)
{
	const char	*path;
	char *const	*arguments;
	char		**splited;
	char		**envi;

	envi = tab_env();
	(void)intro;
	path_in_enviroment(node);
	arguments = NULL;
	splited = ft_split((const char *)node->pipe.parsed_input, '|');
	arguments = ft_split(splited[0], ' ');
	if (node->pipe.ext_path != NULL)
		execve(node->pipe.input, arguments, envi);
	path = path_exe(node->pipe.cmd);
	if (path == NULL)
	{
		clear((char **)arguments);
		free((char *)path);
		clear(envi);
		clear(splited);
		return (-1);
	}
	g_shell.num_quit = execve(path, arguments, envi);
	return (g_shell.num_quit);
}

const char	*path_exe(char *txt)
{
	char		*directory;
	const char	**p;
	int			i;

	i = 0;
	p = (const char **)ft_split(get_env("PATH"), ':');
	while (p[i])
	{
		directory = (char *)p[i];
		directory = stradd(directory, "/");
		directory = stradd(directory, txt);
		if (access((const char *)directory, X_OK) == 0)
		{
			clear((char **)p);
			return ((const char *)directory);
		}
		free(directory);
		i++;
	}
	clear((char **)p);
	return (NULL);
}
