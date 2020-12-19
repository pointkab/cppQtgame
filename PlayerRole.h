//
// Created by pointkab on 2020/11/29.
//

#ifndef QTGAME_PLAYERROLE_H
#define QTGAME_PLAYERROLE_H
#include "Role.h"
#include "QProgressBar"

class PlayerRole: public Role{
public:
    //存活状态
    int _liveStatus;
    PlayerRole();
    void Move(int dx,int dy) {
        _DestX = dx;
        _DestY = dy;
    };
    int Get_X(){return this->_locatedX;};
    int Get_Y(){return this->_locatedY;};
    int Get_dx(){return this->_DestX;};
    int Get_dy(){return this->_DestY;};
    int Get_speed(){return this->speed;};
    bool Get_IsReach(){return this->IsReach;};
    bool IsAlive(){
        if (_bloodBar <= 0)
        {
            _liveStatus = 0;
            return false;
        }
        else
            return true;
    };
    void SetX_Y(int _x,int _y){
        _locatedX +=_x;
        _locatedY +=_y;
    };
    void set_IsReach(bool _isreach){IsReach = _isreach;}
    void set_imgPath();
    void set_Exp(int number){
        _exp += 10;
    };
    void Upgrade(){
        _level++;
        if (_level%3 == 0){
            if (speed < 11)
                speed++;
            _attack += 10;
            _maxBlood += 30;
        }
        _bloodBar = _maxBlood;
    };
    void IsUpgrade();
    void set_bloodBar(int BloodNum){
        _bloodBar += BloodNum;
    };
    void set_BloodBarParent(QWidget*parent){
        playerBloodBar->setParent(parent);
    };
    void updateBloodBar();
    void hideBloodBar(){
        playerBloodBar->setVisible(false);
    };
    QString Get_imgPath(){return _imgPath;};
private:
    void CreatBloodBar();
    //位置坐标
    int _locatedX;
    int _locatedY;
    int _DestX;
    int _DestY;
    int speed;
    bool IsReach;
    //血条
    int _bloodBar;
    //显示血条
    QProgressBar *playerBloodBar;
    //最大血条
    int _maxBlood;
    //攻击
    int _attack;
    //经验
    int _exp;
    //等级
    int _level;
    //技能
    QString _skill;
    //贴图地址
    QString _imgPath;
};


#endif //QTGAME_PLAYERROLE_H
