#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QDesktopWidget>
#include <QStyle>
#include <QPainter>
#include <QColor>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QTimer>
#include "start.h"
#include "myscene.h"
#include "theme.h"

extern int themeNum;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

private:
    Ui::MainWindow *ui;
    MyScene *gameScene;
    theme *pause;
    QTimer *Timer;
    QString message;
    qint16 blockSize;


private slots:
    void on_Pause_clicked();
    void recieve(int);
};
#endif // MAINWINDOW_H
