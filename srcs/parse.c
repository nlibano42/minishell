/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:54:39 by xbasabe-         #+#    #+#             */
/*   Updated: 2022/11/24 01:46:06 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*SI ESTAMOS DENTRO O FUERA DE "dobles" o 'simples'*/
/*Dobles: dentro inhibir menos $*/
/*Simples: dentro inhibir todo*/

char	*parse(char *txt)
{
	int	count[2];
	int	flags[2];

	count[0] = 0;
	count[1] = 0;
	flags[0] = 1;
	flags[1] = 1;
	
	quote_d_count(txt, count);
	if ( (txt = quote_in_or_out_loop(txt, count, flags)) == NULL)
	{
		g_num_quit = 1;
		return("echo -Minishell: echo: opened quotes");
	}
	return(txt);
}

void	quote_d_count(char *txt, int *count)
{
	int	i;

	i = 0;
	while(txt[i] != '\0')
	{
		if(txt[i] == '"')
			count[0]++;
		if(txt[i] == 39)
			count[1]++;
		i++;
	}
}

void	remove_quote(char *txt, int init)
{
	int i;

	i = init + 1;
	while(txt[i])
	{
		txt[i -1] = txt[i];
		i++;
	}
	i--;
	txt[i] = '\0';
}

char *expand_vble(char *txt, int *init)
{
	char *value; //valor que tiene la vble tras el $
	char exp[999]; //el nuevo txt expandido
	int		i;
	int		j;
	int		add;

	i = 0;
	add = *init;
	while (txt[add] != ' ' && txt[add] != '\0' && txt[add] != '"' && txt[add] != '\'')
		add++;
	add = add - *init;
	value = search_vble_env(txt, *init);
	j = 0;
	ft_strncpy(exp, txt, *init);
	if(value != NULL)
	{
		while(value[j])
		{
			exp[*init + j] = value[j];
			j++;
		}
	}
	j = j + *init;
	exp[j] = ' '; //problema!!
	exp[j + 1] = '\0';
	j++;
	i = *init + add;
	while(txt[i])
	{
		i++;
		exp[j] = txt[i];
		j++;
	}
	exp[j] = '\0';
	txt = exp;
	return(txt);
}

char    *search_vble_env(char *txt, int init)
{
	int	j;
	char vble[999];

	init++;
	j = 0;
	while (txt[init] != ' ' && txt[init] != '\0' && txt[init] != '"' && txt[init] != '\'')
	{
		vble[j] = txt[init];
		j++;
		init++;
	}
	vble[j] = '\0';
	if(str_cmp(vble, "?") == 0) //$? devuelve el exit status de la ultima ejecución
	{ 
		//return(ft_itoa(g_num_quit)); //retornar el status. ft_itoa sin 
		return("0"); 
	}
	return (getenv((const char*)vble));
}

char	*quote_in_or_out_loop(char *txt, int *count, int *flags)
{
	int	i;
	int *j;

	i = 0;
	j = &i;
	while(txt[i] != '\0')
	{
		if(txt[i] == 39) // simples ' 39 ascci de '
		{	
			if((count[1] % 2 == 0 && count[1] > 0) && flags[0] != -1)//dentro, entramos simples (ignorar dentro las dobles)
			{
				flip_flag(txt, flags, count, i, 1);
				while(txt[i] != 39)
				{
					if (txt[i] == '\0')
						return(NULL);
					i++;
				}
				flip_flag(txt, flags, count, i, 1);
			}
		}
		else if(txt[i] == 34) //34 es el ascci de ""
		{
			if((count[0] % 2 == 0 && count[0] > 0) && flags[1] != -1) //dentro, entramos dobles (ignorar dentro las simples)
			{	
				flip_flag(txt, flags, count, i, 0);
				while(txt[i] != 34)
				{
					if (txt[i] == 36) //36 es el ascci de $
					{
						txt = expand_vble(txt, j);
					}
					if (txt[i] == '\0')
						return(NULL);
					i++;
				}
				flip_flag(txt, flags, count, i, 0);
			}
		}
		else if (txt[i] == 36) //36 es el ascci de $
			txt = expand_vble(txt, j);
		else if (txt[i] == 39 || txt[i] == 34) //comillas que no cierran, opned quotes
			return(NULL);	
		i++;
	}
	//if (txt[i] == 39 || txt[i] == 34)
	//	return(NULL);
	return(txt);
}

void	flip_flag(char *txt, int *flags, int *count, int i, int f)
{
	int init;
	
	init = i;
	flags[f] = flags[f] * -1;
	count[f]--;
	remove_quote(txt, init);
}
