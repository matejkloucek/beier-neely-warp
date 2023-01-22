#ifndef CLICKABLEGRAPHICSSCENE_H
#define CLICKABLEGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>

class ClickableGraphicsScene : public QGraphicsScene
{
private:
    QList<QPointF> coordinates;
    QList<QGraphicsLineItem *> lines;
    int numberOfPoints = 0;
    QImage image;
    QString fileName = ":/resources/img/F-original.png";
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
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
};


#endif // CLICKABLEGRAPHICSSCENE_H
