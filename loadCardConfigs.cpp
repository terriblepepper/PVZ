#include"loadCardConfigs.h"

// 存储所有卡片的向量
QVector<Cards> cards;

void loadCards(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open file" << filename;
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(data);

    if (document.isNull() || !document.isArray()) {
        qWarning() << "Invalid JSON format";
        return;
    }

    QJsonArray jsonArray = document.array();
    for (const QJsonValue& value : jsonArray) {
        QJsonObject obj = value.toObject();
        Cards card;
        card.name = obj["name"].toString();
        card.cool = obj["cooldown"].toInt() * fpsIndex;
        card.cost = obj["cost"].toInt();
        cards.append(card);
    }
}