#include "graphchart.h"
#include <QPainter>

const int MARGIN_H=5;
const int MARGIN_V=5;
GraphChart::GraphChart(QQuickItem *parent):
    QQuickPaintedItem(parent)
  ,m_current_index(-1)
  ,m_max_x(600)
  ,m_max_y(100)
  ,m_color(Qt::blue)
  ,m_timer(-1)
  ,m_timer_rate(60)
  ,m_pixmap(nullptr)
  ,m_painter(nullptr)
{
    connect(this,SIGNAL(receivedData(double)),this,SLOT(onReceivedData(double)));
    connect(this,SIGNAL(visibleChanged()),this,SLOT(onVisibleChanged()));
}

GraphChart::~GraphChart()
{ if(m_painter){
        delete m_painter;
        m_painter=nullptr;
    }
    if(m_pixmap){
        delete m_pixmap;
        m_pixmap=nullptr;
    }
}


void GraphChart::paint(QPainter *painter)
{
    if(m_pixmap)// draw pixmap in current item
    {
        painter->drawPixmap(0,0,*m_pixmap);
    }
}

void GraphChart::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    if (newGeometry.size() != oldGeometry.size()) {
        stopEventTimer();
        double ITEM_W=newGeometry.width(),ITEM_H=newGeometry.height();

        if(ITEM_H>0&&ITEM_W>0){
            resetPixmapPainter(static_cast<int>(ITEM_W),static_cast<int>(ITEM_H));
        }
    }
    QQuickPaintedItem::geometryChanged(newGeometry, oldGeometry);

}

void GraphChart::resetPixmapPainter(int width,int height)
{
    if(m_painter){
        delete m_painter;
        m_painter=nullptr;
    }
    if(m_pixmap){
        delete m_pixmap;
        m_pixmap=nullptr;
    }

    m_pixmap=new QPixmap(width,height);
    m_pixmap->fill(Qt::transparent);
    m_painter=new QPainter(m_pixmap);
    m_painter->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
    m_painter->setPen(QPen(getLineColor(), 1, Qt::SolidLine,
                           Qt::RoundCap, Qt::RoundJoin));
    // will be show background in erase, should keep sync with item background
    m_painter->setBackground(QBrush("#2a2a2a"));
    m_xScale = width*1.0/m_max_x;
    m_yScale = ( height*1.0/m_max_y);
}
void GraphChart::onReceivedData(double newData)
{
    int MAX = m_max_x;
    m_current_index++;
    m_current_index = m_current_index%MAX;
    QPointF pf(m_current_index,newData);
    pf = transform(pf);
    if(m_data.size()>=MAX)
    {
        m_data.replace(m_current_index,pf);
    }
    else
    {
        m_data.append(pf);
    }
    updatePixmap();

}
QPointF GraphChart::transform(QPointF& normalP)
{
    QPointF pf;
    pf.setX(normalP.x()*m_xScale+MARGIN_H);
    pf.setY(height()-(normalP.y()*m_yScale)-MARGIN_V);
    return pf;
}

void GraphChart::updatePixmap()
{
    if(m_painter==nullptr)
        return;
    int leftX = 0;
    if(m_current_index>=1){
        QPointF pf1 = m_data.at(m_current_index-1);
        QPointF pf2 = m_data.at(m_current_index);

        leftX = static_cast<int>(pf2.x());

        if(m_current_index>m_max_x-1){
            leftX = MARGIN_H;
        }
        m_painter->eraseRect(leftX,MARGIN_V,static_cast<int>(m_xScale*10),m_pixmap->height()-MARGIN_V);
        m_painter->drawLine(pf1,pf2);
    }else{
        m_painter->eraseRect(leftX,MARGIN_V,static_cast<int>(m_xScale*10),m_pixmap->height()-MARGIN_V);
    }
}


void GraphChart::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
    double new_data = (static_cast<double>(qrand()) / RAND_MAX) * 70;
    onReceivedData(new_data);
    update();
}


void GraphChart::startEventTimer()
{
    stopEventTimer();
    m_timer=startTimer(m_timer_rate);
}

void GraphChart::stopEventTimer()
{
    if(m_timer>0){
        killTimer(m_timer);
        m_timer=-1;
    }
}

bool GraphChart::isEventTimerStared()
{
    return m_timer>0;
}

void GraphChart::onVisibleChanged()
{
    if(isVisible()&&!isEventTimerStared()){
        startEventTimer();
    }else{
        stopEventTimer();
    }

}
