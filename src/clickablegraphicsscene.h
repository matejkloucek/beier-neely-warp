#ifndef CLICKABLEGRAPHICSSCENE_H
#define CLICKABLEGRAPHICSSCENE_H

#include "arrow.h"

#include <QGraphicsScene>
#include <QGraphicsLineItem>

class ClickableGraphicsScene : public QGraphicsScene
{
private:
    QList<QPointF> coordinates;
    QList<QGraphicsLineItem *> lines;
    QList<Arrow *> arrows;
    int numberOfPoints = 0;
    QImage image;
    QString fileName = ":/resources/img/F-original.png";
    QColor colors[10] = {"Red", "Green", "Blue", "Yellow", "Orange", "Brown", "Grey", "Pink", "Purple", "Black"};
    bool editMode;
public:
    explicit ClickableGraphicsScene(QObject *parent = nullptr);
    QList<QPointF> getCoordinates();
    QList<QGraphicsLineItem *> getaAllLines();
    void addPoint();
    int getNumberOfPoints();
    QImage getImage();
    void setImage(QImage sourceImage);
    void clearLines();
    void clearCoordinates();
    QImage loadImage(QString file);
    bool getEditMode();
    void switchEditMode();
    void removeLine(int index);
    void removeArrow(QColor color);
    int getLineIndex(QGraphicsItem * line);
    QColor getArrowColor(QGraphicsItem * line);
    void setEditMode(bool status);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
};


#endif // CLICKABLEGRAPHICSSCENE_H
