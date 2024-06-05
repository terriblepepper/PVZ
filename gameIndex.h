#pragma once
#include<QString>
#include<iostream>
#include<map>
#include<QGraphicsScene>

struct sceneCast
{
	bool isValid;
	int count;
	int soundsCount;
};
extern int fpsIndex;
extern int musicVolume;
extern int itemVolume;
extern int maxSounds;
extern QString Difficulty;
extern std::map<QGraphicsScene*,sceneCast> mapScenes;
int difficultyIndex(QString diff);
