#pragma once
#include<QString>
#include<iostream>
#include<map>
#include<QGraphicsScene>

struct sceneCast
{
	bool isValid;
	int count;
};
extern int fpsIndex;
extern int musicVolume;
extern int itemVolume;
extern QString Difficulty;
extern std::map<QGraphicsScene*,sceneCast> mapScenes;
int difficultyIndex(QString diff);
