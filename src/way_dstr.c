/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_dstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 16:36:13 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/25 02:35:19 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void dstr_path(t_w *curr)
{
    t_w *next;

    next = curr->next;
    curr->room = NULL;
    curr->home = NULL;
    curr->prev = NULL;
    curr->next = NULL;
    free(curr);
    curr = NULL;
    while (next != NULL)
    {
        curr = next;
        next = curr->next;
        curr->room = NULL;
        curr->home = NULL;
        curr->prev = NULL;
        curr->next = NULL;
        free(curr);
        curr = NULL;
    }
}

void dstr_way(t_ws **prey)
{
    t_wh *curr;
    t_wh *next;

    curr = (*prey)->ways;
    (*prey)->ways = NULL;
    free(*prey);
    *prey = NULL;
    next = curr->next;
    dstr_path(curr->start);
    curr->start = NULL;
    curr->end = NULL;
    free(curr);
    curr = NULL;
    while (next != NULL)
    {
        curr = next;
        next = curr->next;
        dstr_path(curr->start);
        curr->start = NULL;
        curr->end = NULL;
        free(curr);
        curr = NULL;
    }
}