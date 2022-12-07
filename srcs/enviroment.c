/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:17:41 by marvin            #+#    #+#             */
/*   Updated: 2022/12/05 21:17:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_env	*set_envi(char **env)
{
	t_env *tmp;
    t_env *result;
    char **values;
    int i;

    values = ft_split(env[0], '=');
    result = ft_lstnew(values[0], values[1]);
    i = 1;
    while(env[i])
    {
        values = ft_split(env[i], '=');
        tmp = ft_lstnew(values[0], values[1]);
        result->next = tmp;
        printf("Checking enviro[%d] val %s value %s\n", i, result->name, result->val);
        result = result->next;
        i++;
    }
    return(result);
}

void    print_enviro(t_env *enviro)
{
    t_env *result;
    
    result = enviro;
    while(result->next != NULL)
    {
        printf("Checking val %s value %s\n", result->name, result->val);
        result = result->next;
    }
}

/*
t_env	*set_envi(char **env)
{
	t_env *tmp_env;
    t_env *result;
    int i;

    result = create_vble(env[0]);
    //envir = tmp_env;
    i = 1;
    while(env[i])
    {
        tmp_env = create_vble(env[i]);
       // insert_env(envir, tmp_env);
        result->next = tmp_env;
       // free(tmp_env);
        i++;
    }
    return(result);
}
*/
t_env  *create_vble(char *envi) //para iniciliar y modificar para usar en export 
{
    t_env  *vble;
    char **values;
    
    vble = (t_env *)malloc(sizeof(t_env));
    values = ft_split(envi, '=');
    vble->name = values[0];
    vble->val = values[1];
    vble->next = NULL;

    return(vble);
}

void    insert_env(t_env *envi, t_env *vble) //inseertar al final. usar para añadir en export 
{
    t_env  *temp;
    
    if (envi->next == NULL)
    {
        envi->next = vble;
       // vble->prev = envi;
    }
    else
    {
        temp = envi->next;
        while(temp->next)
            temp = temp->next;
       // vble->prev = temp;
        temp->next = vble;
    }
}

void deleteEnviro(t_env *envi)
{
    t_env * temp;

    while (envi != NULL)
    { 
        temp = envi;
        //free_node_content(temp); // ver que contenido debemos liberar de envi
        envi = envi->next;
        free(temp);
    }
}

/*
char **copy_env(char **env)
{
    char    **copy;
    int     i;

    i = 0;
    copy = (char **)malloc(sizeof(char*) * (ft_str2len(env) + 1));
    while(env[i])
    {
        copy[i] = env[i];
        i++;
    }
    copy[i] = NULL;
    return(copy);
}
*/