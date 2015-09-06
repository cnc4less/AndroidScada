#ifndef TUTOREDITDLG_H
#define TUTOREDITDLG_H

#include <QDialog>
#include "Basectrl.h"
#include "KJLEditBox.h"
#include <QCheckBox>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>


namespace Ui {
class TutorEditDlg;
}

class TutorEditDlg : public QDialog
{
    Q_OBJECT

public:
    explicit TutorEditDlg(LPTutorRecordStr m_pRecord, QWidget *parent = 0);
    ~TutorEditDlg();

//data:
    LPTutorRecordStr m_pRecord;

//controls
    QBoxLayout *m_pLayout;//����
    QPushButton *m_pSetButton;//����
    KJLEditBox *m_pPosBox;//λ��;
    KJLEditBox *m_pSpeedBox;//�ٶ�;
    KJLEditBox *m_pDelayBox;//�ӳ�ʱ��;
    KJLEditBox *m_pDeclineSpeedBox;//��ǰ����;
    KJLEditBox *m_pDeclinePosBox;//��ǰλ��;
    QCheckBox *m_pCheckEndPos;//��ǰ����λ��;
    QCheckBox *m_pCheckDeclineSpeed;//��ǰ����;
    KJLEditBox *m_pLayoutSel;//�ѵ�ѡ��;
    KJLEditBox *m_pMoldInvervalBox;//���ģ��;
    QRadioButton *m_pHorizantalCheck;//ˮƽ;
    QRadioButton *m_pVerticalCheck;//��ֱ;





private:
    Ui::TutorEditDlg *ui;

//methods:
    void setupAxisEidtLayout();//�ᶯ�༭;
    void setupLayerEditLayout();//�ѵ��༭;
    void setupZToolEditLayout();//�ѵ��༭;
    void setupSignalEditLayout();//�ܻ��źű༭;
    void setupExtraEditLayout();//�����豸�༭;
    void setupPreserveEditLayout();//Ԥ���༭;
    void setupCheckEditLayout();//���༭;
    void setupWaitEditLayout();//�ȴ��༭;
    void setupOtherEditLayout();//�����༭;
    void setupSampleEditLayout(bool bMoldInterval = false, int delay_offset=2, int interval_off=3);//�ξ߱༭;

private slots:
    void onCheckDeclineSpeedClicked();//��ǰ����λ�ñ�����;
    void onCheckEndPosClicked();//��ǰ���ٱ�����;

    void on_buttonBox_accepted();//ȷ�ϲ������������ݱ���;
};

#endif // TUTOREDITDLG_H
