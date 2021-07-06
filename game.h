#ifndef GAME_H
#define GAME_H
#include<QPainter>
#include <QWidget>
#include<QPen>
#include<QPushButton>
#include<QMouseEvent>
#include<QMediaPlayer>

class game : public QWidget
{
    Q_OBJECT
public:
    explicit game(QWidget *parent = nullptr);
    int flag=0;       //记录步数，奇数为黑棋，偶数为白棋
    const int game_size=20;  //记录棋盘大小，20*20的单元格
    const int width=20;      //网格宽度
    const int start_x=20;     //开始位置横坐标
    const int start_y=20;     //开始位置纵坐
    int a[21][21];            //棋子数组,存储棋子信息，黑棋为1，白棋为-1
    QPushButton *regame=new QPushButton;         //重新开始按钮
    QPushButton *quit_game=new QPushButton;      //退出游戏
    QPushButton *start_music=new QPushButton;       //播放音乐
    QPushButton *stop_music=new QPushButton;        //停止播放
    QMediaPlayer *sound=new QMediaPlayer;     //音乐资源

private:
    int Array_x,Array_y;            //数组坐标
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent*event);
    void win();
    void mousePressEvent(QMouseEvent *event);

signals:
private slots:
    void re_game();
    void start_mu();
    void finsih_mu();
};

#endif // GAME_H
