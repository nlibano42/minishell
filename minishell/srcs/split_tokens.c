/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:58:40 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/15 01:28:26 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_tokens(char *txt)
{
	int		i;
	//int		*j;
	int		flags[2];
	char	**tokens;
	//char	*temp;
	char	temp[999];
	int		d;
	int		c;
	i = 0;
	d = 0;
	//j = &i;
	c = 0;
	flags[0] = 1;
	flags[1] = 1;
	//temp = (char *)malloc(sizeof(char) * ft_strlen(txt) + 1);
	//temp = NULL;
	tokens = (char **)malloc((sizeof(char *) * 20));
	while (txt[i] != '\0')
	{
		if (txt[i] == 39) // simples ' 39 ascci de '
		{
			if (flags[0] != -1 && flags[1] != -1)//dentro, entramos simples (ignorar dentro las dobles)
			{
				flag_change(txt, flags, i, 1);
				while (txt[i] != 39) // 39 es el ascii de '
				{
					temp[d] = txt[i];
					if (txt[i] == '\0')
					{
						printf("opened quotes in command line\n");
						g_shell.num_quit = 1;
						exit(1);
					}	
					i++;
					d++;
				}
				flag_change(txt, flags, i, 1);
			}
		}
		else if (txt[i] == 34) //34 es el ascci de ""
		{
			if (flags[1] != -1 && flags[0] != -1) //dentro, entramos dobles (ignorar dentro las simples)
			{
				flag_change(txt, flags, i, 0);
				while (txt[i] != 34)
				{
					temp[d] = txt[i];
					if (txt[i] == '\0')
					{
						printf("opened quotes in command line\n");
						g_shell.num_quit = 1;
						exit(1);
					}
					i++;
					d++;
				}
				flag_change(txt, flags, i, 0);
			}
		}
		else if (txt[i] == '|')
		{
			remove_quote(txt, i);
			temp[d] = '\0';
			tokens[c] = ft_strdup(temp);
			c++;
			d = 0;
		}
		temp[d] = txt[i];
		i++;
		d++;
	}
	temp[d] = '\0';
	tokens[c] = ft_strdup(temp);
	tokens[c + 1] = NULL;
	return (tokens);
}

void	flag_change(char *txt, int *flags, int i, int f)
{
	int	init;
	init = i;
	flags[f] = flags[f] * -1;
	remove_quote(txt, init);
}
