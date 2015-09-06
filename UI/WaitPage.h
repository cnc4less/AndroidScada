#ifndef WAITPAGE_H
#define WAITPAGE_H

#include <QWidget>
#include "Basectrl.h"
#include <QButtonGroup>

//�̵�ҳ�����ҳ��:�ȴ�

namespace Ui {
class WaitPage;
}

class WaitPage : public QWidget
{
    Q_OBJECT

public:
    explicit WaitPage(QWidget *parent = 0);
    ~WaitPage();

signals:
    void insertTutorRecord(LPTutorRecordStr pRecord, int nCnt, int nRow);

private slots:
    void onInsertTutorRecord(int nRow);

private:
    Ui::WaitPage *ui;
    QButtonGroup *m_pBtnGroup;
};

#endif // WAITPAGE_H
