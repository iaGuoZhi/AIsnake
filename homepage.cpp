#define QT_NO_OPENGL

#include<QtWidgets>
#include <QDebug>
#include<QMessageBox>
#include "homepage.h"
#include "costomstyle.h"
#include "snakewindow.h"
#include "foreststyle.h"
#include "prairiestyle.h"
#include "seastyle.h"




Homepage::Homepage(QWidget *parent):QDialog(parent)
{
    this->resize(800,400);
    createModeGroupBox();
    createMessageGroupBox();
    createThemeGroupBox();
    createDifficultyGroupBox();


    beginButton=new QPushButton(tr("开始游戏"));
    connect(beginButton,SIGNAL(clicked()),this,SLOT(beginClickFunc()));
    quitButton=new QPushButton(tr("退出游戏"));
    connect(quitButton,&QPushButton::clicked,qApp, &QApplication::quit);
    QGridLayout *mainLayout=new QGridLayout;
    mainLayout->addWidget(modeGroupBox,0,0,3,3);
    mainLayout->addWidget(messageGroupBox,0,3,3,2);
    mainLayout->addWidget(themeGroupBox,3,3,2,2);
    mainLayout->addWidget(difficultyGroupBox,3,0,2,3);
    mainLayout->addWidget(beginButton,5,0,1,5);
    mainLayout->addWidget(quitButton,6,0,1,5);

    setLayout(mainLayout);

    setWindowTitle(tr("QSnake"));
    changeStyle("森林");
}

void Homepage::createThemeGroupBox()
{
    themeGroupBox =new QGroupBox(tr("选择主题"));
    originalPalette=QApplication::palette();
    QApplication::setPalette(originalPalette);

    styleComboBox=new QComboBox;
    styleComboBox->addItem("森林");
    styleComboBox->addItem("草原");
    styleComboBox->addItem("海洋");
    styleComboBox->addItems(QStyleFactory::keys());

    styleLabel=new QLabel(tr("&主题:"));
    styleLabel->setBuddy(styleComboBox);


    connect(styleComboBox,SIGNAL(activated(QString)),this,SLOT(changeStyle(QString)));

    connect(&window,SIGNAL(backHomepage()),this,SLOT(backHomepageFunc()));
    QVBoxLayout *layout=new QVBoxLayout;
     layout->addWidget(styleLabel);
     layout->addWidget(styleComboBox);
      layout->addStretch(1);

     themeGroupBox->setLayout(layout);

}
void Homepage::changeStyle(const QString &styleName)
{
    if (styleName == "森林") {
        QApplication::setStyle(new forestStyle);
    } else {
        if(styleName == "草原")
        {
            QApplication::setStyle(new prairiestyle);
        }
        else{
            if(styleName == "海洋")
            {
                       QApplication::setStyle(new seastyle);
            }
        else{
        QApplication::setStyle(QStyleFactory::create(styleName));
    }
    }
}
}

void Homepage::createModeGroupBox()
{
    modeGroupBox=new QGroupBox(tr("选择模式"));

    singlePlayerButton=new QRadioButton(tr("单人游戏"));
    doublePlayerButton=new QRadioButton(tr("双人PK"));
    playWithAIButton=new QRadioButton(tr("人机对战"));
    watchAIButton=new QRadioButton(tr("AI观战"));


    singlePlayerButton->setChecked(true);

    QVBoxLayout *layout=new QVBoxLayout;
    layout->addWidget(singlePlayerButton);
    layout->addWidget(doublePlayerButton);
    layout->addWidget(playWithAIButton);
    layout->addWidget(watchAIButton);
    layout->addStretch(1);

    modeGroupBox->setLayout(layout);

}

void Homepage::createMessageGroupBox()
{
    messageGroupBox=new QGroupBox(tr("游戏信息"));
    helpButton=new QPushButton(tr("游戏帮助"));
    infoButton=new QPushButton(tr("关于游戏"));

    connect(helpButton,SIGNAL(clicked()),this,SLOT(helpClickFunc()));
    connect(infoButton,SIGNAL(clicked()),this,SLOT(infoClickFunc()));

    QVBoxLayout *layout=new QVBoxLayout;
    layout->addWidget(helpButton);
    layout->addWidget(infoButton);
    layout->addStretch(1);

    messageGroupBox->setLayout(layout);

}

void Homepage::createDifficultyGroupBox()
{
    difficultyGroupBox=new QGroupBox(tr("设置难度"));
    difficultySlider=new QSlider(Qt::Horizontal,difficultyGroupBox);
    difficultySlider->setValue(50);

    QVBoxLayout *layout=new QVBoxLayout;
    layout->addWidget(difficultySlider);
    layout->addStretch(1);

    difficultyGroupBox->setLayout(layout);
}

void Homepage::helpClickFunc()
{
    QMessageBox::about(this,tr("帮助信息"),tr("这是一个充满挑战的小游戏\n"
                                          "游戏模式：单人游戏，双人游戏，人机对战，AI观战\n"
                                          "操作说明:\n"
                                          "单人模式 或者　玩家一  方向键控制移动  ?键隐身;\n"
                                          "玩家二　AWSD控制方向　Ｑ键隐身\n"
                                          "规则说明:\n"
                                          "       1.每次吃到食物会得分，得分越高，等级越高，移动速度越快；\n"
                                          "       2.当蛇咬到自己或者头部撞到墙壁，或者头部与被自己长的蛇的头部相碰时死亡\n"
                                          "       3.在双人对战模式下吃到特定食物时，玩家会具有隐身的能力\n"
                                          "       4.观战模式中，系统将用算法操纵蛇的移动，达到最短路径寻找食物，自动避免障碍物的效果\n"
                                          "       5.人机对战中，AI未解锁隐身、截获功能\n"
                                          "       6.双人游戏中，蛇具有截获蛇身的能力，如果蛇头咬到其他蛇的蛇身，则被咬蛇的蛇身之后的长度将移动至该蛇\n"
                                          "       7.双人游戏中，如果两个蛇头相触，则蛇身短的蛇死亡\n"
                                            ));
}

void Homepage::infoClickFunc()
{
    QMessageBox::about(this,tr("project info"),tr("the first project of course software practice\n"
                                                  "taught by software school SJTU\n"
                                                  "coded by zhiGuo,a 2017th student\n"
                                                  "powered by qt creator\n"
                                                  "the whole demo is uploaded to github:\n"
                                                  "https://github.com/Guozhi-explore/AIsnake"));
}

void Homepage::beginClickFunc()
{
    /*keep the checked mode*/
    if(singlePlayerButton->isChecked())
    {
        this->mode=GAMEMODE::SINGLEPLAYER;
    }
    if(doublePlayerButton->isChecked())
    {
        this->mode=GAMEMODE::DOUBLEPLAYER;
    }
    if(playWithAIButton->isChecked())
    {
        this->mode=GAMEMODE::PLAYWITHAI;
    }
    if(watchAIButton->isChecked())
    {
        this->mode=GAMEMODE::WATCHAIPLAY;
    }

    /*keep the checked style*/
    if(styleComboBox->currentText()=="森林")
    {
        this->theme=THEME::COSTOM_FOREST;
    }
    if(styleComboBox->currentText()=="草原")
    {
        this->theme=THEME::COSTOM_PIRARIE;
    }
    if(styleComboBox->currentText()=="海洋")
    {
        this->theme=THEME::COSTOM_SEA;
    }
    if(styleComboBox->currentText()=="Windows")
    {
        this->theme=THEME::SYSTEM_WINDOWS;
    }
    if(styleComboBox->currentText()=="Fusion")
    {
        this->theme=THEME::SYSTEM_FUSION;
    }

    /*keep the difficulty value*/
    this->difficulty=difficultySlider->value();

    window.remakeAsOrder(this->mode,this->theme,this->difficulty);

    this->hide();
    window.show();
}

void Homepage::backHomepageFunc()
{
    window.hide();
    this->show();
}


