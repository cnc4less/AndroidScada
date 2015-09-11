#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QTimer>
#include <QList>
#include <QMutex>
#include <QTime>
#include "Protocol.h"

#define MONITOR_TIME 50

class Communication : public QObject
{
    Q_OBJECT
public:
    explicit Communication(QObject *parent = 0);
    ~Communication();
    void sendData(QByteArray &srcBuffer);//���ݼ��뻺����;
    void addIdToReqBuf(int id);
    void delIdFromReqBuf(int id);
    void printMonitor();//��ӡ����б�;
    void updateMonitorToHost();//���¼���б�����;



private:
    QByteArray m_SendBuffer;            //���ͻ�����;
    QTimer *m_checkTimer;               //��ʱ�������ڼ��ACK
    QTimer *m_reqTimer;                 //��ʱ��ⶨʱ�������ڶ�ʱ��ȡ��ر���;
    QTime m_testTime;                   //���ڲ�����ʱ;
    int m_nMonitorIndex;                //��ǰ�ļ�ر���ID;
    bool m_bMonitor;                    //ʹ�ܶ�ȡ��ر���
    bool m_bSendSuccess;                //���ͳɹ���־λ;
    bool m_bConnected;                  //���ӷ�������־;
    bool m_bDownLoadMoniotorSuccess;    //���ؼ���б�ɹ�;
    bool m_bSendOnece;                  //ֻ��һ��;
    QList<QByteArray> m_sendBuf;        //���Ͷ���;
    QList<int> m_reqBuf;                //��������б��洢SimulateMan������IDֵ;
    QByteArray m_readMonitorCmd;        //��ȡ�����Ϣ,��λM8040����;
    int m_nTempCoilCode;                //��ʱ����ʶ��,ʶ�����б��һ������;
    QMutex m_sendMutex;


//methods:
    void send();//��ȡ������������;
public:
    bool isConnected()const;
    void connectToHost();
    void setDCoilVar(quint16);//�������ر����ɹ�;
    void writeData(mbyte coil, uint16 addr, uint16 dataGet);
    void sendSuccess();



public slots:
    void doCheckTimer();//��ʱ���;
    void doMonitorVar();//��ʱ��ȡ��ر���;
    void readData();//��ȡ����;
    void doConnected();//�������ӳɹ�;
    void doDisConnected();//�Ͽ�����;
};

#endif // COMMUNICATION_H
