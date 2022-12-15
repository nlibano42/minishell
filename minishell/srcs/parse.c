/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:54:39 by xbasabe-         #+#    #+#             */
/*   Updated: 2022/12/09 00:08:29 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*SI ESTAMOS DENTRO O FUERA DE "dobles" o 'simples'*/
/*Dobles: dentro inhibir menos $*/
/*Simples: dentro inhibir todo*/

/*ESTE ES EL PARSER*/

char	*parse(char *txt)
{
	int	count[2];
	int	flags[2];

	count[0] = 0;
	count[1] = 0;
	flags[0] = 1;
	flags[1] = 1;
	quote_d_count(txt, count);
	txt = quote_in_or_out_loop(txt, count, flags);
	return (txt);
}


void	remove_quote(char *txt, int init)
{
	int	i;

	i = init + 1;
	while (txt[i])
	{
		txt[i -1] = txt[i];
		i++;
	}
	i--;
	txt[i] = '\0';
}


char	*search_vble_env(char *txt, int init)
{
	int		j;
	char	vble[999];

	init++;
	j = 0;
	while (txt[init] != ' ' && txt[init] != '\0'
		&& txt[init] != '"' && txt[init] != '\'')
	{
		vble[j] = txt[init];
		j++;
		init++;
	}
	vble[j] = '\0';
	if (str_cmp(vble, "?") == 0)
	{
		return (ft_itoa(g_shell.num_quit));
	}
	return (get_env(vble));
}

char	*old_quote_in_or_out_loop(char *txt, int *count, int *flags)
{
	int	i;
	int	*j;

	i = 0;
	j = &i;
	while (txt[i] != '\0')
	{
		if (txt[i] == 39)
		{	
			if ((count[1] % 2 == 0 && count[1] > 0) && flags[0] != -1)
			{
				flip_flag(txt, flags, count, i, 1);
				while (txt[i] != 39)
				{
					if (txt[i] == '\0')
						return (NULL);
					i++;
				}
				flip_flag(txt, flags, count, i, 1);
			}
		}
		else if (txt[i] == 34)
		{
			if ((count[0] % 2 == 0 && count[0] > 0) && flags[1] != -1)
			{	
				flip_flag(txt, flags, count, i, 0);
				while (txt[i] != 34)
				{
					if (txt[i] == '\0')
					{
						return (NULL);
					}
					if (txt[i] == 36)
					{
						txt = expand_vble(txt, j);
					}
					i++;
				}
				flip_flag(txt, flags, count, i, 0);
			}
		}
		else if (txt[i] == 36)
		{	
			txt = expand_vble_out(txt, j);
		}
		else if (txt[i] == 39 || txt[i] == 34)
			return (NULL);
		i++;
	}
	return (txt);
}

/*NUEVOLLOP*/

char	*quote_in_or_out_loop(char *txt, int *count, int *flags)
{
	int	i;
	int	*j;

	i = 0;
	j = &i;
	while (txt[i] != '\0')
	{
		if (txt[i] == 39)
		{	
			if ((count[1] % 2 == 0 && count[1] > 0) && flags[0] != -1)
			{
				flip_flag(txt, flags, count, i, 1);
				while (txt[i] != 39)
				{
					if (txt[i] == '\0')
						return (NULL);
					i++;
				}
				flip_flag(txt, flags, count, i, 1);
			}
		}
		else if (txt[i] == 34)
		{
			if ((count[0] % 2 == 0 && count[0] > 0) && flags[1] != -1)
			{	
				flip_flag(txt, flags, count, i, 0);
				while (txt[i] != 34)
				{
					if (txt[i] == '\0')
					{
						return (NULL);
					}
					if (txt[i] == 36)
					{
						txt = expand_vble(txt, j);
					}
					i++;
				}
				flip_flag(txt, flags, count, i, 0);
			}
		}
		else if (txt[i] == 36)
		{	
			txt = expand_vble_out(txt, j);
		}
		else if (txt[i] == 39 || txt[i] == 34)
			return (NULL);
		i++;
	}
	return (txt);
}

void	flip_flag(char *txt, int *flags, int *count, int i, int f)
{
	int	init;

	init = i;
	flags[f] = flags[f] * -1;
	count[f]--;
	remove_quote(txt, init);
}
