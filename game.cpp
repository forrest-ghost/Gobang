#include "game.h"
#include<QPainter>
#include<QPen>
#include<QPushButton>
#include<QMouseEvent>
#include<QString>
#include<QDebug>
#include<QMessageBox>
#include<QPixmap>
#include<QPalette>
#include<QMediaPlayer>

game::game(QWidget *parent) : QWidget(parent)
{
    for (int i=0;i<game_size+1;i++) {
        for (int j=0;j<=game_size;j++) {
            a[i][j]=0;
        }
    }

    //播放音乐
    sound->setMedia(QUrl("qrc:/new/running.mp3"));
    sound->setVolume(50);
    start_mu();

    QImage pixmap1(":/new/fiv_chess");          //背景图片
    QPalette palette;
    QImage pixmap2=pixmap1.scaled(700,500,Qt::IgnoreAspectRatio);
    palette.setBrush(backgroundRole(),QBrush(pixmap2));
    setPalette(palette);
    flag=0;
    Array_x=0;
    Array_y=0;
    //设置鼠标的追踪
    setMouseTracking(true);
        resize(700,500);
        setWindowTitle("五子棋");
        update();
        quit_game->setParent(this);
        quit_game->setText("退出游戏");
        quit_game->move(500,300);
        quit_game->show();
        connect(quit_game,&QPushButton::clicked,this,&game::close); //退出游戏
        regame->setParent(this);
        regame->setText("重新开始");
        regame->move(500,200);
        regame->show();
        connect(regame,&QPushButton::clicked,this,&game::re_game);    //重新开始
        start_music->setParent(this);                       //开始音乐
        start_music->setText("播放音乐");
        start_music->move(500,400);
        start_music->show();
        stop_music->setParent(this);                        //停止音乐
        stop_music->setText("停止音乐");
        stop_music->move(500,450);
        stop_music->show();

            connect(start_music,&QPushButton::clicked,this,&game::start_mu);     //开始播放



            connect(stop_music,&QPushButton::clicked,this,&game::finsih_mu);     //停止播放


}
void game::paintEvent(QPaintEvent *)
{
    QPainter *paint=new QPainter;
    QBrush brush;
    paint->begin(this);
    paint->setPen(QPen(Qt::black,2,Qt::SolidLine));
    for(int i=0;i<=game_size;i++)           //绘制横线
    {
        paint->drawLine(start_x,start_y+i*width,start_x+width*game_size,start_y+i*width);
    }
    for(int i=0;i<=game_size;i++)           //绘制竖线
    {
        paint->drawLine(start_x+width*i,start_y,start_x+width*i,start_y+width*game_size);
    }

    brush.setStyle(Qt::SolidPattern);
    //绘制下棋标记点,显示下一个要下的棋子

    if(Array_x>=0&&Array_x<=20&&Array_y>=0&&Array_y<=20)
    {
   if(flag%2==0)            //下一个是黑棋
   {
       paint->setPen(QPen(Qt::black,4,Qt::SolidLine));
       brush.setColor(Qt::black);
       paint->setBrush(brush);
       paint->drawEllipse(Array_x*width+12.5,Array_y*width+12.5,15,15);
   }
   else {                   //下一个是白棋
       paint->setPen(QPen(Qt::white,4,Qt::SolidLine));
       brush.setColor(Qt::white);
       paint->setBrush(brush);
       paint->drawEllipse(Array_x*width+12.5,Array_y*width+12.5,15,15);
   }
    }
    //绘制棋子
    for (int i=0;i<game_size+1;i++) {
        for (int j=0;j<game_size+1;j++) {
            if(a[i][j]==1)          //绘制黑棋
            {
                paint->setPen(QPen(Qt::black,4,Qt::SolidLine));
                brush.setColor(Qt::black);
                paint->setBrush(brush);
                paint->drawEllipse(i*width+12.5,j*width+12.5,15,15);
            }
            if(a[i][j]==-1)         //绘制白棋
            {
                paint->setPen(QPen(Qt::black,1,Qt::SolidLine));
                brush.setColor(Qt::white);
                paint->setBrush(brush);
                paint->drawEllipse(i*width+12.5,j*width+12.5,15,15);
            }
        }
    }
     paint->end();
}
void game::re_game(){
    for (int i=0;i<21;i++) {
        for (int j=0;j<21;j++) {
            a[i][j]=0;
        }
    }
    flag=0;
    update();
}
    void game::mouseMoveEvent(QMouseEvent *event){
    int x,y;
    x=event->x();           //获取鼠标点的坐标
    y=event->y();
    if(x>=20&&x<=420&&y>=20&&y<=420)
    {

        Array_x=(x-10)/width;
        Array_y=(y-10)/width;

        update();
    }
    else{
        update();
        Array_x=-1;
        Array_y=-1;
    }
//    QString str=QString("鼠标点的位置 x = %1 y = %2").arg(event->x()).arg(event->y());
//    qDebug()<<str;
}
    void game::mousePressEvent(QMouseEvent *event){
        int x,y;
        x=event->x();           //获取鼠标点击处的坐标
        y=event->y();
        if(x>=20&&x<=420&&y>=20&&y<=420)
        {
            Array_x=(x-10)/width;
            Array_y=(y-10)/width;
            flag++;
            if(flag%2==1)
            {
                if(a[Array_x][Array_y]==0)
                {
                    a[Array_x][Array_y]=1;
                }
                else {
                    flag--;
                    QMessageBox *texblack=new QMessageBox;
                    texblack->setParent(this);
                    if(a[Array_x][Array_y]==1)
                    {
                        texblack->information(NULL,"提示","该处已有一个黑棋");
                        texblack->show();
                    }
                    else {
                        texblack->information(NULL,"提示","该处已有一个白棋");
                        texblack->show();
                    }
                }
            }
            else {
                if(a[Array_x][Array_y]==0)
                {
                    a[Array_x][Array_y]=-1;
                }
                else {
                    flag--;
                    QMessageBox *texblack=new QMessageBox;
                    texblack->setParent(this);
                    if(a[Array_x][Array_y]==1)
                    {
                        texblack->information(NULL,"提示","该处已有一个黑棋");
                        texblack->show();
                    }
                    else {
                        texblack->information(NULL,"提示","该处已有一个白棋");
                        texblack->show();
                    }
                }
            }
        }
        else
        {
            Array_x=-1;
            Array_y=-1;
        }
        win();
        update();
    }
    void game::win(){
        int flag_1=0;       //判断黑棋还是白棋获胜，1黑棋，-1白棋
        int fag=0;
        for (int i=0;i<17;i++) {
            for (int j=0;j<17;j++) {
                //上横行扫描
                for (int s=0;s<5;s++) {
                  fag+=a[i][j+s];
                }
                if(fag==5)
                {
                    flag_1=1;
                }
                if(fag==-5)
                {
                    flag_1=-1;
                }
                fag=0;
                //下横行扫描
                for (int s=0;s<5;s++) {
                  fag+=a[i+4][j+s];
                }
                if(fag==5)
                {
                    flag_1=1;
                }
                if(fag==-5)
                {
                    flag_1=-1;
                }
                fag=0;
                //左竖行扫描
                for (int s=0;s<5;s++) {
                  fag+=a[i+s][j];
                }
                if(fag==5)
                {
                    flag_1=1;
                }
                if(fag==-5)
                {
                    flag_1=-1;
                }
                fag=0;
                //右竖行扫描
                for (int s=0;s<5;s++) {
                  fag+=a[i+s][j+4];
                }
                if(fag==5)
                {
                    flag_1=1;
                }
                if(fag==-5)
                {
                    flag_1=-1;
                }
                fag=0;
                //正斜行扫描
                for (int s=0;s<5;s++) {
                  fag+=a[i+s][j+s];
                }
                if(fag==5)
                {
                    flag_1=1;
                }
                if(fag==-5)
                {
                    flag_1=-1;
                }
                fag=0;
                //反斜行扫描
                for (int s=0;s<5;s++) {
                  fag+=a[i+4-s][j+s];
                }
                if(fag==5)
                {
                    flag_1=1;
                }
                if(fag==-5)
                {
                    flag_1=-1;
                }
                fag=0;
            }
        }
        if(flag_1==1)
        {
            QMessageBox *texblack=new QMessageBox;
            texblack->setParent(this);
            texblack->information(NULL,"五子棋","游戏结束，黑棋获胜");
            texblack->show();
        }
        if(flag_1==-1)
        {
            QMessageBox *texblack=new QMessageBox;
            texblack->setParent(this);
            texblack->information(NULL,"五子棋","游戏结束，白棋获胜");
            texblack->show();
        }
        flag_1=0;
    }
    void game::start_mu(){
        sound->play();

    }
    void game::finsih_mu(){
        sound->stop();

    }
