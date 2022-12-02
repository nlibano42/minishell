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

int	echo(t_stack *node)
{
	char *output;

	if (node->pipe.arg[0] == NULL)
	{
		fd_putstr_out("\n", node);
		return (1);
	}
	output = parse(node->pipe.input);
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
			free (var);
			break;
		}
		i++;
		free (var);
	}
}

char	**sort_env(char **env)
{
	char	**sort;
	char	*tmp;
	int		i;
	int		j;

	sort = env;
	i = -1;
	while (sort[++i])
	{
		j = -1;
		while (sort[++j])
		if (ft_strncmp(sort[i], sort[j], ft_strlen(sort[i])) < 0)
		{
			tmp = sort[i];
			sort[i] = sort[j];
			sort[j] = tmp;
		}
	}
	return (sort);
}

void	export_no_args(char **env)
{
	int		i;
	char	**sort;
	char	**split;

	sort = sort_env(env);
	i = -1;
	while (sort[++i])
		if (ft_strncmp(sort[i], "_=", 2) != 0)
		{
			split = ft_split(sort[i], '=');
			printf("declare -x %s=\"%s\"\n", split[0], split[1]);
			free (split);
		}
}

void	export(char *input, char **envi)
{
	int		i;
	int		j;
	int		exist;
	char	**var;
	char	**arguments;

	arguments = ft_split(input, ' ');
	if (!arguments[1])
	{
		export_no_args(envi);
		free(arguments);
		return ;
	}
	i = 0;
	while (arguments[++i])
	{
		var = ft_split(arguments[i], '=');
		j = -1;
		exist = 0;
		while (envi[++j])
		{
			if (str_cmp(envi[j], var[0]) == 0)
			{
				envi[i] = arguments[i];
				exist = 1;
				break ;
			}
		}
		if (exist == 0)
		{
		//	envi[j] = arguments[j];
		// si env es un struct, podriamos añadir al final.
//seg.fault			envi[j] = stradd(envi[j], arguments[i]);
		}
	}
/*	if ((ft_str2len(arguments) == 3)) //1export 2vble 3valor
		while (envi[i])
		{
			var = ft_split(envi[i], '=');
			if (str_cmp(var[0], arguments[1]) == 0)
			{
				envi[i] = stradd(var[0], "=");
				envi[i] = stradd(envi[i], arguments[2]);
				free(var);
				free(arguments);
				return ;
			}
			i++;
			free(var);
		}
	if ((ft_str2len(arguments) == 4))
		envi = str2add(envi, input);
	//opcion de añadir  variable
*/
	
	free(arguments);
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

int	exec_built_in(char *input, char **envi, t_stack *node) //reconvertir en exec in parent y sacar echo para el caso de comillas sin cerrar
{
	char	**tokens;

	tokens = ft_split(input, ' ');
	tokens[0] = lowercase(tokens[0]);
	if (str_cmp(tokens[0], "echo") == 0)
		echo(node);
	else if (str_cmp(tokens[0], "pwd") == 0)
		pwd(envi, node);
	else if (str_cmp(tokens[0], "cd") == 0)
	{
		//create_cmds(node);
		cd(input, envi, node);
	}
	else if (str_cmp(tokens[0], "export") == 0)
		export(input, envi);
	else if (str_cmp(tokens[0], "unset") == 0)
		unset(input, envi);
	else if (str_cmp(tokens[0], "env") == 0)
		env(envi, node);
	else if (str_cmp(tokens[0], "parse") == 0)
		parse(input);
	else if (str_cmp(tokens[0], "exit") == 0)
		exit_kill(node);
	else
	{
		clear(tokens);
		return (1);
	}
	clear(tokens);
	return (0);
}
