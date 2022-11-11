#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include "view.h"
#include <QMovie>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QTimer>
#include "pipegroup.h"
#include "bird.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(230, 260);
    setWindowTitle("Flappy Bird");

    scene = new QGraphicsScene(this);
    scene->setSceneRect(-100,-100, 200, 200);

    QLabel* giflabel = new QLabel;
    giflabel->resize(200, 200);
    giflabel->move(-100,-100);
    giflabel->setScaledContents(true);

    //Adding Background
    QMovie *movie = new QMovie(":/Images/Sky.gif");
    movie->setScaledSize(QSize(200,200));
    movie->setSpeed(300);
    giflabel->setMovie(movie);
    scene->addWidget(giflabel);

    //Adding the Bird
    Bird* bird = new Bird;
    scene->addItem(bird);

    //Now adding pipes through a timer.
    QTimer* timer = new QTimer(this);
    timer->setInterval(3000);
    timer->start();

    //Add Current Score Text
    ScoreItem = new QGraphicsTextItem;
    currentScore = 0;
    QString ScoreText = QString("<font color = blue>" + QString::number(currentScore) + "</font>");
    QFont ScoreFont = QFont("Arial", 16);
    ScoreItem->setHtml(ScoreText);
    ScoreItem->setFont(ScoreFont);
    ScoreItem->setPos(-100,-100);
    scene->addItem(ScoreItem);

    connect(timer, &QTimer::timeout, [=](){
        PipeGroup* pipes = new PipeGroup();
        scene->addItem(pipes);

        //Turn off timer when there is a collision
        connect(pipes, &PipeGroup::collisionDetected, [=](){
            timer->stop();

            //Pause Any Pipes on the screen, can't use pipes pointer because object may be deleted.
            QList<QGraphicsItem*> screenItems = scene->items();
            foreach(QGraphicsItem* element, screenItems)
            {
                PipeGroup* currentPipeGroup = dynamic_cast<PipeGroup*>(element);
                if (currentPipeGroup)
                    currentPipeGroup->AnimateXpos->stop();
            }
            movie->stop();
        });

        //Stop Bird Animations if there is a collision
        connect(pipes, &PipeGroup::collisionDetected, [=](){
            bird->StopAllAnimations();
        });

        //Re-enable the Start Button when the Collision is detected so we can start a new game
        connect(pipes, &PipeGroup::collisionDetected, [=](){
            ui->pushButton->setDisabled(false);
        });

        //Connect to catch whenever the score is incremented
        connect(pipes, &PipeGroup::incrementScore, [=](){
            currentScore++;
            updateScore();
        });


    });

    //If bird drops off screen also shut down the game
    connect(bird, &Bird::BirdOffScreen, [=](){
        timer->stop();

        //Pause Any Pipes on the screen, can't use pipes because that one may have been deleted.
        QList<QGraphicsItem*> screenItems = scene->items();
        foreach(QGraphicsItem* element, screenItems)
        {
            PipeGroup* currentPipeGroup = dynamic_cast<PipeGroup*>(element);
            if (currentPipeGroup)
                currentPipeGroup->AnimateXpos->stop();
        }
        movie->stop();
        ui->pushButton->setDisabled(false);
    });

    View* view = new View(this, bird);
    view->setScene(scene);
    view->setRenderHint(QPainter::Antialiasing);

    ui->verticalLayout->addWidget(view);
    movie->start();

    //Start with the Button Disabled for the first game
    ui->pushButton->setDisabled(true);

    //Handle when the Start Game Button is Pushed
    connect(ui->pushButton, &QPushButton::clicked, [=](){

        //Reset the bird to slide back in
        bird->resetfallingYpos();
        bird->setRotation(0);
        bird->SlideAnimate->start();

        //Change the Bird Appearance
        bird->setPixmap(QPixmap(":/Images/birdmiddle.png"));

        //Remove Any Pipes on Screen
        QList<QGraphicsItem*> screenItems = scene->items();
        foreach(QGraphicsItem* element, screenItems)
        {
            PipeGroup* currentPipeGroup = dynamic_cast<PipeGroup*>(element);
            if (currentPipeGroup)
                scene->removeItem(currentPipeGroup);
        }

        //Restart Pipe Timer to keep creating new pipe objects
        timer->start();

        //Disable this Start Button once you've started the new Game
        ui->pushButton->setDisabled(true);

        //Restart the Sky Movie
        movie->start();

        //Restart Score
        currentScore = 0;
        updateScore();
    });


}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::updateScore()
{
    scene->removeItem(ScoreItem);
    QString ScoreText = QString("<font color = blue>" + QString::number(currentScore) + "</font>");
    QFont ScoreFont = QFont("Arial", 16);
    ScoreItem->setHtml(ScoreText);
    ScoreItem->setFont(ScoreFont);
    ScoreItem->setPos(-100,-100);
    scene->addItem(ScoreItem);
}
