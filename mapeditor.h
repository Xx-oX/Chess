#ifndef MAPEDITOR_H
#define MAPEDITOR_H
#include <QDialog>

namespace Ui {
class MapEditor;
}

class MapEditor : public QDialog
{
    Q_OBJECT

public:
    explicit MapEditor(QWidget *parent = nullptr);
    ~MapEditor();
protected:
    void closeEvent(QCloseEvent *);

signals:
    void exit();

private slots:
    void gotoEditor();

private:
    Ui::MapEditor *ui;
    bool showEditor;
};
#endif // MAPEDITOR_H
