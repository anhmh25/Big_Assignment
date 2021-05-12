#include"common.h"


string getHighScoreFromFile(string filename)
{
	fstream HighScoreFile;
	string highscore;
	HighScoreFile.open(filename, ios::in);
	HighScoreFile >> highscore;

	return highscore;	
}
 
void UpdateHighScore(string filename, const int& score, const string& old_high_score)
{
	int oldHighScore;
	fstream HighScoreFile;
	string newHighScore;
	stringstream high_score(old_high_score);
	HighScoreFile.open(filename, ios::out);
	high_score >> oldHighScore;
	if (score > oldHighScore)
	{
		oldHighScore = score;
	}
	newHighScore = to_string(oldHighScore);

	HighScoreFile << newHighScore;
}

int UpdateGameTimeAndScore(int& time, int& speed, int& score , Ninja ninja)
{
	if (time % 10 == 0)
	{
		score += SCORE_INCREASEMENT;
	}

	if (time == TIMEMAX)
	{
		speed += SPEED_INCREASEMENT;
		time = 0;
		ninja.VELOCITY+=4;
	}

	time += TIME_INCREASEMENT;

	return time;
}



void renderScrollingBackground(vector<double>& offsetSpeed, Texture backgroundTexture[BACKGROUND_LAYER], SDL_Renderer* renderer)
{
	vector <double> layer_speed;
	layer_speed.push_back(LAYER_1_SPEED);
	layer_speed.push_back(LAYER_2_SPEED);
	layer_speed.push_back(LAYER_3_SPEED);
	layer_speed.push_back(LAYER_4_SPEED);
	layer_speed.push_back(LAYER_5_SPEED);
	layer_speed.push_back(LAYER_6_SPEED);
	layer_speed.push_back(LAYER_7_SPEED);
	layer_speed.push_back(LAYER_8_SPEED);
	layer_speed.push_back(LAYER_9_SPEED);

	for (int i = 0; i < BACKGROUND_LAYER; ++i)
	{
		offsetSpeed[i] -= layer_speed[i];
		if (offsetSpeed[i] < -backgroundTexture[i].getWidth())
		{
			offsetSpeed[i] = 0;
		}
		backgroundTexture[i].render(offsetSpeed[i], 0, renderer);
		backgroundTexture[i].render(offsetSpeed[i] + backgroundTexture[i].getWidth(), 0, renderer);
	}
}


void HandlePlayButton(SDL_Event* e, Button& PlayButton, bool& Quit, bool& Play, Mix_Chunk* click)
{
	if (e->type == SDL_QUIT)
	{
		Quit = true;
	}

	if (PlayButton.isInside(e))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			PlayButton.Sprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Play = true;
			Quit = true;
			Mix_PlayChannel(-1 , click, 0);
			PlayButton.Sprite = BUTTON_MOUSE_OVER;
			break;
		}
	}
	else
	{
		PlayButton.Sprite = BUTTON_MOUSE_OUT;
	}
}


void HandleQuitButton(SDL_Event* e, Button& QuitButton, bool& Quit, Mix_Chunk* click)
{
	if (QuitButton.isInside(e))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			QuitButton.Sprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Quit = true;
			QuitButton.Sprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(-1, click, -1);
			break;
		}
	}
	else
	{
		QuitButton.Sprite = BUTTON_MOUSE_OUT;
	}
}



void loadObstacles(Obstacles& grave1, Obstacles& grave2, Obstacles& ghost1, SDL_Rect ghost[FLYING_FRAMES], SDL_Renderer* renderer)
{
	grave1.loadFromFile("rock/grave1.png", renderer);
	grave2.loadFromFile("rock/grave2.png", renderer);
	ghost1.loadFromFile("ghost.png", renderer);
	for(int i =0;i<FLYING_FRAMES;i++){

		ghost[i].x = 120 * i;
		ghost[i].y = 0;
		ghost[i].w = 120;
		ghost[i].h = 176;
	}
}

bool CheckColission(Ninja ninja, SDL_Rect* ninja_rect, Obstacles obstacle, SDL_Rect* obstacle_rect)
{
	bool collide = false;

	int left_ninja = ninja.getPosX() +10;
	int right_ninja = ninja.getPosX() + ninja_rect->w - 40;
	int top_ninja = ninja.getPosY() + 10;
	int bottom_ninja = ninja.getPosY() + ninja_rect->h -20;

	if (obstacle.getType() == GROUND_OBSTACLES_1 || obstacle.getType() == GROUND_OBSTACLES_2)
	{
		const int FALSE_PART_1 = 10;
		const int FALSE_PART_2 = 40;

		int left_obstacle = obstacle.getPosX() + 25;
		int right_obstacle = obstacle.getPosX() + obstacle.getWidth() -20;
		int top_obstacle = obstacle.getPosY();
		int bottom_obstacle = obstacle.getPosY() + obstacle.getHeight();

		if (right_ninja - FALSE_PART_1 >= left_obstacle && left_ninja + FALSE_PART_1 <= right_obstacle)
		{
			if (bottom_ninja - FALSE_PART_2 >= top_obstacle)
			{
				collide = true;
			}
		}
	}
	else
	{
		const int FALSE_PART_1 = 43;
		const int FALSE_PART_2 = 15;

		int left_obstacle = obstacle.getPosX() ;
		int right_obstacle = obstacle.getPosX() + obstacle_rect->w +15;
		int top_obstacle = obstacle.getPosY()+20;
		int bottom_obstacle = obstacle.getPosY() + obstacle_rect->h ;

		if (right_ninja - FALSE_PART_1 >= left_obstacle && left_ninja + FALSE_PART_1 <= right_obstacle)
		{
			if (top_ninja + FALSE_PART_1 <= bottom_obstacle && bottom_ninja >= top_obstacle)
			{
				collide = true;
			}

			if (bottom_ninja >= bottom_obstacle && bottom_ninja <= top_obstacle)
			{
				collide = true;
			}
		}
	}

	return collide;
}

bool CheckObstaclesColission(Ninja ninja, Obstacles grave1, Obstacles grave2, Obstacles ghost1, SDL_Rect* ninja_rect, SDL_Rect* obstacle_rect )
{
	if (CheckColission(ninja, ninja_rect, grave1))
	{
		return true;
	}
	if (CheckColission(ninja, ninja_rect, grave2))
	{
		return true;
	}
	if (CheckColission(ninja, ninja_rect, ghost1, obstacle_rect))
	{
		return true;
	}
	return false;
}

void CheckPosition(Obstacles &grave1, Obstacles &grave2, Obstacles &ghost1) {
	while (abs(grave2.posX - grave1.posX) <= MIN_DISTANCE) {
		if (grave2.posX > grave1.posX)grave2.posX  = grave1.posX  + rand() % SCREEN_WIDTH + MIN_DISTANCE;
		else grave1.posX = grave2.posX + rand() % SCREEN_WIDTH + MIN_DISTANCE;
	}
	if (abs(ghost1.getPosX() - grave1.getPosX()) <= MIN_DISTANCE && abs(ghost1.getPosX() - grave2.getPosX() <= MIN_DISTANCE)) {
		if (abs(grave1.posX - grave2.posX) >= SCREEN_WIDTH) ghost1.posX = grave2.posX  - 200 - rand() % MIN_DISTANCE;
		else {
			if (grave2.posX > grave1.posX)ghost1.posX = grave2.posX + rand() % MIN_DISTANCE;
			else ghost1.posX = grave1.posX + rand() % MIN_DISTANCE;
		}
	}
}

void ControlNinjaFrame(int& frame)
{
	frame += FRAME_INCREASEMENT;
	if (frame /FRAME >= RUNNING_FRAMES)
	{
		frame = 0;
	}
}

void ControlGhostFrame(int& frame)
{
	frame += FRAME_INCREASEMENT;
	if (frame / FRAME >= FLYING_FRAMES)
	{
		frame = 0;
	}
}

void DrawPlayerScore(Texture TextTexture, Texture ScoreTexture, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font, int score)
{
	TextTexture.render(SCORETEXT_POSX, SCORETEXT_POSY, renderer);
	string Score = to_string(score);
	if (ScoreTexture.loadRenderedText(Score.c_str(), font, textColor, renderer))
	{
		ScoreTexture.render(SCORE_POSX, SCORE_POSY, renderer);
	}
}

void DrawPlayerHighScore(Texture TextTexture, Texture HighScoreTexture, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font, string highScore)
{
	TextTexture.render(HIGHSCORETEXT_POSX, HIGHSCORETEXT_POSY, renderer);
	if (HighScoreTexture.loadRenderedText(highScore.c_str(), font, textColor, renderer))
	{
		HighScoreTexture.render(HIGH_SCORE_POSX, HIGH_SCORE_POSY, renderer);
	}
}

void DrawEndGameSelection(Texture DieTexture, Texture PlayAgainTexture, SDL_Event* e, SDL_Renderer* renderer, bool& Play_Again)
{
	if (Play_Again)
	{
		bool End_Game = false;
		while (!End_Game)
		{
			while (SDL_PollEvent(e) != 0)
			{
				if (e->type == SDL_QUIT)
				{
					Play_Again = false;
				}

				if (e->type == SDL_KEYDOWN)
				{
					switch (e->key.keysym.sym)
					{
					case SDLK_SPACE:
						End_Game = true;
						break;
					case SDLK_ESCAPE:
						End_Game = true;
						Play_Again = false;
						break;
					}
				}
			}

			DieTexture.render(700, 400, renderer);
			PlayAgainTexture.render(550, 600, renderer);
			SDL_RenderPresent(renderer);
		}
	}
}