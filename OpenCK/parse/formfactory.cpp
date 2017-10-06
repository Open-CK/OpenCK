#include "formfactory.h"

Form *FormFactory::createForm(const Form &formHeader, QDataStream *in)
{
    Form *newForm;

    switch(formHeader.getType()) {
        case 'TES4':
            newForm = new TES4Form(formHeader);
            break;
        case 'GMST':
            newForm = new GMSTForm(formHeader);
            break;
    }

    newForm->load(in, 0);
    return newForm;
}
