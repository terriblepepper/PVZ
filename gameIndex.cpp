#include"gameIndex.h"
//fps指数倍率（1：30fps，2：60fps，4：120fps，8：240fps）
int fpsIndex;
//音乐音量
int musicVolume ;
//音效音量
int itemVolume;
//场景内最大音效数
int maxSounds = 10;
//难度
QString Difficulty;
//场景指针与场景类的映射
std::map<QGraphicsScene*, sceneCast> mapScenes;
int difficultyIndex(QString diff)
{
	if (diff == "简单")return 1;
	else if (diff == "中等")return 2;
	else if (diff == "困难")return 4;
	else if (diff == "变态")return 8;

	return 0;
}