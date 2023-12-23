#include <gb/gb.h>
#include <gb/drawing.h>

// Datos de los tiles exportados desde GBTiles
unsigned char dino_tiles[] = {
    // Frame 1 (boca cerrada)
    0x00, 0x00, 0x1C, 0x1C, 0x3E, 0x3E, 0x7F, 0x7F,
    0x1C, 0x1C, 0x3E, 0x3E, 0x7F, 0x7F, 0xFF, 0xFF,
    0x7F, 0x7F, 0xFF, 0xFF, 0xE7, 0xE7, 0xC3, 0xC3,
    0x7E, 0x7E, 0x3C, 0x3C, 0x00, 0x00, 0x00, 0x00,

    // Frame 2 (boca abierta)
    0x00, 0x00, 0x1C, 0x1C, 0x3E, 0x3E, 0x7F, 0x7F,
    0x1C, 0x1C, 0x3E, 0x3E, 0x7F, 0x7F, 0xFF, 0xFF,
    0x7F, 0x7F, 0xFF, 0xFF, 0xE7, 0xE7, 0xC3, 0xC3,
    0x7E, 0x7E, 0x3C, 0x3C, 0x3C, 0x3C, 0x00, 0x00,
};

#define DINO_TILE_INDEX 0
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144

UINT8 dinoX = 40;
UINT8 dinoY = SCREEN_HEIGHT - 16;
UINT8 jumpHeight = 40;
UINT8 jumping = 0;
UINT8 frameCounter = 0;
UINT8 currentFrame = 0;  // 0 para el frame de boca cerrada, 1 para el frame de boca abierta

void init_sprites() {
    set_sprite_data(0, 2, dino_tiles);
    set_sprite_tile(0, DINO_TILE_INDEX);
    move_sprite(0, dinoX, dinoY);
    SHOW_SPRITES;
}

void update_game() {
    // Verifica si se ha presionado el botón A
    if (joypad() & J_A && !jumping) {
        jumping = 1;
        frameCounter = 0;  // Reinicia el contador al saltar
    }

    // Realiza la lógica del salto
    if (jumping) {
        if (dinoY > SCREEN_HEIGHT - jumpHeight) {
            dinoY--;
        } else {
            jumping = 0;
        }
    } else if (dinoY < SCREEN_HEIGHT - 16) {
        // Aplica gravedad si no está saltando
        dinoY++;
    }

    // Cambia de frame cada 10 ciclos de juego (ajusta según sea necesario)
    frameCounter++;
    if (frameCounter == 10) {
        // Cambia al siguiente frame
        currentFrame = (currentFrame == 0) ? 1 : 0;
        frameCounter = 0;
    }

    // Actualiza la posición del dinosaurio con el frame actual
    set_sprite_tile(0, DINO_TILE_INDEX + currentFrame);
    move_sprite(0, dinoX, dinoY);
}

void main() {
    init_sprites();

    while (1) {
        update_game();
        wait_vbl_done();
    }
}