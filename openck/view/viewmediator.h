#ifndef VIEWMEDIATOR_H
#define VIEWMEDIATOR_H

#include "window/mainwindow.h"

#include <memory>

class ViewMediator
{
public:
    ViewMediator();
    ~ViewMediator();

private:
    std::unique_ptr<MainWindow> w;
};

#endif //VIEWMEDIATOR_H
