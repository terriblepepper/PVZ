#include"gameIndex.h"
int fpsIndex;
int musicVolume ;
int itemVolume;
QString Difficulty;
std::map<QGraphicsScene*, sceneCast> mapScenes;
int difficultyIndex(QString diff)
{
	if (diff == "简单")return 1;
	else if (diff == "中等")return 2;
	else if (diff == "困难")return 4;
	else if (diff == "变态")return 8;

	return 0;
}