#include "view.h"
#include <QMouseEvent>
#include <QDebug>

View::View(QWidget* parent, Bird* birdparam)
    : QGraphicsView(parent), bird{birdparam}
{

    connect(bird->AnimateFall, &QPropertyAnimation::finished, [=](){
        if(bird->pos().y() < 150)
        {
        bird->AnimateFall->stop();
        bird->AnimateFall->setStartValue(bird->pos().y());
        bird->AnimateFall->setEndValue(bird->pos().y() + 250);
        bird->AnimateFall->setEasingCurve(QEasingCurve::InQuad);
        bird->AnimateFall->setDuration(2500);
        bird->AnimateFall->start();
        }
    });


    connect(bird->AnimateRotate, &QPropertyAnimation::finished, [=](){
        if(bird->rotation()<90)
        {
        bird->AnimateRotate->stop();
        bird->AnimateRotate->setStartValue(-30);
        bird->AnimateRotate->setEndValue(90);
        bird->AnimateRotate->setEasingCurve(QEasingCurve::InQuad);
        bird->AnimateRotate->setDuration(2500);
        bird->AnimateRotate->start();
        }
    });
}

void View::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && bird->armed == true)
    {
        if (bird->pos().y()> -100)
        {
        bird->AnimateFall->stop();
        bird->AnimateFall->setStartValue(bird->pos().y());
        bird->AnimateFall->setEndValue(bird->pos().y() - 20);
        bird->AnimateFall->setEasingCurve(QEasingCurve::Linear);
        bird->AnimateFall->setDuration(100);
        bird->AnimateFall->start();


        bird->AnimateRotate->stop();
        bird->AnimateRotate->setStartValue(bird->rotation());
        bird->AnimateRotate->setEndValue(bird->rotation()-10);
        bird->AnimateRotate->setEasingCurve(QEasingCurve::Linear);
        bird->AnimateRotate->setDuration(100);
        bird->AnimateRotate->start();
        }
    }

}
