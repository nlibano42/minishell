/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:03:32 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/02 23:06:32 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char * no_blancks(char *txt)
{
    int i;
    int j;
    char *ret;

    ret = NULL;
    i = 0;
    j = 0;
    while(txt[i])
    {
        if(txt[i] == ' ')
        {
            while (txt[j] == ' ')
                j++;
            i = i + j;
        }
        j = 0;
        ret[i] = txt[i];
    }
    return(ret);
}

void    create_cmds(t_stack *node)
{
    char    **words;
    int     i;
    
    words = ft_split(node->pipe.input, ' ');
    node->pipe.arg = (char **)malloc(sizeof(char*) * ft_str2len(words)); //tenemos un espacio de más porque words contiene cmd y args
	if (!node->pipe.arg)
		return ;
    node->pipe.cmd = words[0];
    i = 1;
    
    while(words[i])
    {
        node->pipe.arg[i - 1] = words[i];
        //ft_strcpy(node->pipe.arg[i] , words[i]);
        i++;
    }
    node->pipe.arg[i -1] = '\0';
	//node->pipe.arg[i - 1] = NULL;
    
    cmd_path(node);
    free(words);
}

void cmd_path(t_stack *node) //si el cmd viene con ruta
{
    char ruta[999];
    char comand[999];
    int i;
    int c;

    i = ft_strlen(node->pipe.cmd);
    c = 0;
    while(i >= 0)
    {
        if(node->pipe.cmd[i] == '/')
            c++;
        i--;
    }
    i = 0;
    while(c > 0)
    {
        if(node->pipe.cmd[i] == '/')
            c--;
        ruta[i] = node->pipe.cmd[i];
        i++;
    }
    ruta[i] = '\0';
    node->pipe.ext_path = ruta;
    if (ruta[0] != '\0')
        relative_path(node);
    c = 0;
    while(node->pipe.cmd[i] != '\0')
    {
        comand[c] = node->pipe.cmd[i];
        i++;
        c++;
    }
    comand[c] = '\0';
    ft_strcpy(node->pipe.cmd, comand);
}


void    relative_path(t_stack *node) //expandir una ruta relativa ../ o ./
{
    if (node->pipe.ext_path[0] == '.' && node->pipe.ext_path[1] == '/')
        exp_act_path(node);
    if (node->pipe.ext_path[0] == '.' && node->pipe.ext_path[1] == '.' && node->pipe.ext_path[2] == '/')
        exp_up_path(node);
    
}

void    exp_act_path(t_stack *node) //expandir path actuak ./
{
    char    *exp_dir;

    exp_dir = active_dir(node->pipe.envi);
    node->pipe.ext_path++; //cambiar esto?
    exp_dir = stradd(exp_dir, node->pipe.ext_path);
    node->pipe.ext_path = exp_dir;
}

void    exp_up_path(t_stack *node) //expandir directorio arriba ../
{
    char    *exp_dir;
    char    *tmp;
    int     i;

    exp_dir = active_dir(node->pipe.envi);
    i = ft_strlen(exp_dir);
    while(exp_dir[i] != '/')
        i--;
    tmp = (char *)malloc(sizeof(char) * (i + 2));
    tmp[i + 1] = '\0';
    while(i >= 0)
    {
        tmp[i] = exp_dir[i];
        i--;
    }
    node->pipe.ext_path++;
    node->pipe.ext_path++;
    node->pipe.ext_path++;
    exp_dir = tmp;
    exp_dir = stradd(exp_dir, node->pipe.ext_path);
    node->pipe.cmd = exp_dir;
    free(tmp);
}
