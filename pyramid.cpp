#include "pyramid.h"
#include "ui_pyramid.h"

Pyramid::Pyramid(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Pyramid)
{

    ui->setupUi(this);
    ui->image_label->setGeometry(50,50,500,500);
    QImage *image = new QImage(500, 500, QImage::Format_Mono);
    image->setColorCount(1);
    image->setColor(0, qRgba(255, 255, 255, 255));
    ui->image_label->setPixmap(QPixmap::fromImage(*image));
    ui->label_size2->setText(QString::number(image->height())+'x'+QString::number(image->width()));
    }

Pyramid::~Pyramid()
{
    delete ui;
}

void Pyramid::on_actionClose_triggered()
{
    close();
}
