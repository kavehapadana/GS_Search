#include "analyzor.h"

Analyzor::Analyzor()
{
}

double Analyzor::RSSI_SUM_Analyzor_Ave(double _rssi_sum)
{
    RSSI_SUM_Analyzor_List.append(_rssi_sum);
    if(RSSI_SUM_Analyzor_List.size() > _sizeAveSUM)
    {
        RSSI_SUM_Analyzor_List.remove(0);
    }

    double SUM_Analyzor_Mean = std::accumulate(RSSI_SUM_Analyzor_List.begin(),RSSI_SUM_Analyzor_List.end(),.0)/RSSI_SUM_Analyzor_List.size();
    return SUM_Analyzor_Mean;
}
double Analyzor::RSSI_SUM_Analyzor_FIR(double _rssi_sum)
{
    RSSI_SUM_Analyzor_FIR_List.append(_rssi_sum);
    if(RSSI_SUM_Analyzor_FIR_List.size() > _sizeFIR_SUM)
    {
        RSSI_SUM_Analyzor_FIR_List.remove(0);
    }
    int cntSize = RSSI_SUM_Analyzor_FIR_List.size();
    double SUM_Analyzor_FIR = 0;
    for(int i = 0; i < cntSize; i++)
    {
        SUM_Analyzor_FIR += FIR_NUM[cntSize - i - 1]*RSSI_SUM_Analyzor_FIR_List[i];
    }
    return SUM_Analyzor_FIR;
}
double Analyzor::RSSI_Delta_Analyzor_Ave(double _rssi_delta)
{
    RSSI_Delta_Analyzor_List.append(_rssi_delta);
    if(RSSI_Delta_Analyzor_List.size() > _sizeAveDelta)
    {
        RSSI_Delta_Analyzor_List.remove(0);
    }

    double Delta_Analyzor_Mean =  std::accumulate(RSSI_Delta_Analyzor_List.begin(),RSSI_Delta_Analyzor_List.end(),.0)/RSSI_Delta_Analyzor_List.size();

    return Delta_Analyzor_Mean;
}
double Analyzor::RSSI_Delta_Analyzor_FIR(double _rssi_delta)
{
    RSSI_Delta_Analyzor_List.append(_rssi_delta);
    if(RSSI_Delta_Analyzor_List.size() > _sizeFIR_Delta)
    {
        RSSI_Delta_Analyzor_List.remove(0);
    }

    int cntSize = RSSI_Delta_Analyzor_List.size();
    double Delta_Analyzor_FIR = 0;
    for(int i = 0; i < cntSize; i++)
    {
        Delta_Analyzor_FIR += FIR_NUM[cntSize - i - 1]*RSSI_Delta_Analyzor_List[i];
    }
    return Delta_Analyzor_FIR;
}
double Analyzor::RSSI_SLC_Analyzor_Ave(double _rssi_slc)
{
    RSSI_SLC_Analyzor_Ave_List.append(_rssi_slc);
    if(RSSI_SLC_Analyzor_Ave_List.size() > _sizeAveSLC)
    {
        RSSI_SLC_Analyzor_Ave_List.remove(0);
    }

    double SLC_Analyzor_Mean = std::accumulate(RSSI_SLC_Analyzor_Ave_List.begin(),RSSI_SLC_Analyzor_Ave_List.end(),.0)/RSSI_SLC_Analyzor_Ave_List.size();
    return SLC_Analyzor_Mean;
}
double Analyzor::RSSI_SLC_Analyzor_FIR(double _rssi_slc)
{

    return 0;
}

double Analyzor::FIR_NUM[] = {
    0.005466461181640625
   ,0.0016765594482421875
   ,0.0018253326416015625
   ,0.00189971923828125
   ,0.001880645751953125
   ,0.0017566680908203125
   ,0.0015125274658203125
   ,0.001140594482421875
   ,0.000640869140625
   ,0.0000095367431640625
  ,-0.00074005126953125
  ,-0.0015964508056640625
  ,-0.0025348663330078125
  ,-0.003528594970703125
  ,-0.0045413970947265625
  ,-0.0055332183837890625
  ,-0.0064544677734375
  ,-0.007259368896484375
  ,-0.0078945159912109375
  ,-0.00830841064453125
  ,-0.008453369140625
  ,-0.0082759857177734375
  ,-0.0077362060546875
  ,-0.00679779052734375
  ,-0.005435943603515625
  ,-0.003631591796875
  ,-0.0013828277587890625
   ,0.0013065338134765625
   ,0.0044116973876953125
   ,0.007904052734375
   ,0.011732101440429688
   ,0.015838623046875
   ,0.020153045654296875
   ,0.02459716796875
   ,0.029088973999023438
   ,0.033529281616210938
   ,0.037822723388671875
   ,0.041889190673828125
   ,0.045623779296875
   ,0.048948287963867188
   ,0.05178070068359375
   ,0.054059982299804688
   ,0.055727005004882813
   ,0.056743621826171875
   ,0.057085037231445313
   ,0.056743621826171875
   ,0.055727005004882813
   ,0.054059982299804688
   ,0.05178070068359375
   ,0.048948287963867188
   ,0.045623779296875
   ,0.041889190673828125
   ,0.037822723388671875
   ,0.033529281616210938
   ,0.029088973999023438
   ,0.02459716796875
   ,0.020153045654296875
   ,0.015838623046875
   ,0.011732101440429688
   ,0.007904052734375
   ,0.0044116973876953125
   ,0.0013065338134765625
  ,-0.0013828277587890625
  ,-0.003631591796875
  ,-0.005435943603515625
  ,-0.00679779052734375
  ,-0.0077362060546875
  ,-0.0082759857177734375
  ,-0.008453369140625
  ,-0.00830841064453125
  ,-0.0078945159912109375
  ,-0.007259368896484375
  ,-0.0064544677734375
  ,-0.0055332183837890625
  ,-0.0045413970947265625
  ,-0.003528594970703125
  ,-0.0025348663330078125
  ,-0.0015964508056640625
  ,-0.00074005126953125
   ,0.0000095367431640625
   ,0.000640869140625
   ,0.001140594482421875
   ,0.0015125274658203125
   ,0.0017566680908203125
   ,0.001880645751953125
   ,0.00189971923828125
   ,0.0018253326416015625
   ,0.0016765594482421875
   ,0.005466461181640625
};
