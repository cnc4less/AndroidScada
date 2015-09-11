#include "ResManager.h"
#include <QFile>
#include <QSettings>
#include <QDebug>
#include <QMessageBox>
#include <QTextCodec>
#include <QTextStream>


//!���캯��
/*!
 * �л�Ĭ������;
 * ����16��������(���������б�������б�);
 * ����ϵͳ����;
 * ����ͼƬ;
 * �����ַ���;
 * ���ؾ�����Ϣ;
 */
ResManager::ResManager(QObject *parent)
    : QObject(parent)
    , m_nLanguageSel(0)
    , m_nMaxLanguage(0)
    , pHex(0)
    , m_pTranslator(new QTranslator())
{
    g_pResManModule = this;
    m_pTranslator->load(LAGNUAGEFILE);//����Ĭ�����԰�;
    loadHex();
    loadLanguageConfig();
    loadImg();
    loadStr();
    loadWarnText();

    m_dXfactor = (double)g_pResManModule->m_pProjectParm->m_nWidth / 800;//��Ϊ��UI�ļ��в���ʱ���Ǽ�������СΪ800*600;
    m_dYfactor = (double)g_pResManModule->m_pProjectParm->m_nHeight / 600;//��Ϊ��UI�ļ��в���ʱ���Ǽ�������СΪ800*600;
}

//!��������
/*!
 * �ͷ�m_pTranslator
 * �ͷ�16�������ݻ�����;
 * �����ҳ���б�;
 * ��������б�;
 * �ͷ�ͼƬ;
 * �ͷ��ַ���;
 * �ͷž�����Ϣ;
 */
ResManager::~ResManager()
{
	qDebug()<<"~ResManager()";
    m_pTranslator->deleteLater();

    if(pHex)
        delete pHex;
    pHex = NULL;

    m_pageStruct.pSubPageVector.clear();
	m_pTaskVector.clear();
    releaseImgRes();
    releaseStrRes();
    releaseWarnRes();

}

//!����16���������ļ�,Hex�ļ��ṹ���£�
/*!
 *   |������Ŀ|(4)\n
 *   |���������С|(4)\n
 *   |����|(����)\n
 *   |���̲���|(ProjectParm�ṹ��С)\n
 *   |������|(PanelParm�ṹ��С)\n
 *   |һ��ҳ����Ŀ|(4)\n
 *   |ҳ��0ͷ|(PageHead�ṹ��С)\n
 *   |ҳ��0�ؼ��б����|(����)\n
 *   |ҳ��1ͷ|(PageHead�ṹ��С)\n
 *   |ҳ��1�ؼ��б����|(����)\n
 *   ....\n
 *   |ҳ��nͷ|(PageHead�ṹ��С)\n
 *   |ҳ��n�ؼ��б����|(����)\n
 *   |һ��ҳ��0��Ӧ���ӻ����б�|\n
 *   |һ��ҳ��1��Ӧ���ӻ����б�|\n
 *   ...\n
 *   |һ��ҳ��n��Ӧ���Ի����б�|\n
 *   |�������|(4)\n
 *   |����0����|\n
 *   |����1����|\n
 *   ....\n
 *   |����n����|\n
 */
void ResManager::loadHex()
{
    char *pTemp;
    QFile file(HEXFILE);
    if(!file.open(QIODevice::ReadOnly))
        return;

    qint64 size = file.size();
    pHex = new char[size];
    file.read(pHex, size);//�Ƿ���ж϶�ȡ�Ĵ�С?????????????????

    m_pSimulateVar = pHex;//ģ�������Ŀ(ռ4 bytes)
    pTemp = m_pSimulateVar;
    pTemp = (char *)((int *)pTemp + 1);//ģ�������������Ĵ�С(4 bytes)
    pTemp = (char *)(pTemp + *((int *)pTemp));//���̲���;
    m_pProjectParm = (LPProjectParm)pTemp;
    m_pPanelParm = (LPPanelParm)(pTemp+sizeof(ProjectParm));//������;

    //ҳ����Ŀ;
    int *pNum = (int*)((char*)m_pPanelParm + sizeof(PanelParm));
    m_pageStruct.nPageNum = *pNum;
    LPPageHead pPageHead = (LPPageHead)((char*)pNum + sizeof(int));
    for(int i = 0; i < *pNum; i++)
    {
        m_pageStruct.pageVector.append(pPageHead);
        pPageHead = (LPPageHead)((char *)pPageHead + pPageHead->nPageSize);
    }

    //�����ӻ������;
    m_pageStruct.pSubPageVector.resize(*pNum);
    LPSubPageListHead pSubPageListHead = (LPSubPageListHead)pPageHead;
    for(int i = 0; i < *pNum; i++)
    {
        setupSubPageVector(pSubPageListHead, i);
        pSubPageListHead = (LPSubPageListHead)((char *)pSubPageListHead + pSubPageListHead->nSubPageListSize);
    }

    //���������б�;
    pNum = (int *)pSubPageListHead;//�������;
	m_pTaskVector.resize(*pNum);
    if(*pNum > 0)
    {
        int *p = pNum + 1;
        for(int i = 0; i < *pNum; i++)
        {
            setupTaskVector(p, i);
            p =(int *)((char*)p+ *p);
        }
    }

    file.close();

}

//!������������ѡ��,����ѡ��;
/*!
 * ���������Ŀ;\n
 * ��ǰѡ�е�����;\n
 */
void ResManager::loadLanguageConfig()
{
    QSettings settings(OPTIONGFILE, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GB2312"));
    m_nMaxLanguage = settings.value("SYS/MaxLanguage").toInt();//���֧�ֵ�������Ŀ;
    m_nLanguageSel = settings.value("SYS/LanguageSel").toInt();//ѡ�е�����;
}



void ResManager::loadImg()
{
    QSettings settings(OPTIONGFILE, QSettings::IniFormat);
    QString strPath;
    QString strTemp;
    int num = settings.value("IMG/num").toInt();
    for(int i = 0; i < num; i++)
    {
        strTemp = QString("IMG/%1").arg(i);
        strPath = settings.value(strTemp).toString();
        QPixmap *pPixmap = new QPixmap(strPath);
        m_imgVec.append(pPixmap);
    }
}

void ResManager::loadWarnText()
{
    QSettings settings(WARNINIFILE, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GB2312"));
    QString string;
    QString strTemp;
	
	int num = settings.value("WARN/num").toInt();
	for(int i = 0; i < num; i++)
	{
		strTemp = QString("WARN/%1").arg(i);
		string = settings.value(strTemp).toString();
//		qDebug()<<string;
		QString *pString = new QString(string);
		m_warnVec.append(pString);
	}
}


//�����ַ�����Դ;
void ResManager::loadString()
{
     QSettings settings(OPTIONGFILE, QSettings::IniFormat);
     settings.setIniCodec(QTextCodec::codecForName("GB2312"));
     QString string;
     QString strTemp;
     QString strLanguage="STRING";//����ѡ��;
     strLanguage = strLanguage + QString::number(m_nLanguageSel);

     int num = settings.value(strLanguage+"/num").toInt();
     for(int i = 0; i < num; i++)
     {
        strTemp = QString(strLanguage+"/%1").arg(i);
        string = settings.value(strTemp).toString();
        //qDebug()<<string;
        QString *pString = new QString(string);
        m_strVec.append(pString);
     }
}

/**
* @param nLanguage ָʾʹ���������� 0:���� 1:Ӣ��.
* @param bInit �Ƿ��һ�������ó���.
* @see ResManager()
* @return void
*/
void ResManager::changeLanguage(int nLanguage, bool bInit/* = false*/)
{
	if(bInit)
		nLanguage = m_nLanguageSel;
    int nTemp = nLanguage%m_nMaxLanguage;

    if((!bInit) && (m_nLanguageSel == nTemp))//
	{
		return;
	}
	m_nLanguageSel = nTemp;
	releaseStrRes();
	loadString();

    //���µ�ǰҳ��;
    emit(updateDisp());

    //���浽�����ļ�;
    QSettings settings(OPTIONGFILE, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GB2312"));
    settings.setValue("SYS/LanguageSel", m_nLanguageSel);

    if(m_nLanguageSel==0)//����;
	{
		qApp->installTranslator(m_pTranslator);
	}
    else//Ӣ��;
	{
		qApp->removeTranslator(m_pTranslator);
	}

}



void ResManager::releaseStrRes()
{
    for(int i = 0; i < m_strVec.size(); i++)
    {
        delete m_strVec.at(i);
    }
    m_strVec.clear();
}

void ResManager::releaseImgRes()
{
    for(int i = 0; i < m_imgVec.size(); i++)
    {
        delete m_imgVec.at(i);
    }
    m_imgVec.clear();
}

void ResManager::releaseWarnRes()
{
    for(int i = 0; i < m_warnVec.size(); i++)
    {
        delete m_warnVec.at(i);
    }
    m_warnVec.clear();
}

//����ID��ȡͼƬ��Դ;
QPixmap *ResManager::getPixmap(const int id)
{
    if(id == -1)
        return NULL;
    if(id >= m_imgVec.size())
    {
        QMessageBox warn(QMessageBox::NoIcon, tr("Warning"),tr("img res id out of range"));
        warn.exec();
        return NULL;
    }
    return m_imgVec.at(id);
}

//��ȡ���ı���ͼƬ;
QPixmap *ResManager::getPanelBkPixmap()
{
    int id = m_pPanelParm->nBkPic;
    return getPixmap(id);
}

//����ID��ȡ�ַ�����Դ;
QString *ResManager::getString(const int id)
{
    if(id == -1)
        return NULL;
    if(id >= m_strVec.size())
    {
        QMessageBox warn(QMessageBox::NoIcon, tr("Warning"),tr("string res id:%1 out of range").arg(id));
        warn.exec();
        return NULL;
    }
    return m_strVec.at(id);
}

const QString &ResManager::getWarningText(const int id)
{
    if(id == -1)
        return m_nullString;
    if(id >= m_warnVec.size())
    {
        QMessageBox::warning(0, tr("Warning"),tr("Warning res id:%1 out of range").arg(id));
        return m_nullString;
    }
    return *m_warnVec.at(id);
}

void ResManager::setupSubPageVector(const LPSubPageListHead pSub, int nId)
{
    int nMax = pSub->nSubPageCnt;
    LPPageHead pPageHead = (LPPageHead)(pSub + 1);
	QVector<LPPageHead> *pPVector = const_cast< QVector<LPPageHead> *>(&m_pageStruct.pSubPageVector.at(nId) );
    for(int i = 0; i < nMax; i++)
    {
		pPVector->append(pPageHead);
        pPageHead = (LPPageHead)((char *)pPageHead + pPageHead->nPageSize);
    }
}

//!���������б�
/*!
 *  |�����С|(4)
 *  |�����ĸ���|(4)
 *  |����0|
 *  |����1|
 *  ...
 *  |����n|
 */
void ResManager::setupTaskVector(int *p, int nId)
{
    int *pp = p;
    pp = pp + 1;
    if(*pp == 0)
        return;
    int nCnt = *pp;//�����ĸ���;
    pp = pp + 1;//ָ���һ������;
    LPActDeal pAct = (LPActDeal)(pp);
	QVector<LPActDeal> *pTVector = const_cast< QVector<LPActDeal> * >(&m_pTaskVector.at(nId) );
    for(int i = 0; i < nCnt; i++)
    {
		pTVector->append(pAct);
        pAct = pAct + 1;
    }
}

void ResManager::loadStr(void)
{
	changeLanguage(0, true);
}

