#ifndef OTHERPAGE_H
#define OTHERPAGE_H

#include <QWidget>
#include <QCheckBox>
#include "Basectrl.h"


//�̵�ҳ�����ҳ��:����

namespace Ui {
class OtherPage;
}

class OtherPage : public QWidget
{
    Q_OBJECT

public:
    explicit OtherPage(QWidget *parent = 0);
    ~OtherPage();

signals:
    void insertTutorRecord(LPTutorRecordStr pRecord, int nCnt, int nRow);

private slots:
    void onInsertTutorRecord(int nRow);

private:
    Ui::OtherPage *ui;
    QVector<QCheckBox *>m_btnGroup;
};

#endif // OTHERPAGE_H
