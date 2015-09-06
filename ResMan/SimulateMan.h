#ifndef SIMULATEMAN_H
#define SIMULATEMAN_H

#include <QtCore/QObject>

class ArchiveManager;

typedef struct tagSimulateStruct
{
    int nAddr;
    char nAddrType;
    char nDataType;
    char nDecimal;
    char nSavePeriod;
    int nMax;
    int nMin;
    int nUpAlarm;
    int nDownAlarm;
    int nBase;
    int nFactor;
    bool bWarning;
	bool bMinDollar;//��Сֵ���Ѱַ;
	bool bMaxDollar;//���ֵ���Ѱַ;

}SimulateStruct, *LPSimulateStruct;


class SimulateMan : public QObject
{
    Q_OBJECT
public:
    explicit SimulateMan( ArchiveManager *pArch, QObject *parent = 0);
    ~SimulateMan();
    void setupPrivate(char *p);
    void getFmt(int *pMax, int *pMin, int *pDecimal, QString &strMax, QString &strMin);
    void getFmt(int *pMax, int *pMin, int *pDecimal, int *pUpAlarm=0, int *pDwnAlarm=0);
    void write(const QString &data, QObject *who = 0, bool bSend = true);
    void write(const int data, QObject *who = 0, bool bSend = true);
    QString read();
    int readInt();
    void trigle();//������ȡ����;
    void addToMonitorList();//�����ض���;
    void delFromMonitorList();//�Ӽ�ض������;


    QByteArray m_coilCode;
    SimulateStruct *m_pData;//˽������;

signals:
    void updateData(const QString data, SimulateMan *pVar, QObject *who);
    void updateData(const int data, SimulateMan *pVar, QObject *who);
public slots:

private:
    ArchiveManager *m_pArch;

//methods:
    void sendOut();//�����ݷ��ͳ�ȥ(����);
};

#endif // SIMULATEMAN_H
