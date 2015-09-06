#ifndef SIGNALPAGE_H
#define SIGNALPAGE_H

#include <QWidget>
#include "Basectrl.h"
//�̵�ҳ�����ҳ��:�ܻ��ź�

namespace Ui {
class SignalPage;
}

class SignalPage : public QWidget
{
    Q_OBJECT

public:
    explicit SignalPage(QWidget *parent = 0);
    ~SignalPage();

signals:
    void insertTutorRecord(LPTutorRecordStr pRecord, int nCnt, int nRow);

private slots:
    void onInsertTutorRecord(int nRow);

private:
    Ui::SignalPage *ui;
    QStringList nameList;
};

#endif // SIGNALPAGE_H
