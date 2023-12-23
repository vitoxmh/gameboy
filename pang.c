#include<gb/gb.h>
#include <stdio.h>
#include "Peach.c"

#define PIXEL_WIDTH 8
#define PIXEL_HEIGHT 8
#define PEACH_TOTAL_TILE 16
unsigned char plx, ply;

struct objeto;


void player(UINT8 px, UINT8 py){

    UINT8 count = 0;


    set_sprite_data(0,PEACH_TOTAL_TILE,Peach);

    for(int i=0; i< PEACH_TOTAL_TILE; ++i){

         set_sprite_tile(i,i);

    }

    for(int y=0; y < 4; y++){

        for(int x=0; x < 4; x++){

            move_sprite(count, px + (x*8) , py + (y*8));

            count++;
        }

    }

    

}


void main(){
	
    plx = 30;
    ply = 120;
 
    player(50,50);
    SHOW_SPRITES;

    while(1){

        if(joypad() & J_LEFT){

                --plx;

        }

        if(joypad() & J_RIGHT){

                ++plx;

        }


         player(plx,ply);
         delay(5);

    }

  
   

}

