/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 11:39:07 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/02 23:05:17 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stack *pipe_stack(char * input, char **envi)
{
    t_stack  *stack;
    t_stack  *tmp_node;
    char            **tokens;
    int             i;
    
    //input = parse(input);   /* UNA VEZ BIEN HECHO, PARSEAR AQUÍ */ 
    tokens = ft_split(input, '|');
    if (tokens[0])
    {
        stack = create_node(tokens[0], envi);
        create_cmds(stack);
    }
    i = 1;
    while (tokens[i])
    {
        tmp_node = create_node(tokens[i], envi);
        create_cmds(tmp_node);
        insert_l_pipe(tmp_node, stack);
        i++;
    }
    
    clear(tokens);
    return (stack);
}

t_stack  *create_node(char *txt, char **envi) 
{
    t_stack  *node;

    node = (t_stack *)malloc(sizeof(t_stack));
    node->pipe.input = txt;
    node->pipe.envi = envi;
    node->pipe.cmd = NULL;
    node->pipe.arg = NULL;
    node->pipe.ext_path = NULL;
    node->next = NULL;
    node->prev = NULL;
    pipe(node->pipe.p);
    return(node);
}

void    insert_f_pipe(t_stack *node, t_stack *stack) //first MAL!!
{
    node->next = stack;
    //stack->next = node;
}

void    insert_l_pipe(t_stack *node, t_stack *stack) //last
{
    t_stack  *temp;
    
    if (stack->next == NULL)
    {
        stack->next = node;
        node->prev = stack;
    }
    else
    {
        temp = stack->next;
        while(temp->next)
            temp = temp->next;
        node->prev = temp;
        temp->next = node;
    }
}

void    free_stack(t_stack *stack)
{
    //t_stack  *tmp;

    
    if (stack->next == NULL)
    {
        free_node(stack);
        //free(stack);
    }
    /*
    else if(stack->next != NULL) //recorrer la pila y liberar los nodos
    {
        tmp = stack;
        while(stack)
        {
            tmp = stack->next;
            free_node(stack->prev);
            stack = tmp;
        }
        free(stack);
    } */
}

void    free_node(t_stack *node)
{
    if (node == NULL)
        return ;
    
    //free(node->pipe.arg);
    if (node->pipe.arg)
        clear(node->pipe.arg);
    //free(node->pipe.cmd);

    free_node(node->next);
    free_node(node->prev);
    free(node->pipe.input);
    free(node);
}

void    free_node_content(t_stack *node)
{
    if (node == NULL)
        return ;
    if (node->pipe.arg != NULL)
        clear(node->pipe.arg);
    free(node->pipe.cmd);
    free(node->pipe.input); //lo podemos liberar en lexerc al crear cmds
}

void deleteAllNodes(t_stack *start)
{
    t_stack * temp;

    while (start != NULL)
    { 
        temp = start;
        free_node_content(temp);
        start = start -> next;
        free(temp);
    }
}
