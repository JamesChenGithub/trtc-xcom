#ifndef _Square_H_
#define _Square_H_

#include <SDL2/SDL.h>
#include "Defines.h"
#include "Enums.h"

class Square
{
public:
	Square(void);
	Square(int center_x, int center_y, SDL_Texture* texture);
	~Square(void);

public:
	
	void DrawToRenderer(SDL_Renderer* renderer);
	
	void Move(Direction dir);


public:

	int getCenter_x() const { return center_x; }
	int getCenter_y() const { return center_y; }

	void setCenter_x(int center_x) { this->center_x = center_x; }
	void setCenter_y(int center_y) { this->center_y = center_y; }
	void setTexture(SDL_Texture* texture) { this->texture = texture; }

private:

	int center_x;					
	int center_y;
	
	SDL_Texture* texture;
};

#endif
