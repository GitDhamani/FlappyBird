#ifndef VIEW_H
#define VIEW_H
#include <QGraphicsView>
#include "bird.h"

class View: public QGraphicsView
{
public:
    View(QWidget* parent, Bird* birdparam);
private:
    Bird* bird;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // VIEW_H
