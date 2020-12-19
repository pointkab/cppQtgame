//
// Created by pointkab on 2020/11/17.
//

#ifndef QTGAME_MAINWINDOW_H
#define QTGAME_MAINWINDOW_H

#include "QMainWindow"
#include "GameUi.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void CreateGameUi();
    void SetBackGroundImage();
    ~MainWindow();
    signals:
public slots:
    void reshow();
private:
    Ui::MainWindow *ui;
    GameUi *gameui;
    QPalette palette1;
    QImage UiImage;
    QImage UiImage1;
};


#endif //QTGAME_MAINWINDOW_H
