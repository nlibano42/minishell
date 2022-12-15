/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:43:29 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/14 10:43:29 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_envi(t_env **envi, char **env)
{
	t_env	*new;
	char	**values;
	int		i;

	i = -1;
	while (env[++i])
	{
		values = ft_split(env[i], '=');
		new = ft_lstnew(values[0], values[1]);
		ft_lstadd_back(envi, new);
		clear(values);
	}
}
