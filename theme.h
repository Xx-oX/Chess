#ifndef THEME_H
#define THEME_H

#include <QDialog>

namespace Ui {
class theme;
}

class theme : public QDialog
{
    Q_OBJECT

public:
    explicit theme(QWidget *parent = nullptr);
    ~theme();

private slots:
    void on_classic_clicked();

    void on_newspaper_clicked();

    void on_bit_clicked();

signals:
    void send(int);

private:
    Ui::theme *ui;
};

#endif // THEME_H
