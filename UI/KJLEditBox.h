#ifndef KJLEDITBOX_H
#define KJLEDITBOX_H

#include <QLineEdit>
#include <QtGui/QKeyEvent>
#include "Basectrl.h"
#include "ResMan/ArchiveManager.h"
#include <QDebug>

class KJLEditBox : public QLineEdit
{
    Q_OBJECT
public:
    KJLEditBox(QWidget *parent=0, char *data=0);
    ~KJLEditBox();

    void setDataFmt(const int nDecimal, const QString &min, const QString &max, const QString &iniText);


protected:
    virtual void keyPressEvent(QKeyEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * e);
    virtual void closeEvent(QCloseEvent * event);


private:
//data:
    LPBaseCtrl m_pData;//�ؼ�ͨ������;
    LPEditPri m_pPriData;//�༭��ؼ���˽������;
    SimulateMan *m_pSimulate;//�󶨵�ģ�����;
    //QValidator *m_pValidator;//��ʽ����;
    int m_nMax;//���ֵ;
    int m_nMin;//��Сֵ;
    int m_nDecimal;//С��λ;
    QString m_strMax;//���ֵ�ַ���;
    QString m_strMin;//��Сֵ�ַ���;
    QString m_strDisp;//��ʾ���ַ���;

//methods:
    void checkValidity(QString &);
    void showWarning();

private slots:
     void fmText(const QString &);//���������ַ���;
     void onUpdateTime(const QString time);
     void onUpdateData(QString, SimulateMan*, QObject*);//���¶�Ӧ�ı�������;
     void onUpdateData(int, SimulateMan*, QObject*);//���¶�Ӧ�ı�������;


};

#endif // KJLEDITBOX_H
