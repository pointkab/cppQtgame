//
// Created by pointkab on 2020/11/29.
//

#ifndef QTGAME_MONSTERROLE_H
#define QTGAME_MONSTERROLE_H

#include "Role.h"
#define MonsterNumber 5

class MonsterRole: public Role {
public:
    //存活状态
    int _liveStatus;
    MonsterRole();
    QString Get_imgPath(){return _imgPath;}
    static int MonsterLocateArray[MonsterNumber][2];
    static int randArg;
    static int markNum;
    void set_imgPath();
    QPoint locateRandCreate();
    void Move(int dx,int dy) {
        _DestX = dx;
        _DestY = dy;
    };
    int Get_X(){return this->_locatedX;};
    int Get_Y(){return this->_locatedY;};
    int Get_dx(){return this->_DestX;};
    int Get_dy(){return this->_DestY;};
    int Get_speed(){return this->speed;};
    int Get_isreach(){return this->IsReach;}
    int Get_attack(){return this->_attack;}
    void SetX_Y(int _x,int _y){
        _locatedX +=_x;
        _locatedY +=_y;
    };
    void Set_isReach(bool isreach){IsReach = isreach;}
    bool IsOverlap(int tx,int ty);
    void Relive();
private:
    //位置坐标
    int _locatedX;
    int _locatedY;
    int _DestX;
    int _DestY;
    //移动速度
    int speed;
    bool IsReach;
    //血条
    int _bloodBar;
    //攻击
    int _attack;
    //技能
    QString _skill;
    //贴图地址
    QString _imgPath;
};


#endif //QTGAME_MONSTERROLE_H
