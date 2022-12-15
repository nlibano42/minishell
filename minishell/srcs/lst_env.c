/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:47:55 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/14 17:20:27 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdelone(t_env *lst)
{
	if (lst)
	{
		free(lst->name);
		free(lst->val);
		free(lst);
	}
}

t_env	*ft_lstlast(t_env *lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

char	*ft_lstfind_val(t_env *lst, char *name)
{
	while (lst)
	{
		if (ft_strncmp(lst->name, name, ft_strlen(name)) == 0)
			return (lst->val);
		lst = lst->next;
	}
	return (NULL);
}
