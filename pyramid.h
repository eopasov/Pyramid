#ifndef PYRAMID_H
#define PYRAMID_H
#include <QMainWindow>
#include <QScrollArea>
#include <QMessageBox>
#include <QFileDialog>
#include<QInputDialog>

namespace Ui {
class Pyramid;
}

class Pyramid : public QMainWindow
{
    Q_OBJECT

public:
    explicit Pyramid(QWidget *parent = 0);
    ~Pyramid();

    int getLayers() const;
    void setLayers(int value);

private slots:
    void on_actionClose_triggered();
    void gener_pics();
    void on_actionOpen_triggered();

private:
    Ui::Pyramid *ui;
    QPixmap *picture;
    QHash<int,QImage> pics;
    int layers;
};

#endif // PYRAMID_H
