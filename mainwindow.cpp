//
// Created by pointkab on 2020/11/17.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"
#define WINDOW_W 1117
#define WINDOW_H 752

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*窗口标题，大小设置*/
    this->setWindowTitle("精灵游戏");
    this->setFixedSize(WINDOW_W,WINDOW_H);
    CreateGameUi();
    /* 设置button事件链接 */
    //退出按钮
    connect(ui->quitButton,&QPushButton::clicked, this,&MainWindow::close);
    //开始按钮
    connect(ui->startButton,&QPushButton::clicked, [=](){
        gameui->SetPause(false);
        gameui->ShowUI();
    });
    connect(ui->startButton,&QPushButton::clicked,this,&QMainWindow::hide);
    connect(this->gameui,&GameUi::sendClose, [=](){
        gameui->SetPause(true);
        reshow();
    });
    this->SetBackGroundImage();
}

void MainWindow::SetBackGroundImage() {
    QString imagePath = QCoreApplication::applicationDirPath();
    imagePath += "../../qrc/ui.jpg";
    UiImage.load(imagePath);
    UiImage1 = UiImage.scaled(WINDOW_W,WINDOW_H);
    palette1.setBrush(this->backgroundRole(),QBrush(UiImage1));
    this->setPalette(palette1);
    this->setAutoFillBackground(true);
}

void MainWindow::CreateGameUi() {
    gameui = new GameUi(this);
}

void MainWindow::reshow() {
    this->show();
    this->gameui->close();
}


MainWindow::~MainWindow()
{
    delete ui;
}

