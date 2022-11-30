/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:54:17 by marvin            #+#    #+#             */
/*   Updated: 2022/11/30 21:34:06 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    mov_last(struct t_stack *node, struct t_stack *stack)
{
    struct t_stack  *last;
    struct t_stack  *tmp;

    (void)stack;
    tmp = node; // tmp = stack; ??
    last = node;
    while(tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = last;
}

int exit_cmd_in_stack(struct t_stack *stack)
{
    int i;
    struct t_stack *tmp;

    i = 0;
    tmp = stack;
    while(tmp != NULL)
    {
        if(str_cmp(tmp->pipe.cmd, "exit") == 0)
            return(i);
        i++;
        tmp = tmp->next;
    }
    return(0);
}


struct t_stack *jump_to(struct t_stack *stack, int to)
{
    //saltar en la cola de comandos hasta el cmd siguiente al exit la posicion to
    int i;
    struct t_stack *jump;
    
    i = 0;
    to++;
    jump = stack;
    while(i < to)
    {
        jump = jump->next;
        i++;
    }
    free(stack);
    return(jump);
}

struct t_stack *stack_first(struct t_stack *stack)
{
    struct t_stack *jump;
    
    jump = stack;
    while(jump != NULL)
    {
        jump = jump->prev;
    }
    deleteAllNodes(stack);
    return(jump);
}

struct t_stack *reorder_stack(struct t_stack *stack) // que debe hacer?
{
    int i;

    i = exit_cmd_in_stack(stack);
    if (i != 0) //si tenemos un cmd exit se ejecutan los comandos que estén despues, saltamoms hasta el cmd siguiente en el stack
        return(jump_to(stack, i));
    return(stack);
}
