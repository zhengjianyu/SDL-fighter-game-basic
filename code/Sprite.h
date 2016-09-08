#pragma once

#include "SDL.h"
#include <vector>
#include <map>
#include "SDL_mixer.h"

class Sprite
{
public:
	Sprite(int width, int height, SDL_Renderer* ren, unsigned int frame_duration = 0);
	~Sprite(void);

	void setPos(int x, int y);
	void movex(int delta);
	void movey(int delta);
	int getX();
	int getY();

	void addSound(std::string soundname, Mix_Chunk* sound);
	void playsound(std::string soundname);
	
	
	//int getwidth();

	// makeFrame returns the unique index of the frame
	int makeFrame(SDL_Texture* texture, int x, int y);

	// addFrameToSequence returns the number of frames in the sequence after the add is done
	int addFrameToSequence(std::string seqName, int frameIndex);

	// show(int) renders the frame with the specified frameIndex
	void show(int frameIndex);
	// show(string) cycles through all frames in the specified sequence, one per call
	void show(std::string sequence);


	void fixrate();
	


// The private part of the class is given as a hint or suggestion.
// In homework 3 you can make any modifications you want to the class's innards.
private:
	int width, height;
	int currX, currY;		// the coordinates of the sprite's upper left hand corner relative to the window
	SDL_Renderer* renderer;
	unsigned int frameduration;

	struct frame
	{
		SDL_Texture* texture;
		int x;
		int y;
	};
	std::vector<frame> frames;

	std::map<std::string, std::vector<int>> sequenceList;

	std::map<std::string, Mix_Chunk*> SoundList;

	int sequenceIndex;		// shared by all sequences; it would be better to have
							// one for each sequence

};

