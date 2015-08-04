#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>

class MapView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit MapView(QWidget *parent = 0);
    ~MapView();

    void wheelEvent(QWheelEvent * event);
};

#endif // MAPVIEW_H
