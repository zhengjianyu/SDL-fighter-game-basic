#include <iostream>
#include <sstream>
#include <Windows.h>
//#include "res_path.h"
#include "SDL_image.h"
#include "Sprite.h"



void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}



void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst,
				   SDL_Rect *clip = nullptr)
{
	SDL_RenderCopy(ren, tex, clip, &dst);
}


void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y,
				   SDL_Rect *clip = nullptr)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != nullptr){
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else {
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	}
	renderTexture(tex, ren, dst, clip);
}




Sprite::Sprite(int width, int height, SDL_Renderer* ren, unsigned int frame_duration)
{
	Sprite::width = width;
	Sprite::height = height;
	renderer = ren;
	frameduration = frame_duration;
}


Sprite::~Sprite()
{
	std::cout << "fk you" << std::endl;
}

void Sprite::setPos(int x, int y)
{
	currX = x;
	currY = y;
}

void Sprite::movex(int delta)
{
	currX += delta;
}

void Sprite::movey(int delta)
{
	currY += delta;
}

int Sprite::getX()
{
	return currX;
}

int Sprite::getY()
{
	return currY;
}

//int Sprite::getwidth()
//{
//	return width;
//}

void Sprite::addSound(std::string soundname, Mix_Chunk* sound)
{
	SoundList[soundname] = sound;
}

int Sprite::makeFrame(SDL_Texture* texture, int x, int y)
{
	frame result = {texture, x, y};
	frames.push_back(result);
	//std::cout << "makeFrame    " << frames.back().x << ",    index     " << frames.size()-1 << std::endl;
	return frames.size()-1;
}

int Sprite::addFrameToSequence(std::string seqName, int frameIndex)
{
	sequenceList[seqName].push_back(frameIndex);
	//std::vector<int> sequence;
	//sequence.push_back(frameIndex);
	//sequenceList.insert(std::pair<std::string, std::vector<int>> (seqName, sequence));
	//for (std::pair<std::string, std::vector<int>> j : sequenceList){
	//	std::cout << j.first << " ";
	//	for (int i : j.second)
	//		std::cout << i << " ";
	//}
	//std::cout << "\n";

	return sequenceList[seqName].size();
}


void Sprite::show(int frameIndex)
{
	//int xW, xH;
	//SDL_RenderClear(renderer);
	frame result = frames.at(frameIndex);
	SDL_Rect PIC = {result.x, result.y, width, height};
	//renderTexture(result.texture, renderer, 0, 0, 640, 480);
	//SDL_RenderPresent(renderer);
	//std::cout << PIC.x << " " << PIC.y << std::endl;
	//SDL_QueryTexture(result.texture, NULL, NULL, &xW, &xH);
	//std::cout << "show!   " << result.x << result.y << std::endl;
	renderTexture(result.texture, renderer, currX, currY, &PIC);
	/*renderTexture(result.texture, renderer, result.x, result.y, result.x + width, result.y + height);*/
}


void Sprite::show(std::string sequence)
{
	std::vector<int> result = sequenceList[sequence];
	//for(unsigned int i=0; i < result.size(); i++){
		//SDL_RenderClear(renderer);
		//show(result.at(i));
		//SDL_Delay(1000);
		//frame pics = frames.at(result[i]);
		//renderTexture(pics.texture, renderer, width, height);
	//}
	if (sequenceIndex > result.at(result.size()-1) || sequenceIndex < result.at(0)){
		sequenceIndex = result.at(0);
		/*if (sequence == "jump"){
			sequence = "stay";
			sequenceIndex = 0;
		}*/
	}
	show(sequenceIndex);
	sequenceIndex++;
}

void Sprite::playsound(std::string soundname)
{
	Mix_PlayChannel( -1, SoundList[soundname], 0 );
}


void Sprite::fixrate()
{
	SDL_Delay(frameduration);
}