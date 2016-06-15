#pragma once

class Monstro {
private:
	int posX, posY, hp;
	bool visible;
public:
	Monstro();
	int getPosX();
	int getPosY();
	int getHP();
	bool getVisible();
	void setVisible(bool v);
	void setHP(int h);
	void setX(int x);
	void setY(int y);
};