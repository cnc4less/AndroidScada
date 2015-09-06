#include "LayerPage.h"
#include "ui_LayerPage.h"
#include "UI/Basectrl.h"
#include "UI/KJLStatic.h"
#include "UI/KJLStatus.h"

//QRect rect;
//bool bPen;
//bool bBrush;
//LOGPEN logpen;
//LOGBRUSH logbrush;
//QRgb forwardColor;
//bool bVar;
//int nTextID;
//bool bDynamic;
//int nDynamicID;
//int nDynamicCondition;
//int nPermission;//�ؼ���Ȩ��0:���Ա, 1:����Ա, 2:ϵͳ����Ա;

//�������£��������ø�����һ��;
int b[12][20]={
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        55,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        59,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        63,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        56,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        60,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        64,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        57,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        61,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        65,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        58,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        62,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        66,//����id
        0,
        -1,
        -1,
        2,
        2
    },

};

////����:0-2�����֣�ͼƬ������;
//int m_nType;
//// ˮƽ���뷽ʽ:0-2���ҡ���;
//int m_nHorizantalAlign;
////״̬��Ŀ��;
//int m_nStatCnt;
//����˳����һ��;
int a[4][26]={
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,
        51,//����
        0,
        -1,
        -1,
        2,
        //˽������:
        0,
        2,
        4,
        149,151,150,152//״̬;
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,
        52,//����
        0,
        -1,
        -1,
        2,
        //˽������:
        0,
        2,
        4,
        149,151,150,152//״̬;
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,
        53,//����
        0,
        -1,
        -1,
        2,
        //˽������:
        0,
        2,
        4,
        149,151,150,152//״̬;
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,
        54,//����
        0,
        -1,
        -1,
        2,
        //˽������:
        0,
        2,
        4,
        149,151,150,152//״̬;
    },
};

//������ʾ���������label;
int c[12][26]={
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,
        172,//����
        0,
        -1,
        -1,
        2,
        //˽������:
        0,
        1,//���뷽ʽ
        2,
        391,392//״̬;(MY:����/MY:����)
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,
        173,//����
        0,
        -1,
        -1,
        2,
        //˽������:
        0,
        1,//���뷽ʽ
        2,
        393,394//״̬;(MZ:����/MZ:����)
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,
        174,//����
        0,
        -1,
        -1,
        2,
        //˽������:
        0,
        1,//���뷽ʽ
        2,
        395,396//״̬;(X:����/X:����)
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,
        176,//����
        0,
        -1,
        -1,
        2,
        //˽������:
        0,
        2,
        2,
        391,392//״̬;(MY:����/MY:����)
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,
        177,//����
        0,
        -1,
        -1,
        2,
        //˽������:
        0,
        1,//���뷽ʽ
        2,
        393,394//״̬;(MZ:����/MZ:����)
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,
        178,//����
        0,
        -1,
        -1,
        2,
        //˽������:
        0,
        1,//���뷽ʽ
        2,
        395,396//״̬;(X:����/X:����)
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,
        180,//����
        0,
        -1,
        -1,
        2,
        //˽������:
        0,
        1,//���뷽ʽ
        2,
        391,392//״̬;(MY:����/MY:����)
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,
        181,//����
        0,
        -1,
        -1,
        2,
        //˽������:
        0,
        1,//���뷽ʽ
        2,
        393,394//״̬;(MZ:����/MZ:����)
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,
        182,//����
        0,
        -1,
        -1,
        2,
        //˽������:
        0,
        1,//���뷽ʽ
        2,
        395,396//״̬;(X:����/X:����)
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,
        184,//����
        0,
        -1,
        -1,
        2,
        //˽������:
        0,
        1,//���뷽ʽ
        2,
        391,392//״̬;(MY:����/MY:����)
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,
        185,//����
        0,
        -1,
        -1,
        2,
        //˽������:
        0,
        1,//���뷽ʽ
        2,
        393,394//״̬;(MZ:����/MZ:����)
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,
        186,//����
        0,
        -1,
        -1,
        2,
        //˽������:
        0,
        1,//���뷽ʽ
        2,
        395,396//״̬;(X:����/X:����)
    },
};

//���ü����һ��;
int d[12][20]={
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        67,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        71,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        75,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        68,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        72,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        76,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        69,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        73,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        77,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        70,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        74,//����id
        0,
        -1,
        -1,
        2,
        2
    },
    {
        0,0,0,0,
        0,
        0,0,0,0,
        0,0,0,
        0,
        1,//�Ƿ����;
        78,//����id
        0,
        -1,
        -1,
        2,
        2
    },

};



LayerPage::LayerPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerPage)
{
    ui->setupUi(this);
    ui->label1_0->setData(b[0], true);
    ui->label1_1->setData(b[1], true);
    ui->label1_2->setData(b[2], true);
    ui->label1_3->setData(b[3], true);
    ui->label1_4->setData(b[4], true);
    ui->label1_5->setData(b[5], true);
    ui->label1_6->setData(b[6], true);
    ui->label1_7->setData(b[7], true);
    ui->label1_8->setData(b[8], true);
    ui->label1_9->setData(b[9], true);
    ui->label1_10->setData(b[10], true);
    ui->label1_11->setData(b[11], true);
    ui->label->setData(a[0], true);
    ui->label_2->setData(a[1], true);
    ui->label_3->setData(a[2], true);
    ui->label_4->setData(a[3], true);

    ui->label_5->setData(c[0], true);
    ui->label_6->setData(c[1], true);
    ui->label_7->setData(c[2], true);
    ui->label_8->setData(c[3], true);
    ui->label_9->setData(c[4], true);
    ui->label_10->setData(c[5], true);
    ui->label_11->setData(c[6], true);
    ui->label_12->setData(c[7], true);
    ui->label_13->setData(c[8], true);
    ui->label_14->setData(c[9], true);
    ui->label_15->setData(c[10], true);
    ui->label_16->setData(c[11], true);

    ui->label_17->setData(d[0], true);
    ui->label_18->setData(d[1], true);
    ui->label_19->setData(d[2], true);
    ui->label_20->setData(d[3], true);
    ui->label_21->setData(d[4], true);
    ui->label_22->setData(d[5], true);
    ui->label_23->setData(d[6], true);
    ui->label_24->setData(d[7], true);
    ui->label_25->setData(d[8], true);
    ui->label_26->setData(d[9], true);
    ui->label_27->setData(d[10], true);
    ui->label_28->setData(d[11], true);

    setStyleSheet("QRadioButton::indicator:unchecked {image: url(:/res/radiobtn0.png);}"
                  "QRadioButton::indicator:checked {image: url(:/res/radiobtn.png);}");

}

LayerPage::~LayerPage()
{
    delete ui;
}

void LayerPage::onInsertTutorRecord(int nRow)
{
    LPTutorRecordStr pRecord = new TutorRecordStr;
    pRecord->strList.append("0");
    pRecord->strList.append("14");
    pRecord->strList.append("15");
    pRecord->strList.append(tr("0"));
    pRecord->strList.append("16");
    pRecord->strList.append("5");
    pRecord->strList.append("0.00");

    pRecord->record.nStep = 0;
    pRecord->record.nType = LAYER_ACT_TUTOR_RECORD_TYPE;
    pRecord->record.pData = new qint16[2];
    qint16 *p = (qint16 *)pRecord->record.pData;
    //������ѡ�����;
    if(ui->radioButton->isChecked())
        p[0]=1;
    else if(ui->radioButton_2->isChecked())
        p[0]=2;
    else if(ui->radioButton_3->isChecked())
        p[0]=3;
    else if(ui->radioButton_4->isChecked())
        p[0]=4;
    p[1]=0;//��ʱ;

    emit(insertTutorRecord(pRecord, 1, nRow));
}



