#include "glob.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

void GlobalVariable::load(ESMReader& esm)
{
    constant = esm.readHeader().flags.test(GlobalVariable::Constant);
    editorId = esm.readSubZString('EDID');
    value.load(esm, Variant::Format_GLOB);
}

void GlobalVariable::save(ESMWriter& esm) const
{
    esm.writeSubZString('EDID', editorId);
    value.write(esm, Variant::Format_GMST);
}

void GlobalVariable::blank()
{
    editorId = "";
    value.setType(VariantType::Var_None);
    constant = false;
}

bool operator==(const GlobalVariable& l, const GlobalVariable& r)
{
    return l.value == r.value;
}
