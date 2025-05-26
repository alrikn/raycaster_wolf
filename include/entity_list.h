/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** entity_list.h
*/

#ifndef ENTITY_LIST
    #define ENTITY_LIST
    #include <SFML/Graphics/Rect.h>
    #include <SFML/Graphics/Types.h>
    #include <SFML/System/Types.h>
    #include <SFML/System/Vector2.h>
    #include <stdbool.h>

typedef struct core core_t;

typedef enum {
    SF_SPRITE,
    SF_RECTANGLE,
    SF_TEXT,
    MAX_ENTITY_SIZE,
} entity_type_t;

typedef enum {
    ENEMY,
    HUD_BG,
    HUD_FRAME,
    HUD_SCORE,
    HUD_HEALTH,
    HUD_TITLE,
    HUD_AMMO,
    HUD_WEAPON,
    HUD_CROSSHAIR,
    LAST_TYPE,
} context_type_t;

typedef enum {
    DRAW_FIRST,
    DRAW_LAST,
} draw_priority_t;

typedef struct entity_context {
    void *info;
    sfTexture *texture;
    context_type_t type;
    sfVector2f position;
    sfVector2f base_offset;
    draw_priority_t priority;
    sfFont *font;
    sfIntRect texture_rect;
    sfIntRect entity_rect;
    int rect_counter;
} entity_context_t;

typedef struct entity entity_t;

typedef void *(*create_fn_t)();
typedef void (*draw_fn_t)(sfRenderWindow *, void *, void *);
typedef void (*destroy_fn_t)(void *);

typedef bool (*init_fn_t)(entity_t *, core_t *core);
typedef bool (*update_fn_t)(entity_t *, core_t *core);

typedef struct sf_fn_tuple {
    create_fn_t create;
    destroy_fn_t destroy;
    draw_fn_t draw;
} sf_fn_tuple_t;

typedef struct entity {
    void *data;
    entity_type_t entity_type;
    sf_fn_tuple_t sf_functions;
    init_fn_t init;
    update_fn_t update;
    sfClock *clock;
    entity_context_t *context;
    entity_t *next;
    entity_t *prev;
} entity_t;

#endif /* ENTITY_LIST */
