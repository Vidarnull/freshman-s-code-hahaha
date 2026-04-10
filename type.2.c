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
#define FILE_NAME "top10_scores.txt"

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

// 2. For leaderboard
typedef struct {
    char name[20];
    int score;
} Record;

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
void saveScore(int finalScore);
void showLeaderboard();

int main() {
    // Random seed
    srand((unsigned int)time(NULL));

    // Show leaderboard
    showLeaderboard();
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
    
    // Save score
    saveScore(score);

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

// Save score and handle Top 10
void saveScore(int finalScore) {
    Record records[11]; // Extra slot for current score
    int count = 0;
    FILE *fp = fopen(FILE_NAME, "r");

    // 1. Read historical records
    if (fp != NULL) {
        while (count < 10 && fscanf(fp, "%s %d", records[count].name, &records[count].score) == 2) {
            count++;
        }
        fclose(fp);
    }

    // 2. Add current user's score
    printf("\nEnter your name: ");
    scanf("%s", records[count].name);
    records[count].score = finalScore;
    count++;

    // 3. Sort (bubble sort, descending by score)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (records[j].score < records[j+1].score) {
                Record temp = records[j];
                records[j] = records[j+1];
                records[j+1] = temp;
            }
        }
    }

    // 4. Write top 10 back to file
    fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("Cannot save score file!\n");
        return;
    }
    
    int saveCount = count < 10 ? count : 10;
    printf("\n--- LATEST TOP 10 ---\n");
    for (int i = 0; i < saveCount; i++) {
        fprintf(fp, "%s %d\n", records[i].name, records[i].score);
        printf("Rank %d: %s \t %d points\n", i+1, records[i].name, records[i].score);
    }
    fclose(fp);
    printf("Records saved.\n");
}

// Display leaderboard
void showLeaderboard() {
    FILE *fp = fopen(FILE_NAME, "r");
    char name[20];
    int s;
    printf("=============================\n");
    printf("      TOP 10 HIGH SCORES     \n");
    printf("=============================\n");
    if (fp == NULL) {
        printf("No records yet.\n");
    } else {
        int i = 1;
        while (fscanf(fp, "%s %d", name, &s) == 2) {
            printf("%d. %s \t %d\n", i++, name, s);
        }
        fclose(fp);
    }
    printf("=============================\n");
}