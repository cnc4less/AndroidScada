#ifndef ADDRMANAGER_H 
#define ADDRMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QFile>
#include <QtCore/QMap>
#include <QtCore/QTimer>
#include <QtCore/QVector>
#include "SimulateMan.h"
#include "UI/Basectrl.h"
#include "Communication.h"

extern ArchiveManager *g_pArchiveModule;//��������ģ��;



class ArchiveManager : public QObject
{
    Q_OBJECT
public:
    ArchiveManager(QObject *parent = 0);
    ~ArchiveManager();

    //����ģ���������;
    void setupSimulateManager(char *p);
    //������ַ�����������;
    void setupAddrManger(int nAddrOff, int nAddrRange);//������ַ������ģ��;
    //д1�ֽڵ�ַ����;
    void writeByte(int addr, char val);
    //��1�ֽڵ�ַ����;
    char readByte(int addr);
    //д2�ֽڵ�ַ����;
    void writeWord(int addr, int val);//��Ҫ����;
    //��2�ֽڵ�ַ����;
    int readWord(int addr);
    //д4�ֽڵ�ַ����;
    void writeDWord(int addr, int val);
    //��4�ֽڵ�ַ����;
    int readDWord(int addr);
    //�������;
    void saveMold();
    //ģ�Ÿı����;
    void changeMold(const QString strFile, bool bFromBackup = false);
    //����ģ��;
    void loadMold(const QString strFile);
    //����������;
    void loadPanel(const QString strFile);
    //����������;
    void savePanel();

    //���Ա�ģ��Ķ�д����;
    void test();

//ϵͳ��������:
    //���µ�ǰҳ;
    void updateSysPage(int page);
    int getSysPage();
    //����ģ��;
    void updateMold();

//��������:
    void triggerRecord();//������ȡ������Ϣ;
    void loadWarnRecord();//���ر�����¼;
    void saveWarnRecord();//���汨����¼;
    void insertWarning(const int id);//���뱨����Ϣ;
    void removeWarning(const int id);//���������Ϣ;
    void releaseWarnRecord();//�ͷ�m_WarningMap�Ŀռ�;
    QMap<int, QString *>m_WarningMap;//������Ϣ������;
    QVector<LPTutorRecordStr> m_tutorVec;//�̵���Ϣ;
    QMap<int, SimulateMan*>simulateMap; //ģ������������;
    Communication *m_pCommunication;

    const QString &getMoldName();
    const QString &getPanelName();

private:
    int m_nAddrOff;//��ַƫ����;
    int m_nAddrRange;//��ַ��Χ;
    char *m_pParameter;//����������;
    QString m_moldName;//ģ������;
    QString m_panelFile;//�������ļ�����;
    QTimer * timer;//��ʱ��;
    int m_nNewestWarnId;//���±�����¼;
    int m_nMaxWarnCnt;//��󱨾���¼��Ŀ;

private:
    bool checkAddr(int addr);//����ַ��Ч��;
    void clearTutorVec();//��ս̵���¼;

signals:
    void updateTime(const QString time);
    void updateSys(const SysStatus type, const int data, const QString str);//����ϵͳ��Ϣ;
    void updateWarn(const QString &pStr, bool reslv);

public slots:
    void saveTime();


};

#endif // ADDRMANAGER_H


