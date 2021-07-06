#include "widget.h"
#include"game.h"
#include<QPushButton>
#include<QWidget>
#include<QPainter>
#include<QImage>
#include<QPalette>
#include<QPixmap>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(300,400);
    QImage Image(":/new/back");
    QPalette palettle;
    Image.scaled(this->width(),this->height(),Qt::IgnoreAspectRatio);
    palettle.setBrush(backgroundRole(),QBrush(Image));
    setPalette(palettle);
    fivbtn_start->setText("开始游戏");
    fivbtn_finish->setText("退出游戏");
    fivbtn_finish->move(150,200);
    fivbtn_start->show();
    fivbtn_finish->show();
    layout->addWidget(fivbtn_start);        //设置按钮位置
    layout->addWidget(fivbtn_finish);
    setLayout(layout);

    //建立点击按钮事件联系
    connect(fivbtn_finish,&QPushButton::clicked,this,&Widget::close);
    connect(fivbtn_start,&QPushButton::clicked,this,&Widget::close);
    connect(fivbtn_start,&QPushButton::clicked,this,&Widget::Gstartbutton);
}

Widget::~Widget()
{
}
void Widget::Gstartbutton(){
    game_play->show();
}

