#include "pyramid.h"
#include "ui_pyramid.h"

Pyramid::Pyramid(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Pyramid)
{

    ui->setupUi(this);
    ui->image_label->setGeometry(50,50,500,500);
//    QImage *image = new QImage(500, 500, QImage::Format_Mono);
    //image->setColorCount(1);
   // image->setColor(0, qRgba(255, 255, 255, 255));
    //ui->image_label->setPixmap(QPixmap::fromImage(*image));
   // ui->label_size2->setText(QString::number(image->height())+'x'+QString::number(image->width()));
    QScrollArea *area=new QScrollArea;
    ui->verticalLayout->addWidget(area);
    area->setWidget(ui->image_label);
    area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->image_label->setScaledContents(true);
}

Pyramid::~Pyramid()
{
    delete ui;
}

void Pyramid::on_actionClose_triggered()
{
    close();
}

void Pyramid::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Images"), "/Users/Pictures/Sample Pictures",
                                                    tr("Image Files (*.png  *.jpg)"));
    if (!fileName.isEmpty())
    {
            QImage image(fileName);
            ui->comboBox->addItem(fileName);
            ui->comboBox->setCurrentText(fileName);
            if (image.isNull())
            {
                QMessageBox::information(this, tr("Image Viewer"),
                                         tr("Cannot load %1.").arg(fileName));
                return;
            }
            picture=new QPixmap(QPixmap::fromImage(image));
            ui->image_label->resize(picture->width(),picture->height());
    }


    ui->image_label->setPixmap(*picture);
}
