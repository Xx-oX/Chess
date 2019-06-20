#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QGraphicsScene>
#include "editorscene.h"
#include "theme.h"
#include "multi.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(int mode,QWidget *parent = nullptr,bool a = false,QString ip = "127.0.0.1");
    ~Dialog();

private slots:
    void on_pause_clicked();

    void on_back_clicked();

private:
    Ui::Dialog *ui;
    editorScene *Scene;
    Multi *NetScene;
    theme *pause;
};

#endif // DIALOG_H
