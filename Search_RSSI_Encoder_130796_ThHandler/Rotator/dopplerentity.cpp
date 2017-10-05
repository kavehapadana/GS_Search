#include "dopplerentity.h"

DopplerEntity::DopplerEntity()
{
    this->_doppler = 100000;
}

void DopplerEntity::setDoppler(double doppler)
{
    _doppler = doppler;
}

double DopplerEntity::getDoppler()
{
    return _doppler;
}
