#include <cfloat> // こちらを推奨
#include <QDebug>
#include <QLabel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <opencv2/imgproc.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cap.open("C://Users//survey//Desktop//concon.MP4");
    if (!cap.isOpened()) {
        qDebug() << "Error opening video file";
        return;
    }

    label = new QLabel(this); // QLabelインスタンスを割り当てる
    label->setGeometry(QRect(0, 0, 640, 480)); // QLabelの位置とサイズを設定する

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateFrame);
    timer->start(1000 / cap.get(cv::CAP_PROP_FPS));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateFrame()
{
    cap.read(frame);
    if (frame.empty()) {
        timer->stop();
        qDebug() << "End of video";
        return;
    }

    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    QImage image(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(image);

    label->setPixmap(pixmap); // ui->labelの代わりにlabelを使う
}
