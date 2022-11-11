#include "pipegroup.h"
#include <QGraphicsScene>
#include <QRandomGenerator>
#include "bird.h"
#include <QDebug>


PipeGroup::PipeGroup()
{

    topPipe = new QGraphicsPixmapItem(QPixmap(":/Images/Pipe.png"));
    bottomPipe = new QGraphicsPixmapItem(QPixmap(":/Images/Pipe.png"));
    topPipe->setScale(0.3);
    bottomPipe->setScale(0.3);

    topPipe->setPos(-topPipe->boundingRect().width()*0.3/2,
                    -topPipe->boundingRect().height()*0.3 - 30);

    bottomPipe->setPos(-bottomPipe->boundingRect().width()*0.3/2, 30);

    addToGroup(topPipe);
    addToGroup(bottomPipe);

    AnimateXpos = new QPropertyAnimation(this, "x", this);
    AnimateXpos->setStartValue(150);
    AnimateXpos->setEndValue(-150);
    AnimateXpos->setEasingCurve(QEasingCurve::Linear);
    AnimateXpos->setDuration(4000);
    AnimateXpos->start();

    RandomYValue = QRandomGenerator::global()->bounded(-50,50);

    connect(AnimateXpos, &QPropertyAnimation::finished, [=](){
        scene()->removeItem(this);
        delete this;
    });
}

qreal PipeGroup::x() const
{
    return m_x;
}

void PipeGroup::setX(qreal newX)
{

    QList<QGraphicsItem*> items = topPipe->collidingItems();
    items.append(bottomPipe->collidingItems());
    foreach(QGraphicsItem* element, items)
    {
    Bird* bird = dynamic_cast<Bird*>(element);
    if (bird)
    {
        AnimateXpos->stop();
        emit collisionDetected();
    }
    }

    setPos(newX,RandomYValue);
    m_x = newX;

    //Increment score if pipes make it past the bird at x = -30;
    if (m_x < -40 && onlyOnce)
    {
        emit incrementScore();
        onlyOnce = 0;
    }
}
