#include"gameObjects.h"
#include"TextureManager.h"

gameObject::gameObject(const char* texturesheet, SDL_Renderer* ren,int x,int y){
	renderer = ren;
	objectText = TextureManager::loadTexture("Idle__000.png", ren);

	xpos = x;
	ypos = y;
}

void gameObject::update() {
	//xpos++;
	

	scrRec.h = 90;
	scrRec.w = 60;
	scrRec.x = 0;
	scrRec.y = 0;

	desRec.x = xpos;
	desRec.y = ypos;
	desRec.h = scrRec.h;
	desRec.w = scrRec.w;
}



void gameObject::render() {
	SDL_RenderCopy(renderer, objectText, NULL, &desRec);
}