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

//!��������ģ��,�����ṩ�ӿ�:
/*!
 * ģ���л�.\n
 * ����������.\n
 * ��ȡģ������.\n
 * ��ȡ�������ļ�����.\n
 * ���µ�ǰҳ��id�������ʾ.\n
 * ��ȡ��ǰҳ��ID\n
 * �����û�����.\n
 * ������ʾ������Ϣ.\n
 * ���뱨����Ϣ.\n
 * ɾ��������Ϣ.\n
 *
 * �̵������б�.\n
 * ģ������б�.\n
 * ͨѶ����ģ��.\n
 */
class ArchiveManager : public QObject
{
    Q_OBJECT
public:
    ArchiveManager(QObject *parent = 0);
    ~ArchiveManager();
    friend class SimulateMan;                               //����SimulateMan������;

    void changeMold(const QString strFile, bool bFromBackup = false);//!<ģ�Ÿı����;
    void loadPanel(const QString strFile);                  //!<����������;
    const QString &getMoldName();                           //!<��ȡģ������;
    const QString &getPanelName();                          //!<��ȡ�������;
    void updateSysPage(int page);                           //!<���µ�ǰҳ������ʾ;
    int getSysPage();                                       //!<��ȡ��ǰҳ��ID;
    void changePwd(int who, int oldPwd, int newPwd);        //!<��������;
    void test();                                            //!<���Ա�ģ��Ķ�д����;

    void triggerDisplayRecord();                            //!<������ʾ������Ϣ;
    void insertWarning(const int id);                       //!<���뱨����Ϣ;
    void removeWarning(const int id);                       //!<���������Ϣ;

    QVector<LPTutorRecordStr> m_tutorVec;                   //!<�̵������б�;
    QMap<int, SimulateMan*>simulateMap;                     //!<ģ������������;
    Communication *m_pCommunication;                        //!<ͨѶģ��;


private:
    int m_nAddrOff;                                         //��ַƫ����;
    int m_nAddrRange;                                       //��ַ��Χ;
    char *m_pParameter;                                     //����������;
    QString m_moldName;                                     //ģ������;
    QString m_panelFile;                                    //�������ļ�����;
    int m_nAdminPwd;                                        //!<����Ա����;
    int m_nSeniorAdminPwd;                                  //!<�߼�����Ա����;
    QTimer * timer;                                         //��ʱ��;
    int m_nNewestWarnId;                                    //���±�����¼;
    int m_nMaxWarnCnt;                                      //��󱨾���¼��Ŀ;
    QMap<int, QString *>m_WarningMap;                       //������Ϣ������;

    bool checkAddr(int addr);                               //����ַ��Ч��;
    void clearTutorVec();                                   //��ս̵���¼;
    void setupSimulateManager(char *p);                     //����ģ���������;
    void setupAddrManger(int nAddrOff, int nAddrRange);     //������ַ����;
    void loadMold(const QString strFile);                   //����ģ��;
    void saveMold();                                        //����ģ�Ų���;
    void updateMold();                                      //������ʾģ��;
    void savePanel();                                       //����������;

    void writeByte(int addr, char val);                     //д1�ֽڵ�ַ����;
    void writeWord(int addr, int val);                      //д2�ֽڵ�ַ����;
    void writeDWord(int addr, int val);                     //д4�ֽڵ�ַ����;
    char readByte(int addr);                                //��1�ֽڵ�ַ����;
    int readWord(int addr);                                 //��2�ֽڵ�ַ����;
    int readDWord(int addr);                                //��4�ֽڵ�ַ����;

    void loadWarnRecord();                                  //���ر�����¼;
    void saveWarnRecord();                                  //���汨����¼;
    void releaseWarnRecord();                               //�ͷ�m_WarningMap�Ŀռ�;

signals:
    void updateTime(const QString time);
    void updateSys(const SysStatus type, const int data, const QString str);//����ϵͳ��Ϣ;
    void updateWarn(const QString &pStr, bool reslv);

private slots:
    void saveTime();

};

#endif // ADDRMANAGER_H


