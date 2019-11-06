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

    QString getName() const;
    void setName(const QString &value);

private slots:
    void on_actionClose_triggered();
    void gener_pics();
    void on_actionOpen_triggered();
    void gener_hash(QString name);
    void changelayers(int layernumber);
    void on_comboBox_layers_currentIndexChanged(int index);

    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::Pyramid *ui;
    QPixmap *picture;
    QHash<int,QImage> pics;
    int layers;
    QHash<QString,QHash<int,QImage>> hash;
    QString name;
};

#endif // PYRAMID_H
