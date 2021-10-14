#ifndef WIDGET_H
#define WIDGET_H

#include "types.h"
#include "point.h"
#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <vector>

using namespace MY_DATA;

class Top : public QWidget {
    enum ALIGN {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT
    };
    void paintEvent(QPaintEvent *);
public:
    Top(QWidget * parent = 0);
    void setup();
    void btnRun_clicked();
    void drawLine(QPainter &p, double x1, double y1, double x2, double y2);
    double scr_to_vw_x(int x);
    int vw_to_scr_x(double x);
    double scr_to_vw_y(int y);
    int vw_to_scr_y(double y);
    void CalcScale();
    void DrawText(QPainter &p, QFont &font, double x, double y, QString sText);
    void DrawText(QPainter &p, QFont &font, double x, double y, QString sText, ALIGN align);
    void DrawText2(QPainter &p, QFont &font, int x, int y, QString sText);
    void SetXLabel(QPainter &p, QFont &font, QString sText);
    void SetYLabel(QPainter &p, QFont &font, QString sText);
    void DrawXTick(QPainter &p);
    void DrawYTick(QPainter &p);
private:
    void resizeEvent(QResizeEvent*);
    QPushButton *m_btnRun;
    std::vector<Point<WORD>> data;
    double m_scale, m_scale_w, m_scale_h;
    double m_v_org_x;
    double m_v_org_y;
    int m_w, m_h;
    double m_v_w, m_v_h;
    double m_bound_x_min, m_bound_x_max, m_bound_y_min, m_bound_y_max;
};

#endif // WIDGET_H
