//Tile Settings
#define NUMBEROFTILESX 28
#define NUMBEROFTILESY 31
#define PIXELPERTILE 16

//Pacman Settings
#define PACMAN_SPEED 2.5
#define PACMAN_STARTTILE_X 13
#define PACMAN_STARTTILE_Y 23

//Ghost setting
#define GHOST_SPEED 2.5
#define GHOST_DEAD_DURATION 3000

//Assets Settings
#define LEVEL_UP_ANIMATION_RESERVE 3
#define PACMAN_ASSETS_NUM 3
#define GHOST_ASSETS_RESERVE 17
#define GHOST_ASSETS_NUM 8
#define GHOST_SCARED_ASSETS_NUM 5
#define GHOST_EYE_ASSETS_NUM 4
#define LARGE_FOOD_NUM 4
#define SMALL_FOOD_NUM 240
#define READY_TEXT_X 8
#define READY_TEXT_Y -28
#define MAP_WIDTH 448
#define MAP_HEIGHT 496

//Score
#define FOOD_SCORE 10
#define FULL_FOOD_SCORE ((LARGE_FOOD_NUM + SMALL_FOOD_NUM) * FOOD_SCORE)

//Transport point
#define TP_TILE_1_X 27
#define TP_TILE_2_X 0
#define TP_TILE_Y 14
#define TP_X1 (MAP_WIDTH/2 + PIXELPERTILE) 
#define TP_X2 (-MAP_WIDTH/2 - PIXELPERTILE) 

//Bouns
#define BONUS_STAGE_1 70
#define BONUS_STAGE_2 170

//Level
#define START_LEVEL 5
#define TOTAL_LEVEL 10

//BGM
#define NORMAL_BGM_CHANGE_SCORE_THRESHOLD 1000

//Other
#define GAME_OPENING_TIME_DURATION 4550
#define LEVEL_UP_ANIMATION_DURATION 2000
#define PILL_DURATION 10000
#define DONT_FLASH_DURATION 7000
#define PI 3.14159265358979323846
