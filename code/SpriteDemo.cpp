#include <iostream>
#include <sstream>
#include <Windows.h>
#include <SDL.h>
#include "res_path.h"
#include "SDL_image.h"
#include "Sprite.h"

//#include "test.cpp"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;


//void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
//	//Setup the destination rectangle to be at the position we want
//	SDL_Rect dst;
//	dst.x = x;
//	dst.y = y;
//	dst.w = w;

//	dst.h = h;
//	SDL_RenderCopy(ren, tex, NULL, &dst);
//}
/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
	std::ostringstream errMsg;
	errMsg << " error: " << SDL_GetError() << std::endl;
	OutputDebugString(errMsg.str().c_str());
}

/**
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr){
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}


int main(int argc, char **argv){

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::ostringstream debugMsg;
		debugMsg << "SDL_Init Error: " << SDL_GetError() << std::endl;
		OutputDebugString(debugMsg.str().c_str());
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		logSDLError(std::cout, "IMG_Init");
		SDL_Quit();
		return 1;
	}
    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        logSDLError(std::cout, "Mixer_Init");
        SDL_Quit();
		return 1;
    }

	SDL_Window *window = SDL_CreateWindow("Sprite Demo", 800, 100, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		logSDLError(std::cout, "CreateRenderer");
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	const std::string resPath = getResourcePath("HW5");
	//std::cout << resPath << std::endl;
	// background is "Suguaro Cactus Forrest" from fineartamerica.com
	SDL_Texture *background = loadTexture(resPath + "Background.png", renderer);
	//renderTexture(background, renderer, 0, 0, 640, 480);
	//SDL_RenderPresent(renderer);
	//Make sure all is well
	if (background == nullptr){
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(background);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	SDL_Texture *word = loadTexture(resPath + "word.png", renderer);
	if (background == nullptr){
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(background);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	std::string deat = resPath + "death.wav";
	std::string bg = resPath + "bgm.wav";
	std::string ht = resPath + "hit.wav";
	Mix_Music *Bgm = Mix_LoadMUS(bg.c_str());
	Mix_Chunk *gDeath = Mix_LoadWAV(deat.c_str());
	Mix_Chunk *hit = Mix_LoadWAV(ht.c_str());
    if( Bgm == NULL )
    {
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(background);
		Mix_FreeMusic(Bgm);
		Bgm = NULL;
		IMG_Quit();
		SDL_Quit();
		Mix_Quit();
		return 1;
    }
	if( gDeath == NULL )
    {
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(background);
		Mix_FreeChunk(gDeath);
		gDeath = NULL;
		IMG_Quit();
		SDL_Quit();
		Mix_Quit();
		return 1;
    }
	if( hit == NULL )
    {
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(background);
		Mix_FreeChunk(hit);
		hit = NULL;
		IMG_Quit();
		SDL_Quit();
		Mix_Quit();
		return 1;
    }

	Sprite* spriteBG = new Sprite(SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
	spriteBG->setPos(0,0);
	int bgFrame = spriteBG->makeFrame(background, 0, 0);
	Sprite* spriteWD = new Sprite(386, 43, renderer);
	spriteWD->setPos(300,70);
	int wdFrame = spriteWD->makeFrame(word, 0, 0);
	SDL_Texture *spritesheet4 = loadTexture(resPath + "Mis_000.png", renderer);
	SDL_Texture *spritesheet5 = loadTexture(resPath + "Mis_001.png", renderer);
	SDL_Texture *spritesheet6 = loadTexture(resPath + "Mis_002.png", renderer);
	SDL_Texture *spritesheet7 = loadTexture(resPath + "Mis_003.png", renderer);
	SDL_Texture *spritesheet8 = loadTexture(resPath + "Mis_004.png", renderer);
	SDL_Texture *spritesheet9 = loadTexture(resPath + "Mis_005.png", renderer);
	SDL_Texture *spritesheet10 = loadTexture(resPath + "Mis_006.png", renderer);
	SDL_Texture *spritesheet11 = loadTexture(resPath + "Mis_007.png", renderer);

	SDL_Texture *spritesheet12 = loadTexture(resPath + "Mis_045.png", renderer);
	SDL_Texture *spritesheet13 = loadTexture(resPath + "Mis_046.png", renderer);
	SDL_Texture *spritesheet14 = loadTexture(resPath + "Mis_047.png", renderer);
	SDL_Texture *spritesheet15 = loadTexture(resPath + "Mis_048.png", renderer);
	SDL_Texture *spritesheet16 = loadTexture(resPath + "Mis_049.png", renderer);
	SDL_Texture *spritesheet17 = loadTexture(resPath + "Mis_050.png", renderer);
	SDL_Texture *spritesheet18 = loadTexture(resPath + "Mis_051.png", renderer);
	SDL_Texture *spritesheet19 = loadTexture(resPath + "Mis_052.png", renderer);
	SDL_Texture *spritesheet20 = loadTexture(resPath + "Mis_053.png", renderer);
	SDL_Texture *spritesheet21 = loadTexture(resPath + "Mis_054.png", renderer);
	SDL_Texture *spritesheet22 = loadTexture(resPath + "Mis_055.png", renderer);
	SDL_Texture *spritesheet23 = loadTexture(resPath + "Mis_056.png", renderer);

	SDL_Texture *spritesheet24 = loadTexture(resPath + "Mis_141.png", renderer);
	SDL_Texture *spritesheet25 = loadTexture(resPath + "Mis_142.png", renderer);
	SDL_Texture *spritesheet26 = loadTexture(resPath + "Mis_143.png", renderer);
	SDL_Texture *spritesheet27 = loadTexture(resPath + "Mis_144.png", renderer);
	SDL_Texture *spritesheet28 = loadTexture(resPath + "Mis_145.png", renderer);
	SDL_Texture *spritesheet29 = loadTexture(resPath + "Mis_146.png", renderer);

	SDL_Texture *spritesheet30 = loadTexture(resPath + "Mis_134.png", renderer);
	SDL_Texture *spritesheet31 = loadTexture(resPath + "Mis_135.png", renderer);
	SDL_Texture *spritesheet32 = loadTexture(resPath + "Mis_136.png", renderer);
	SDL_Texture *spritesheet33 = loadTexture(resPath + "Mis_137.png", renderer);
	SDL_Texture *spritesheet34 = loadTexture(resPath + "Mis_138.png", renderer);
	SDL_Texture *spritesheet35 = loadTexture(resPath + "Mis_139.png", renderer);

	SDL_Texture *spritesheet36 = loadTexture(resPath + "Mis_173.png", renderer);
	SDL_Texture *spritesheet37 = loadTexture(resPath + "Mis_174.png", renderer);
	SDL_Texture *spritesheet38 = loadTexture(resPath + "Mis_175.png", renderer);
	SDL_Texture *spritesheet39 = loadTexture(resPath + "Mis_176.png", renderer);
	SDL_Texture *spritesheet40 = loadTexture(resPath + "Mis_177.png", renderer);
	SDL_Texture *spritesheet41 = loadTexture(resPath + "Mis_178.png", renderer);
	SDL_Texture *spritesheet42 = loadTexture(resPath + "Mis_179.png", renderer);
	SDL_Texture *spritesheet43 = loadTexture(resPath + "Mis_180.png", renderer);
	SDL_Texture *spritesheet44 = loadTexture(resPath + "Mis_181.png", renderer);
	SDL_Texture *spritesheet45 = loadTexture(resPath + "Mis_182.png", renderer);
	SDL_Texture *spritesheet46 = loadTexture(resPath + "Mis_183.png", renderer);
	SDL_Texture *spritesheet47 = loadTexture(resPath + "Mis_184.png", renderer);

	SDL_Texture *spritesheet48 = loadTexture(resPath + "Mis_008.png", renderer);
	SDL_Texture *spritesheet49 = loadTexture(resPath + "Mis_009.png", renderer);
	SDL_Texture *spritesheet50 = loadTexture(resPath + "Mis_010.png", renderer);
	SDL_Texture *spritesheet51 = loadTexture(resPath + "Mis_011.png", renderer);
	SDL_Texture *spritesheet52 = loadTexture(resPath + "Mis_012.png", renderer);
	SDL_Texture *spritesheet53 = loadTexture(resPath + "Mis_013.png", renderer);
	SDL_Texture *spritesheet54 = loadTexture(resPath + "Mis_014.png", renderer);
	SDL_Texture *spritesheet55 = loadTexture(resPath + "Mis_015.png", renderer);
	SDL_Texture *spritesheet56 = loadTexture(resPath + "Mis_016.png", renderer);
	SDL_Texture *spritesheet57 = loadTexture(resPath + "Mis_017.png", renderer);
	SDL_Texture *spritesheet58 = loadTexture(resPath + "Mis_018.png", renderer);
	SDL_Texture *spritesheet59 = loadTexture(resPath + "Mis_019.png", renderer);
	SDL_Texture *spritesheet60 = loadTexture(resPath + "Mis_020.png", renderer);
	SDL_Texture *spritesheet61 = loadTexture(resPath + "Mis_021.png", renderer);
	SDL_Texture *spritesheet62 = loadTexture(resPath + "Mis_022.png", renderer);
	SDL_Texture *spritesheet63 = loadTexture(resPath + "Mis_023.png", renderer);
	SDL_Texture *spritesheet64 = loadTexture(resPath + "Mis_024.png", renderer);

	if (spritesheet4 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet4);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet5 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet5);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet6 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet6);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet7 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet7);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet8 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet8);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet9 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet9);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet10 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet10);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet11 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet11);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet12 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet12);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet13 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet13);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet14 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet14);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet15 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet15);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet16 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet16);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet17 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet17);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet18 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet18);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet19 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet19);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet20 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet20);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet21 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet21);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet22 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet22);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet23 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet23);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet24 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet24);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet25 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet25);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet26 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet26);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet27 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet27);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet28 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet28);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet29 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet29);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet30 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet30);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet31 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet31);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet32 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet32);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet33 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet33);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet34 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet34);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet35 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet35);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet36 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet36);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet37 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet37);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet38 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet38);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet39 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet39);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet40 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet40);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet41 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet41);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet42 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet42);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet43 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet43);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet44 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet44);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet45 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet45);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet46 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet46);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet47 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet47);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet48 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet48);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet49 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet49);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet50 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet50);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet51 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet51);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet52 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet52);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet53 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet53);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet54 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet54);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet55 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet55);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet56 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet56);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet57 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet57);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet58 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet58);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet59 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet59);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet60 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet60);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet61 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet61);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet62 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet62);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet63 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet63);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	if (spritesheet64 == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(spritesheet64);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	//Sprite* sprite1 = new Sprite(95, 130, renderer);
	//sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 0, 0));
	//sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 95, 0));
	//sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 190, 0));
	//sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 285, 0));
	//sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 380, 0));
	//sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 475, 0));
	//sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 570, 0));

	//sprite1->addFrameToSequence("walk left", sprite1->makeFrame(spritesheet, 570, 260));
	//sprite1->addFrameToSequence("float up", sprite1->makeFrame(spritesheet2, 0, 0));
	//for (int i=0; i<13; i++)
	//{
	//	for (int j=0; j<5; j++)
	//	{
	//		sprite1->addFrameToSequence("float down", sprite1->makeFrame(spritesheet3, 0, i*130));
	//	}
	//}

	//int x = SCREEN_WIDTH / 2 ;
	//int y = SCREEN_HEIGHT / 2;
	//sprite1->setPos(x, y);

	Sprite* sprite2 = new Sprite(800, 640, renderer, 80);
	sprite2->addFrameToSequence("stay", sprite2->makeFrame(spritesheet4, 0, 0));
	sprite2->addFrameToSequence("stay", sprite2->makeFrame(spritesheet5, 0, 0));
	sprite2->addFrameToSequence("stay", sprite2->makeFrame(spritesheet6, 0, 0));
	sprite2->addFrameToSequence("stay", sprite2->makeFrame(spritesheet7, 0, 0));
	sprite2->addFrameToSequence("stay", sprite2->makeFrame(spritesheet8, 0, 0));
	sprite2->addFrameToSequence("stay", sprite2->makeFrame(spritesheet9, 0, 0));
	sprite2->addFrameToSequence("stay", sprite2->makeFrame(spritesheet10, 0, 0));
	sprite2->addFrameToSequence("stay", sprite2->makeFrame(spritesheet11, 0, 0));
	sprite2->addFrameToSequence("jump", sprite2->makeFrame(spritesheet12, 0, 0));
	sprite2->addFrameToSequence("jump", sprite2->makeFrame(spritesheet13, 0, 0));
	sprite2->addFrameToSequence("jump", sprite2->makeFrame(spritesheet14, 0, 0));
	sprite2->addFrameToSequence("jump", sprite2->makeFrame(spritesheet15, 0, 0));
	sprite2->addFrameToSequence("jump", sprite2->makeFrame(spritesheet16, 0, 0));
	sprite2->addFrameToSequence("jump", sprite2->makeFrame(spritesheet17, 0, 0));
	sprite2->addFrameToSequence("jump", sprite2->makeFrame(spritesheet18, 0, 0));
	sprite2->addFrameToSequence("jump", sprite2->makeFrame(spritesheet19, 0, 0));
	sprite2->addFrameToSequence("jump", sprite2->makeFrame(spritesheet20, 0, 0));
	sprite2->addFrameToSequence("jump", sprite2->makeFrame(spritesheet21, 0, 0));
	sprite2->addFrameToSequence("jump", sprite2->makeFrame(spritesheet22, 0, 0));
	sprite2->addFrameToSequence("jump", sprite2->makeFrame(spritesheet23, 0, 0));
	sprite2->addFrameToSequence("walk right", sprite2->makeFrame(spritesheet24, 0, 0));
	sprite2->addFrameToSequence("walk right", sprite2->makeFrame(spritesheet25, 0, 0));
	sprite2->addFrameToSequence("walk right", sprite2->makeFrame(spritesheet26, 0, 0));
	sprite2->addFrameToSequence("walk right", sprite2->makeFrame(spritesheet27, 0, 0));
	sprite2->addFrameToSequence("walk right", sprite2->makeFrame(spritesheet28, 0, 0));
	sprite2->addFrameToSequence("walk right", sprite2->makeFrame(spritesheet29, 0, 0));
	sprite2->addFrameToSequence("walk left", sprite2->makeFrame(spritesheet30, 0, 0));
	sprite2->addFrameToSequence("walk left", sprite2->makeFrame(spritesheet31, 0, 0));
	sprite2->addFrameToSequence("walk left", sprite2->makeFrame(spritesheet32, 0, 0));
	sprite2->addFrameToSequence("walk left", sprite2->makeFrame(spritesheet33, 0, 0));
	sprite2->addFrameToSequence("walk left", sprite2->makeFrame(spritesheet34, 0, 0));
	sprite2->addFrameToSequence("walk left", sprite2->makeFrame(spritesheet35, 0, 0));
	sprite2->addFrameToSequence("down", sprite2->makeFrame(spritesheet36, 0, 0));
	sprite2->addFrameToSequence("down", sprite2->makeFrame(spritesheet37, 0, 0));
	sprite2->addFrameToSequence("down", sprite2->makeFrame(spritesheet38, 0, 0));
	sprite2->addFrameToSequence("down", sprite2->makeFrame(spritesheet39, 0, 0));
	sprite2->addFrameToSequence("down", sprite2->makeFrame(spritesheet40, 0, 0));
	sprite2->addFrameToSequence("down", sprite2->makeFrame(spritesheet41, 0, 0));
	sprite2->addFrameToSequence("down", sprite2->makeFrame(spritesheet42, 0, 0));
	sprite2->addFrameToSequence("down", sprite2->makeFrame(spritesheet43, 0, 0));
	sprite2->addFrameToSequence("down", sprite2->makeFrame(spritesheet44, 0, 0));
	sprite2->addFrameToSequence("down", sprite2->makeFrame(spritesheet45, 0, 0));
	sprite2->addFrameToSequence("down", sprite2->makeFrame(spritesheet46, 0, 0));
	sprite2->addFrameToSequence("down", sprite2->makeFrame(spritesheet47, 0, 0));
	sprite2->addFrameToSequence("dead", sprite2->makeFrame(spritesheet47, 0, 0));
	sprite2->addFrameToSequence("attack", sprite2->makeFrame(spritesheet48, 0, 0));
	sprite2->addFrameToSequence("attack", sprite2->makeFrame(spritesheet49, 0, 0));
	sprite2->addFrameToSequence("attack", sprite2->makeFrame(spritesheet50, 0, 0));
	sprite2->addFrameToSequence("attack", sprite2->makeFrame(spritesheet51, 0, 0));
	sprite2->addFrameToSequence("attack", sprite2->makeFrame(spritesheet52, 0, 0));
	sprite2->addFrameToSequence("attack", sprite2->makeFrame(spritesheet53, 0, 0));
	sprite2->addFrameToSequence("attack", sprite2->makeFrame(spritesheet54, 0, 0));
	sprite2->addFrameToSequence("attack", sprite2->makeFrame(spritesheet55, 0, 0));
	sprite2->addFrameToSequence("attack", sprite2->makeFrame(spritesheet56, 0, 0));
	sprite2->addFrameToSequence("attack", sprite2->makeFrame(spritesheet57, 0, 0));
	sprite2->addFrameToSequence("attack", sprite2->makeFrame(spritesheet58, 0, 0));
	sprite2->addFrameToSequence("attack", sprite2->makeFrame(spritesheet59, 0, 0));
	sprite2->addFrameToSequence("attack", sprite2->makeFrame(spritesheet60, 0, 0));
	sprite2->addFrameToSequence("attack", sprite2->makeFrame(spritesheet61, 0, 0));
	sprite2->addFrameToSequence("attack", sprite2->makeFrame(spritesheet62, 0, 0));
	sprite2->addFrameToSequence("attack", sprite2->makeFrame(spritesheet63, 0, 0));
	sprite2->addFrameToSequence("attack", sprite2->makeFrame(spritesheet64, 0, 0));

	sprite2->addSound("hit", hit);
	sprite2->addSound("dead", gDeath);

	sprite2->setPos(0, 0);

	SDL_Event e;
	bool quit = false;
	std::string spriteDirection = "stay";
	int jumpcounter = 0;
	int downcounter = 0;
	int attackcounter = 0;

	if(Mix_PlayMusic(Bgm, 0) == -1) 
	{
		SDL_Quit();
		return 1;
	}


	while (!quit){
		//int OldTime = SDL_GetTicks();
		while (SDL_PollEvent(&e)){
			//int NewTime = SDL_GetTicks();
			//int TimeSinceLastFrame = NewTime - OldTime;
			//OldTime = NewTime;
			if (e.type == SDL_QUIT){
				quit = true;
			}
			if (e.type == SDL_KEYDOWN){
				if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d)
				{
					sprite2->movex(10);
					spriteDirection = "walk right";
				}
				else if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a)
				{
					sprite2->movex(-7);
					spriteDirection = "walk left";
				}
				else if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w)
				{
					spriteDirection = "jump";
				}
				else if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s)
				{
					sprite2->playsound("dead");
					spriteDirection = "down";
				}
				else if (e.key.keysym.sym == SDLK_j)
				{
					sprite2->playsound("hit");
					spriteDirection = "attack";
				}
			}
		}
		if (spriteDirection == "jump")
			jumpcounter++;
		if (spriteDirection == "down")
			downcounter++;
		if (spriteDirection == "attack")
			attackcounter++;
		if (jumpcounter == 13){
			jumpcounter = 0;
			spriteDirection = "stay";
		}
		if (downcounter == 12){
			downcounter = 0;
			spriteDirection = "dead";
		}
		if (attackcounter == 18){
			attackcounter = 0;
			spriteDirection = "stay";
		}
		SDL_RenderClear(renderer);
		spriteBG->show(bgFrame);
		spriteWD->show(wdFrame);
		//sprite1->show(spriteDirection.c_str());
		sprite2->show(spriteDirection.c_str());
		SDL_RenderPresent(renderer);
		sprite2->fixrate();
	}
	Mix_HaltMusic();
	Mix_FreeMusic(Bgm);
	Mix_FreeChunk(gDeath);
	Mix_CloseAudio();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	//SDL_DestroyTexture(spritesheet);
	//SDL_DestroyTexture(spritesheet2);
	//SDL_DestroyTexture(spritesheet3);
	SDL_DestroyTexture(spritesheet4);
	SDL_DestroyTexture(spritesheet5);
	SDL_DestroyTexture(spritesheet6);
	SDL_DestroyTexture(spritesheet7);
	SDL_DestroyTexture(spritesheet8);
	SDL_DestroyTexture(spritesheet9);
	SDL_DestroyTexture(spritesheet10);
	SDL_DestroyTexture(spritesheet11);
	SDL_DestroyTexture(spritesheet12);
	SDL_DestroyTexture(spritesheet13);
	SDL_DestroyTexture(spritesheet14);
	SDL_DestroyTexture(spritesheet15);
	SDL_DestroyTexture(spritesheet16);
	SDL_DestroyTexture(spritesheet17);
	SDL_DestroyTexture(spritesheet18);
	SDL_DestroyTexture(spritesheet19);
	SDL_DestroyTexture(spritesheet20);
	SDL_DestroyTexture(spritesheet21);
	SDL_DestroyTexture(spritesheet22);
	SDL_DestroyTexture(spritesheet23);
	SDL_DestroyTexture(spritesheet24);
	SDL_DestroyTexture(spritesheet25);
	SDL_DestroyTexture(spritesheet26);
	SDL_DestroyTexture(spritesheet27);
	SDL_DestroyTexture(spritesheet28);
	SDL_DestroyTexture(spritesheet29);
	SDL_DestroyTexture(spritesheet30);
	SDL_DestroyTexture(spritesheet31);
	SDL_DestroyTexture(spritesheet32);
	SDL_DestroyTexture(spritesheet33);
	SDL_DestroyTexture(spritesheet34);
	SDL_DestroyTexture(spritesheet35);
	SDL_DestroyTexture(spritesheet36);
	SDL_DestroyTexture(spritesheet37);
	SDL_DestroyTexture(spritesheet38);
	SDL_DestroyTexture(spritesheet39);
	SDL_DestroyTexture(spritesheet40);
	SDL_DestroyTexture(spritesheet41);
	SDL_DestroyTexture(spritesheet42);
	SDL_DestroyTexture(spritesheet43);
	SDL_DestroyTexture(spritesheet44);
	SDL_DestroyTexture(spritesheet45);
	SDL_DestroyTexture(spritesheet46);
	SDL_DestroyTexture(spritesheet47);
	SDL_DestroyTexture(spritesheet48);
	SDL_DestroyTexture(spritesheet49);
	SDL_DestroyTexture(spritesheet50);
	SDL_DestroyTexture(spritesheet51);
	SDL_DestroyTexture(spritesheet52);
	SDL_DestroyTexture(spritesheet53);
	SDL_DestroyTexture(spritesheet54);
	SDL_DestroyTexture(spritesheet55);
	SDL_DestroyTexture(spritesheet56);
	SDL_DestroyTexture(spritesheet57);
	SDL_DestroyTexture(spritesheet58);
	SDL_DestroyTexture(spritesheet59);
	SDL_DestroyTexture(spritesheet60);
	SDL_DestroyTexture(spritesheet61);
	SDL_DestroyTexture(spritesheet62);
	SDL_DestroyTexture(spritesheet63);
	SDL_DestroyTexture(spritesheet64);
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(word);
	IMG_Quit();
	SDL_Quit();

	SDL_Quit();

	return 0;
}
