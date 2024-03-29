#define QT_NO_OPENGL
#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QDialog>

#include "snakewindow.h"
#include "shareinfo.h"
#include<QString>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLCDNumber;
class QLabel;
class QPushButton;
class QRadioButton;
class QSlider;
QT_END_NAMESPACE

class SnakeWindow;

class Homepage:public QDialog
{
    Q_OBJECT
public:
    Homepage(QWidget *parent=0);

private slots:
    void changeStyle(const QString &styleName);
    void helpClickFunc();
    void infoClickFunc();
    void beginClickFunc();
    void backHomepageFunc();

private:
    void createModeGroupBox();
    void createMessageGroupBox();
    void createThemeGroupBox();
    void createDifficultyGroupBox();


    THEME theme;
    int difficulty;
    GAMEMODE mode;

    SnakeWindow *window;


    QPalette originalPalette;

    QGroupBox *themeGroupBox;
    QLabel *styleLabel;
    QComboBox *styleComboBox;

    QGroupBox *modeGroupBox;
    QRadioButton *singlePlayerButton;
    QRadioButton *doublePlayerButton;
    QRadioButton *playWithAIButton;
    QRadioButton *watchAIButton;

    QGroupBox *difficultyGroupBox;
    QSlider *difficultySlider;

    QGroupBox *messageGroupBox;
    QPushButton *helpButton;
    QPushButton *infoButton;

    QPushButton *beginButton;
    QPushButton *quitButton;
};

#endif // HOMEPAGEWINDOW_H
