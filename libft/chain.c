/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:18:15 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/07/05 12:18:15 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*stradd(char *s1, char *s2)
{
	char	*united;
	int		len;
	int		i;
	int		j;

	len = (ft_strlen((const char*)s1) + ft_strlen((const char *)s2) + 1);
	i = ft_strlen((const char *)s1);
	j = 0;
	united = (char *)malloc(sizeof(char) * len);
	ft_strcpy(united, s1);
	j = 0;
	while (i < len)
	{
		united[i] = s2[j];
		i++;
		j++;
	}
	united[i] = '\0';
	return (united);
}


char	**str2add(char **s1, char *s2)
{
	char	**united;
	int		len;
	int		i;

	len = (ft_str2len(s1) + 2);
	i = 0;
	united = (char **)malloc(sizeof(char *) * len);
	while (s1[i])
	{
		//united[i] = s1[i];
		ft_strcpy(united[i],s1[i]);
		i++;
	}
	ft_strcpy(united[i],s2);
	//united[i] = s2;
	united[i + 1] = '\0';
	return (united);
}


int	str_cmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return(1);
	if (ft_strlen(str1) != ft_strlen(str2))
		return (1);
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	return (0);
}

int	fd_putstr(char *str, int fd)
{
	int i;

	i = 0;
	while(str[i])
		write(fd, &str[i++], 1);
	return (i);
}

char	*lowercase(char *str)
{
	int	i;
	
	i = 0;
	while(str[i])
	{
		if (str[i] > 'A' && str[i] < 'Z')
			str[i] = str[i] + 32; 
	i++;
	}
	return(str);
}
