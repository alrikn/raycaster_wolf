/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** entity_list.h
*/

#ifndef MENU_BAR
    #define MENU_BAR
    #include <SFML/Graphics/Types.h>
    #include <SFML/System/Types.h>
    #include <SFML/System/Vector2.h>
    #include <SFML/Graphics/Rect.h>

typedef struct mouse_struct_menu {
    sfVector2f mouse;
    sfFloatRect start_bounds;
    sfFloatRect quit_bounds;
    sfFloatRect volup_bounds;
    sfFloatRect voldown_bounds;
} menu_mouse_t;

#endif /* MENU_BAR */
