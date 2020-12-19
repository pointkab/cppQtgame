//
// Created by pointkab on 2020/11/19.
//

#ifndef QTGAME_ROLE_H
#define QTGAME_ROLE_H
#include "QString"

class Role {
public:
    virtual void set_imgPath() = 0;
private:
    //位置坐标
    int _locatedX;
    int _locatedY;
    int _DestX;
    int _DestY;
    int speed;
    //血条
    int _bloodBar;
    //存活状态
    int _liveStatus;
    //攻击
    int _attack;
    //技能
    QString _skill;
    //贴图地址
    QString _imgPath;
};


#endif //QTGAME_ROLE_H
