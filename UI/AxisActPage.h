#ifndef AXISACTPAGE_H
#define AXISACTPAGE_H

#include <QWidget>
#include "Basectrl.h"
#include "KJLEditBox.h"

//�̵�ҳ�����ҳ��:�ᶯ��;


namespace Ui {
class AxisActPage;
}

class AxisActPage : public QWidget
{
    Q_OBJECT

public:
    explicit AxisActPage(QWidget *parent = 0);
    ~AxisActPage();
	void setAllSelected();

signals:
    //void insertTutorRecord(LPTutorRecordStr pRecord, int nCnt, int nRow);
	void insertTutorRecord(QVector<LPTutorRecordStr> &tutorVec, int nCnt, int nRow);

private slots:
    void on_checkBoxMY_clicked();

    void on_checkBoxMZ_clicked();

    void on_checkBoxX_clicked();

    void on_checkBoxSY_clicked();

    void on_checkBoxSZ_clicked();

    void on_checkBoxC_clicked();

    void on_pushButtonSet_clicked();

public slots:
	void onInsertTutorRecord(int nRow);

private:
    Ui::AxisActPage *ui;
    int m_nFlagArray[7];//��¼����ѡ����Ŀ�Լ�����ѡ���;
    //Ϊ�˷����ȡ�༭�����ݣ�������������;
    QVector<KJLEditBox *>posVec;
    QVector<KJLEditBox *>speedVec;
    QVector<KJLEditBox *>delayVec;
    QVector<QString>strVec;
	QVector<LPTutorRecordStr> m_tutorVec;


};

#endif // AXISACTPAGE_H
