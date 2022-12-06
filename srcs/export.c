/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:15:56 by marvin            #+#    #+#             */
/*   Updated: 2022/12/01 11:15:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	export_no_args(char **env, t_stack *node)
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
			fd_putstr_out("declare -x ", node);
			fd_putstr_out(split[0], node);
			fd_putstr_out("=\"", node);
			fd_putstr_out(split[1], node);
			fd_putstr_out("\"", node);
			fd_putstr_out("\n", node);
			clear (split);
		}
}

//char	**export_add(char **envi, char *vbl)
void	export_add(char **envi, char *vbl)
{
	char	**united;
	int		len;
	int		i;

	len = (ft_str2len(envi)) + 2;
	united = (char **)malloc(sizeof(char *) * len);
	if (!united)
		//return (NULL);
		return ;
	i = 0;
	while (envi[i])
	{
		//united[i] = envi[i];
		united[i] = ft_strdup((const char*)envi[i]);
		i++;
	}
	//united[i] = vbl;
	united [i] = ft_strdup((const char*)vbl);
	united[i + 1] = NULL;
	envi = united;
	clear(united);
	//return (united);
}

void	export(char *input, char **envi, t_stack *node)
{
	int		j;
	int		exist;
	char	**var;
	char	**envi_var;

	(void)input;
	if (!node->pipe.arg[0])
	{
		export_no_args(envi, node);
		return ;
	}
	//comprobra si hay más de un argumento? cada argumento de node se toma como una variable a trata por export
	var = ft_split(node->pipe.arg[0], '=');
	j = -1;
	exist = 0;
	while (envi[++j])
	{
		envi_var = ft_split(envi[j], '=');
		if (str_cmp(envi_var[0], var[0]) == 0) 
		{
			ft_strcpy(envi[j], node->pipe.arg[0]);
			exist = 1;
			clear(envi_var);
			break ;
		}
		clear(envi_var);
	}
	if (exist == 0) //vble no encontrada, añadirla al final
	{
		printf("export añadir vble -%s-\n", node->pipe.arg[0]);
		export_add(envi, node->pipe.arg[0]);
	}
	clear(var);
	//clear(envi_var);
}
