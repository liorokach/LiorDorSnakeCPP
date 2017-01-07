
#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <cstring>
#include "Point.h"
#include <fstream>
#include <vector>
#include "Mission.h"
#include "Bullet.h"
class TheSnakesGame;

class Snake {
	enum { SIZE = 5 };
	enum { UP = 0, DOWN, LEFT, RIGHT };

	//int size;
	vector<Point> body;
	int direction; // TODO: use enum!
	char arrowKeys[4];
	Color color;
	Mission m;
	TheSnakesGame* theGame = nullptr;
	char symbol;
	char ShootKey;
	bool stuck;
	bool suspended = false;
	int numBul = 5;
public:
	Snake(int dir, unsigned int size, char _symbol, Point start, Color c, char Skey)
		: symbol(_symbol)
	{
		for (unsigned int i = 0; i < size; i++)
		{
			body.push_back(start);
		}
		setColor(c);
		direction = dir;
		ShootKey = Skey;
	
	}
	~Snake()
	{
		body.clear();
	}
	
	void newSnake(int x, int y, int dir);
	char getSymbol() {
		return this->symbol;
	}

	void setGame(TheSnakesGame* _theGame) {
		theGame = _theGame;
	}
	//void setPosition(int y, int x);
	void setArrowKeys(const char* keys) {
		arrowKeys[0] = keys[0];
		arrowKeys[1] = keys[1];
		arrowKeys[2] = keys[2];
		arrowKeys[3] = keys[3];
	}
	void setColor(Color c) {
		color = c;
	}
	Color getColor() {return color;}
	int move(char opSymbol, int numOfMission);//handle the movement of the snake and checking that he's move to a free and legit place 
	int getDirection(char key);//handle and adjust char direction input to int direction 
	int getDirection() {return direction;}//get the current direction of the snake
	void setDirection(int dir) {
		direction = dir;
	}
	int getSize() { return body.size(); }
	bool goodNum(int numMission, int num);//checking if the number meets the mission requirements
	void snakeGrow(){body.push_back(body[body.size() - 1]);}
	void backToStart(int x, int y, int dir = 4)
	{
		for (unsigned int i = 0; i < body.size(); i++)
			body[i].set(x, y);
		direction = dir;
	}
	void clearSnake();//clear the snake from the board
	bool checkNotSnake(Snake *s, Point p) {//check that the snake's body is not in this point
		for (unsigned int i = 0; i < s->body.size(); i++)
		{
			if (s->body[i].isSame(p))
				return false;
		}
		return true;
	}
	void findFreeSpot(Snake *s);//this function find a free spot for the snake on the board
	void clearBody() {//delete the body of the snake
		for (unsigned int i = 0; i < body.size(); i++)
			body.pop_back();
		//size = 0;
	}
	void getGameM(Mission gameM) { m = gameM; }
	char getShoot() { return ShootKey; }

	void Setsuspend(bool s) {
		suspended = s;
	}
	void setBul(int n) { numBul = n; updateBullets(); }
	bool isSuspend() { return suspended; }
	Point getbodyPlace() { return Point(body[0].getX(), body[0].getY()); }
	void addBullet() { numBul++; updateBullets(); }
	bool deleteBullet()
	{
		if (numBul > 0)
		{
			numBul--;
			updateBullets();
			return true;
		}
		return false;
	}
	void updateBullets();
};

#endif
