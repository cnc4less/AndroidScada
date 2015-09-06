#ifndef KJLBASECTRL_H
#define KJLBASECTRL_H
#include <QtCore/QObject>
#include "ResMan/ResManager.h"

class KJLBaseCtrl;
typedef void (KJLBaseCtrl::*LPdoAct) (int, int);

class KJLBaseCtrl : public QObject
{

    Q_OBJECT
public:
    static KJLBaseCtrl* getInstance();
    ~KJLBaseCtrl();
    LPdoAct m_pFundoAct[6];

protected:
    KJLBaseCtrl(QObject *parent=0);
    void doActSingleSet(int var, int val);//���ز���(��λ����)
    void doActSet(int var, int val);//ģ�������ò���;
    void doActLinkPage(int var, int val);//�������Ӳ���;
    void doActRunTask(int var, int val);//ִ���������;
    void doActLinkSubWin(int var, int val);//�Ӵ��л�ҳ�����;
    void doActRunScript(int var, int val);//�˳�����;

signals:
    void changePage(int nPage);
    void subWinChangePage(int nSubWin, int nPage);
};



#endif // KJLBASECTRL_H

