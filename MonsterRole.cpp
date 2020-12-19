//
// Created by pointkab on 2020/11/29.
//

#include <QtCore/QCoreApplication>
#include "Qtime"
#include "QPoint"
#include "MonsterRole.h"
#define WIDTH 1700
#define HEIGHT 900

int MonsterRole::MonsterLocateArray[MonsterNumber][2];
int MonsterRole::randArg = 0;
int MonsterRole::markNum;

MonsterRole::MonsterRole(): speed(2), _liveStatus(1), _attack(100), _bloodBar(200),IsReach(true){
    _skill = "HunCircleKongfu";
    set_imgPath();
    QPoint tempPoint;
    tempPoint = locateRandCreate();
    _locatedX = tempPoint.x();
    _locatedY = tempPoint.y();
}

void MonsterRole::set_imgPath() {
    this->_imgPath = QCoreApplication::applicationDirPath() + "../../qrc/Monster.png";
}


QPoint MonsterRole::locateRandCreate() {
    QTime time = QTime::currentTime();
    QPoint result;
    qsrand(time.msec() + time.second()*1000);
    for (int i = 0; i <= MonsterRole::randArg;i++){
        result.setX(qrand() % (WIDTH-98));
        result.setY(qrand() % (HEIGHT-90 -30)+30);
    }
    MonsterRole::randArg += 2;
    return result;
}

void MonsterRole::Relive() {
    _liveStatus = 1;
    QPoint temppoint = locateRandCreate();
    _locatedX = temppoint.x();
    _locatedY = temppoint.y();
}

bool MonsterRole::IsOverlap(int tx, int ty) {
    if (abs(tx - this->Get_X()) < 60 && abs(ty - this->Get_Y()) < 68)
    {
        return true;
    } else{
        return false;
    }
}