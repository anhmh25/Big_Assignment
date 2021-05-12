#ifndef COMMON__H_
#define COMMON__H_

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include"Ninja.h"
#include"Obstacles.h"
#include"Button.h"

#define OFFSET_SPEED 0
#define TIMEMAX 1000
#define SPEED_INCREASEMENT 1
#define SCORE_INCREASEMENT 1
#define TIME_INCREASEMENT 1
#define FRAME_INCREASEMENT 1
#define MIN_DISTANCE 850
#define BACKGROUND_SPEED 9


const int SCORETEXT_POSX = 750;
const int SCORETEXT_POSY = 20;
const int HIGHSCORETEXT_POSX = 750;
const int HIGHSCORETEXT_POSY = 80;
const int SCORE_POSX = 1020;
const int SCORE_POSY = 20;
const int HIGH_SCORE_POSX = 1010;
const int HIGH_SCORE_POSY = 80;

const int RUNNING_FRAMES = 10;
const int JUMPING_FRAMES = 10;
const int FLYING_FRAMES = 10;
const int BACKGROUND_LAYER = 9;

const int FRAME = 6;

const double LAYER_1_SPEED = 0.0;
const double LAYER_2_SPEED = 0.25;
const double LAYER_3_SPEED = 0.5;
const double LAYER_4_SPEED = 0.75;
const double LAYER_5_SPEED = 1.0;
const double LAYER_6_SPEED = 1.25;
const double LAYER_7_SPEED = 1.5;
const double LAYER_8_SPEED = 1.75;
const double LAYER_9_SPEED = 2.0;



const string LAYER[BACKGROUND_LAYER] = {
	"game_background/layers/1.png",
	"game_background/layers/2.png",
	"game_background/layers/3.png",
	"game_background/layers/4.png",
	"game_background/layers/5.png",
	"game_background/layers/6.png",
	"game_background/layers/7.png",
	"game_background/layers/8.png",
	"game_background/layers/9.png",
};

using namespace std;

string getHighScoreFromFile(string highscore);

void UpdateHighScore(string highscore, const int &score, const string &old_high_score);

int UpdateGameTimeAndScore(int& time, int& speed, int& score, Ninja ninja);

void HandlePlayButton(SDL_Event* e, Button& PlayButton, bool& QuitMenu, bool& Play ,Mix_Chunk* click);

void HandleQuitButton(SDL_Event* e, Button& quitButton, bool& Quit, Mix_Chunk* click);

void renderScrollingBackground(vector<double>& offsetSpeed, Texture BackgroundTexture[BACKGROUND_LAYER], SDL_Renderer* renderer);

void HandlePlayButton(SDL_Event* e, Button& PlayButton, bool& Quit, bool& Play, Mix_Chunk* click);

void HandleQuitButton(SDL_Event* e, Button& QuitButton, bool& Quit, Mix_Chunk* click);

void loadObstacles(Obstacles &grave1, Obstacles &grave2, Obstacles &ghost1, SDL_Rect ghost[FLYING_FRAMES], SDL_Renderer* renderer);

bool CheckColission(Ninja ninja, SDL_Rect* ninja_rect, Obstacles obstacle, SDL_Rect* obstacle_rect = nullptr);

bool CheckObstaclesColission(Ninja ninja, Obstacles grave1, Obstacles grave2, Obstacles ghost1, SDL_Rect* char_clip, SDL_Rect* Obstacles_clip = nullptr);

void CheckPosition(Obstacles &grave1, Obstacles &grave2, Obstacles &ghost1);

void ControlNinjaFrame(int& frame);

void ControlGhostFrame(int& frame);

void DrawPlayerScore(Texture TextTexture, Texture ScoreTexture, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font, int score);

void DrawPlayerHighScore(Texture TextTexture, Texture HighScoreTexture, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font, string highScore);

void DrawEndGameSelection(Texture dieTexture, Texture PlayAgainTexture, SDL_Event* e, SDL_Renderer* renderer, bool& Play_Again);

#endif
