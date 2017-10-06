#ifndef ANALYZOR_H
#define ANALYZOR_H
#include <QVector>

#define  _sizeAveSUM    50
#define  _sizeAveDelta  50
#define  _sizeAveSLC    50

#define  _sizeFIR_SUM    89
#define  _sizeFIR_Delta  89
#define  _sizeFIR_SLC    89

class Analyzor
{

public:
    Analyzor();
    double RSSI_SUM_Analyzor_Ave(double _rssi_sum);
    double RSSI_Delta_Analyzor_Ave(double _rssi_delta);
    double RSSI_SLC_Analyzor_Ave(double _rssi_slc);
    double RSSI_SUM_Analyzor_FIR(double _rssi_sum);
    double RSSI_SUM_Analyzor_FIR_Armand(double _rssi_sum);
    double RSSI_Delta_Analyzor_FIR(double _rssi_delta);
    double RSSI_SLC_Analyzor_FIR(double _rssi_slc);

private:
    QVector<double>     RSSI_SUM_Analyzor_List;
    QVector<double>     RSSI_SUM_Analyzor_FIR_List;
    QVector<double>     RSSI_Delta_Analyzor_List;
    QVector<double>     RSSI_SLC_Analyzor_Ave_List;
    QVector<double>     RSSI_SLC_Analyzor_FIR_List;
    static double FIR_NUM[89];
};

#endif // ANALYZOR_H
