#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QMessageBox>
#include <map>
#include <iostream>
#include "entity.h"
#include "asteroidbig.h"
#include "planet.h"
#include "sellingpoint.h"
#include "spaceship.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_buttonAddPlanet_clicked();

    void on_xPosSpinBox_editingFinished();

    void on_yPosSpinBox_editingFinished();

    void on_xVelSpinBox_editingFinished();

    void on_yVelSpinBox_editingFinished();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_asteroidBigAdd_clicked();

    void on_asteroidMediumAdd_clicked();

    void on_asteroidSmallAdd_clicked();

    void on_levelEdgeSpinBox_editingFinished();

    void on_rotationSpinBox_editingFinished();

    void on_massSpinBox_editingFinished();

    void on_sellingPointAdd_clicked();

    void on_actionWczytaj_triggered();

    void on_actionZapisz_triggered();

    void on_zoomButtonUp_clicked();

    void on_zoomButtonDown_clicked();

    void on_spaceshipAdd_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    int itemID;
    std::map<int, Entity*> entityList;

    void UpdateView();
    void UpdateComboBox();
};

#endif // MAINWINDOW_H
