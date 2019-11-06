#include "pyramid.h"
#include "ui_pyramid.h"

Pyramid::Pyramid(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Pyramid)
{

    ui->setupUi(this);
    //ui->image_label->setGeometry(50,50,500,500);
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
            if (hash.contains(fileName))
            {
                QMessageBox::information(this, tr("Warning!"),
                                         tr("Этот файл уже открыт,попробуйте другой").arg(fileName));

            }
            else{
            ui->comboBox->addItem(fileName);
            ui->comboBox->setCurrentText(fileName);
            if (image.isNull())
            {
                QMessageBox::information(this, tr("Image Viewer"),
                                         tr("Cannot load %1.").arg(fileName));
                return;
            }
            ui->comboBox_layers->setCurrentIndex(0);
            ui->comboBox_layers->clear();
            //************************************************************************************************
            //Вызываем дополнительное диалоговое окно,для получения количества слоев пирамиды
            bool okno;
            QString str=QInputDialog::getText(0,"Ввод","Количество слоев",QLineEdit::Normal,"0",&okno);
            setLayers(str.toInt());  //Получаем численное значение количества слоев

            picture=new QPixmap(QPixmap::fromImage(image));
            ui->image_label->resize(picture->width(),picture->height());
            gener_pics();
    }


}
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
    ui->comboBox_layers->clear();
    for(int i=0;i<getLayers();i++)
    {
        ui->comboBox_layers->addItem(QString::number(i));
        pics.insert(i,picture->toImage().scaled(picture->width()/pow(2,i),picture->height()/pow(2,i)));
    }
    hash.insert(getName(),pics);
    changelayers(0);
}
void Pyramid::gener_hash(QString name)
{
    ui->comboBox_layers->clear();
    for(int i=0;i<hash.value(name).size();i++)
    {
       ui->comboBox_layers->addItem(QString::number(i));
    }
    hash.value(name).value(0);
    setName(name);
    ui->image_label->setPixmap(QPixmap::fromImage(hash.value(name).value(0)));
}

QString Pyramid::getName() const
{
    return name;
}

void Pyramid::setName(const QString &value)
{
    name = value;
}

void Pyramid::changelayers(int layernumber)
{
    ui->image_label->setPixmap(QPixmap::fromImage(hash.value(getName()).value(layernumber)).scaled(picture->width(),picture->height()));
    ui->label_size2->setText(QString::number(hash.value(getName()).value(layernumber).width())+"x"+QString::number(hash.value(getName()).value(layernumber).height()));
}

void Pyramid::on_comboBox_layers_currentIndexChanged(int index)
{
    changelayers(index);
}

void Pyramid::on_comboBox_currentIndexChanged(const QString &arg1)
{

    gener_hash(arg1);
}
