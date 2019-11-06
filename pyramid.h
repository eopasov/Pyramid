#ifndef PYRAMID_H
#define PYRAMID_H
#include <QMainWindow>
#include <QScrollArea>

namespace Ui {
class Pyramid;
}

class Pyramid : public QMainWindow
{
    Q_OBJECT

public:
    explicit Pyramid(QWidget *parent = 0);
    ~Pyramid();

private slots:
    void on_actionClose_triggered();

private:
    Ui::Pyramid *ui;
    QPixmap *picture;
};

#endif // PYRAMID_H
