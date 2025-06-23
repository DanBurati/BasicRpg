// BasicRpg version: 1
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<time.h>
#define HEIGHT 21
#define WIDTH 61

struct game {
    int mode;
};

struct enemy{
    int x,y;
};

struct village{
    int x,y;
};

struct player {
    int x,y;
    int life;
    int gold;
};

void field(char grid[HEIGHT][WIDTH]){
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            if ((i == 0 || i == HEIGHT-1) && (j == 0 || j == WIDTH-1)) grid[i][j] = '#';
            else if (i == 0 || i == HEIGHT-1) grid[i][j] = '-';
            else if (j == 0 || j == WIDTH-1) grid[i][j] = '|';
            else grid[i][j] = ' ';
        }
    }
}

void printer(char grid[HEIGHT][WIDTH]){
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
                printf("%c", grid[i][j]);
        }
        printf("\n");
    }
}

void enemy_move(struct enemy *e) {
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };
    int dir = rand() % 4;
    int nx = e->x + dx[dir];
    int ny = e->y + dy[dir];
    if (nx > 0 && nx < WIDTH - 1) e->x = nx;
    if (ny > 0 && ny < HEIGHT - 1) e->y = ny;
}

int main (void){
    struct game main = {1};
    

    srand(time(NULL));
    char grid[HEIGHT][WIDTH];
    struct player p = {1,19,10,0};
    int e_num = 100;
    struct enemy e[e_num];
    for (int i = 0; i < e_num; i++) {
        e[i].x = rand() % 59 + 1;
        e[i].y = rand() % 19 + 1;
    }
    struct village v[2];
    v[0].x = 20;
    v[0].y = 5;
    v[1].x = 40;
    v[1].y = 16;

    int command;
    while(1){
if (main.mode == 2) {
    system("clear");
    printf("===Battle===\n");
    printf("YOU ENCOUNT ENEMY!\n");
    p.life--;
    p.gold++;
    sleep(1);
    main.mode = 1;
    continue;
}
if (main.mode == 3) {
    system("clear");
    printf("=== VILLAGE ===\n");
    printf("Do you want to go to Hotel ($5)? (y/n): ");
    int ans = getchar();
    while (getchar() != '\n');

    if(ans == 'y' && p.gold >= 5){
        p.life = 10;
        p.gold -= 5;
        printf("You had a good rest!\n");
    } else if(ans == 'y' && p.gold < 5){
        printf("You don't have enough money. Fuck Off.\n");
    } else {
        printf("Then get out.\n");
    }

    sleep(1);
    main.mode = 1;
    continue;
}

        system("clear");
        field(grid);
        grid[p.y][p.x] = 'A';
        for (int i = 0; i < e_num; i++) {
            grid[e[i].y][e[i].x] = 'e';
            enemy_move(&e[i]);
            if (p.x == e[i].x && p.y == e[i].y) {
                main.mode = 2;
            }
        }
        for (int i = 0; i < 2; i++) {
            grid[v[i].y][v[i].x] = 'V';
            if (p.x == v[i].x && p.y == v[i].y) {
                main.mode = 3;
            }
        }
        printf("Life:%d/10 | Gold:%d\n",p.life,p.gold);
        printer(grid);
        command = getchar();
        if (command == 'a' && p.x > 1) p.x--;
        else if (command == 'd' && p.x < WIDTH - 2) p.x++;
        else if (command == 'w' && p.y > 1) p.y--;
        else if (command == 's' && p.y < HEIGHT - 2) p.y++;
        else if (command == 'q') break;
        usleep(10000);
    }
}