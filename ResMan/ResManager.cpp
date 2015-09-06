#include "ResManager.h"
#include <QFile>
#include <QSettings>
#include <QDebug>
#include <QMessageBox>
#include <QTextCodec>
#include <QTextStream>



ResManager::ResManager(QObject *parent)
    : QObject(parent)
    , m_nLanguageSel(0)
    , m_nMaxLanguage(0)
{
    pHex = NULL;

	m_pTranslator = new QTranslator();
    m_pTranslator->load(LAGNUAGEFILE);
}

ResManager::~ResManager()
{
	qDebug()<<"~ResManager()";
    if(pHex)
        delete pHex;
    pHex = NULL;

    m_pageStruct.pSubPageVector.clear();
        
	m_pTaskVector.clear();

    //�ͷ�ͼƬ��Դ;
    releaseImgRes();
    //�ͷ��ַ�����Դ;
    releaseStrRes();
    //�ͷž�����Ϣ�ַ���;
    releaseWarnRes();

	m_pTranslator->deleteLater();
}

//����Hex�ļ�;
void ResManager::loadHex()
{
    //[0]��������;
    //[1]���̲���;
    //[2]������;
    //[3]ҳ�����;
    char *pTemp;
    QFile file(HEXFILE);
    if (!file.open(QIODevice::ReadOnly))
        return;

    qint64 size = file.size();
//    if(pHex)
//    {
//        delete pHex;
//        pHex = NULL;
//    }
    //��ȡ�ļ�;
    pHex = new char[size];
    file.read((char *)pHex, size);
    m_pSimulateVar = (char *)pHex;//ģ�������Ŀ(4 bytes)
    pTemp = m_pSimulateVar;
    pTemp = (char *)((int *)pTemp + 1);//ģ�������������Ĵ�С(4 bytes)
    pTemp = (char *)(pTemp + *((int *)pTemp));//���̲���;
    m_pProjectParm = (LPProjectParm)pTemp;
    m_pPanelParm = (LPPanelParm)(pTemp+sizeof(ProjectParm));
    //ҳ����Ŀ;
    int *pNum = (int*)((char*)m_pPanelParm + sizeof(PanelParm));
    m_pageStruct.nPageNum = *pNum;
    LPPageHead pPageHead = (LPPageHead)((char*)pNum + sizeof(int));
    for(int i = 0; i < *pNum; i++)
    {
        m_pageStruct.pageVector.append(pPageHead);
        pPageHead = (LPPageHead)((char *)pPageHead + pPageHead->nPageSize);
    }

    //m_pageStruct.pSubPageVector = new (QVector<LPPageHead>)[*pNum];//�����ӻ������;
	m_pageStruct.pSubPageVector.resize(*pNum);//�����ӻ������;
    LPSubPageListHead pSubPageListHead = (LPSubPageListHead)pPageHead;
    for(int i = 0; i < *pNum; i++)
    {
//        qDebug()<<"����:"<<i;
//        qDebug()<<"�ӻ�����Ŀ:"<<pSubPageListHead->nSubPageCnt;
//        qDebug()<<"�ӻ����С:"<<pSubPageListHead->nSubPageListSize;
        setupSubPageVector(pSubPageListHead, i);
        pSubPageListHead = (LPSubPageListHead)((char *)pSubPageListHead + pSubPageListHead->nSubPageListSize);
    }


    pNum = (int *)pSubPageListHead;//�������;
    qDebug()<<"..."<<pNum;
    qDebug()<<"..."<<pHex;
    qDebug()<<"task num:"<<*pNum;
    //m_pTaskVector = new QVector<LPActDeal>[*pNum];
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
    //ҳ������;
    file.close();

}

void ResManager::loadConfig()
{
    //��ȡ����ѡ��;
    QSettings settings(OPTIONGFILE, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GB2312"));
    m_nMaxLanguage = settings.value("SYS/MaxLanguage").toInt();//���֧�ֵ�������Ŀ;
    m_nLanguageSel = settings.value("SYS/LanguageSel").toInt();//������ѡ�е�����;
    m_nAdminPwd = settings.value("SYS/AdminPwd").toInt();//����Ա����;
    m_nSeniorAdminPwd = settings.value("SYS/SeniorAdminPwd").toInt();//�߼�����Ա����;
}




//����ͼƬ��Դ;
void ResManager::loadImg()
{
    QSettings settings(OPTIONGFILE, QSettings::IniFormat);
    QString strPath;
    QString strTemp;
    //ͼƬ��Դ��Ŀ;
    int num = settings.value("IMG/num").toInt();
    for(int i = 0; i < num; i++)
    {
        strTemp = QString("IMG/%1").arg(i);
        strPath = settings.value(strTemp).toString();
        qDebug()<<strPath;
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
    //������Ϣ��Ŀ;
	
	int num = settings.value("WARN/num").toInt();
	for(int i = 0; i < num; i++)
	{
		strTemp = QString("WARN/%1").arg(i);
		string = settings.value(strTemp).toString();
		qDebug()<<string;
		QString *pString = new QString(string);
		m_warnVec.append(pString);
	}
	qDebug()<<"fucking load warn done";
}

//    QSettings settings("Option.ini", QSettings::IniFormat); // ��ǰĿ¼��INI�ļ�
//    settings.beginGroup("DevOption");
//    settings.setValue("1", QString("���"));
//    settings.setValue("2", QString("���"));
//    settings.setValue("3", QString("���"));
//    settings.endGroup();

//�����ַ�����Դ;
void ResManager::loadString()
{
     QSettings settings(OPTIONGFILE, QSettings::IniFormat);
     settings.setIniCodec(QTextCodec::codecForName("GB2312"));
     QString string;
     QString strTemp;
     QString strLanguage="STRING";//����ѡ��;
     strLanguage = strLanguage + QString::number(m_nLanguageSel);
     //�ַ�����Դ��Ŀ;
     int num = settings.value(strLanguage+"/num").toInt();
     for(int i = 0; i < num; i++)
     {
        strTemp = QString(strLanguage+"/%1").arg(i);
        string = settings.value(strTemp).toString();
        //qDebug()<<string;
        QString *pString = new QString(string);
        m_strVec.append(pString);
     }
    qDebug()<<"fucking load string done";
}

void ResManager::changeLanguage(int nLanguage, bool bInit/* = false*/)
{
	if(bInit)
		nLanguage = m_nLanguageSel;
    int nTemp = nLanguage%m_nMaxLanguage;
	//int nTemp = 0;
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

	if(m_nLanguageSel==0)
	{
		qApp->installTranslator(m_pTranslator);
	}
	else
	{
		qApp->removeTranslator(m_pTranslator);
	}

}

void ResManager::changePwd(int who, int oldPwd, int newPwd)
{
    if(who==0)//����Ա;
    {
        if(oldPwd != m_nAdminPwd)
        {
            QMessageBox::warning(0, tr("Warning"),tr("PWD ERROR"));
            return;
        }
        m_nAdminPwd = newPwd;
        //���浽�����ļ�;
        QSettings settings(OPTIONGFILE, QSettings::IniFormat);
        settings.setIniCodec(QTextCodec::codecForName("GB2312"));
        settings.setValue("SYS/AdminPwd", m_nAdminPwd);

        QMessageBox::information(0, tr("Tips"), tr("Change Pwd success"));
    }
    else//�߼�����Ա;
    {
        if(oldPwd != m_nSeniorAdminPwd)
        {
            QMessageBox::warning(0, tr("Warning"),tr("PWD ERROR"));
            return;
        }
        m_nSeniorAdminPwd = newPwd;
        //���浽�����ļ�;
        QSettings settings(OPTIONGFILE, QSettings::IniFormat);
        settings.setIniCodec(QTextCodec::codecForName("GB2312"));
        settings.setValue("SYS/SeniorAdminPwd", m_nSeniorAdminPwd);

        QMessageBox::information(0, tr("Tips"), tr("Change Pwd success"));
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
        //m_pageStruct.pSubPageVector[nId].append(pPageHead);
		pPVector->append(pPageHead);
        pPageHead = (LPPageHead)((char *)pPageHead + pPageHead->nPageSize);
    }
}

void ResManager::setupTaskVector(int *p, int nId)
{
    int *pp = p;
    pp = pp + 1;//������ĸ���;
    if(*pp == 0)
        return;
    int nCnt = *pp;
    qDebug()<<"action cnt:"<<nCnt;
    pp = pp + 1;//ָ���һ������;
    qDebug()<<"---"<<pp;
    LPActDeal pAct = (LPActDeal)(pp);
	QVector<LPActDeal> *pTVector = const_cast< QVector<LPActDeal> * >(&m_pTaskVector.at(nId) );
    for(int i = 0; i < nCnt; i++)
    {
        //qDebug()<<"*pp="<<*pp;
        //m_pTaskVector[nId].append(pAct);
		pTVector->append(pAct);
        pAct = pAct + 1;
    }
}

void ResManager::loadStr(void)
{
	changeLanguage(0, true);
	qDebug()<<"fuck1";
}

