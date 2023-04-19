#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QFileDialog>
#include <opencv2/opencv.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateFrame();
	 void openVideoFile();
//	 void on_actionOpen_triggered();
	 void on_actionOpen_triggered();
	 void playVideo();
	 void stopVideo();
//	 void setupActions();

private:
    Ui::MainWindow *ui;
//    cv::VideoCapture cap;
    QTimer *timer;
    cv::VideoCapture cap;
    cv::Mat frame;
//    QLabel *label; // QLabelポインタのメンバ変数を追加
};
#endif // MAINWINDOW_H
