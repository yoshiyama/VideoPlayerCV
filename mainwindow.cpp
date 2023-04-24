#include <cfloat> // こちらを推奨
#include <QDebug>
#include <QLabel>
#include <QSettings>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileInfo>
#include <QSize>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QWidget>
#include <QShortcut>
#include <opencv2/imgproc.hpp>

QLabel *label; // QLabelポインタのメンバ変数を追加
QLabel *info_label; // QLabelポインタのメンバ変数を追加
QLabel *fps_label; // QLabelポインタのメンバ変数を追加
QFileInfo *fileInfo;

MainWindow::MainWindow(QWidget *parent)
		  : QMainWindow(parent) {
//MainWindow::MainWindow(QWidget *parent)
//    : QMainWindow(parent), ui(new Ui::MainWindow) {
	 //ui->setupUi(this);は、このコードにより、フォームのすべてのウィジェットがインスタンス化され、ウィンドウの構成が完了します。したがって、このコードは、Qt Designerで作成されたGUIフォームを使用する場合には必要です。
//	 ui->setupUi(this);//これはとにかくuiの設定をする.これはuiのため

	 //配置関係のオブジェクト
	 QVBoxLayout *vmainLayout = new QVBoxLayout();
	 QHBoxLayout *hmainLayout = new QHBoxLayout();

	 //QWidgetクラスには、GUI要素の外観、大きさ、位置、配置などを定義するための多数のメソッドが用意されています。
	 QWidget *centralWidget = new QWidget(this);
	 //setCentralWidget:メインウィンドウの中央にウィジェットを設定する.QMainWindowのメソッド
	 //一般的に、メソッドはアクションを実行するために使用され、プロパティはオブジェクトの状態を取得または設定するために使用されます。
	 setCentralWidget(centralWidget);

	 QMenuBar *menuBar = new QMenuBar(this);
	 setMenuBar(menuBar); //ウィンドウにメニューバーを設定する
	 //QMenu:ポップアップメニュー
	 QMenu *menuFile = menuBar->addMenu(tr("&File"));
	 //QMenuオブジェクトは、メニューのコンテナを表します。メニューには、アクション（例えば、新規作成、開く、保存など）を追加することができます。アクションは、ユーザーがメニューを開いてクリックすることで、アプリケーション内の機能を実行することができます。
//    timer->start(1000 / cap.get(cv::CAP_PROP_FPS));
	 QAction *openAction = new QAction(tr("&Open"), this);
	 openAction->setShortcut(QKeySequence::Open);//操作
	 openAction->setStatusTip(tr("Open a file"));//操作
	 menuFile->addAction(openAction); // Fileメニューに追加する
	 //this:つまりMainWindowクラスのオブジェクト(インスタンス)を指す
	 //MAinWindow:アプリケーションのメインウィンドウを作成するために使用されることが
	 connect(openAction, &QAction::triggered, this, &MainWindow::openVideoFile); // メニューアクションを接続する
	 ////////////////////////////////////////

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
//	 label->setGeometry(QRect(0, 0, 640, 480));
	 label->setFixedSize(640, 480); // 固定サイズを設定
	 label->setAlignment(Qt::AlignCenter); // 中央寄せ

	 info_label = new QLabel(this); // QLabelインスタンスを割り当てる
	 vmainLayout->addWidget(info_label);
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
	 //Stopボタンについて
	 QPushButton *stopButton = new QPushButton("Stop",this);
//	 stopButton= setShortcut(Qt::Key_Escape);
	 //////////////////////////////////////////////////////
	 //これでウィジェットを中心におけます
	 vmainLayout->addWidget(label, 0, Qt::AlignCenter);
//	 vmainLayout->addWidget(playButton, 0, Qt::AlignCenter);
	 QWidget *centralWidget_again = new QWidget();
	 centralWidget_again->setLayout(vmainLayout);
	 setCentralWidget(centralWidget_again);
	 connect(playButton, &QPushButton::clicked, this, &MainWindow::playVideo);
	 connect(stopButton, &QPushButton::clicked, this, &MainWindow::stopVideo);
//	 menuFile->addAction(playAction);
	 hmainLayout->addWidget(playButton);
	 hmainLayout->addWidget(stopButton);
//	 vmainLayout->addWidget(playButton, 0, Qt::AlignCenter);
	 vmainLayout->addLayout(hmainLayout);

//	 QAction *stopAction = new QAction(tr("&Stop"), this);
//	 QAction *stopAction = new QAction(this);
//
//	 stopAction->setShortcut(Qt::Key_Escape);
//	 stopAction->setStatusTip(tr("Stop the video"));
//	 connect(stopAction, &QAction::triggered, this, &MainWindow::stopVideo);
//	 menuFile->addAction(stopAction);
//
//	 menuBar->addMenu(menuFile);// ショートカットキーをウィンドウ全体に割り当てる
	 QShortcut *startshortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
	 startshortcut->setContext(Qt::ApplicationShortcut);
	 connect(startshortcut, &QShortcut::activated, this, &MainWindow::playVideo);
	 //stop
	 QShortcut *stopshortcut = new QShortcut(QKeySequence(Qt::Key_F1), this);
	 stopshortcut->setContext(Qt::ApplicationShortcut);
	 connect(stopshortcut, &QShortcut::activated, this, &MainWindow::stopVideo);

}

MainWindow::~MainWindow()
{
    delete ui;
	 cap.release(); // カメラ/ビデオファイルを開放する
}

void MainWindow::updateFrame()
{
    cap.read(frame);
    if (frame.empty()) {
        timer->stop();
        qDebug() << "End of video";
        return;
    }
	 double fps = cap.get(cv::CAP_PROP_FPS);

	 // 現在のフレーム番号を取得する
	 int currentFrame = cap.get(cv::CAP_PROP_POS_FRAMES);
	 // 総フレーム数を取得する
	 int totalFrames = cap.get(cv::CAP_PROP_FRAME_COUNT);
	 // フレーム番号の文字列を作成する
//	 QString frameText = QString("Frame %1 / %2 FPS: %3").arg(currentFrame).arg(totalFrames).arg(fps);
	 // フレーム番号の文字列を作成する
	 QString frameText = QString(" %1  Frame %2 / %3 FPS: %4").arg(fileInfo->fileName()).arg(currentFrame).arg(totalFrames).arg(fps);
	 // ラベルにフレーム番号を表示する
	 info_label->setText(frameText);

//	 double fps = cap.get(cv::CAP_PROP_FPS);
//	 QString fpsText = QString("FPS: %1").arg(fps);
//	 fps_label->setText(fpsText);



    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
	 cv::resize(frame, frame, cv::Size(label->width(), label->height())); // フレームをリサイズする
	 // フレームをQImageに変換する
    QImage image(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
	 // QImageをQPixmapに変換する
    QPixmap pixmap = QPixmap::fromImage(image);
	 // ラベルにQPixmapをセットする
    label->setPixmap(pixmap); // ui->labelの代わりにlabelを使う
//	 label->setGeometry(QRect(0, 0, 640, 480));
//	 label->setFixedSize(640, 480); // 固定サイズを設定
	 label->setScaledContents(true); // labelのサイズに動画のサイズに合わせる

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
//		  timer->start(1000 / cap.get(cv::CAP_PROP_FPS));
		  timer->stop();
		  // ファイル情報を更新
		  fileInfo = new QFileInfo(fileName);
		  // 最初のフレームを表示する
		  cv::Mat frame;
		  cap >> frame;
		  if (!frame.empty()) {
				cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
				QImage image((uchar*) frame.data, frame.cols, frame.rows, QImage::Format_RGB888);
				QPixmap pixmap = QPixmap::fromImage(image);
				label->setPixmap(pixmap);
//				ui->videoLabel->setPixmap(QPixmap::fromImage(image));
		  }
//		  double fps = cap.get(cv::CAP_PROP_FPS);
//		  QString fpsText = QString("FPS: %1").arg(fps);
//		  fps_label->setText(fpsText);

//////////////////////////////////////////////////////////////
		  QFileInfo fileInfo(fileName);
		  settings.setValue("LastPath", fileInfo.absolutePath());
	 }
}
void MainWindow::stopVideo()
{
	 timer->stop();
//	 cap.release(); // カメラ/ビデオファイルを開放する
}
void MainWindow::playVideo()
{
	 if (!cap.isOpened()) {
		  return;
	 }
	 if (timer->isActive()) {
		  return; // 再生中は何もしない
	 }

//	  最初のフレームを読み込んで表示する
	 cap.read(frame);
	 if (frame.empty()) {
		  qDebug() << "End of video";
		  return;
	 }
//	 // 最初のフレームを読み込んで表示する
//	 if (frame.empty()) {
//		  cap.read(frame);
//	 }
	 cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
	 cv::resize(frame, frame, cv::Size(label->width(), label->height())); // フレームをリサイズする
	 QImage image(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
	 QPixmap pixmap = QPixmap::fromImage(image);
	 label->setPixmap(pixmap);
//	 label->setGeometry(QRect(0, 0, 640, 480));
//	 label->setFixedSize(640, 480); // 固定サイズを設定

	 // 再生ボタンを押した時にタイマーを開始する
	 timer->start(1000 / cap.get(cv::CAP_PROP_FPS));
	 // cap.release(); // カメラ/ビデオファイルを開放する
}