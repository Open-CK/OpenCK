#include "baseidtable.hpp"

BaseIdTable::BaseIdTable(unsigned int features) :
    features(features)
{

}

unsigned int BaseIdTable::getFeatures() const
{
    return features;
}