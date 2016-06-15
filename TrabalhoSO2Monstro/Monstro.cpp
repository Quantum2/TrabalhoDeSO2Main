#include "Monstro.h"

Monstro::Monstro()
{
	hp = 100;
	visible = false;
}

int Monstro::getPosX()
{
	return posX;
}

int Monstro::getPosY()
{
	return posY;
}

int Monstro::getHP()
{
	return hp;
}

void Monstro::setHP(int h)
{
	hp = h;
}

void Monstro::setX(int x)
{
	posX = x;
}

void Monstro::setY(int y)
{
	posY = y;
}

bool Monstro::getVisible() {
	return visible;
}

void Monstro::setVisible(bool v) {
	visible = v;
}
