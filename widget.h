#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QVBoxLayout>
#include"game.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QPushButton *fivbtn_start=new QPushButton;
    QPushButton *fivbtn_finish=new QPushButton;
    QVBoxLayout *layout=new QVBoxLayout;
    game *game_play=new game;        //打开游戏界面
public Q_SLOTS:
    void Gstartbutton();
   };
#endif // WIDGET_H
