#include "clickablegraphicsscene.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <iostream>

using namespace std;

ClickableGraphicsScene::ClickableGraphicsScene(QObject *parent)
    : QGraphicsScene{parent}
{
    // setting up the graphics scene
    this->image = loadImage(fileName);
    setImage(this->image);
}

QList<QPointF> ClickableGraphicsScene::getCoordinates()
{
    return coordinates;
}

QList<QGraphicsLineItem *> ClickableGraphicsScene::getaAllLines()
{
    return lines;
}

void ClickableGraphicsScene::addPoint()
{
    numberOfPoints++;
}

int ClickableGraphicsScene::getNumberOfPoints()
{
    return numberOfPoints;
}

QImage ClickableGraphicsScene::getImage()
{
    return image;
}

void ClickableGraphicsScene::setImage(QImage sourceImage)
{
    this->image = sourceImage.copy();
    QPixmap sourcePixmap = QPixmap::fromImage(this->image);
    this->addPixmap(sourcePixmap);
}

void ClickableGraphicsScene::clearLines()
{
    this->lines.clear();
}

void ClickableGraphicsScene::clearCoordinates()
{
    this->coordinates.clear();
    this->numberOfPoints = 0;
}

QImage ClickableGraphicsScene::loadImage(QString file)
{
    // loading, scaling and cropping the image
    QImage sourceImage = QImage(file);
    QImage scaledImage = sourceImage.scaled(350, 350,
                                            Qt::KeepAspectRatioByExpanding);
    return scaledImage.copy(QRect((scaledImage.width() - 350) / 2, (scaledImage.height() - 350) / 2, 350, 350));
}


void ClickableGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // adding a line when two points are selected on a given image
    this->addPoint();
    if(this->numberOfPoints % 2 == 0){
        QGraphicsLineItem *	line = this->addLine(coordinates.last().x(), coordinates.last().y(),
                                                 event->scenePos().x(), event->scenePos().y(),
                                                 QPen (QColor ("red"), 5));
        lines.append(line);
    }
    coordinates.append(event->scenePos());

}

