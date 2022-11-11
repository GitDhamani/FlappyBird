#include "bird.h"
#include <QTimer>
#include <QDebug>
#include "pipegroup.h"

Bird::Bird()
{
    setPixmap(QPixmap(":/Images/birdmiddle.png"));
    //setScale(2);
    flapstate = 1;
    armed = false;

    //Slide Animation
    SlideAnimate = new QPropertyAnimation(this, "slide", this);
    SlideAnimate->setStartValue(-120);
    SlideAnimate->setEndValue(-30);
    SlideAnimate->setEasingCurve(QEasingCurve::Linear);
    SlideAnimate->setDuration(1500);
    SlideAnimate->start();

    //Setting up the WingFlaps
    timer = new QTimer(this);
    timer->setInterval(80);
    connect(SlideAnimate, &QPropertyAnimation::finished, [=](){
        timer->start();
    });
    connect(timer, &QTimer::timeout, [=](){
        flapstate++;
        if (flapstate%4 == 0)
            setPixmap(QPixmap(":/Images/birddown.png"));
        if (flapstate%4 == 1 || flapstate == 3)
            setPixmap(QPixmap(":/Images/birdmiddle.png"));
        if (flapstate%4 == 2)
            setPixmap(QPixmap(":/Images/birdup.png"));
    });

    //Falling Animation
    AnimateFall = new QPropertyAnimation(this, "fallingYpos", this);

    connect(SlideAnimate, &QPropertyAnimation::finished, [=](){

        AnimateFall->setStartValue(0);
        AnimateFall->setEndValue(250);
        AnimateFall->setEasingCurve(QEasingCurve::InQuad);
        AnimateFall->setDuration(2500);
        AnimateFall->start();
        armed = true;
    });


    //Rotating Animation
    AnimateRotate = new QPropertyAnimation(this, "rotation", this);

    connect(SlideAnimate, &QPropertyAnimation::finished, [=](){
        AnimateRotate->setStartValue(-30);
        AnimateRotate->setEndValue(90);
        AnimateRotate->setEasingCurve(QEasingCurve::InQuad);
        AnimateRotate->setDuration(2500);
        AnimateRotate->start();
    });
}

qreal Bird::slide() const
{
    return m_slide;
}

void Bird::setSlide(qreal newSlide)
{
    setPos(newSlide,0);
    m_slide = newSlide;
}

qreal Bird::fallingYpos() const
{
    return m_fallingYpos;
}

void Bird::setFallingYpos(qreal newFallingYpos)
{
    moveBy(0, newFallingYpos - m_fallingYpos);
    m_fallingYpos = newFallingYpos;

    if (m_fallingYpos >= 120)
    {
        emit BirdOffScreen();
        StopAllAnimations();
    }
}

qreal Bird::rotation() const
{
    return m_rotation;
}

void Bird::setRotation(qreal newRotation)
{
    QTransform tf = transform();
    tf.translate(boundingRect().center().x(), boundingRect().center().y());
    tf.rotate(newRotation-m_rotation);
    tf.translate(-boundingRect().center().x(), -boundingRect().center().y());
    setTransform(tf);
    m_rotation = newRotation;
}

void Bird::StopAllAnimations()
{
    armed = false; //Mouse Clicks won't work now
    setPixmap(QPixmap(":/Images/birdupv2.png")); //Bird now looks surprised it got hit
    AnimateFall->stop();
    AnimateRotate->stop();
    timer->stop();
}

void Bird::resetfallingYpos()
{
    m_fallingYpos = 0;
}
