#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clickablegraphicsscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_warpButton_clicked();
    void on_clearButton_clicked();

    void on_aSpinBox_valueChanged(double arg1);

    void on_bSpinBox_valueChanged(double arg1);

    void on_pSpinBox_valueChanged(double arg1);

    void on_hintButton_clicked();

    void on_loadButton_clicked();

private:
    Ui::MainWindow *ui;
    ClickableGraphicsScene sourceScene;
    ClickableGraphicsScene targetScene;
    void removeAllLines(ClickableGraphicsScene * scene);
    void warp();
    QRgb assignPixel(float x, float y);
    float shortestDist(QVector2D x, QLineF qp ,float u, float v);
    float a;
    float b;
    float p;
    int myCeil(float x);
    float correctColor(float x);
};
#endif // MAINWINDOW_H
