#ifndef TUTORPAGE_H
#define TUTORPAGE_H

#include <QWidget>
#include <QVector>
#include <QAbstractTableModel>
#include "UI/Basectrl.h"


/* @�̵�ҳ��;
 * @˵��:��ģ��ʵ�̵ֽ�ҳ��Ŀ����߼��Լ�����̵�ҳ��ĵײ����ݽṹ��;
 * @���ݽṹ:�̵���Ŀ�ǽ̵��������б����ʾ��һ������,��Ӧ�����ݽṹΪһ���̵���¼�ṹ��TutorRecord;
 *      ���Ա��ǽ̵���¼��������������еĽ̵���¼������ʹ�õ����Ա���ʽΪQT���õ�QVecotr�����࣬�������;
 * @�����߼�:���ڲ������Ա���һ�׷���,�ֱ��ǳ�ʼ�������롢ɾ���Ȳ��������׷������²������Ա����ݣ����ϳн�Model�Ĳ�����Ҳ����MVCģ����Model�����ݵĲ���;
*/
class TutorModel;
typedef QString (TutorModel::*FmtTutorRecord)(LPTutorRecordStr pRecord);

class TutorModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TutorModel(QObject *parent = 0);
    ~TutorModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool insertRow(int row, const QModelIndex & parent = QModelIndex());
    bool insertRows(int row, int count, const QModelIndex & parent = QModelIndex());
    bool removeRow(int row, const QModelIndex & parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());

    void deleteTutorRecord(int nRow);//�����Ա���ɾ����nRowָ���Ľ̵���Ŀ,5 < nRow < ���Ľ̵���ĿID; deleteTutorRecord;
    void comboTutorRecord(int nRow);//���nRow��λ�Ľ̵���Ŀ���ڲ�������updateRecordStep���½̵���Ŀ����;
    void splitTutorRecord(int nRow);//�ֽ�nRow��λ�Ľ̵���Ŀ���ڲ�������updateRecordStep���½̵���Ŀ����;
    LPTutorRecordStr getRawTutorRecord(int nRow);//��ȡnRow��λ�Ľ̵���Ŀ��ԭʼ����;
	

public slots:
    void onInsertTutorRecord(LPTutorRecordStr pRecord, int cnt, int nRow);//�����Ա�ĵ�nRow�У�����cnt���̵���¼;
	void onInsertTutorRecord(QVector<LPTutorRecordStr> &, int cnt, int nRow);//�����Ա�ĵ�nRow�У�����cnt���̵���¼;


private:
//data:
    QVector<LPTutorRecordStr> &m_tutorVec;//�̵���¼�ļ���;
    FmtTutorRecord m_fmtRecord[10];
	QStringList m_strListAxist;//�ᶯ����¼�õ����ַ�������Ҫ����;
//methods:
    void initTutorRecordVec();//��ʼ���̵���Ŀ���Ա�:������λ��[5������ξ�]��ģ���������7���̵���¼;
    //����̵���Ŀ�����Ա�,public slots:onInsertTutorRecord

    //��ȡ���Ա�Ĵ�С:rowCount�����Ѿ�ʵ��;
    
    void replaceTurtorRecord(int nRow, LPTutorRecordStr pRecord);//�滻�̵���Ŀ���ݣ��༭ʱ���õ�;
    void serializeTutorRecordVec();//���л����Ա��ļ�;
	void updateRecordStep(int nRow, int add);//���½̵���Ŀ�����;
    //�ӽ̵���Ŀ�����и�ʽ�����ַ���,����tableView����ʾ,data�������õ�;
    QString fmtAxisRecord(LPTutorRecordStr pRecord);//��ʽ���ᶯ������Ϊ��ʾ�ַ���;
    QString fmtLayerRecord(LPTutorRecordStr pRecord);//��ʽ���ѵ���������Ϊ��ʾ�ַ���;
    QString fmtZToolRecord(LPTutorRecordStr pRecord);//��ʽ���ξ�����Ϊ��ʾ�ַ���;
    QString fmtSignalRecord(LPTutorRecordStr pRecord);//��ʽ���ܻ��ź�����Ϊ��ʾ�ַ���;
    QString fmtExtraDevRecord(LPTutorRecordStr pRecord);//��ʽ�������豸����Ϊ��ʾ�ַ���;
    QString fmtPreserveRecord(LPTutorRecordStr pRecord);//��ʽ��Ԥ������Ϊ��ʾ�ַ���;
    QString fmtCheckRecord(LPTutorRecordStr pRecord);//��ʽ���������Ϊ��ʾ�ַ���;
    QString fmtWaitRecord(LPTutorRecordStr pRecord);//��ʽ���ȴ�����Ϊ��ʾ�ַ���;
    QString fmtOtherRecord(LPTutorRecordStr pRecord);//��ʽ����������Ϊ��ʾ�ַ���;
	QString fmtEndRecord(LPTutorRecordStr pRecord);//��ʽ��ģ�����Ϊ��ʾ�ַ���;
};










namespace Ui {
class TutorPage;
}

class TutorPage : public QWidget
{
    Q_OBJECT

public:
    explicit TutorPage(QWidget *parent = 0);
    ~TutorPage();

signals:
    void insertTutorRecord(int nRow);//����̵���Ŀ;

private slots:
    void on_pushButtonInsert_clicked();//����;
    void on_pushButtonEdit_clicked();//�༭;
    void on_pushButtonDel_clicked();//ɾ��;
    void on_pushButtonMenu_clicked();//�˵�;
    void onPushBtnAxisActionClicked();//�ᶯ��;
    void onPushBtnLayerClicked();//�ѵ�;
    void onPushBtnZToolClicked();//�ξ�;
    void onPushBtnSignalClicked();//�ܻ��ź�;
    void onPushBtnExtraDeviceClicked();//�����豸;
    void onPushBtnPreserveClicked();//Ԥ��;
    void onPushBtnCheckClicked();//���;
    void onPushBtnWaitClicked();//�ȴ�;
    void onPushBtnOtherClicked();//����;

    void on_pushButtonSplit_clicked();//�ֽ�;
    void on_pushButtonCombo_clicked();//���;
	void on_pushButtonReset_clicked();//��������;

    void on_pushButtonQuickSet_clicked();

private:
//DATA:
    Ui::TutorPage *ui;
    int m_nTutorMode;

//METHOD:
    void clearSubPage();//����ӻ���;
};









#endif // TUTORPAGE_H
