#ifndef GRAPHCHART_H
#define GRAPHCHART_H

#include <QQuickPaintedItem>
#include <QPointF>
#include <QVector>
#include <QColor>

class GraphChart : public QQuickPaintedItem
{
    Q_OBJECT
    Q_DISABLE_COPY(GraphChart)
    Q_PROPERTY(QColor lineColor READ getLineColor WRITE setLineColor NOTIFY lineColorChanged)
public:
    GraphChart(QQuickItem *parent = nullptr);
    ~GraphChart();
    void paint(QPainter *painter);
        QColor getLineColor(){
            return m_color;
        }
        void setLineColor(QColor color){
            m_color=color;
        }
        bool isEventTimerStared();
        Q_INVOKABLE void startEventTimer();
        Q_INVOKABLE void stopEventTimer();
    signals:
        void receivedData(double newData);
        void lineColorChanged();
    public slots:
        void onReceivedData(double newData);
        void onVisibleChanged();
    protected:
        virtual void timerEvent(QTimerEvent *event);
        virtual void geometryChanged(const QRectF &newGeometry,
                                     const QRectF &oldGeometry);
    private:
        /**
         * @brief transform human understand coordinate point into curve real coordinate
         * @param nomalP human understand point
         * @return point after transform
         */
        QPointF transform(QPointF& nomalP);
        /**
         * @brief initialize cached QPixmap and QPainter
         * @param width width of pixmap
         * @param height height of pixmap
         */
        void resetPixmapPainter(int width,int height);
        /**
         * @brief updatePixmap draw received data into line in pixmap
         */
        void updatePixmap();
    private:
        int m_current_index;
        int m_max_x,m_max_y;
        QVector<QPointF> m_data;
        QColor m_color;
        double m_xScale,m_yScale;
        int m_timer;//timer event handler
        int m_timer_rate;//timer interval


        QPixmap *m_pixmap;//cached pixmap for curve
        QPainter *m_painter;//painter in QPixmap
};

#endif // GRAPHCHART_H
