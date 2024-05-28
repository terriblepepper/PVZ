#include "CustomButton.h"
#include <QPainter>

CustomButton::CustomButton(QWidget* parent)
    : QPushButton(parent), backgroundScaleX(1.0), backgroundScaleY(1.0),
    overlayScaleX(1.0), overlayScaleY(1.0) {}

void CustomButton::setBackgroundImage(const QString& imagePath, const QPoint& pos, double scaleX, double scaleY) {
    background = QPixmap(imagePath);
    backgroundPos = pos;
    backgroundScaleX = scaleX;
    backgroundScaleY = scaleY;
    update(); // Trigger a repaint to apply the new image
}

void CustomButton::setOverlayImage(const QString& imagePath, const QPoint& pos, double scaleX, double scaleY) {
    overlay = QPixmap(imagePath);
    overlayPos = pos;
    overlayScaleX = scaleX;
    overlayScaleY = scaleY;
    update(); // Trigger a repaint to apply the new image
}

void CustomButton::setButtonName(const QString& name) {
    ButtonName = name;
}

QString CustomButton::getButtonName() {
    return ButtonName;
}

void CustomButton::setDisplayText(const QString& text) {
    displayText = text;
    update(); // Trigger a repaint to apply the new text
}

void CustomButton::paintEvent(QPaintEvent* event) {
    QPushButton::paintEvent(event); // Call the base class implementation first

    QPainter painter(this);

    // Draw the background image
    if (!background.isNull()) {
        QSize scaledSize(background.width() * backgroundScaleX, background.height() * backgroundScaleY);
        painter.drawPixmap(QRect(backgroundPos, scaledSize), background.scaled(scaledSize));
    }

    // Draw the overlay image
    if (!overlay.isNull()) {
        QSize scaledSize(overlay.width() * overlayScaleX, overlay.height() * overlayScaleY);
        painter.drawPixmap(QRect(overlayPos, scaledSize), overlay.scaled(scaledSize));
    }

    // Draw the display text
    if (!displayText.isEmpty()) {
        painter.drawText(10, 76, displayText); // Adjust the coordinates as needed
    }
}
