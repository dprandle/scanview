#include <mapview.h>
#include <QWheelEvent>

MapView::MapView(QWidget *parent) :
    QGraphicsView(parent)
{}

MapView::~MapView()
{}


void MapView::wheelEvent(QWheelEvent * event)
{
    float dlt = event->angleDelta().y();
    dlt /= 360.0f*2.0f;
    dlt += 1.0f;
    setTransformationAnchor(AnchorUnderMouse);
    scale(dlt,dlt);
}
