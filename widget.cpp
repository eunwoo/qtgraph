#include "widget.h"
#include <QPainter>
#include <QPushButton>
#include "data.h"
#include "point.h"
#include <QDebug>

void Top::DrawText(QPainter &p, QFont &font, double x, double y, QString sText, ALIGN align) {
    QFontMetrics fm(font);
    QSize size = fm.size(Qt::TextSingleLine, sText);
    int xoffset, yoffset;
    switch(align) {
        case BOTTOM:
            xoffset = -size.width()/2;
            yoffset = 20;
            break;
        case TOP:
            xoffset = -size.width()/2;
            yoffset = -20;
            break;
        case LEFT:
            xoffset = -20 - size.width();
            yoffset = -size.height()/2;
            break;
        case RIGHT:
            xoffset = 20;
            yoffset = -size.height()/2;
            break;
    }

    QRect font_rect(vw_to_scr_x(x)+xoffset, vw_to_scr_y(y)+yoffset, size.width(), size.height());
    p.drawText(font_rect, Qt::AlignCenter, sText);
//    QPen pen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
//    p.drawRect(font_rect);
}
void Top::DrawText(QPainter &p, QFont &font, double x, double y, QString sText) {
    QFontMetrics fm(font);
    QSize size = fm.size(Qt::TextSingleLine, sText);
    QRect font_rect(vw_to_scr_x(x)-size.width()/2, vw_to_scr_y(y)+20, size.width(), size.height());
    p.drawText(font_rect, Qt::AlignCenter, sText);
//    QPen pen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
//    p.drawRect(font_rect);
}
void Top::DrawText2(QPainter &p, QFont &font, int x, int y, QString sText) {
    QFontMetrics fm(font);
    QSize size = fm.size(Qt::TextSingleLine, sText);
    QRect font_rect(x-size.width()/2, y-size.height()-20, size.width(), size.height());
    p.drawText(font_rect, Qt::AlignCenter, sText);
//    QPen pen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
//    p.drawRect(font_rect);
}
void Top::resizeEvent(QResizeEvent *)
{
    qDebug() << "width:" << this->width();
    m_w = this->width();
    m_h = this->height();
    CalcScale();
}
void Top::paintEvent(QPaintEvent *) {
    QPainter p(this);
    QPen pen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    p.setPen(pen);
    std::vector<Point<WORD>>::iterator itr;
    for(itr = data.begin(); itr < data.end(); itr++) {
        Point<WORD> pt = static_cast<Point<WORD>>(*itr);
        p.drawPoint(vw_to_scr_x(pt.x), vw_to_scr_y(pt.y));
        if(itr < data.end()-1) {
            Point<WORD> pt2 = static_cast<Point<WORD>>(*(itr+1));
            p.drawLine(vw_to_scr_x(pt.x), vw_to_scr_y(pt.y), vw_to_scr_x(pt2.x), vw_to_scr_y(pt2.y));
        }
    }

    QPen pen_grid(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    p.setPen(pen_grid);
    int x1, x2, y1, y2;
    x1 = vw_to_scr_x(m_bound_x_min);
    y1 = vw_to_scr_y(m_bound_y_min);
    x2 = vw_to_scr_x(m_bound_x_max + m_v_w*0.1);
    y2 = vw_to_scr_y(m_bound_y_min);
    p.drawLine(x1, y1, x2, y2);
    x1 = vw_to_scr_x(m_bound_x_min);
    y1 = vw_to_scr_y(m_bound_y_min);
    x2 = vw_to_scr_x(m_bound_x_min);
    y2 = vw_to_scr_y(m_bound_y_max + m_v_h*0.1);
    p.drawLine(x1, y1, x2, y2);

    QFont font = QFont("Arial", 10);
    QPen pen_tick(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    p.setPen(pen_tick);
    p.setFont(font);
    DrawText(p, font, m_bound_x_min, m_bound_y_min, QString::number(m_bound_x_min));
    DrawText(p, font, m_bound_x_max, m_bound_y_min, QString::number(m_bound_x_max));
    DrawText(p, font, m_bound_x_min, m_bound_y_min, QString::number(m_bound_y_min), LEFT);
    DrawText(p, font, m_bound_x_min, m_bound_y_max, QString::number(m_bound_y_max), LEFT);
    SetXLabel(p, font, "wPwmAmp2");
    SetYLabel(p, font, "wAsrKgainFactor");
    DrawXTick(p);
    DrawYTick(p);
}
void Top::SetXLabel(QPainter &p, QFont &font, QString sText)
{
    DrawText(p, font, (m_bound_x_min+m_bound_x_max)*0.5, m_bound_y_min, sText);
}

void Top::SetYLabel(QPainter &p, QFont &font, QString sText)
{
    double x = m_bound_x_min;
    double y = (m_bound_y_min+m_bound_y_max)*0.5;
    int ix = vw_to_scr_x(x);
    int iy = vw_to_scr_y(y);
    qDebug() << "ix:" << ix;
    p.translate(ix, iy);
    p.rotate(-90);
    DrawText2(p, font, 0, 0, sText);
}
void Top::DrawXTick(QPainter &p)
{
    QPen pen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    p.setPen(pen);
    double x;
    int loop_cnt, loop_cnt_max = 10;
    p.resetTransform();
    for(loop_cnt = 0; loop_cnt < loop_cnt_max; loop_cnt++) {
        x = m_bound_x_min + loop_cnt*(m_bound_x_max - m_bound_x_min)/loop_cnt_max;
        p.drawLine(vw_to_scr_x(x), vw_to_scr_y(m_bound_y_min), vw_to_scr_x(x), vw_to_scr_y(m_bound_y_min) + 5);
    }
}
void Top::DrawYTick(QPainter &p)
{
    QPen pen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    p.setPen(pen);
    double y;
    int loop_cnt, loop_cnt_max = 10;
    p.resetTransform();
    for(loop_cnt = 0; loop_cnt < loop_cnt_max; loop_cnt++) {
        y = m_bound_y_min + loop_cnt*(m_bound_y_max - m_bound_y_min)/loop_cnt_max;
        p.drawLine(vw_to_scr_x(m_bound_x_min) - 5, vw_to_scr_y(y), vw_to_scr_x(m_bound_x_min), vw_to_scr_y(y));
    }
}

void Top::CalcScale() {
    m_scale_w = m_w/m_v_w;
    m_scale_h = m_h/m_v_h;
//    if (m_scale_w > m_scale_h) {
//        m_scale = m_scale_h;
//    }
//    else {
//        m_scale = m_scale_w;
//    }

}
Top::Top(QWidget * parent) : QWidget(parent)
{
    setup();
    m_w = 600;
    m_h = 600;
    m_v_w = 1000.0;
    m_v_h = 1000.0;
    m_v_org_x = 0.0;
    m_v_org_y = 0.0;
    GenerateData(data);
    m_bound_x_min = data[0].x;
    m_bound_x_max = data[0].x;
    m_bound_y_min = data[0].y;
    m_bound_y_max = data[0].y;
    std::vector<Point<WORD>>::iterator itr;
    for(itr = data.begin(); itr < data.end(); itr++) {
        if(m_bound_x_max < (*itr).x) {
            m_bound_x_max = (*itr).x;
        }
        else if(m_bound_x_min > (*itr).x) {
            m_bound_x_min = (*itr).x;
        }
        if(m_bound_y_max < (*itr).y) {
            m_bound_y_max = (*itr).y;
        }
        else if(m_bound_y_min > (*itr).y) {
            m_bound_y_min = (*itr).y;
        }
    }
    m_v_w = (m_bound_x_max - m_bound_x_min) * 1.4;
    m_v_h = (m_bound_y_max - m_bound_y_min) * 1.4;
    m_v_org_x = m_bound_x_min - m_v_w * 0.1;
    m_v_org_y = m_bound_y_min - m_v_h * 0.1;

    CalcScale();

}
void Top::setup()
{
//    m_btnRun = new QPushButton("Run", this);
//    m_btnRun->setGeometry(100, 100, 100, 30);
//    connect(m_btnRun, &QPushButton::released, this, &Top::btnRun_clicked);
}
double Top::scr_to_vw_x(int x)
{
    return x/m_scale_w + m_v_org_x;
}
int Top::vw_to_scr_x(double x)
{
    return static_cast<int>((x - m_v_org_x)*m_scale_w);
}
double Top::scr_to_vw_y(int y)
{
    return y/m_scale_h + m_v_org_y;
}
int Top::vw_to_scr_y(double y)
{
    return m_h - static_cast<int>((y - m_v_org_y)*m_scale_h);
}
void Top::drawLine(QPainter &p, double x1, double y1, double x2, double y2)
{
    int ix1 = vw_to_scr_x(x1);
    int iy1 = vw_to_scr_y(y1);
    int ix2 = vw_to_scr_x(x2);
    int iy2 = vw_to_scr_y(y2);
    p.drawLine(ix1, iy1, ix2, iy2);
}
void Top::btnRun_clicked()
{
    m_btnRun->setText("hi");
}
