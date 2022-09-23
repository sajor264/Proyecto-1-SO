#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "logic.c"

#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1800

int main(int argc, char *argv[]){
    srand (time(NULL));

    int difficulty, matrixSize;
    struct Matrix* matrix;

    // Asks for the matrix size
    printf("Seleccione la dificultad:\n1-Facil\n2-Medio\n3-Dificil\n");
    printf("Dificultad: ");
    scanf("%d", &difficulty);
    printf("--------------------------\n\n");

    switch (difficulty){
        case 1:
            matrixSize = 10;
            matrix = createMatrix(matrixSize);
            break;
        case 2:
            matrixSize = 20;
            matrix = createMatrix(matrixSize);
            break;
        case 3:
            matrixSize = 30;
            matrix = createMatrix(matrixSize);
            break;
        default:
            break;
    }


    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    
    SDL_Window* win = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
 
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
 
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
 
    // creates heroe texture
    SDL_Surface* surface = IMG_Load("Images/heroe.png");
    SDL_Texture* heroe = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates monster texture
    surface = IMG_Load("Images/monster.png");
    SDL_Texture* monster = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates room texture
    surface = IMG_Load("Images/room.jpg");
    SDL_Texture* roomTexture = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates trap dialog texture
    surface = IMG_Load("Images/trapDialog.jpg");
    SDL_Texture* trapDialog = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates treasure dialog texture
    surface = IMG_Load("Images/treasureDialog.jpg");
    SDL_Texture* treasureDialog = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates door1 texture
    surface = IMG_Load("Images/door.png");
    SDL_Texture* door1 = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates door2 texture
    surface = IMG_Load("Images/door.png");
    SDL_Texture* door2 = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates door3 texture
    surface = IMG_Load("Images/door.png");
    SDL_Texture* door3 = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates openedTreasure texture
    surface = IMG_Load("Images/openedTreasure.png");
    SDL_Texture* openedTreasure = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates closedTreasure texture
    surface = IMG_Load("Images/closedTreasure.png");
    SDL_Texture* closedTreasure = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates closedTrap texture
    surface = IMG_Load("Images/closedTreasure.png");
    SDL_Texture* closedTrap = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
 
    // Let us control our image position
    SDL_Rect heroeRect;
    SDL_Rect monsterRect;
    SDL_Rect trapDialogRect;
    SDL_Rect treasureDialogRect;
    SDL_Rect door1Rect;
    SDL_Rect door2Rect;
    SDL_Rect door3Rect;
    SDL_Rect closedTreasureRect;
    SDL_Rect closedTrapRect;
    SDL_Rect openedTreasureRect;
 
    // connects our textures with Rects to control position
    SDL_QueryTexture(heroe, NULL, NULL, &heroeRect.w, &heroeRect.h);
    SDL_QueryTexture(monster, NULL, NULL, &monsterRect.w, &monsterRect.h);
    SDL_QueryTexture(trapDialog, NULL, NULL, &trapDialogRect.w, &trapDialogRect.h);
    SDL_QueryTexture(treasureDialog, NULL, NULL, &treasureDialogRect.w, &treasureDialogRect.h);
    SDL_QueryTexture(door1, NULL, NULL, &door1Rect.w, &door1Rect.h);
    SDL_QueryTexture(door2, NULL, NULL, &door2Rect.w, &door2Rect.h);
    SDL_QueryTexture(door3, NULL, NULL, &door3Rect.w, &door3Rect.h);
    SDL_QueryTexture(closedTreasure, NULL, NULL, &closedTreasureRect.w, &closedTreasureRect.h);
    SDL_QueryTexture(closedTrap, NULL, NULL, &closedTrapRect.w, &closedTrapRect.h);
    SDL_QueryTexture(openedTreasure, NULL, NULL, &openedTreasureRect.w, &openedTreasureRect.h);
 
    // adjust height and width of our image box.
    heroeRect.w /= 4;
    heroeRect.h /= 4;

    monsterRect.w /= 3;
    monsterRect.h /= 3;

    trapDialogRect.w /= 1;
    trapDialogRect.h /= 1;

    treasureDialogRect.w /= 1;
    treasureDialogRect.h /= 1;

    door1Rect.w /= 5;
    door1Rect.h /= 5;

    door2Rect.w /= 5;
    door2Rect.h /= 5;

    door3Rect.w /= 5;
    door3Rect.h /= 5;

    closedTreasureRect.w /= 12;
    closedTreasureRect.h /= 12;

    closedTrapRect.w /= 12;
    closedTrapRect.h /= 12;

    openedTreasureRect.w /= 4;
    openedTreasureRect.h /= 4;

    // sets initial x-position of object
    heroeRect.x = (WINDOW_WIDTH - heroeRect.w) / 2;
    monsterRect.x = ((WINDOW_WIDTH - monsterRect.w) / 2) + 150;
    trapDialogRect.x = (WINDOW_WIDTH - trapDialogRect.w) / 2;
    treasureDialogRect.x = (WINDOW_WIDTH - treasureDialogRect.w) / 2;
    closedTreasureRect.x = (WINDOW_WIDTH - closedTreasureRect.w) - 300;
    closedTrapRect.x = (WINDOW_WIDTH - closedTrapRect.w) - 300;
    openedTreasureRect.x = (WINDOW_WIDTH - openedTreasureRect.w) - 300;
    
    
    // sets initial y-position of object
    heroeRect.y = (WINDOW_HEIGHT - heroeRect.h) / 2;
    monsterRect.y = (WINDOW_HEIGHT - monsterRect.h) / 2;
    trapDialogRect.y = (WINDOW_HEIGHT - trapDialogRect.h) - 50;
    treasureDialogRect.y = (WINDOW_HEIGHT - treasureDialogRect.h) - 50;
    closedTreasureRect.y = (WINDOW_HEIGHT - closedTreasureRect.h) - 200;
    closedTrapRect.y = (WINDOW_HEIGHT - closedTrapRect.h) - 200;
    openedTreasureRect.y = (WINDOW_HEIGHT - openedTreasureRect.h) - 200;
   
 
    // controls animation loop
    int close = 0;

    // Create Map and Rooms
    Rooms *rooms = malloc(sizeof(struct Rooms));
    createMap(matrix, rooms);
    
    //printMatrix(matrix);
    // for(int i = 0; i < matrixSize; i++){
    // printf("POS:\tx = %d y = %d\n N1:\tx = %d y = %d\n N2:\tx = %d y = %d\n N3:\tx = %d y = %d\n COFFER TYPE:\t %d\n ROOM TYPE:\t%d\n\n", rooms[i] -> pos[0], rooms[i] -> pos[1], rooms[i] -> neighbour1[0], rooms[i] -> neighbour1[1], rooms[i] -> neighbour2[0], rooms[i] -> neighbour2[1], rooms[i] -> neighbour3[0], rooms[i] -> neighbour3[1], rooms[i] -> cofferType, rooms[i] -> type);
    // } 

    Hero heroStruct;
    heroStruct.posX = rooms[0] -> pos[0];
    heroStruct.posY = rooms[0] -> pos[1];
    heroStruct.life = 5;
    heroStruct.attack = 1;

    int index = indexCurrentRoom(rooms, matrixSize, heroStruct.posX, heroStruct.posY);
    int n1 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour1[0],rooms[index]->neighbour1[1]);
    int n2 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour2[0],rooms[index]->neighbour2[1]);
    int n3 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour3[0],rooms[index]->neighbour3[1]);
    int roomCofferType = rooms[index] -> cofferType;
    bool isCofferOpened = rooms[index] -> isCofferOpened;
    int monsterID = rooms[index] -> monsterId;

    while (!close) {
        SDL_Event event;

        if(heroStruct.life == 0){
            printf("GAME OVER\n");
            close = 1;
        }
        if((heroStruct.posX == rooms[matrixSize-1] -> pos[0]) && (heroStruct.posY == rooms[matrixSize-1] -> pos[1])){
            printf("\n\nYOU WON!!\n\n");
            close = 1;
        }
 
        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
 
            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;
 
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                    if(n1 == 2 || n2 == 2 || n3 == 2){
                        heroStruct.posX--;
                        index = indexCurrentRoom(rooms, matrixSize, heroStruct.posX,heroStruct.posY);
                        n1 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour1[0],rooms[index]->neighbour1[1]);
                        n2 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour2[0],rooms[index]->neighbour2[1]);
                        n3 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour3[0],rooms[index]->neighbour3[1]);
                        roomCofferType = rooms[index] -> cofferType;
                        isCofferOpened = rooms[index] -> isCofferOpened;
                        monsterID = rooms[index] -> monsterId;
                    }
                    break;
                case SDL_SCANCODE_A:
                    if(n1 == 0 || n2 == 0 || n3 == 0){
                        heroStruct.posY--;
                        index = indexCurrentRoom(rooms, matrixSize, heroStruct.posX,heroStruct.posY);
                        n1 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour1[0],rooms[index]->neighbour1[1]);
                        n2 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour2[0],rooms[index]->neighbour2[1]);
                        n3 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour3[0],rooms[index]->neighbour3[1]);
                        roomCofferType = rooms[index] -> cofferType;
                        isCofferOpened = rooms[index] -> isCofferOpened;
                        monsterID = rooms[index] -> monsterId;
                    }
                    break;
                case SDL_SCANCODE_S:
                    if(n1 == 3 || n2 == 3 || n3 == 3){
                        heroStruct.posX++;
                        index = indexCurrentRoom(rooms, matrixSize, heroStruct.posX,heroStruct.posY);
                        n1 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour1[0],rooms[index]->neighbour1[1]);
                        n2 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour2[0],rooms[index]->neighbour2[1]);
                        n3 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour3[0],rooms[index]->neighbour3[1]);
                        roomCofferType = rooms[index] -> cofferType;
                        isCofferOpened = rooms[index] -> isCofferOpened;
                        monsterID = rooms[index] -> monsterId;
                    }
                    break;
                case SDL_SCANCODE_D:
                    if(n1 == 1 || n2 == 1 || n3 == 1){
                        heroStruct.posY++;
                        index = indexCurrentRoom(rooms, matrixSize, heroStruct.posX,heroStruct.posY);
                        n1 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour1[0],rooms[index]->neighbour1[1]);
                        n2 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour2[0],rooms[index]->neighbour2[1]);
                        n3 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour3[0],rooms[index]->neighbour3[1]);
                        roomCofferType = rooms[index] -> cofferType;
                        isCofferOpened = rooms[index] -> isCofferOpened;
                        monsterID = rooms[index] -> monsterId;
                    }
                    break;
                case SDL_SCANCODE_E:                    
                    if(rooms[index] -> cofferType == 0){
                        SDL_RenderCopy(rend, treasureDialog, NULL, &treasureDialogRect);
                        rooms[index] -> isCofferOpened = true;
                        isCofferOpened = true;
                        SDL_RenderPresent(rend);
                        if((rand() % 2) == 0){
                            heroStruct.attack++;
                        } else {
                            heroStruct.life++;
                        }
                        sleep(2);
                    }

                    if(rooms[index] -> cofferType == 1){
                        SDL_RenderCopy(rend, trapDialog, NULL, &trapDialogRect);
                        rooms[index] -> isCofferOpened = true;
                        isCofferOpened = true;
                        SDL_RenderPresent(rend);
                        heroStruct.life--;
                        sleep(2);
                    }
                    break;
                default:
                    break;
                }
            }
        }
 
        //clears the screen
        SDL_SetRenderDrawColor(rend, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(rend);

        // Renderiza el cuarto
        SDL_RenderCopy(rend, roomTexture, NULL, NULL);
           
        // Renderiza las puertas
        if(n1 == 0){
            // Izquierda
             door1Rect.x = 80;
             door1Rect.y =(WINDOW_HEIGHT -  door1Rect.h) / 2;
             SDL_RenderCopy(rend, door1, NULL, &door1Rect);
           
        }else if(n1 == 1){
            // Derecha
             door1Rect.x = (WINDOW_WIDTH -  door1Rect.w) - 80;
             door1Rect.y =(WINDOW_HEIGHT -  door1Rect.h) / 2;
             SDL_RenderCopy(rend, door1, NULL, &door1Rect);
            
        }else if(n1 == 2){
            // Arriba
             door1Rect.x = (WINDOW_WIDTH -  door1Rect.w) / 2;
             door1Rect.y =0;
             SDL_RenderCopy(rend, door1, NULL, &door1Rect);
            
        }else if(n1 == 3){
            // Abajo
             door1Rect.x = (WINDOW_WIDTH -  door1Rect.w) / 2;
             door1Rect.y =(WINDOW_HEIGHT -  door1Rect.h);
             SDL_RenderCopy(rend, door1, NULL, &door1Rect);
        
        }

        if(n2 == 0){
             door2Rect.x = 80;
             door2Rect.y =(WINDOW_HEIGHT -  door2Rect.h) / 2;
             SDL_RenderCopy(rend, door2, NULL, &door2Rect);
            
        }else if(n2 == 1){
             door2Rect.x = (WINDOW_WIDTH -  door2Rect.w) - 80;
             door2Rect.y =(WINDOW_HEIGHT -  door2Rect.h) / 2;
            SDL_RenderCopy(rend, door2, NULL, &door2Rect);

        }else if(n2 == 2){
             door2Rect.x = (WINDOW_WIDTH -  door2Rect.w) / 2;
             door2Rect.y =0;
            SDL_RenderCopy(rend, door2, NULL, &door2Rect);
            
        }else if(n2 == 3){
             door2Rect.x = (WINDOW_WIDTH -  door2Rect.w) / 2;
             door2Rect.y =(WINDOW_HEIGHT -  door2Rect.h);
            SDL_RenderCopy(rend, door2, NULL, &door2Rect);
        
        }

        if(n3 == 0){
             door3Rect.x = 80;
             door3Rect.y =(WINDOW_HEIGHT -  door3Rect.h) / 2;
             SDL_RenderCopy(rend, door3, NULL, &door3Rect);
           
        }else if(n3 == 1){
             door3Rect.x = (WINDOW_WIDTH -  door3Rect.w) - 80;
             door3Rect.y =(WINDOW_HEIGHT -  door3Rect.h) / 2;
            SDL_RenderCopy(rend, door3, NULL, &door3Rect);

        }else if(n3 == 2){
             door3Rect.x = (WINDOW_WIDTH -  door3Rect.w) / 2;
             door3Rect.y =0;
            SDL_RenderCopy(rend, door3, NULL, &door3Rect);
            
        }else if(n3 == 3){
            door3Rect.x = (WINDOW_WIDTH -  door3Rect.w) / 2;
            door3Rect.y =(WINDOW_HEIGHT -  door3Rect.h);
            SDL_RenderCopy(rend, door3, NULL, &door3Rect);
        
        }

        // Renderiza los tesoros / trampas
        if(roomCofferType == 0 && !isCofferOpened){
            SDL_RenderCopy(rend, closedTreasure, NULL, &closedTreasureRect);
        } else if(roomCofferType == 0 && isCofferOpened){
            SDL_RenderCopy(rend, openedTreasure, NULL, &openedTreasureRect);
        }
        if(roomCofferType == 1 && !isCofferOpened){
            SDL_RenderCopy(rend, closedTreasure, NULL, &closedTreasureRect);
        } else if(roomCofferType == 1 && isCofferOpened){
            SDL_RenderCopy(rend, openedTreasure, NULL, &openedTreasureRect);
        }

        // Renderiza los monstruos
        if(monsterID >= 0){
            SDL_RenderCopy(rend, monster, NULL, &monsterRect);
        }

        // Renderiza el heroe
        SDL_RenderCopy(rend, heroe, NULL, &heroeRect);
      
        
        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(rend);
 
        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }
 
    // destroy textures
    SDL_DestroyTexture(heroe);
    SDL_DestroyTexture(roomTexture);
    SDL_DestroyTexture(trapDialog);
    SDL_DestroyTexture(treasureDialog);
    SDL_DestroyTexture(monster);
    SDL_DestroyTexture(door1);
    SDL_DestroyTexture(door2);
    SDL_DestroyTexture(door3);
    SDL_DestroyTexture(openedTreasure);
    SDL_DestroyTexture(closedTreasure);
    SDL_DestroyTexture(closedTrap);

    // destroy renderer
    SDL_DestroyRenderer(rend);
 
    // destroy window
    SDL_DestroyWindow(win);
     
    // close SDL
    SDL_Quit();
 
    return 0;
}