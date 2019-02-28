#include "viewmediator.h"

ViewMediator::ViewMediator()
{
    w.reset(new MainWindow());
    w->show();
}

ViewMediator::~ViewMediator()
{

}
