#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

#define NY 30
#define NX 10

#define FPS 60
#define FRAME_NS (1000000000L / FPS)

char tiles[NX][NY];

typedef struct POS
{
    int pos_x;
    int pos_y;
    int dest;
    int tail;
    int tail_x[99];
    int tail_y[99];
} p;

typedef struct FOOD
{
    int pos_x;
    int pos_y;
} f;

void print_board(p *player, f *food)
{
    for (int i = 0; i < NX; i++)
    {
        for (int j = 0; j < NY; j++)
        {
            char c = '#';

            for (int k = 0; k < player->tail; k++)
                if (i == player->tail_x[k] && j == player->tail_y[k])
                    c = 'P';

            if (i == player->pos_x && j == player->pos_y)
                c = 'P';

            if (i == food->pos_x && j == food->pos_y)
                c = 'F';

            putchar(c);
        }
        putchar('\n');
    }
}

void init_board()
{
    for (int i = 0; i < NX; i++)
    {
        for (int j = 0; j < NY; j++)
        {
            tiles[i][j] = '#';
        }
    }
}

void death(p *player)
{
    if (player->pos_x > NX || player->pos_x < 0)
    {
        end();
    }
    if (player->pos_y > NY || player->pos_y < 0)
    {
        end();
    }
    for (int k = 1; k < player->tail; k++)
        if (player->pos_x == player->tail_x[k] && player->pos_y == player->tail_y[k])
            end();
}

void move(p *player, int *plays)
{
    (*plays)++;
    int limit = (player->dest == 2 || player->dest == 4) ? 12 : 24;

    if (*plays >= limit)
    {
        for (int k = player->tail; k > 0; k--)
        {
            player->tail_x[k] = player->tail_x[k - 1];
            player->tail_y[k] = player->tail_y[k - 1];
        }
        if (player->tail > 0)
        {
            player->tail_x[0] = player->pos_x;
            player->tail_y[0] = player->pos_y;
        }

        if (player->dest == 1)
            player->pos_x--;
        if (player->dest == 2)
            player->pos_y--;
        if (player->dest == 3)
            player->pos_x++;
        if (player->dest == 4)
            player->pos_y++;

        *plays = 0;
        death(player);
    }
}

void new_food(f *food)
{

    food->pos_x = rand() % NX;
    food->pos_y = rand() % NY;
}

void ate(p *player, f *food)
{
    if (player->pos_x == food->pos_x && player->pos_y == food->pos_y)
    {
        player->tail++;
        player->tail_x[player->tail - 1] = player->pos_x;
        player->tail_y[player->tail - 1] = player->pos_y;
        new_food(food);
    }
}

int main()
{
    srand(time(0));
    p player;
    f food;
    player.pos_x = rand() % 2 + 4;
    player.pos_y = rand() % 2 + 14;
    player.dest = rand() % 4 + 1;
    player.tail = 0;
    int plays = 0;
    init_board();
    new_food(&food);

    for (;;)
    {
        long start = clock();

        ate(&player, &food);
        if (_kbhit())
        {
            int key = _getch();

            if (key == 'w')
            {
                player.dest = 1;
            }
            if (key == 'a')
            {
                player.dest = 2;
            }
            if (key == 's')
            {
                player.dest = 3;
            }
            if (key == 'd')
            {
                player.dest = 4;
            }
        }

        move(&player, &plays);
        system("cls");
        print_board(&player, &food);

        while (1)
        {
            long now = clock();
            long elapsed_ns = (now - start) * (1000000000L / CLOCKS_PER_SEC);
            if (elapsed_ns >= FRAME_NS)
                break;
        }
    }

    return 0;
}

void end()
{
    system("cls");
    printf("ded");
    exit(0);
}