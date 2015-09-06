#ifndef RESMAN_H
#define RESMAN_H

//Desc:ResMan������Դ����;

#include <QtCore/QObject>
#include <QColor>
#include <QtCore/QVector>
#include <QPixmap>
#include <QTranslator>
#include <QApplication>
#include "SimulateMan.h"
#include "UI/Basectrl.h"



typedef struct _tagProjectParm{
    // ��������;
    int m_nFirstPage;
    //���;
    int m_nWidth;
    //�߶�;
    int m_nHeight;
    // �Ƿ�������;
    bool m_bPageCirculation;
    // ��������;
    int m_nPeriod;
    //��ַƫ��;
    int m_nAddrOff;
    //��ַ��Χ;
    int m_nAddrRange;
    //����;
    int m_nLanguage;

}ProjectParm, *LPProjectParm;

//������;
typedef struct _tagPanelParm
{
    int widith;//��;
    int height;//��;
    int BkMode;//0��ɫ��1���䣻2������ͼƬ
    QRgb bkColor;//������ɫ;
    QRgb topColor;//������ɫ;
    QRgb bottomColor;//�ײ���ɫ;
    int nBkPic;//����ͼƬID;
}PanelParm, *LPPanelParm;


//ҳ��ͷ����������һ��ҳ��
typedef struct _tagPageHead
{
    int nPageSize;
    int nTitleID;
    int nCtrlNum;
}PageHead, *LPPageHead;

typedef struct _tagSubPageListHead
{
    int nSubPageListSize;//�ӻ����б��С;
    int nSubPageCnt;//�ӻ�����Ŀ;
}SubPageListHead, *LPSubPageListHead;

//���������е�ҳ������;
typedef struct _tagPagesStruct
{
    int nPageNum;//ҳ����Ŀ;
   QVector<LPPageHead> pageVector;//���е�ҳ��ָ��;
   //QVector<LPPageHead> *pSubPageVector;//�ӻ������;
   QVector< QVector<LPPageHead> >pSubPageVector;//�ӻ������;

}PagesStruct, *LPPagesStruct;





class ResManager : public QObject
{
    Q_OBJECT
public:
    explicit ResManager(QObject *parent = 0);
    ~ResManager();

private:
//data:
    //��Դ;
    QVector<QPixmap*> m_imgVec;//ͼƬ��Դ;
    QVector<QString *>m_strVec;//�ַ�����Դ;
    QVector<QString *>m_warnVec;//������Ϣ��Դ;
    QString m_nullString;//���ַ���;
    void *pHex;//��ȡ��Hex�ļ�������;
    int m_nLanguageSel;//����ѡ��:0-����, 1-Ӣ��;
    int m_nMaxLanguage;//���֧�ֵ�������Ŀ;
    int m_nAdminPwd;//����Ա����;
    int m_nSeniorAdminPwd;//�߼�����Ա����;
	QTranslator *m_pTranslator;
	

//methods:
    void setupSubPageVector(const LPSubPageListHead pSub, int nId);
    void setupTaskVector(int *p, int nId);
	void loadString(void);//�����ַ���;

public:
//data:
    char *m_pSimulateVar;//ģ������������;
    LPProjectParm m_pProjectParm;//���̲���;
    LPPanelParm m_pPanelParm;//������;
    PagesStruct m_pageStruct;//���е�ҳ�����;
    //QVector<LPActDeal> *m_pTaskVector;//�ӻ������;
	QVector< QVector<LPActDeal> >m_pTaskVector;//�ӻ������;


//methods:
    //������Դ;
    void loadHex(void);//���ر����ļ�;
    void loadConfig(void);//��������ѡ��;
    void loadImg(void);//����ͼƬ��Դ;
    void loadWarnText(void);//���ؾ�����Ϣ;
	void loadStr(void);//�����ַ���;
    void releaseStrRes();//�ͷ��ַ�����Դ;
    void releaseImgRes();//�ͷ�ͼƬ��Դ;
    void releaseWarnRes();//�ͷž�����Ϣ;
    void changeLanguage(int nLanguage, bool bInit=false);//�л�����;
    void changePwd(int who, int oldPwd, int newPwd);
    QPixmap *getPixmap(const int id);
    QPixmap *getPanelBkPixmap();
    QString *getString(const int id);
    const QString &getWarningText(const int id);


signals:
    void updateDisp();

};


extern  ResManager *g_pResManModule;//��Դ����ģ��;

#endif // RESMAN_H
