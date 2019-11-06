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
            //************************************************************************************************
            //Вызываем дополнительное диалоговое окно,для получения количества слоев пирамиды
            bool okno;
            QString str=QInputDialog::getText(0,"Ввод","Количество слоев",QLineEdit::Normal,"0",&okno);
            setLayers(str.toInt());  //Получаем численное значение количества слоев

            picture=new QPixmap(QPixmap::fromImage(image));
            ui->image_label->resize(picture->width(),picture->height());
    }
            gener_pics();

   // ui->image_label->setPixmap(*picture);
}

int Pyramid::getLayers() const
{
    return layers;
}

void Pyramid::setLayers(int value)
{
    layers = value;
}
void Pyramid::gener_pics()
{
    for(int i=0;i<getLayers();i++)
    {
        ui->comboBox_layers->addItem(QString::number(i));
        pics.insert(i,picture->toImage().scaled(picture->width()/pow(2,i),picture->height()/pow(2,i)));
    }
    ui->image_label->setPixmap(QPixmap::fromImage(pics[0]));
}
