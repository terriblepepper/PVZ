#pragma once
#include <QPushButton>
#include <QPixmap>
#include <QString>

class CustomButton : public QPushButton {
    Q_OBJECT

public:
    explicit CustomButton(QWidget* parent = nullptr);
    void setBackgroundImage(const QString& path, const QPoint& pos = QPoint(), double scaleX = 1.0, double scaleY = 1.0);
    void setOverlayImage(const QString& path, const QPoint& pos = QPoint(), double scaleX = 1.0, double scaleY = 1.0);
    void setButtonName(const QString& name);
    QString getButtonName();
    void setDisplayText(const QString& text);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QPixmap background;
    QPoint backgroundPos;
    double backgroundScaleX;
    double backgroundScaleY;

    QPixmap overlay;
    QPoint overlayPos;
    double overlayScaleX;
    double overlayScaleY;

    QString ButtonName;
    QString displayText;  // New member variable for storing text
};
