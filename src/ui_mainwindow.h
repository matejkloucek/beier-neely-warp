#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *sourceGraphicsView;
    QGraphicsView *targetGraphicsView;
    QPushButton *warpButton;
    QLabel *warningLabel;
    QPushButton *clearButton;
    QLabel *parametersLabel;
    QDoubleSpinBox *aSpinBox;
    QLabel *aLabel;
    QLabel *bLabel;
    QDoubleSpinBox *bSpinBox;
    QLabel *cLabel;
    QDoubleSpinBox *pSpinBox;
    QPushButton *hintButton;
    QPushButton *loadButton;
    QPushButton *editButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 700);
        MainWindow->setAutoFillBackground(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        sourceGraphicsView = new QGraphicsView(centralwidget);
        sourceGraphicsView->setObjectName("sourceGraphicsView");
        sourceGraphicsView->setGeometry(QRect(100, 100, 350, 350));
        targetGraphicsView = new QGraphicsView(centralwidget);
        targetGraphicsView->setObjectName("targetGraphicsView");
        targetGraphicsView->setGeometry(QRect(550, 100, 350, 350));
        warpButton = new QPushButton(centralwidget);
        warpButton->setObjectName("warpButton");
        warpButton->setGeometry(QRect(370, 540, 251, 71));
        warningLabel = new QLabel(centralwidget);
        warningLabel->setObjectName("warningLabel");
        warningLabel->setGeometry(QRect(380, 465, 231, 31));
        clearButton = new QPushButton(centralwidget);
        clearButton->setObjectName("clearButton");
        clearButton->setGeometry(QRect(500, 630, 89, 25));
        editButton = new QPushButton(centralwidget);
        editButton->setObjectName("editButton");
        editButton->setGeometry(QRect(400, 630, 89, 25));
        editButton->setText("Edit");
        parametersLabel = new QLabel(centralwidget);
        parametersLabel->setObjectName("parametersLabel");
        parametersLabel->setGeometry(QRect(100, 40, 121, 21));
        aSpinBox = new QDoubleSpinBox(centralwidget);
        aSpinBox->setObjectName("aSpinBox");
        aSpinBox->setGeometry(QRect(320, 40, 61, 26));
        aSpinBox->setDecimals(2);
        aSpinBox->setMinimum(0.010000000000000);
        aSpinBox->setMaximum(0.100000000000000);
        aSpinBox->setSingleStep(0.010000000000000);
        aSpinBox->setValue(0.010000000000000);
        aLabel = new QLabel(centralwidget);
        aLabel->setObjectName("aLabel");
        aLabel->setGeometry(QRect(290, 40, 31, 21));
        QFont font;
        font.setPointSize(13);
        aLabel->setFont(font);
        bLabel = new QLabel(centralwidget);
        bLabel->setObjectName("bLabel");
        bLabel->setGeometry(QRect(460, 40, 31, 21));
        bLabel->setFont(font);
        bSpinBox = new QDoubleSpinBox(centralwidget);
        bSpinBox->setObjectName("bSpinBox");
        bSpinBox->setGeometry(QRect(490, 40, 65, 26));
        bSpinBox->setMinimum(0.500000000000000);
        bSpinBox->setMaximum(2.000000000000000);
        bSpinBox->setSingleStep(0.050000000000000);
        bSpinBox->setValue(0.700000000000000);
        cLabel = new QLabel(centralwidget);
        cLabel->setObjectName("cLabel");
        cLabel->setGeometry(QRect(630, 40, 31, 21));
        cLabel->setFont(font);
        pSpinBox = new QDoubleSpinBox(centralwidget);
        pSpinBox->setObjectName("pSpinBox");
        pSpinBox->setGeometry(QRect(660, 40, 65, 26));
        pSpinBox->setMaximum(1.000000000000000);
        pSpinBox->setSingleStep(0.100000000000000);
        pSpinBox->setValue(0.500000000000000);
        hintButton = new QPushButton(centralwidget);
        hintButton->setObjectName("hintButton");
        hintButton->setGeometry(QRect(810, 40, 89, 25));
        loadButton = new QPushButton(centralwidget);
        loadButton->setObjectName("loadButton");
        loadButton->setGeometry(QRect(450, 500, 89, 25));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Beier-Neely Image Warping", nullptr));
        warpButton->setText(QCoreApplication::translate("MainWindow", "WARP", nullptr));
        warningLabel->setText(QString());
        clearButton->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        parametersLabel->setText(QCoreApplication::translate("MainWindow", "Set paramaters: ", nullptr));
        aLabel->setText(QCoreApplication::translate("MainWindow", "a = ", nullptr));
        bLabel->setText(QCoreApplication::translate("MainWindow", "b = ", nullptr));
        cLabel->setText(QCoreApplication::translate("MainWindow", "p = ", nullptr));
        hintButton->setText(QCoreApplication::translate("MainWindow", "Hint", nullptr));
        loadButton->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
