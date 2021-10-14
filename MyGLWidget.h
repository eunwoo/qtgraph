#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}
protected:
    void initializeGL() override
    {
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
};

#endif // MYGLWIDGET_H
