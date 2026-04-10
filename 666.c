#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>   // for _kbhit(), _getch()
#include <windows.h> // for Sleep()

// --- Macro Definitions ---
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define MAX_WORDS_ON_SCREEN 10 // Maximum words on screen at once

// --- Word Bank ---
const char *WORD_BANK[] = {
    "cat", "dog", "sky", "red", "blue", 
    "code", "java", "ruby", "perl", "unix",
    "linux", "apple", "hello", "world", "pixel",
    "pointer", "struct", "system", "memory", "random"
};
const int WORD_BANK_SIZE = 20;

// --- Structure Definitions ---
// 1. Represents a falling word on screen
typedef struct {
    char text[20];       // Word content
    int x;               // X coordinate (column)
    int y;               // Y coordinate (row)
    int length;          // Word length
    int typedIndex;      // How many letters have been typed correctly
    int active;          // Is active (1 = falling, 0 = inactive)
    int speedCounter;    // Controls falling rhythm
} Word;

// --- Global Variables ---
Word activeWords[MAX_WORDS_ON_SCREEN]; // Array to manage words on screen
char screenBuffer[SCREEN_HEIGHT][SCREEN_WIDTH + 1]; // Screen buffer
int score = 0;
int gameLevel = 1;
int fallSpeedDelay = 200; // Game loop delay (milliseconds)
int gameOver = 0;

// --- Function Declarations ---
void initGame();
void drawScreen();
void updateGame();
void handleInput();
void spawnWord();

int main() {
    // Random seed
    srand((unsigned int)time(NULL));

    // Removed leaderboard display
    printf("\nPress any key to start game...\n");
    _getch();

    initGame();

    // --- Main Game Loop ---
    while (!gameOver) {
        drawScreen();   // 1. Draw screen
        handleInput();  // 2. Handle input
        updateGame();   // 3. Update game logic
        Sleep(fallSpeedDelay); // 4. Delay
    }

    // Game Over
    system("cls");
    printf("\n\n\n");
    printf("=============================\n");
    printf("         GAME OVER!         \n");
    printf("      Final Score: %d       \n", score);
    printf("=============================\n");
    
    // Removed score saving functionality

    printf("\nPress any key to exit...\n");
    _getch();
    return 0;
}

// --- Function Implementations ---

// Initialize game data
void initGame() {
    score = 0;
    gameLevel = 1;
    fallSpeedDelay = 200;
    gameOver = 0;
    
    // Initialize all word slots as inactive
    for (int i = 0; i < MAX_WORDS_ON_SCREEN; i++) {
        activeWords[i].active = 0;
    }
}

// Core: Spawn a new word
void spawnWord() {
    // 1. Find an available slot
    int slot = -1;
    for (int i = 0; i < MAX_WORDS_ON_SCREEN; i++) {
        if (activeWords[i].active == 0) {
            slot = i;
            break;
        }
    }

    // If no available slot, or reached max words allowed by difficulty
    int maxWordsAllowed = 1 + (gameLevel / 2);
    if (maxWordsAllowed > MAX_WORDS_ON_SCREEN) maxWordsAllowed = MAX_WORDS_ON_SCREEN;
    
    // Count current active words
    int currentCount = 0;
    for(int i=0; i<MAX_WORDS_ON_SCREEN; i++) if(activeWords[i].active) currentCount++;

    if (slot != -1 && currentCount < maxWordsAllowed) {
        // Generate new word
        int wordIdx = rand() % WORD_BANK_SIZE;
        // Difficulty: higher levels get longer words
        if (gameLevel > 5) {
             wordIdx = 10 + rand() % (WORD_BANK_SIZE - 10);
        }

        strcpy(activeWords[slot].text, WORD_BANK[wordIdx]);
        activeWords[slot].length = strlen(activeWords[slot].text);
        activeWords[slot].x = rand() % (SCREEN_WIDTH - 15); // Random X position
        activeWords[slot].y = 0; // Start from top
        activeWords[slot].typedIndex = 0; // No letters typed yet
        activeWords[slot].active = 1;
        activeWords[slot].speedCounter = 0;
    }
}

// Render data to 2D array, then print
void drawScreen() {
    // 1. Clear buffer (fill with spaces)
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            screenBuffer[i][j] = ' ';
        }
        screenBuffer[i][SCREEN_WIDTH] = '\0'; // String terminator
    }

    // 2. Fill buffer with words
    for (int i = 0; i < MAX_WORDS_ON_SCREEN; i++) {
        Word *w = &activeWords[i]; 

        if (w->active) {
            int drawY = w->y;
            if (drawY >= 0 && drawY < SCREEN_HEIGHT) {
                // Write each character to 2D array
                for (int k = 0; k < w->length; k++) {
                    int drawX = w->x + k;
                    if (drawX < SCREEN_WIDTH) {
                        // Change correctly typed letters to underscore
                        if (k < w->typedIndex) {
                            screenBuffer[drawY][drawX] = '_';
                        } else {
                            screenBuffer[drawY][drawX] = w->text[k];
                        }
                    }
                }
            }
        }
    }

    // 3. Draw status bar at bottom
    sprintf(screenBuffer[SCREEN_HEIGHT-1], " Score: %d | Level: %d | Speed: %dms (Type to play)", score, gameLevel, fallSpeedDelay);

    // 4. Refresh screen
    system("cls");
    
    // Print all lines at once
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        printf("%s\n", screenBuffer[i]);
    }
}

// Handle user input
void handleInput() {
    if (_kbhit()) { // Check if key pressed
        char ch = _getch(); // Read key
        
        // Check all active words for match
        for (int i = 0; i < MAX_WORDS_ON_SCREEN; i++) {
            Word *w = &activeWords[i];
            
            if (w->active) {
                // Get the current target letter
                char targetChar = w->text[w->typedIndex];
                
                if (ch == targetChar) {
                    w->typedIndex++; // Move to next letter
                    
                    // Check if entire word is completed
                    if (w->typedIndex >= w->length) {
                        w->active = 0; // Remove word
                        score += 10;   // Add points
                        
                        // Level up logic
                        if (score % 50 == 0) {
                            gameLevel++;
                            if (fallSpeedDelay > 50) fallSpeedDelay -= 10; // Increase speed
                        }
                    }
                    // Only match first eligible word per keypress
                    break; 
                }
            }
        }
    }
}

// Update game logic: move words, check conditions
void updateGame() {
    static int spawnTimer = 0;
    spawnTimer++;

    // 1. Spawn new words periodically
    // Difficulty: higher levels spawn faster
    int spawnRate = 15 - gameLevel; 
    if (spawnRate < 2) spawnRate = 2;
    
    if (spawnTimer % spawnRate == 0) {
        spawnWord();
    }

    // 2. Move all words
    for (int i = 0; i < MAX_WORDS_ON_SCREEN; i++) {
        Word *w = &activeWords[i];
        if (w->active) {
            w->y++; // Move down one row
            
            // 3. Ground collision check (game over)
            if (w->y >= SCREEN_HEIGHT - 1) { // Subtract 1 for status bar
                gameOver = 1;
            }
        }
    }
}