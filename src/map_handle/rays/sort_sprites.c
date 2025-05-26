/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** sort_sprites
*/

#include "my.h"
#include "struct.h"

void swapper(bool *swapped, enemy_list_t **current, enemy_list_t **head)
{
    enemy_list_t *real_cur = *current;
    enemy_list_t *next_node = real_cur->next;

    if (real_cur->dist < next_node->dist) {
        if (real_cur->prev != NULL) {
            real_cur->prev->next = next_node;
        } else
            *head = next_node;
        next_node->prev = real_cur->prev;
        real_cur->next = next_node->next;
        if (next_node->next != NULL) {
            next_node->next->prev = real_cur;
        }
        next_node->next = real_cur;
        real_cur->prev = next_node;
        *swapped = true;
    } else
        *current = real_cur->next;
}

void bubble_sort(enemy_list_t **head)
{
    bool swapped;
    enemy_list_t *current;
    enemy_list_t *last = NULL;

    if (*head == NULL)
        return;
    do {
        swapped = false;
        current = *head;
        while (current->next != last) {
            swapper(&swapped, &current, head);
        }
        last = current;
    } while (swapped);
}
