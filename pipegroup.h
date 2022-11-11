#ifndef PIPEGROUP_H
#define PIPEGROUP_H

#include <QGraphicsItemGroup>
#include <QPropertyAnimation>

class PipeGroup: public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)

public:
    PipeGroup();

    qreal x() const;
    void setX(qreal newX);
    QPropertyAnimation* AnimateXpos;

signals:
    void collisionDetected();
    void incrementScore();

private:
    QGraphicsPixmapItem* topPipe;
    QGraphicsPixmapItem* bottomPipe;
    qreal m_x;
    int RandomYValue;
    int onlyOnce = 1;

};

#endif // PIPEGROUP_H
