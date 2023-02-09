#include "clickablegraphicsscene.h"
#include "arrow.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <iostream>
#include <QtMath>

using namespace std;

ClickableGraphicsScene::ClickableGraphicsScene(QObject *parent)
    : QGraphicsScene{parent}
{
    // setting up the graphics scene
    this->image = loadImage(fileName);
    setImage(this->image);
    editMode = false;
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

bool ClickableGraphicsScene::getEditMode()
{
    return this->editMode;
}

void ClickableGraphicsScene::switchEditMode()
{
    this->editMode = !this->editMode;
}

void ClickableGraphicsScene::removeLine(int index)
{
    if(index < this->lines.size()){
        this->removeItem(this->lines[index]);
    }
}

void ClickableGraphicsScene::removeArrow(QColor color)
{
    for(int i = 0; i < this->arrows.size(); i++){
        if(this->arrows[i]->getColor() == color){
            this->removeItem(this->arrows[i]->getLine());
            this->removeItem(this->arrows[i]->getArrowHead());
            this->lines.removeOne(this->arrows[i]->getLine());
            this->arrows.removeOne(this->arrows[i]);
            return;
        }
    }
    // if none of the arrows in the scene have the desired color than it means the other scene had more lines than this one
    // in order to keep the colors of any future pairs of arrows the same we need to add two to the number of points in this scene
    this->numberOfPoints = this->numberOfPoints + 2;
}


int ClickableGraphicsScene::getLineIndex(QGraphicsItem *line)
{
    for(int i = 0; i < this->lines.size(); i++){
        if(line == lines[i]){
            return i;
        }
    }
    cout << "Error: line not found";
    return -1;
}

QColor ClickableGraphicsScene::getArrowColor(QGraphicsItem *line)
{
    for(int i = 0; i < this->arrows.size(); i++){
        if(line == this->arrows[i]->getLine()){
            return this->arrows[i]->getColor();
        }
    }
    return QColor();
}

void ClickableGraphicsScene::setEditMode(bool status)
{
    this->editMode = status;
}


void ClickableGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // adding a line when two points are selected on a given image
    if(event->button() == Qt::LeftButton && !this->editMode){
        if(this->lines.size() < 10){
            this->addPoint();
            if(this->numberOfPoints % 2 == 0){
                QGraphicsLineItem *	line = this->addLine(coordinates.last().x(), coordinates.last().y(),
                                                         event->scenePos().x(), event->scenePos().y(),
                                                         QPen (QColor (this->colors[((numberOfPoints / 2) - 1) % 10]), 5));
                lines.append(line);
                line->setFlags(QGraphicsItem::ItemIsSelectable);
                QPolygon arrowHead;
                QPointF arrowRoot = line->line().pointAt(0.9);
                int k = QLineF(line->line()).length() / 10;
                arrowHead.putPoints(0, 3, line->line().x2(), line->line().y2(),
                                    qFloor(arrowRoot.x() + line->line().dy() / k), qFloor(arrowRoot.y() - line->line().dx() / k),
                                    qFloor(arrowRoot.x() - line->line().dy() / k), qFloor(arrowRoot.y() + line->line().dx() / k));

                QGraphicsPolygonItem * arrowHeadItem = this->addPolygon(arrowHead, QPen (QColor (this->colors[((numberOfPoints / 2) - 1) % 10]), 5),
                        QBrush(QColor (this->colors[((numberOfPoints / 2) - 1) % 10])));
                this->arrows.append(new Arrow(line, arrowHeadItem, this->colors[((numberOfPoints / 2) - 1) % 10]));
            }
            coordinates.append(event->scenePos());
        }
        else{
            cout << "Maximum number of lines reached" << endl;
        }
    }
}

