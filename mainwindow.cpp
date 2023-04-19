#include <cfloat> // こちらを推奨
#include <QDebug>
#include <QLabel>
#include <QSettings>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSize>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QWidget>
#include <opencv2/imgproc.hpp>

QLabel *label; // QLabelポインタのメンバ変数を追加

MainWindow::MainWindow(QWidget *parent)
		  : QMainWindow(parent) {
//MainWindow::MainWindow(QWidget *parent)
//    : QMainWindow(parent), ui(new Ui::MainWindow) {
	 //ui->setupUi(this);は、このコードにより、フォームのすべてのウィジェットがインスタンス化され、ウィンドウの構成が完了します。したがって、このコードは、Qt Designerで作成されたGUIフォームを使用する場合には必要です。
//	 ui->setupUi(this);//これはとにかくuiの設定をする.これはuiのため

	 //配置関係のオブジェクト
	 QVBoxLayout *vmainLayout = new QVBoxLayout();
	 QHBoxLayout *hmainLayout = new QHBoxLayout();
//	 QVBoxLayout *vmainLayout = new QVBoxLayout(centralWidget);
	 //addWidget:ウィジェットをレイアウトに追加する.QVBoxLayoutのメソッド.
	 //QVBoxLayout:ウィジェットを縦に並べるレイアウト
//	 vmainLayout->addWidget(label, 0, Qt::AlignCenter);

	 //QWidgetクラスには、GUI要素の外観、大きさ、位置、配置などを定義するための多数のメソッドが用意されています。
	 QWidget *centralWidget = new QWidget(this);
	 //setCentralWidget:メインウィンドウの中央にウィジェットを設定する.QMainWindowのメソッド
	 //一般的に、メソッドはアクションを実行するために使用され、プロパティはオブジェクトの状態を取得または設定するために使用されます。
	 setCentralWidget(centralWidget);

	 QMenuBar *menuBar = new QMenuBar(this);
	 setMenuBar(menuBar); // メニューバーを設定する
	 //QMenu:ポップアップメニュー
	 QMenu *menuFile = menuBar->addMenu(tr("&File"));
	 //QMenuオブジェクトは、メニューのコンテナを表します。メニューには、アクション（例えば、新規作成、開く、保存など）を追加することができます。アクションは、ユーザーがメニューを開いてクリックすることで、アプリケーション内の機能を実行することができます。
//    timer->start(1000 / cap.get(cv::CAP_PROP_FPS));
	 QAction *openAction = new QAction(tr("&Open"), this);
//    QAction *openAction = new QAction(this);
	 openAction->setShortcut(QKeySequence::Open);//操作
	 openAction->setStatusTip(tr("Open a file"));//操作
	 //this:つまりMainWindowクラスのオブジェクト(インスタンス)を指す
	 //MAinWindow:アプリケーションのメインウィンドウを作成するために使用されることが
	 connect(openAction, &QAction::triggered, this, &MainWindow::openVideoFile); // メニューアクションを接続する
	 menuFile->addAction(openAction); // Fileメニューに追加する
//	 ui->menuFile->addAction(openAction); // Fileメニューに追加する
	 // Quit アクションの追加
	 QAction *quitAction = new QAction(tr("&Quit"), this);
	 quitAction->setShortcut(QKeySequence::Quit);
	 quitAction->setStatusTip(tr("Quit the application"));
	 //終了
	 connect(quitAction, &QAction::triggered, this, &MainWindow::close);
	 menuFile->addAction(quitAction);
//メニューバーへの追加
	 menuBar->addMenu(menuFile);

//labelは画像表示用
//	 QLabel *label; // QLabelポインタのメンバ変数を追加
	 label = new QLabel(this); // QLabelインスタンスを割り当てる
	 label->setScaledContents(true); // QLabelのサイズに合わせて画像を拡大縮小する
	 label->setGeometry(QRect(0, 0, 640, 480));
	 label->setFixedSize(640, 480); // 固定サイズを設定
	 label->setAlignment(Qt::AlignCenter); // 中央寄せ


	 // メインウィンドウのサイズを画像のサイズに合わせる
	 //this:つまりMainWindowクラスのオブジェクト(インスタンス)を指す
	 //親のオブジェクトにも
	 timer = new QTimer(this);
	 //timerオブジェクトのtimeoutシグナルをupdateFrameスロットに接続する
	 //この connect 関数は、timer の timeout シグナルが発生したときに、MainWindow クラスの updateFrame スロットを呼び出すように設定しています。つまり、タイマーが動作している間、updateFrame 関数が定期的に呼び出され、ビデオフレームが更新され続けます。したがって、動画の画像が再生され続けます。
	 connect(timer, &QTimer::timeout, this, &MainWindow::updateFrame);

	 //////////////////////////////////////////////////
	 //Playボタンについて
	 QPushButton *playButton = new QPushButton("Play",this);

	 //////////////////////////////////////////////////////
	 //これでウィジェットを中心におけます
	 vmainLayout->addWidget(label, 0, Qt::AlignCenter);
//	 vmainLayout->addWidget(playButton, 0, Qt::AlignCenter);
	 QWidget *centralWidget_again = new QWidget();
	 centralWidget_again->setLayout(vmainLayout);
	 setCentralWidget(centralWidget_again);
//	 setMenuBar(menuBar); // メニューバーを設定する
//	 QAction *playAction = new QAction(tr("&Play"), this);
//	 playAction->setShortcut(Qt::Key_Space);
//	 playAction->setStatusTip(tr("Play the video"));
//	 connect(playButton, &QPushButton::clicked, this, &MainWindow::playVideo);
//これだからupdateされるだけ
//	 connect(playButton, &QPushButton::clicked, this, &MainWindow::updateFrame);
	 connect(playButton, &QPushButton::clicked, this, &MainWindow::playVideo);
//	 connect(playAction, &QAction::triggered, this, &MainWindow::playVideo);
//	 menuFile->addAction(playAction);
	 vmainLayout->addWidget(playButton, 0, Qt::AlignCenter);

	 QAction *stopAction = new QAction(tr("&Stop"), this);
	 stopAction->setShortcut(Qt::Key_Escape);
	 stopAction->setStatusTip(tr("Stop the video"));
	 connect(stopAction, &QAction::triggered, this, &MainWindow::stopVideo);
	 menuFile->addAction(stopAction);

	 menuBar->addMenu(menuFile);
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
	 cv::resize(frame, frame, cv::Size(label->width(), label->height())); // フレームをリサイズする
	 // フレームをQImageに変換する
    QImage image(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
	 // QImageをQPixmapに変換する
    QPixmap pixmap = QPixmap::fromImage(image);
	 // ラベルにQPixmapをセットする
    label->setPixmap(pixmap); // ui->labelの代わりにlabelを使う
	 label->setGeometry(QRect(0, 0, 640, 480));
	 label->setFixedSize(640, 480); // 固定サイズを設定
	 label->setScaledContents(true); // labelのサイズに動画のサイズに合わせる
//	 label->setGeometry(QRect((width() - frame.cols) / 2, (height() - frame.rows) / 2, frame.cols, frame.rows));

//	 label->setScaledContents(false); // labelのサイズに動画のサイズに合わせる
//	 // labelのサイズを動画のサイズに合わせる
////	 label->setFixedSize(frame.cols, frame.rows);
//	 if (frame.cols > label->width() || frame.rows > label->height()) {
//		  label->setPixmap(pixmap.scaled(label->size(), Qt::KeepAspectRatio, Qt::FastTransformation)); // labelのサイズをフレームのサイズに合わせる
//	 }

}
void MainWindow::on_actionOpen_triggered()
{
	 openVideoFile();
}

void MainWindow::openVideoFile()
{
	 QSettings settings("MyCompany", "MyApp");
	 QString lastPath = settings.value("LastPath").toString();
	 QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video File"), lastPath,
																	 tr("Video Files (*.avi *.mp4 *.mkv);;All Files (*)"));

	 if (!fileName.isEmpty()) {
		  cap.open(fileName.toStdString());
		  if (!cap.isOpened()) {
				qDebug() << "Error opening video file";
				return;
		  }
//ここをstartにするか？stopにするかで動画が止まるか止まらないかが決まる
		  timer->start(1000 / cap.get(cv::CAP_PROP_FPS));
//		  timer->stop();
		  QFileInfo fileInfo(fileName);
		  settings.setValue("LastPath", fileInfo.absolutePath());
	 }
}
void MainWindow::stopVideo()
{
	 timer->stop();
	 cap.release(); // カメラ/ビデオファイルを開放する
}
void MainWindow::playVideo()
{
	 if (!cap.isOpened()) {
		  return;
	 }
	 if (timer->isActive()) {
		  return; // 再生中は何もしない
	 }

	 // 最初のフレームを読み込んで表示する
	 cap.read(frame);
	 if (frame.empty()) {
		  qDebug() << "End of video";
		  return;
	 }

	 cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
	 cv::resize(frame, frame, cv::Size(label->width(), label->height())); // フレームをリサイズする
	 QImage image(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
	 QPixmap pixmap = QPixmap::fromImage(image);
	 label->setPixmap(pixmap);
	 label->setGeometry(QRect(0, 0, 640, 480));
	 label->setFixedSize(640, 480); // 固定サイズを設定

	 // 再生ボタンを押した時にタイマーを開始する
	 timer->start(1000 / cap.get(cv::CAP_PROP_FPS));
	 // cap.release(); // カメラ/ビデオファイルを開放する
}