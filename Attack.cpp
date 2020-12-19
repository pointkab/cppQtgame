//
// Created by pointkab on 2020/12/18.
//
#include <QtCore/QCoreApplication>
#include "Attack.h"
Attack::Attack() {
    IsVisable = false;
    Isreach = false;
    speed = 15;
    _sendPoint = new QPoint();
    _desPoint = new QPoint();
    set_attackImg();
}

void Attack::set_attackImg() {
    this->_attackImg = QCoreApplication::applicationDirPath() + "../../qrc/playerAttack.png";
}