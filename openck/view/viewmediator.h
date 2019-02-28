#ifndef VIEWMEDIATOR_H
#define VIEWMEDIATOR_H

#include "window/mainwindow.h"

#include <QObject>

#include <memory>

class ViewMediator : public QObject
{
    Q_OBJECT

public:
    ViewMediator();
    ~ViewMediator();

public slots:
    void showDataDialog();

private:
    std::unique_ptr<MainWindow> w;
};

#endif //VIEWMEDIATOR_H
