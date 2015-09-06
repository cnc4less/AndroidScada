#ifndef KJLProgress_H
#define KJLProgress_H
#include<QLabel>
#include"Basectrl.h"
#include<ResMan/SimulateMan.h>

class KJLProgress : public QLabel
{
    Q_OBJECT
public:
    KJLProgress(QWidget *parent=0, char *data=0);
    ~KJLProgress();

private:
    enum {NORMAL, UPALARM, DOWNALRAM};
    SimulateMan *m_pSimulate;//�󶨵�ģ�����;
    LPBaseCtrl m_pData;
    LPProgressPri m_pPriData;
    int m_nProgressFlag;//���ȱ�־;0-2:������ ���ߣ�����;
    int m_nMax;//���ֵ;
    int m_nData;//��ǰֵ;
    int m_nMin;//��Сֵ;
    int m_nDecimal;//С����;
    int m_nUpAlarm;//���߾���ֵ;
    int m_nDwnAlarm;//���;���ֵ;
    QString m_strMax;//���ֵ�ַ���;
    QString m_strMin;//��Чֵ�ַ���;

protected:
    virtual void paintEvent(QPaintEvent *event);


private slots:
    void onUpdateTime(const QString time);
    void onUpdateData(int, SimulateMan*, QObject*);//���¶�Ӧ�ı�������;
    void onUpdateSys(const SysStatus type, const int data, const QString str);//����ϵͳ״̬;
};

#endif // KJLProgress_H
