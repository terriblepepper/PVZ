#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QVector>
#include <vector>
#include<QString>
#include"gameIndex.h"
#include"card.h"

extern QVector<Cards> cards;
// 定义一个结构体来存储卡片信息
struct Cards {
    QString name;
    int cool;
    int cost;
};
void loadCards(const QString& filename);
