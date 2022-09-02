#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    udp_client = new UdpClient();
    custom_scene = new CustomGraphicScene();
    client_reciev_thread = new QThread(this);

    // Устанавливаем графическую сцену
    ui->graphicsView->setScene(custom_scene);

    // Соединяю сигнал destroyed со слотом quit для закрытия потока:
    connect(this, &Widget::destroyed, client_reciev_thread, &QThread::quit);

    // Соединение слота параметров с сигналом из udp_client для получения параметров из поток сетевой части клиента
    connect(udp_client, &UdpClient::signal_ParametersFromServer, custom_scene, &CustomGraphicScene::slot_ParametersFromServer,Qt::QueuedConnection);
    connect(udp_client, &UdpClient::signal_ParametersFromServer, this, &Widget::slot_ParametersFromServer,Qt::QueuedConnection);

    // Закидываю сетевую часть приложения в поток:
    udp_client->moveToThread(client_reciev_thread);
    client_reciev_thread->start();

    // Заполняю список цветов заднего фона
    settingBackgroundColour();

    // заполняю combobox с цветами прицела
    settingSightColorInCombobox();

    // Отключаем скроллбар по вертикали и горизонтали
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Соединяем слот установки цвета прицела из Sight с сигналом из Widget
    connect(this, &Widget::signal_SetColorSight, custom_scene->sight, &Sight::slot_SetColorSight);

    // Соединяем сигнал, испускаемый при смене размера виджетов и соответствующий слот из CustomGraphicScene
    connect(this, &Widget::signal_GraphicsViewNewSize, custom_scene, &CustomGraphicScene::slot_GraphicsViewNewSize);

    on_comboBox_background_color_currentIndexChanged(ui->comboBox_background_color->currentIndex());

    ui->graphicsView->resize(400,300);
    custom_scene->setStartgraphicsViewSize(ui->graphicsView->size());

}

Widget::~Widget()
{
    delete ui; 
    delete custom_scene;
}

void Widget::settingBackgroundColour()
{
    //Заполняю список цветов заднего фона:
    QPair<QString,QColor> color;

    color.first = "Черный";
    color.second = QColor(Qt::black);
    background_colors.append(color);

    color.first = "Белый";
    color.second = QColor(Qt::white);
    background_colors.append(color);

    color.first = "Серый";
    color.second = QColor(Qt::gray);
    background_colors.append(color);

    //Отображаю список цветов в combobox:
    for(auto color:background_colors)
        ui->comboBox_background_color->addItem(color.first);
}

void Widget::settingSightColorInCombobox()
{
    for(auto color:custom_scene->sight->Get_sight_colors())
        ui->comboBox_sight_color->addItem(color.first);
}


void Widget::on_comboBox_background_color_currentIndexChanged(int index)
{
    custom_scene->setBackgroundBrush(QBrush(background_colors.at(index).second));
}


void Widget::on_comboBox_sight_color_currentTextChanged(const QString &arg1)
{
    emit signal_SetColorSight(arg1);
}

void Widget::slot_ParametersFromServer(qreal viewing_angle, qreal horizontal_shift, qreal vertical_shift)
{
    qDebug() << "Client Widget = "<<QThread::currentThreadId();
    ui->lineEdit_camera_angle->setText(QString::number(viewing_angle));
    ui->lineEdit_horizontal_shift->setText(QString::number(horizontal_shift));
    ui->lineEdit_vertical_shift->setText(QString::number(vertical_shift));

}

void Widget::resizeEvent(QResizeEvent *e)
{
    // Реализация условия про соотношение сторон:
    if(ui->graphicsView->width() > ratioWidetoHeigh*ui->graphicsView->height()){
        ui->graphicsView->resize(ratioWidetoHeigh*ui->graphicsView->height(),ui->graphicsView->height());

    }else {
        ui->graphicsView->resize(ui->graphicsView->width(),ui->graphicsView->width()/ratioWidetoHeigh);
    }

    ui->graphicsView->setGeometry((this->width()-ui->graphicsView->width())/2,0,ui->graphicsView->width(),ui->graphicsView->height());

    emit signal_GraphicsViewNewSize(ui->graphicsView->size());

    qDebug()<<"this->size() = "<<this->size();
    qDebug()<<"ui->graphicsView->size() = "<<ui->graphicsView->size();

    QWidget::resizeEvent(e);
}

