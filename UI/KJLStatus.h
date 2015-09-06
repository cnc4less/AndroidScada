#ifndef KJLSTATUS_H
#define KJLSTATUS_H
#include<QLabel>
#include"Basectrl.h"
#include<ResMan/SimulateMan.h>

class KJLStatus : public QLabel
{
    Q_OBJECT
public:
    KJLStatus(QWidget *parent=0, char *data=0);
    ~KJLStatus();

    void setData(void *data, bool byHand = false);

private:
    SimulateMan *m_pSimulate;//�󶨵�ģ�����;
    LPBaseCtrl m_pData;
    LPStatusPri m_pPriData;
    //״̬�б�;
    int *m_pStatus;


private slots:
    void onUpdateTime(const QString time);
    void onUpdateData(int, SimulateMan*, QObject*);//���¶�Ӧ�ı�������;
};

#endif // KJLSTATUS_H
