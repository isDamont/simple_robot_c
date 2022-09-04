#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <time.h>

#define SIZE 9
#define W 119
#define A 97
#define S 115
#define D 100
#define ESC 27

#define MAX_FPS 100

int fps(){
    return 1000/MAX_FPS;
}

struct interface{
    char ** field;
    char * player;
} robot;


void set_player_settings(){
    struct interface *player = &robot;
    robot.player = (char*)malloc(sizeof(char));
    *player->player = 'O';
}

void set_player_position(int x, int y){
    struct interface *field = &robot;
    field->field[x-1][y-1]=*field->player;
}

void player_delete(){
    free(robot.player);
}

void field_init(){
    struct interface *field = &robot;
    robot.field = (char**)malloc(SIZE * sizeof(char*));
    for (int i = 0; i < SIZE; ++i) {
        robot.field[i] = (char*)malloc(SIZE*sizeof(char));
    }

}

void fill_field(){
    struct interface *field = &robot;
    for (int x = 0; x < SIZE; ++x) {
        for (int i = 0; i < SIZE; ++i) {
            field->field[i][x] = '_';
        }
    }
}

void screen(){
    for (int x = 0; x < SIZE; ++x) {
        printf("\n");
        for (int i = 0; i < SIZE; ++i) {
            printf("%C", robot.field[i][x]);
        }
    }
}

void clear(){
    system("cls");
}

void field_delete(){
    for(int i = 0; i < SIZE; i++) {
        free(robot.field[i]);
    }
    free(robot.field);
}

void fps_is(){
    printf("\n");
    int x = fps();
    int time_now = clock();
    while(time_now%x!=0){
        x++;
    }
    int fps = 1000/x;
    printf("fps: %i", fps);
}

int main() {
    int x_position = 5;
    int y_position = 5;
    int capture;

    field_init();
    set_player_settings();

    //game cycle
    while (1){
        if(clock() % fps() == 0){
        fill_field();
        set_player_position(x_position,y_position);
        fps_is();
        screen();
        clear();

            if(kbhit()){
                capture = getch();
                if(capture == ESC){ break;}
                if(capture == W && y_position != 1){ set_player_position(x_position,y_position--);}
                if(capture == A && x_position != 1){ set_player_position(x_position--,y_position);}
                if(capture == S && y_position != 9){ set_player_position(x_position,y_position++);}
                if(capture == D && x_position != 9){ set_player_position(x_position++,y_position);}
            }
        }
    }
    //game cycle!

    field_delete();
    player_delete();
}

