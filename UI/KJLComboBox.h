#ifndef KJLCOMBOBOX_H
#define KJLCOMBOBOX_H

#include<QComboBox>
#include"Basectrl.h"
#include"ResMan/SimulateMan.h"

class KJLComboBox : public QComboBox
{
    Q_OBJECT
public:
    KJLComboBox(QWidget *parent=0, char *data=0);
    ~KJLComboBox();

private:
    LPBaseCtrl m_pData;
    LPEditPri m_pPriData;
    SimulateMan *m_pSimulate;//�󶨵�ģ�����;
    int *m_pOpt;//ѡ��;


private slots:
    void onCurrentIndexChanged(int index);
    void onUpdateData(int, SimulateMan*, QObject*);//���¶�Ӧ�ı�������;

};

#endif // KJLCOMBOBOX_H
