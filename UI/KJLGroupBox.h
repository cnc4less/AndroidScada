#ifndef KJLGROUPBOX_H
#define KJLGROUPBOX_H

#include<QGroupBox>
#include"Basectrl.h"
#include"ResMan/SimulateMan.h"

class KJLGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    KJLGroupBox(QWidget *parent=0, char *data=0);
    ~KJLGroupBox();

private:
    LPBaseCtrl m_pData;
    SimulateMan *m_pSimulate;

private slots:
    void onUpdateData(int, SimulateMan*, QObject*);//���¶�Ӧ�ı�������;


};

#endif // KJLGROUPBOX_H
