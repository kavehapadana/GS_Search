#include "Worker.h"
#include <QDebug>

Worker::Worker(QObject *parent) :
    QObject(parent)
{
    CntThread = 0;
}
Worker::~Worker() {
    // free resources
}

void Worker::beforProcess()
{
    serialFileStream.setFileName(serialFileName);
    if(!serialFileStream.open(QIODevice::ReadWrite | QFile::Append))
        afterProcess();
}

void Worker::afterProcess()
{
    serialFileStream.flush();
    serialFileStream.close();
    //qDebug("Thread work done");
    //qDebug()<<tmStringList_th.at(0)<< " " << tmStringList_th.at(1);
    emit finished();
}

// --- PROCESS ---
// Start processing data.
void Worker::process() {
    // allocate resources using new here

    //CntThread++;
    QTextStream mystream(&serialFileStream);
    for(int i = 0;i < RSSI_SUM_List.size(); i++)
    {
        //mystream <<   "Time" <<      ","  <<doubleTime <<      "," <<     "Deg"       << "," <<         "Rev" <<   "," <<     "EncDeg"     << "," <<   "EncRev" <<   ","<< "Ref_Deg" <<     ","  << "Ref_Rev" <<    "," << "Doppler_data" << "," << "RSSI_SUM_Data" << "," << "RSSI_Delta_Data" << "," << "Detection" << "," << endl;
        mystream << tmStringList[i] << "," << tmDoubleList[i] << "," << FinalDegList[i] << "," << FinalRevList[i] << "," << EncDegList[i] << "," << EncRevList[i] << ","<< RefDegList[i] << "," << RefRevList[i] << "," << DopplerList[i] << "," << RSSI_SUM_List[i] << "," << RSSI_Delta_List[i] << "," << InterruptList[i] << "," << endl;
    }
}

