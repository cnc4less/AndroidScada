#ifndef ZTOOL_H
#define ZTOOL_H

#include <QWidget>
#include "Basectrl.h"

//�̵�ҳ�����ҳ��:�ξ�

namespace Ui {
class Ztool;
}

class Ztool : public QWidget
{
    Q_OBJECT

public:
    explicit Ztool(QWidget *parent = 0);
    ~Ztool();

    void adjustHeaderWidth();

signals:
    void insertTutorRecord(LPTutorRecordStr pRecord, int nCnt, int nRow);

private slots:
    void onInsertTutorRecord(int nRow);


private:
    Ui::Ztool *ui;
    QStringList nameList;
    int m_nFlagArray[7];//��¼����ѡ����Ŀ�Լ�����ѡ���;
};

#endif // ZTOOL_H
