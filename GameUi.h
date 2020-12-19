//
// Created by pointkab on 2020/11/18.
//

#ifndef QTGAME_GAMEUI_H
#define QTGAME_GAMEUI_H
#include "QMainWindow"
#include "QPalette"
#include "QPaintEvent"
#include "QImage"
#include "QAction"
#include "QMenuBar"
#include "QMenu"
#include "QTimer"
#include "PlayerRole.h"
#include "MonsterRole.h"

class Arg{
public:
    int x;
    int y;
    int dx;
    int dy;
    int speed;
    bool IsReach;
    Arg(int x,int y,int dx,int dy,int speed,bool isreach):x(x),y(y),dx(dx),dy(dy),speed(speed),IsReach(isreach){}
};

class GameUi : public QMainWindow{
    Q_OBJECT
public:
    explicit GameUi(QWidget *parent = 0);
    void initGameWindow();
    //创建玩家角色
    PlayerRole* CreatPlayerRole();
    //绘图事件
    void paintEvent(QPaintEvent *);
    //鼠标事件
    void mousePressEvent(QMouseEvent *e);
    MonsterRole* CreatMonsterRole();
    QPoint RoleGo(Arg &argment);
    void ReMoveDeadMonster();
    //int IsOverlap(int i,int tx,int ty);
    void IsOverlap();
    void OverlapMonster(int number);
    void SetPause(bool judge){
        if (judge){
            monsterTimer->stop();
        } else{
            monsterTimer->start(1000/24);
        }
    };
    void AttackJudge();
signals:
    void sendClose();
    void MonsterBeDefeat();
public slots:
    void ShowUI(void);
    void DealFun();

private:
    //返回按钮
    QMenuBar *BackMemuBar;
    QMenu *BackMenu;
    //玩家角色
    PlayerRole *player;
    QTimer *randReFreshTimer;
    QTimer *monsterTimer;
    QTimer *ReliveMonsterTimer;
    MonsterRole* monsters[MonsterNumber];
    int overlapArray[MonsterNumber];
    int overlapNum;
    //是否到达终点
};


#endif //QTGAME_GAMEUI_H
