#ifndef BIRD_H
#define BIRD_H

#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Bird: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal slide READ slide WRITE setSlide)
    Q_PROPERTY(qreal fallingYpos READ fallingYpos WRITE setFallingYpos)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    qreal m_slide;

public:
    Bird();
    qreal slide() const;
    void setSlide(qreal newSlide);

    qreal fallingYpos() const;
    void setFallingYpos(qreal newFallingYpos);

    qreal rotation() const;
    void setRotation(qreal newRotation);

    QPropertyAnimation* AnimateFall;
    QPropertyAnimation* AnimateRotate;
    QPropertyAnimation* SlideAnimate;

    bool armed = false;
    void StopAllAnimations();
    void resetfallingYpos();
    qreal m_fallingYpos;

signals:
    void BirdOffScreen();

private:

    int flapstate; //0 means down, 1 means middle, 2 means up, 3 means middle. 
    qreal m_rotation;
    QTimer* timer;
};

#endif // BIRD_H
