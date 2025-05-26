/*
** EPITECH PROJECT, 2025
** maze_generator
** File description:
** logic
*/

#include "my.h"
#include "time.h"

void push_stack(size_t col, size_t row, maze_state_t *state)
{
    state->col_stack[state->stack_index] = col;
    state->row_stack[state->stack_index] = row;
    state->stack_index++;
}

void pop_stack(maze_state_t *state)
{
    if (state->stack_index > 0) {
        state->stack_index--;
    }
}

/*
** this means that maze at maze[1][1] will always be open,
** so if you have a player, set hime here
** you can change the initlai spot if you want
*/
void init_maze(char array[][SIZE], maze_state_t *state)
{
    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            array[i][j] = WALL;
        }
    }
    state->current_col = 1;
    state->current_row = 1;
    array[state->current_col][state->current_row] = SPACE;
    push_stack(state->current_col, state->current_row, state);
}

static void reset_directions(maze_state_t *state)
{
    for (int i = 0; i < DIR; ++i) {
        state->directions[i] = 0;
    }
    state->remaining_directions = DIR;
}

/*
* pair values are column,
* impair are rows
*/
void set_values(size_t values[][VALUES], size_t col, size_t row)
{
    size_t possibilities[DIR][VALUES] = {
    {col, row + 1, col, row + 2, col, row + 3, col - 1, row + 1,
        col + 1, row + 1, col + 1, row + 2, col - 1, row + 2,
        col - 1, row + 3, col + 1, row + 3, row < (SIZE - 2)},
    {col, row - 1, col, row - 2, col, row - 3, col - 1, row - 1,
        col - 1, row - 2, col - 1, row - 3, col + 1, row - 1,
        col + 1, row - 2, col + 1, row - 3, row > 1},
    {col - 1, row, col - 2, row, col - 3, row, col - 1, row + 1,
        col - 2, row + 1, col - 3, row + 1, col - 1, row - 1,
        col - 2, row - 1, col - 3, row - 1, col > 1},
    {col + 1, row, col + 2, row, col + 3, row, col + 1, row + 1,
        col + 2, row + 1, col + 3, row + 1, col + 1, row - 1,
        col + 2, row - 1, col + 3, row - 1, col < (SIZE - 2)}
    };

    for (size_t x = 0; x < DIR; ++x) {
        for (size_t y = 0; y < VALUES; ++y) {
            values[x][y] = possibilities[x][y];
        }
    }
}

static int get_valid_direction(maze_state_t *state)
{
    int dir;

    while (state->remaining_directions > 0) {
        dir = rand() % DIR;
        if (!state->directions[dir]) {
            state->directions[dir] = 1;
            state->remaining_directions--;
            return dir;
        }
    }
    return -1;
}

static int try_create_path(char array[][SIZE],
    maze_state_t *state, int direction)
{
    size_t values[DIR][VALUES];
    size_t col;
    size_t row;

    set_values(values, state->current_col, state->current_row);
    if (direction == -1 || !values[direction][18])
        return 0;
    for (int i = 0; i < 9; ++i) {
        col = values[direction][i * 2];
        row = values[direction][i * 2 + 1];
        if (col >= SIZE || row >= SIZE)
            return 0;
        if (array[col][row] != WALL)
            return 0;
    }
    state->current_col = values[direction][0];
    state->current_row = values[direction][1];
    array[state->current_col][state->current_row] = SPACE;
    return 1;
}

static void backtrack(maze_state_t *state)
{
    if (state->stack_index > 0) {
        pop_stack(state);
        state->current_col = state->col_stack[state->stack_index];
        state->current_row = state->row_stack[state->stack_index];
    }
}

static bool direction_parse(maze_state_t *state, char array[][SIZE])
{
    bool path_created = false;
    int dir;

    while (state->remaining_directions > 0) {
        dir = get_valid_direction(state);
        if (try_create_path(array, state, dir)) {
            push_stack(state->current_col, state->current_row, state);
            path_created = true;
            return path_created;
        }
    }
    return path_created;
}

void maze_generator(char array[SIZE][SIZE])
{
    maze_state_t state = {0};
    int path_created = 0;

    srand(time(NULL));
    init_maze(array, &state);
    push_stack(state.current_col, state.current_row, &state);
    while (state.stack_index > 0) {
        reset_directions(&state);
        path_created = direction_parse(&state, array);
        if (!path_created)
            backtrack(&state);
    }
}
