#ifndef PRESERVEPAGE_H
#define PRESERVEPAGE_H

#include <QWidget>
#include "Basectrl.h"

//�̵�ҳ�����ҳ��:Ԥ��

namespace Ui {
class PreservePage;
}

class PreservePage : public QWidget
{
    Q_OBJECT

public:
    explicit PreservePage(QWidget *parent = 0);
    ~PreservePage();

signals:
    void insertTutorRecord(LPTutorRecordStr pRecord, int nCnt, int nRow);

private slots:
    void onInsertTutorRecord(int nRow);

private:
    Ui::PreservePage *ui;
};

#endif // PRESERVEPAGE_H
