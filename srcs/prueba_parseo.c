/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba_parseo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:58:40 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/14 22:05:26 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
char	*parse(char *txt)
{
	int	count[2];
	int	flags[2];

	count[0] = 0;
	count[1] = 0;
	flags[0] = 1;
	flags[1] = 1;
	quote_d_count(txt, count);
	txt = parse_loop(txt, count, flags);
	return (txt);
}
*/

/*
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
*/

void	init_parser(int *index, int *flags)
{
	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	flags[0] = 1;
	flags[1] = 1;
}

char	*parse_loop(char *txt)
{
	int		flags[2];
	char	**tokens;
	char	temp[999];
	int		index[3];

	init_parser(index, flags);
	tokens = (char **)malloc((sizeof(char *) * 20));
	while (txt[index[0]] != '\0')
	{
		if (txt[index[0]] == 39)
			into_simple(flags, txt, temp, index);
		else if (txt[index[0]] == 34)
			into_double(flags, txt, temp, index);
		else if (txt[index[0]] == '|')
		{
			remove_quote(txt, index[0]);
			temp[index[1]] = '\0';
			tokens[index[2]] = ft_strdup(temp);
			index[2] = index[2] + 1;
			index[1] = 0;
		}
		if (txt[index[0]] == 36)
			txt = expand_vble(txt, &index[0]);
		temp[index[1]] = txt[index[0]];
		index[0] = index[0] + 1;
		index[1] = index[1] + 1;
	}
	temp[index[1]] = '\0';
	tokens[index[2]] = ft_strdup(temp);
	tokens[index[2] + 1] = NULL;
	return (chard_to_chars(tokens));
}

void	into_simple(int *flags, char *txt, char *temp, int *index)
{	
	if (flags[0] != -1 && flags[1] != -1)
	{
		flag_change(txt, flags, &index[0], 1);
		while (txt[index[0]] != 39)
		{
			temp[index[1]] = txt[index[0]];
			if (txt[index[0]] == '\0')
			{
				//printf("opened quotes in command line\n");
				//txt = strdup("opened quotes in command line\n");
				g_shell.num_quit = 1;
				return ;
			}	
			index[0] = index[0] + 1;
			index[1] = index[1] + 1;
		}
		flag_change(txt, flags, &index[0], 1);
	}
}

void	into_double(int *flags, char *txt, char *temp, int *index)
{
	if (flags[1] != -1 && flags[0] != -1)
	{
		flag_change(txt, flags, &index[0], 0);
		while (txt[index[0]] != 34)
		{
			temp[index[1]] = txt[index[0]];
			if (txt[index[0]] == '\0')
			{
				//printf("opened quotes in command line\n");
				//txt = strdup("opened quotes in command line\n");
				g_shell.num_quit = 1;
				return ;
			}
			if (txt[index[0]] == 36)
				txt = expand_vble(txt, &index[0]);
			index[0] = index[0] + 1;
			index[1] = index[1] + 1;
		}
		flag_change(txt, flags, &index[0], 0);
	}
}

/*  y esta en dsplit toknes
void	flag_change(char *txt, int *flags, int *i, int f)
{
	int	init;

	init = *i;
	flags[f] = flags[f] * -1;
	remove_quote(txt, init);
}
*/

char	*chard_to_chars(char **intro)
{
	char	*txt;
	int		i;	

	i = 0;
	while (intro[i])
		txt = ft_strjoin((const char *)intro[i], (const char *)txt);
	return (txt);
}