#ifndef FORMFACTORY_H
#define FORMFACTORY_H

#include "tes4form.h"
#include "gmstform.h"

class FormFactory
{
public:
    FormFactory() {}
    Form *createForm(const Form &formHeader, QDataStream *in);
};

#endif // FORMFACTORY_H
