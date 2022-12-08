/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:33:24 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/08 02:44:25 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tab_env(void)
{
	t_env	*env;
	char	**tab;
	int		i;
	char	*s;
	char	*s1;

	env = g_shell.env;
	i = 0;
	while (env)
	{
		i++;
		env = env ->next;
	}
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

int	launch(char *intro, t_stack *node)
{
	const char	*path;
	char *const	*arguments;
	char **splited;
	char	**envi;

	envi = tab_env();
	arguments = NULL;
	splited = ft_split((const char*)intro, '|');
	arguments = ft_split(splited[0], ' ');
	if (node->pipe.ext_path != NULL) //(existe path en el comando introducido)
		execve(node->pipe.input, arguments, envi); 
	path = path_exe(node->pipe.cmd);
	if(path == NULL)
	{
		clear((char **)arguments);
		free((char *)path);
		clear(envi);
		return(-1) ;
	}
	execve(path, arguments, envi);
	clear(envi);
	return(0);
}

int	old_launch(char *intro, t_stack *node)
{
	const char	*path;
	char *const	*arguments;
	char		**tokens;
	char	**envi;

	envi = tab_env();
	arguments = NULL;
	tokens = ft_split(intro, ' '); //SI NO HAY ARGUMENTOS ALGO MANDA DE MÁS
	if (tokens[0] == NULL)
		tokens[0] = node->pipe.cmd;
	arguments = (char *const *)tokens;
	if (node->pipe.ext_path != NULL) //(existe path en el comando introducido)
		execve(node->pipe.input, arguments, envi); 
	path = path_exe(node->pipe.cmd);
	printf("Launchc execv.c argumentos %s\n", (char *)arguments);
	if(path == NULL)
	{
		clear((char **)arguments);
		free((char *)path);
		clear(envi);
		return(-1) ;
	}
	execve(path, arguments, envi);
	clear(envi);
	return(0);
}

const char	*path_exe(char *txt)
{
	char	*directory;
	const char	**p;
	int			i;

	i = 0;
	p = (const char **)ft_split(getenv("PATH"), ':');
	while (p[i])
	{
		directory = (char *)p[i];
		directory = stradd(directory, "/");
		directory = stradd(directory, txt);
		if (access((const char*)directory, F_OK) == 0)
		{
			clear((char **)p);
			return((const char*)directory);
		}
		free(directory);
		i++;
	}
	clear((char **)p);
	return(NULL);
}
