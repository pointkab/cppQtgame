//
// Created by pointkab on 2020/11/29.
//

#include "PlayerRole.h"
#include <QtCore/QCoreApplication>
#include "QPainter"




void PlayerRole::set_imgPath() {
    this->_imgPath = QCoreApplication::applicationDirPath() + "../../qrc/role.png";
}

PlayerRole::PlayerRole(){
    _exp = 0;
    _level = 1;
    _locatedX = 100;
    _locatedY = 100;
    _bloodBar = 200;
    _maxBlood = 200;
    speed = 7;
    _liveStatus = 1;
    _attack = 10;
    IsReach = true;
    _skill = "FlashFiveWhips";
    playerAttack = NULL;
    CreatBloodBar();
    set_imgPath();
}

void PlayerRole::CreatBloodBar() {
    playerBloodBar = new QProgressBar();
    playerBloodBar->setMinimum(0);
    playerBloodBar->setMaximum(_maxBlood);
    playerBloodBar->setValue(_bloodBar);
    playerBloodBar->setOrientation(Qt::Horizontal);
    playerBloodBar->setGeometry(_locatedX,_locatedY-20,98,20);
    playerBloodBar->setFormat("%v");
    playerBloodBar->setStyleSheet("QProgressBar{border:none;color:white;text-align:center;background:rgb(0,0,0);}QProgressBar::chunk{border:none;background:rgb(255,0,0);}");
}

void PlayerRole::updateBloodBar() {
    playerBloodBar->setMinimum(0);
    playerBloodBar->setMaximum(_maxBlood);
    playerBloodBar->setValue(_bloodBar);
    playerBloodBar->setGeometry(_locatedX,_locatedY-20,98,20);
    playerBloodBar->setFormat("%v");
}

void PlayerRole::IsUpgrade() {
    if (_exp > 2*10*_level*(_level-1)){
        Upgrade();
    }
}

void PlayerRole::attack(int x, int y) {
    if (playerAttack == NULL) {
        playerAttack = new Attack();
    }
    playerAttack->set_desPoint(x-10,y-10);
    playerAttack->set_sendPoint(_locatedX+45,_locatedY+49);
    playerAttack->IsVisable = true;
    playerAttack->set_Isreach(false);
}
