#include"common.h"
#include"TextureManager.h"
using namespace std;

void init();
void loadMedia();
void clean();

SDL_Color textColor1 = { 0, 255, 255 };
SDL_Color textColor2 = { 255, 0, 0 };
TTF_Font* font1 = NULL;
TTF_Font* font2 = NULL;
TTF_Font* font3 = NULL;
Mix_Music* music = NULL;
Mix_Music* menuMusic = NULL;
Mix_Chunk* jump = NULL;
Mix_Chunk* die = NULL;
Mix_Chunk* click = NULL;

SDL_Rect playButton[BUTTON_TOTAL];
SDL_Rect quitButton[BUTTON_TOTAL];
SDL_Rect ninja_running[RUNNING_FRAMES];
SDL_Rect ninja_jumping[JUMPING_FRAMES];
SDL_Rect ghost[FLYING_FRAMES];

const int PLAY_BUTTON_POSX = 400;
const int PLAY_BUTTON_POSY = 600;
const int QUIT_BUTTON_POSX = 400;
const int QUIT_BUTTON_POSY = 800;
Button PlayButton(PLAY_BUTTON_POSX, PLAY_BUTTON_POSY);
Button QuitButton(QUIT_BUTTON_POSX, QUIT_BUTTON_POSY);

Texture menuTexture;
Texture NinjaTexture1;
Texture NinjaTexture2;
Texture backgroundTexture[BACKGROUND_LAYER];
Texture PlayButtonTexture;
Texture QuitButtonTexture;
Texture dieTexture;
Texture PlayAgainTexture;
Texture ScoreSpace;
Texture ScoreTexture;
Texture HighScoreSpace;
Texture HighScoreTexture;

SDL_Window* window ;
SDL_Renderer* renderer;
Ninja ninja;

bool isRunning;
int main(int argc, char* argv[]) {
	
	init();
	loadMedia();

	if (isRunning) {

		bool Quit_Menu = false;
		bool Play_Again = false;

		Mix_PlayMusic(menuMusic, -1);
		while (!Quit_Menu)
		{
			SDL_Event e_mouse;
			menuTexture.render(0, 0, renderer);

				SDL_Rect* Rect_Play = &playButton[PlayButton.Sprite];
				PlayButton.render(Rect_Play, renderer, PlayButtonTexture);

				SDL_Rect* Rect_Quit = &quitButton[QuitButton.Sprite];
				QuitButton.render(Rect_Quit, renderer, QuitButtonTexture);

				SDL_RenderPresent(renderer);
			while (SDL_PollEvent(&e_mouse) != 0)
			{
				if (e_mouse.type == SDL_QUIT)
				{
					Quit_Menu = true;
				}

				bool Quit_Game = false;
				HandlePlayButton(&e_mouse, PlayButton, Quit_Menu, Play_Again, click);

				HandleQuitButton(&e_mouse, QuitButton, Quit_Menu, click);

				if (Quit_Game == true)
				{
					return 0;
				}
			}	
		}

		while (Play_Again)
		{
			Mix_ResumeMusic();
			srand(time(NULL));
			int time = 0;
			int score = 0;
			int acceleration = 0;
			int frame_ninja= 0;
			int frame_ghost = 0;
			string highscore = getHighScoreFromFile("highscore.txt");

			SDL_Event e;
			Obstacles grave1(GROUND_OBSTACLES_1);
			Obstacles grave2(GROUND_OBSTACLES_2);
			Obstacles ghost1(FLY_OBSTACLES);
			CheckPosition(grave1, grave2, ghost1);
			Mix_PlayMusic(music, -1);
			loadObstacles(grave1, grave2, ghost1, ghost, renderer);
			int OffsetSpeed_Ground = OFFSET_SPEED;
			vector <double> OffsetSpeed(BACKGROUND_LAYER, OFFSET_SPEED);

			bool Quit = false;
			bool In_Game = true;
			while (!Quit)
			{
				if (In_Game)
				{
					UpdateGameTimeAndScore(time, acceleration, score,ninja);
					
					while (SDL_PollEvent(&e) != 0)
					{
						if (e.type == SDL_QUIT)
						{
							Quit = true;
							Play_Again = false;
						}

						ninja.HandleEvent(e, jump);
					}
					SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(renderer);

					renderScrollingBackground(OffsetSpeed, backgroundTexture, renderer);
					ninja.Move();
					SDL_Rect* ninja_des;
					if (ninja.Running())
					{
						ninja_des = &ninja_running[frame_ninja/ FRAME];
						ninja.render(ninja_des, renderer, NinjaTexture1);
					}
					else
					{
						ninja_des = &ninja_jumping[5];
						ninja.render(ninja_des, renderer, NinjaTexture2);
					}
					CheckPosition(grave1, grave2, ghost1);
					grave1.move(acceleration);
					grave1.render(renderer);
					CheckPosition(grave1, grave2, ghost1);
					grave2.move(acceleration);
					grave2.render(renderer);
					CheckPosition(grave1, grave2, ghost1);
					SDL_Rect* Obstacles_des = &ghost[frame_ghost /FRAME];
					if (acceleration >= 2) {
						ghost1.move(acceleration);
						ghost1.render(renderer, Obstacles_des);
					}
					CheckPosition(grave1, grave2, ghost1);

					UpdateHighScore("highscore.txt", score, highscore);
					DrawPlayerScore(ScoreSpace, ScoreTexture, textColor1, renderer, font1, score);
					DrawPlayerHighScore(HighScoreSpace, HighScoreTexture, textColor1, renderer, font1, highscore);
					if (CheckObstaclesColission(ninja ,grave1 , grave2, ghost1, ninja_des, Obstacles_des))
					{
						Mix_PauseMusic();
						Mix_PlayChannel(-1, die, 0);
						Quit = true;
					}


					SDL_RenderPresent(renderer);

					ControlNinjaFrame(frame_ninja);
					ControlGhostFrame(frame_ghost);
				}
			}

			DrawEndGameSelection(dieTexture, PlayAgainTexture, &e, renderer, Play_Again);
			if (!Play_Again)
			{
				grave1.~Obstacles();
				grave2.~Obstacles();
				ghost1.~Obstacles();
			}
		}
	}
	clean();
	return 0;
}


void init() {
	isRunning = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		isRunning = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		window = SDL_CreateWindow("NINJA ADVENTURE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			isRunning = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				isRunning = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					isRunning = false;
				}
			}
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			{
				printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
				isRunning = false;
			}
			if (TTF_Init() == -1) {
				printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			}
		}
	}
}

void loadMedia()
{
	isRunning = true;

	music = Mix_LoadMUS("music/background_sound.mp3");
	if (music == NULL)
	{
		cout << "Failed to load background music" << endl;
		isRunning = false;
	}

	menuMusic = Mix_LoadMUS("music/background_sound.mp3");
	if (menuMusic == NULL)
	{
		cout << "Failed to load menu music" << endl;
		isRunning = false;
	}

	jump = Mix_LoadWAV("music/jump-sound.wav");
	if (jump == NULL)
	{
		cout << "Failed to load jumping sound" << endl;
		isRunning = false;
	}

	die = Mix_LoadWAV("music/die_sound.wav");
	if (die == NULL)
	{
		printf("Failed to load die sound!!!SDL_mixer Error: %s\n",Mix_GetError());
		isRunning = false;
	}

	click = Mix_LoadWAV("music/click_sound.wav");
	if (jump == NULL)
	{
		cout << "Failed to load click sound" << endl;
		isRunning = false;
	}

	font1 = TTF_OpenFont("font.ttf", 40);
	font2 = TTF_OpenFont("die.ttf", 150);
	font3 = TTF_OpenFont("die.ttf", 50);
	if (font1 == NULL)
	{
		printf("Failed to load font1 ! SDL_ttf Error: %s\n", TTF_GetError());
		isRunning = false;
	}
	if(font2 == NULL)
	{
		printf("Failed to load font2 ! SDL_ttf Error: %s\n", TTF_GetError());
		isRunning = false;
	}
	if (!ScoreSpace.loadRenderedText("Your score: ", font1, textColor1, renderer))
		{
			cout << "Failed to render text1 texture" << endl;
			isRunning = false;
		}

	if (!HighScoreSpace.loadRenderedText("High score: ", font1, textColor1, renderer))
		{
			cout << "Failed to render text2 texture" << endl;
			isRunning = false;
		}

	if (!dieTexture.loadRenderedText("YOU DIE !!!", font2, textColor2, renderer))
	{
		cout << "Failed to render die texture" << endl;
		isRunning = false;
	}
	if (!PlayAgainTexture.loadRenderedText("Press Space to play again or ESC to quit =.=" , font3, textColor2, renderer))
	{
		cout << "Failed to render play again texture" << endl;
		isRunning = false;
	}
	if (!menuTexture.loadTexture("game_background/background.png", renderer))
		{
		cout << "Failed to load menu image" << endl;
		isRunning = false;
		}

	if (!PlayButtonTexture.loadTexture("play_button.png", renderer))
		{
			cout << "Failed to load play_button image" << endl;
			isRunning = false;
		}
	else {
			for (int i = 0; i < BUTTON_TOTAL; i++)
			{
				playButton[i].x = 0;
				playButton[i].y = 150*i;
				playButton[i].w = 400;
				playButton[i].h = 150;
			}
		}

	if (!QuitButtonTexture.loadTexture("quit_button.png", renderer))
		{
			cout << "Failed to load quit_button image" << endl;
			isRunning = false;
		}
	else
		{
			for (int i = 0; i < BUTTON_TOTAL; ++i)
			{
				quitButton[i].x = 0;
				quitButton[i].y = 150*i;
				quitButton[i].w = 400;
				quitButton[i].h = 150;
			}
		}

	if (!NinjaTexture1.loadTexture("ninjaRunning.png", renderer))
		{
			cout << "Failed to load running_ninja image." << endl;
			isRunning = false;
		}
	else {
		for (int i = 0; i < RUNNING_FRAMES; i++) {
			ninja_running[i].x = 200 * i;
			ninja_running[i].y = 0;
			ninja_running[i].w = 200;
			ninja_running[i].h = 252;
		}
	}

	if (!NinjaTexture2.loadTexture("ninjaJumping.png", renderer))
		{
			cout << "Failed to load jumping_ninja image." << endl;
			isRunning = false;
		}
	else {
		for (int i = 0; i < JUMPING_FRAMES; i++) {
			ninja_jumping[i].x = 200 * i;
			ninja_jumping[i].y = 0;
			ninja_jumping[i].w = 200;
			ninja_jumping[i].h = 252;
		}

	}

	for (int i = 0; i < BACKGROUND_LAYER; i++)
		{
			if (!backgroundTexture[i].loadTexture(LAYER[i].c_str(), renderer))
				{
					cout << "Failed to load background image" << endl;
					isRunning = false;
				}
			}
}

void clean() {
	menuTexture.free();
	NinjaTexture1.free();
	PlayButtonTexture.free();
	QuitButtonTexture.free();
	dieTexture.free();
	ScoreSpace.free();
	ScoreTexture.free();
	HighScoreSpace.free();
	HighScoreTexture.free();

	for (int i = 0; i < BACKGROUND_LAYER; ++i)
	{
		backgroundTexture[i].free();
	}

	Mix_FreeMusic(music);
	Mix_FreeMusic(menuMusic);
	Mix_FreeChunk(click);
	Mix_FreeChunk(die);
	Mix_FreeChunk(jump);
	music = nullptr;
	menuMusic = nullptr;
	click = nullptr;
	die = nullptr;
	jump = nullptr;

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;

	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
	cout << "Game cleaned !!!" << endl;
}