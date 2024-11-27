#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "game.h"
#include "card.h"

// Load texture from file
SDL_Texture* load_texture(SDL_Renderer* renderer, const char* filepath) {
    SDL_Surface* surface = IMG_Load(filepath);
    if (!surface) {
        printf("Unable to load image: %s\n", IMG_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

// Draw card on screen
void draw_card(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y) {
    SDL_Rect cardRect = { x, y, 100, 150 };  // Card dimensions
    SDL_RenderCopy(renderer, texture, NULL, &cardRect);  // Render the texture
    SDL_RenderPresent(renderer);  // Update the window
}

// Animate card dealing: move cards from deck to player
void animate_card_dealing(SDL_Renderer* renderer, SDL_Texture* card_back, SDL_Texture* card_front, int start_x, int start_y, int end_x, int end_y) {
    int x = start_x, y = start_y;
    
    while (x != end_x || y != end_y) {
        SDL_RenderClear(renderer);  // Clear the screen
        
        // Draw the card back (simulate card facing down)
        draw_card(renderer, card_back, x, y);
        
        // Move the card position (simple linear animation)
        if (x < end_x) x += 10;  // Move x right
        if (y < end_y) y += 10;  // Move y down
        
        SDL_Delay(20);  // Delay for animation effect
    }
    
    // After the card reaches the player, flip it to the front
    draw_card(renderer, card_front, end_x, end_y);
    SDL_Delay(500);  // Show the front for a moment
}

// Main game logic to handle animation
void start_game(SDL_Renderer* renderer, SDL_Texture* card_back, SDL_Texture* card_front) {
    // Example of dealing cards to players with animation
    animate_card_dealing(renderer, card_back, card_front, 100, 100, 300, 100);  // Move card from (100,100) to (300,100)
    animate_card_dealing(renderer, card_back, card_front, 100, 100, 300, 200);  // Another card
}

// Initialize SDL and start the game with 2D animation
void run_animation() {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    
    // Initialize SDL and create window and renderer
    if (SDL_Init(SDL_INIT_VIDEO) != 0 || IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        printf("SDL Initialization failed: %s\n", SDL_GetError());
        return;
    }
    
    window = SDL_CreateWindow("Liar's Deck Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    // Load card images
    SDL_Texture* card_back = load_texture(renderer, "assets/card_back.png");
    SDL_Texture* card_front = load_texture(renderer, "assets/card_front.png");
    
    // Start the game and animate card dealing
    start_game(renderer, card_back, card_front);

    SDL_Delay(2000);  // Wait before closing
    
    // Clean up
    SDL_DestroyTexture(card_back);
    SDL_DestroyTexture(card_front);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
}

int main() {
    run_animation();
    return 0;
}
