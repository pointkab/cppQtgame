//
// Created by pointkab on 2020/11/18.
//

#include <QtCore/QCoreApplication>
#include <QtGui/QPainter>
#include "math.h"
#include "QPushButton"
#include "QMouseEvent"
#include "GameUi.h"
#include "QToolTip"
#define WIDTH 1700
#define HEIGHT 900
//todo 音效系统
GameUi::GameUi(QWidget *parent):QMainWindow(parent)  {
    this->initGameWindow();
    player = CreatPlayerRole();
    randReFreshTimer = new QTimer(this);
    ReliveMonsterTimer = new QTimer(this);
    monsterTimer = new QTimer(this);
    //3 second relive monsters
    ReliveMonsterTimer->start(3000);
    //rand argument refresh frequency
    randReFreshTimer->start(1500);
    MonsterRole::markNum = 0;
    MonsterRole* tempMonster;
    //碰撞数组初始化
    for (int i = 0; i < MonsterNumber;i++){
        overlapArray[i] = -1;
    }
    overlapNum = 0;
    //怪物生成的函数
    for (int i = 0; i < MonsterNumber;i++)
    {
        if (tempMonster = CreatMonsterRole()){
            monsters[MonsterRole::markNum++] = tempMonster;
        }
    }
    //处理玩家和怪物位置数据和是否重叠的函数
    connect(this->monsterTimer,&QTimer::timeout, this, &GameUi::DealFun);
    //随机参数刷新
    connect(this->randReFreshTimer,&QTimer::timeout,[=](){
       MonsterRole::randArg = 0;
    });
    //复活怪物的函数
    connect(this->ReliveMonsterTimer,&QTimer::timeout,[=](){
       for (int i = 0;i < MonsterRole::markNum;i++){
           if (!monsters[i]->_liveStatus){
               monsters[i]->Relive();
               while(monsters[i]->IsOverlap(player->Get_X(),player->Get_Y()))
               {
                   monsters[i]->Relive();
               }
           }
       }
    });
}

QPoint GameUi::RoleGo(Arg &argment) {
    int xflag,yflag;
    QPoint result;
    int dx = argment.dx - argment.x;
    int dy = argment.dy - argment.y;
    if (dx == 0&&dy == 0){
        result.setX(0);
        result.setY(0);
        argment.IsReach = true;
        return result;
    }
    if (dx < 0)
    {
        xflag = -1;
    } else if(dx == 0){
        xflag = 0;
    } else{
        xflag = 1;
    }
    if (dy < 0)
    {
        yflag = -1;
    } else if(dy == 0){
        yflag = 0;
    } else{
        yflag = 1;
    }
    if (abs(dx) >= abs(dy)&&dx != 0){
        if (abs(dx) <= argment.speed){
            result.setX(dx);
            result.setY(dy);
            argment.IsReach = true;
            return result;
        } else
            {
                double rate = (double)dy/(double )dx;
                if (abs((argment.speed*rate*2)) >= floor(abs((argment.speed*rate)))*2+1)
                {
                    result.setX(argment.speed*xflag);
                    result.setY(ceil(abs(argment.speed*rate))*yflag);
                    return result;
                } else{
                    result.setX(argment.speed*xflag);
                    result.setY(floor(abs(argment.speed*rate))*yflag);
                    return result;
                }
            }
    } else if (dy != 0){
        if (abs(dy) <= argment.speed){
            result.setX(dx);
            result.setY(dy);
            argment.IsReach = true;
            return result;
        }
        else {
            double rate = (double) dx / (double) dy;
            if (abs((argment.speed * rate * 2)) >= floor(abs((argment.speed * rate))) * 2 + 1)
            {
                result.setY(argment.speed*yflag);
                result.setX(ceil(abs(argment.speed*rate))*xflag);
                return result;
            } else {
                result.setY(argment.speed*yflag);
                result.setX(floor(abs(argment.speed*rate))*xflag);
                return result;
            }
        }
    }
}

void GameUi::ShowUI(void) {
    //设置背景图片
    QImage backImage;
    QImage backImage1;
    QString imagePath = QCoreApplication::applicationDirPath();
    imagePath += "../../qrc/glassimage.jpg";
    backImage.load(imagePath);
    backImage1 = backImage.scaled(WIDTH,HEIGHT);
    QPalette palette1;
    palette1.setBrush(this->backgroundRole(),QBrush(backImage1));
    this->setPalette(palette1);
    this->setAutoFillBackground(true);
    this->show();
    //global and monster timer
    monsterTimer->start(1000/24);
}

void GameUi::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton){
        player->Move(e->x()-45,e->y()-49);
        player->set_IsReach(false);
    }
    if (e->button() == Qt::RightButton){
        player->attack(e->x(),e->y());
    }
}

void GameUi::paintEvent(QPaintEvent*) {
    QPainter a(this);
    for (int i = 0; i < MonsterRole::markNum;i++){
        if (monsters[i]->_liveStatus)
        a.drawPixmap(monsters[i]->Get_X(),monsters[i]->Get_Y(),QPixmap(monsters[i]->Get_imgPath()));
    }
    //for 循环画怪
    if (player->_liveStatus)
    a.drawPixmap(player->Get_X(),player->Get_Y(),QPixmap(player->Get_imgPath()));
    if (player->Get_attack()&&player->Get_attack()->IsVisable){
        a.drawPixmap(player->Get_attack()->Get_X(),player->Get_attack()->Get_Y(),QPixmap(player->Get_attack()->Get_ImgPath()));
    }
}

void GameUi::initGameWindow() {
    this->setWindowTitle("游戏中");
    this->setFixedSize(WIDTH, HEIGHT);
    //菜单
    BackMemuBar = new QMenuBar(this);
    BackMemuBar->setGeometry(0,0,width(),30);
    BackMenu = new QMenu("菜单",this);
    QAction * actBack = BackMenu->addAction("返回");
    BackMemuBar->addMenu(BackMenu);
    connect(actBack,&QAction::triggered, [=](){
        sendClose();
    });
    connect(this,&GameUi::MonsterBeDefeat,[=](){
        QToolTip::showText(QPoint(this->geometry().x()+player->Get_X(), this->geometry().y()+player->Get_Y()),"经验 +10",this);
    });
}

PlayerRole* GameUi::CreatPlayerRole() {
    PlayerRole *p = new PlayerRole();
    p->set_BloodBarParent(this);
    return p;
}

MonsterRole* GameUi::CreatMonsterRole() {
    MonsterRole *p = new MonsterRole();
    if (MonsterRole::markNum > MonsterNumber)
    {
        return NULL;
    }
    MonsterRole::MonsterLocateArray[MonsterRole::markNum][0] = p->Get_X();
    MonsterRole::MonsterLocateArray[MonsterRole::markNum][1] = p->Get_Y();
    return p;
}

void GameUi::DealFun() {
    QPoint tempPoint;
    if (!player->Get_IsReach()){
        Arg temp(player->Get_X(),player->Get_Y(),player->Get_dx(),player->Get_dy(),player->Get_speed(),player->Get_IsReach());
        QPoint dPoint = RoleGo(temp);
        player->set_IsReach(temp.IsReach);
        player->SetX_Y(dPoint.x(),dPoint.y());
        player->updateBloodBar();
    }
    for (int i = 0; i < MonsterRole::markNum;i++){
        if (monsters[i]->Get_isreach()) {
            tempPoint = monsters[i]->locateRandCreate();
            monsters[i]->Move(tempPoint.x(), tempPoint.y());
            monsters[i]->Set_isReach(false);
        }
        Arg temp(monsters[i]->Get_X(),monsters[i]->Get_Y(),monsters[i]->Get_dx(),monsters[i]->Get_dy(),monsters[i]->Get_speed(),monsters[i]->Get_isreach());
        tempPoint = RoleGo(temp);
        monsters[i]->SetX_Y(tempPoint.x(),tempPoint.y());
        MonsterRole::MonsterLocateArray[i][0] = monsters[i]->Get_X();
        MonsterRole::MonsterLocateArray[i][1] = monsters[i]->Get_Y();
        monsters[i]->Set_isReach(temp.IsReach);
    }
    if (player->Get_attack()){
        if (!player->Get_attack()->Get_Isreach()){
            Arg temp(player->Get_attack()->Get_X(),player->Get_attack()->Get_Y(),player->Get_attack()->Get_dx(),player->Get_attack()->Get_dy(),player->Get_attack()->Get_speed(),player->Get_attack()->Get_Isreach());
            tempPoint = RoleGo(temp);
            player->Get_attack()->updateSendPoint(tempPoint.x(),tempPoint.y());
            player->Get_attack()->set_Isreach(temp.IsReach);
        } else{
            player->Get_attack()->IsVisable = false;
        }
    }
    IsOverlap();
    AttackJudge();
    if (overlapNum){
        OverlapMonster(overlapNum);
        player->set_Exp(overlapNum);
        ReMoveDeadMonster();
        player->IsUpgrade();
        player->updateBloodBar();
    }
    if(!player->IsAlive()){
        monsterTimer->stop();
        player->hideBloodBar();
    }
    update();
}

void GameUi::IsOverlap() {
    for (int i = 0; i < MonsterRole::markNum;i++){
        if (monsters[i]->_liveStatus){
            if (abs(player->Get_X() - monsters[i]->Get_X()) < 60 && abs(player->Get_Y() - monsters[i]->Get_Y()) < 68)
            {
                overlapArray[overlapNum++] = i;
            }
        }
    }
}

void GameUi::AttackJudge() {
    if (player->Get_attack())
    {for (int i = 0; i < MonsterRole::markNum;i++){
            if (monsters[i]->_liveStatus){
                if (abs(player->Get_attack()->Get_X() - monsters[i]->Get_X() -45) < 30 && abs(player->Get_attack()->Get_Y() - monsters[i]->Get_Y()-49) < 38)
                {
                    monsters[i]->_liveStatus = 0;
                    player->set_Exp(1);
                    player->IsUpgrade();
                    player->updateBloodBar();
                    player->Get_attack()->IsVisable = false;
                    player->Get_attack()->set_Isreach(true);
                    emit MonsterBeDefeat();
                }
            }
        }
    }
}

void GameUi::ReMoveDeadMonster() {
    for (int i = 0; i < overlapNum;i++){
        monsters[overlapArray[i]]->_liveStatus = 0;
        emit MonsterBeDefeat();
    }
    for (int i = 0; i < MonsterNumber;i++){
        overlapArray[i] = -1;
    }
    overlapNum = 0;
}

void GameUi::OverlapMonster(int number){
    int temp = monsters[0]->Get_attack();
    player->set_bloodBar(-temp*number);
}

