#ifndef DOPPLERENTITY_H
#define DOPPLERENTITY_H

class DopplerEntity
{
private:
    volatile double _doppler;
public:
    DopplerEntity();
    void setDoppler(double doppler);
    double getDoppler();
};

#endif // DOPPLERENTITY_H
