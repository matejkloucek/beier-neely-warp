#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "clickablegraphicsscene.h"
#include <iostream>
#include <QVector2D>
#include <QFileDialog>
#include <QMessageBox>
#include <QtMath>


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // setting up main window
    ui->setupUi(this);
    ui->sourceGraphicsView->setScene(&sourceScene);
    ui->targetGraphicsView->setScene(&targetScene);
    ui->sourceGraphicsView->adjustSize();
    ui->targetGraphicsView->adjustSize();
    ui->warningLabel->setStyleSheet("QLabel {color : red; }");
    this->a = ui->aSpinBox->value();
    this->b = ui->bSpinBox->value();
    this->p = ui->pSpinBox->value();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_warpButton_clicked()
{
    // making sure that the number of lines is equal
    QList<QGraphicsLineItem*> targetLines = targetScene.getaAllLines();
    QList<QGraphicsLineItem*> sourceLines = sourceScene.getaAllLines();
    ui->warningLabel->setGeometry(QRect(380, 465, 231, 31));
    if(sourceLines.size() == 0 || targetLines.size() == 0){
        ui->warningLabel->setText("Add lines to both images!");
    }
    else if(targetLines.size() != sourceLines.size()){
        ui->warningLabel->setText("Both images need to have the same amount of lines!");
    }
    else{
        ui->warningLabel->setText("");     
        sourceScene.setEditMode(false);
        targetScene.setEditMode(false);
        ui->clearButton->setText("Reset");
        // start warping
        this->warp();
    }
    ui->warningLabel->adjustSize();
}

void MainWindow::on_clearButton_clicked()
{
    if(sourceScene.getEditMode()){
       // remove selected lines
        this->removeSelectedLines(&sourceScene, &targetScene);
        this->removeSelectedLines(&targetScene, &sourceScene);
    }
    else{
        // removing lines, setting default image
        this->removeAllArrows(&sourceScene);
        this->removeAllArrows(&targetScene);
        QImage sourceImage = sourceScene.getImage();
        targetScene.setImage(sourceImage);
        sourceScene.setImage(sourceImage);
        ui->warningLabel->setText("");
    }
}

void MainWindow::on_editButton_clicked()
{
    if(sourceScene.getEditMode()){
        ui->warningLabel->setText("");
        ui->warningLabel->setGeometry(QRect(380, 465, 231, 31));
        ui->clearButton->setText("Reset");
    }
    else{
        ui->warningLabel->setText("YOU ARE NOW IN EDIT MODE (Select lines by double-clicking on them and then delete them by pressing the 'Delete' button)");
        ui->warningLabel->setGeometry(QRect(100, 465, 231, 31));
        ui->warningLabel->adjustSize();
        ui->clearButton->setText("Delete");
    }
    sourceScene.switchEditMode();
    targetScene.switchEditMode();

}

void MainWindow::removeAllLines(ClickableGraphicsScene * scene)
{
    QList<QGraphicsLineItem*> lines = scene->getaAllLines();
    for(int i = 0; i < lines.size(); i++){
        scene->removeItem(lines[i]);
    }
    scene->clearLines();
    scene->clearCoordinates();
}

void MainWindow::removeSelectedLines(ClickableGraphicsScene *searchedScene, ClickableGraphicsScene * otherScene)
{
    QList<QGraphicsItem *> selectedLines = searchedScene->selectedItems();
    for(int i = 0; i < selectedLines.size(); i++){
        QColor color = searchedScene->getArrowColor(selectedLines[i]);
        otherScene->removeArrow(color);
        searchedScene->removeArrow(color);
    }
}

void MainWindow::removeAllArrows(ClickableGraphicsScene *scene)
{
    QList<Arrow *> arrows = scene->getAllArrows();
    for(int i = 0; i < arrows.size(); i++){
        scene->removeItem(arrows[i]->getArrowHead());
        scene->removeItem(arrows[i]->getLine());
    }
    scene->clearLines();
    scene->clearCoordinates();
    scene->clearArrows();
}

void MainWindow::warp()
{
    QImage targetImage = targetScene.getImage();
    QList<QGraphicsLineItem*> targetLines = targetScene.getaAllLines();
    QList<QGraphicsLineItem*> sourceLines = sourceScene.getaAllLines();
    // Beier - Neely algorithm
    for(int i=0; i < targetImage.width(); i++){
        for(int j = 0; j < targetImage.height(); j++){
            QVector2D weightedDisplacementSum = QVector2D(0, 0);
            float weightSum = 0;
            for(int k = 0; k < targetLines.size(); k++){
                QVector2D xp = QVector2D(i - targetLines[k]->line().x1(), j - targetLines[k]->line().y1());
                QVector2D qp = QVector2D(targetLines[k]->line().x2() - targetLines[k]->line().x1(),
                        targetLines[k]->line().y2() - targetLines[k]->line().y1());
                float u = QVector2D::dotProduct(xp, qp) / QVector2D::dotProduct(qp, qp);
                QVector2D perp_qp = QVector2D(targetLines[k]->line().y2() - targetLines[k]->line().y1(),
                        -(targetLines[k]->line().x2() - targetLines[k]->line().x1()));
                float v = QVector2D::dotProduct(xp, perp_qp) / qSqrt(QVector2D::dotProduct(qp, qp));
                QVector2D source_p = QVector2D(sourceLines[k]->line().x1(), sourceLines[k]->line().y1());
                QVector2D source_qp = QVector2D(sourceLines[k]->line().x2() - sourceLines[k]->line().x1(),
                        sourceLines[k]->line().y2() - sourceLines[k]->line().y1());
                QVector2D source_perp_qp = QVector2D(sourceLines[k]->line().y2() - sourceLines[k]->line().y1(),
                        -(sourceLines[k]->line().x2() - sourceLines[k]->line().x1()));
                QVector2D sourcePixel = source_p + u * source_qp + v * source_perp_qp / qSqrt(QVector2D::dotProduct(source_qp, source_qp));
                QVector2D displacement = QVector2D(sourcePixel.x() - i, sourcePixel.y() - j);
                float dist = this->shortestDist(QVector2D(i, j), targetLines[k]->line(), u, v);
                float weight = qPow(qPow(qSqrt(QVector2D::dotProduct(qp, qp)) , this->p) / (this->a + dist), this->b);
                weightedDisplacementSum = weightedDisplacementSum + displacement * weight;
                weightSum = weightSum + weight;
            }
            QVector2D weightedSourcePixel = QVector2D(i, j) + weightedDisplacementSum / weightSum;
            targetImage.setPixel(i, j, this->assignPixel(weightedSourcePixel.x(), weightedSourcePixel.y()));
        }
    }
    targetScene.setImage(targetImage);
    this->removeAllArrows(&sourceScene);
    this->removeAllArrows(&targetScene);
    sourceScene.setImage(sourceScene.getImage());
}

QRgb MainWindow::assignPixel(float x, float y)
{
    QImage sourceImage = sourceScene.getImage();
    if(x < 0 || x >= sourceImage.width() || y < 0 || y >= sourceImage.height()){
        return qRgb(0, 0 ,0);
    }
    // Bilinear interpolation
    float a = x - qFloor(x);
    float b = y - qFloor(y);
    QColor c1 = sourceImage.pixelColor(qFloor(x), qFloor(y));
    QColor c2 = sourceImage.pixelColor(myCeil(x), qFloor(y));
    QColor c3 = sourceImage.pixelColor(qFloor(x), myCeil(y));
    QColor c4 = sourceImage.pixelColor(myCeil(x), myCeil(y));
    float red = (1 - b) * ((1 - a) * c1.redF() + a * c2.redF()) + b * ((1 - a) * c3.redF() + a * c4.redF());
    float green = (1 - b) * ((1 - a) * c1.greenF() + a * c2.greenF()) + b * ((1 - a) * c3.greenF() + a * c4.greenF());
    float blue = (1 - b) * ((1 - a) * c1.blueF() + a * c2.blueF()) + b * ((1 - a) * c3.blueF() + a * c4.blueF());
    red = correctColor(red);
    green = correctColor(green);
    blue = correctColor(blue);
    QColor color;
    color.setRgbF(red, green, blue);
    return color.rgb();
}

float MainWindow::shortestDist(QVector2D x, QLineF qpLine, float u, float v)
{
    // calculating the shrotest distance of point x to line PQ
    QVector2D p = QVector2D(qpLine.x1(), qpLine.y1());
    QVector2D q = QVector2D(qpLine.x2(), qpLine.y2());
    if(u < 0){
        return qSqrt(QVector2D::dotProduct(x-p, x-p));
    }
    else if(u > 1){
        return qSqrt(QVector2D::dotProduct(x-q, x-q));
    }
    else{
        return qFabs(v);
    }
}

int MainWindow::myCeil(float x)
{
    // making sure to stay within range of the image
    if(qCeil(x) >= sourceScene.getImage().width()){
        return qFloor(x);
    }
    return qCeil(x);
}

float MainWindow::correctColor(float x)
{
    if(x > 1){
        return 1;
    }
    return x;
}


void MainWindow::on_hintButton_clicked()
{
    Dialog * hintDialog = new Dialog(this);
    hintDialog->setWindowTitle("Hint");
    hintDialog->show();
}

void MainWindow::on_aSpinBox_valueChanged(double arg1)
{
    this->a = arg1;
}


void MainWindow::on_bSpinBox_valueChanged(double arg1)
{
    this->b = arg1;
}


void MainWindow::on_pSpinBox_valueChanged(double arg1)
{
    this->p = arg1;
}

void MainWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open image", QDir::homePath(), tr("Images (*.png *.jpg)"));
    QImage newImage = sourceScene.loadImage(fileName);
    sourceScene.setImage(newImage);
    targetScene.setImage(newImage);
}

