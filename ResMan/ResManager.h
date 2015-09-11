/*!
 *  \file      ResManager.h
 *  \brief     Pretty nice class.
 *  \details   This class is used to demonstrate a number of section commands.
 *  \author    WJF
 *  \version   v0.0
 *  \date      2015/09/06
 *  \pre       First initialize the system.
 *  \bug       Not all memory is freed when deleting an object of this class.
 *  \warning   Improper use can crash your application
 *  \copyright GNU Public License.
 */
#ifndef RESMAN_H
#define RESMAN_H


#include <QtCore/QObject>
#include <QColor>
#include <QtCore/QVector>
#include <QPixmap>
#include <QTranslator>
#include <QApplication>
#include "SimulateMan.h"
#include "UI/Basectrl.h"


//!���̲���
/*! ����MyScada��̬������̵Ĺ��̲���*/
typedef struct _tagProjectParm{
    int m_nFirstPage;           //!<��������id.
    int m_nWidth;               //!<Ŀ����Ļ���(pixel).
    int m_nHeight;              //!<Ŀ����Ļ�߶�(pixel).
    bool m_bPageCirculation;    //!<�Ƿ�������.
    int m_nPeriod;              //!<��������.
    int m_nAddrOff;             //!<��ַƫ��.
    int m_nAddrRange;           //!<��ַ��Χ.
    int m_nLanguage;            //!<����.

}ProjectParm, *LPProjectParm;


//!�����ʾ����
/*! ���������ʾ������Ϣ��\n
 * �ο������;\n
 * �ο����߶�;\n
 * ����ģʽ;\n
 * ��������ɫ;\n
 * ������ɫ(����);\n
 * �ײ���ɫ(����);\n
 * ����ͼƬID;\n
 */
typedef struct _tagPanelParm
{
    int widith;                 //!<��(pixel).
    int height;                 //!<��(pixel).
    int BkMode;                 //!< 0��ɫ��1���䣻2������ͼƬ
    QRgb bkColor;               //!<������ɫ;
    QRgb topColor;              //!<������ɫ;
    QRgb bottomColor;           //!<�ײ���ɫ;
    int nBkPic;                 //!<����ͼƬID;
}PanelParm, *LPPanelParm;


//!ҳ��ͷ
/*! ����һ��ҳ�����Ϣ:��С(��ҳ����ռ�õ��ֽ���)��ҳ�����ID���ؼ���Ŀ*/
typedef struct _tagPageHead
{
    int nPageSize;
    int nTitleID;
    int nCtrlNum;
}PageHead, *LPPageHead;


//!��ҳ���б�ͷ
/*! ������ҳ���б����Ϣ:�ӻ����б��С(��ռ�ֽ���)���ӻ�����Ŀ*/
typedef struct _tagSubPageListHead
{
    int nSubPageListSize;
    int nSubPageCnt;
}SubPageListHead, *LPSubPageListHead;


//!ҳ�����ṹ��
/*! ���������е�ҳ������,���и�����ҳ��������ڴ��ҵ�*/
typedef struct _tagPagesStruct
{
   int nPageNum;//!<һ��ҳ����Ŀ;
   QVector<LPPageHead> pageVector;//!<���е�һ��ҳ��ָ��;
   QVector< QVector<LPPageHead> >pSubPageVector;//!<�ӻ������(���еĶ���ҳ��ָ��);

}PagesStruct, *LPPagesStruct;



//! ��Դ����ģ��,�����ṩ�ӿ�:
/*!
 *  ģ����hex��ַ.\n
 *  ���̲���.\n
 *  ������.\n
 *  ����ҳ��ļ���.\n
 *  �����б�.\n
 *  ͼƬ��Դ��ȡ.\n
 *  �ַ�����Դ��ȡ.\n
 *  ������Ϣ��Դ��ȡ.\n
 *  �����л�.\n
 *  ���غ���������.\n
 *  ��������������.\n
 */
class ResManager : public QObject
{
    Q_OBJECT

public:
    explicit ResManager(QObject *parent = 0);
    ~ResManager();

private:
//data:
    QVector<QPixmap*> m_imgVec;         //!<ͼƬ��Դ;
    QVector<QString *>m_strVec;         //!<�ַ�����Դ;
    QVector<QString *>m_warnVec;        //!<������Ϣ��Դ;
    QString m_nullString;               //!<���ַ���;
    char *pHex;                         //!<��ȡ��Hex�ļ�������;
    int m_nLanguageSel;                 //!<����ѡ��:0-����, 1-Ӣ��;
    int m_nMaxLanguage;                 //!<���֧�ֵ�������Ŀ;
    QTranslator *m_pTranslator;         //!<������;
    double m_dXfactor;                  //!<����������.
    double m_dYfactor;                  //!<����������.
	
//methods:
    void setupSubPageVector(const LPSubPageListHead pSub, int nId); //�����ӻ����б�;
    void setupTaskVector(int *p, int nId);                          //���������б�;
    void loadString(void);                                          //�����ַ���;
    void loadStr(void);                                             //��������ѡ������ַ���.
    void loadHex(void);                                             //����16���������ļ�.
    void loadLanguageConfig(void);                                  //������������ѡ��.
    void loadImg(void);                                             //����ͼƬ��Դ.
    void loadWarnText(void);                                        //���ؾ�����Ϣ.
    void releaseStrRes();                                           //�ͷ��ַ�����Դ.
    void releaseImgRes();                                           //�ͷ�ͼƬ��Դ.
    void releaseWarnRes();                                          //�ͷž�����Ϣ.

public:
//data:
    char *m_pSimulateVar;                                   //!<ģ������������.
    LPProjectParm m_pProjectParm;                           //!<���̲���.
    LPPanelParm m_pPanelParm;                               //!<�����ʾ����.
    PagesStruct m_pageStruct;                               //!<���е�ҳ�����.
    QVector< QVector<LPActDeal> >m_pTaskVector;             //!<�����б����.


//methods:
    QPixmap *getPixmap(const int id);                       //!<����ͼƬID��ȡͼƬ��Դ;
    QPixmap *getPanelBkPixmap();                            //!<��ȡ��屳��ͼƬ;
    QString *getString(const int id);                       //!<�����ַ���ID��ȡ�ַ�����Դ;
    const QString &getWarningText(const int id);            //!<����ID��ȡ������Ϣ�ַ�����Դ;
    void changeLanguage(int nLanguage, bool bInit=false);   //!<�����л�;
    const double getdXfactor() const {return m_dXfactor;}   //!���غ���������.
    const double getdYfactor() const {return m_dYfactor;}   //!��������������.



signals:
    void updateDisp();                                      //!<ˢ�µ�ǰҳ���ź�;

};

//!��Դ����ģ��ȫ�ֶ���
extern  ResManager *g_pResManModule;//��Դ����ģ��;

#endif // RESMAN_H
