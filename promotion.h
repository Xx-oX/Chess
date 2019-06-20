#ifndef PROMOTION_H
#define PROMOTION_H

#include <QDialog>

namespace Ui {
class promotion;
}

class promotion : public QDialog
{
    Q_OBJECT

public:
    explicit promotion(QWidget *parent = nullptr);
    ~promotion();

private slots:
    void on_QueenButton_clicked();

    void on_BishopButton_clicked();

    void on_KnightButton_clicked();

    void on_RookButton_clicked();

signals:
    void send(int);

private:
    Ui::promotion *ui;
};

#endif // PROMOTION_H
