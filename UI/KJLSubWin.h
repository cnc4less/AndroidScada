#ifndef KJLSUBWIN_H
#define KJLSUBWIN_H

#include <QWidget>
#include "Basectrl.h"
#include "ResMan/ResManager.h"
#include "ResMan/ArchiveManager.h"
#include "ResMan/SimulateMan.h"

class KJLSubWin : public QWidget
{
    Q_OBJECT
public:
    explicit KJLSubWin(QWidget *parent = 0, char *data=0);
    ~KJLSubWin();

private:
    SimulateMan *m_pSimulate;
    LPBaseCtrl m_pData;
    LPSubWinPri m_pPriData;
    int *m_pSubPage;//�ӻ���ƫ����ָ��;
    QVector<QWidget *>m_ctrlVec;//�ؼ��б�;
    int m_nCurSubPage;//��ǰ�ӻ���;

    void clearCtrlVec();//����ؼ��б�;

protected:
    virtual void closeEvent(QCloseEvent * event);

signals:

public slots:
    void onChangePage(int nPage);
    void onUpdateData(int, SimulateMan*, QObject*);//���¶�Ӧ�ı�������;
};

#endif // KJLSUBWIN_H
