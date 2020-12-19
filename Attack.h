//
// Created by pointkab on 2020/12/18.
//

#ifndef QTGAME_ATTACK_H
#define QTGAME_ATTACK_H
#include "QString"
#include "QPoint"
//右键触发攻击
class Attack {
public:
    Attack();
    void set_attackImg();
    void set_sendPoint(int x,int y){
        _sendPoint->setX(x);
        _sendPoint->setY(y);
    };
    void set_desPoint(int x,int y){
        _desPoint->setX(x);
        _desPoint->setY(y);
    };
    void updateSendPoint(int dx,int dy){
        _sendPoint->setX(_sendPoint->x()+dx);
        _sendPoint->setY(_sendPoint->y()+dy);
    }
    int Get_X(){return _sendPoint->x();}
    int Get_Y(){return _sendPoint->y();}
    int Get_dx(){return _desPoint->x();}
    int Get_dy(){return _desPoint->y();}
    int Get_speed(){return speed;}
    bool Get_Isreach(){return Isreach;}
    QString Get_ImgPath(){return _attackImg;}
    void set_Isreach(bool isreach){Isreach = isreach;}
    bool IsVisable;
private:
    bool Isreach;
    int speed;
   QPoint *_sendPoint{};
   QPoint *_desPoint{};
   QString _attackImg;
};


#endif //QTGAME_ATTACK_H
