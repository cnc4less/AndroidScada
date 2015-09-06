#include "KJLEditBox.h"
#include <QDebug>
#include <QtCore/qmath.h>
#include "KeyboardDialog.h"
#include "ResMan/ResManager.h"
#include <QMessageBox>
#include <QApplication>
#include <QMainWindow>



extern QMainWindow *gMainWindow;

KJLEditBox::KJLEditBox(QWidget *parent/*=0*/, char *data/*=0*/):
    QLineEdit(parent),
    //m_pValidator(NULL),
    m_pSimulate(NULL),
    m_pData(NULL),
    m_pPriData(NULL)
{
    if( data )//���˽��������Ч;
    {
        //[����λ��]
        m_pData = (LPBaseCtrl)data;
        m_pPriData = (LPEditPri)( (char *)m_pData + sizeof(BaseCtrl) );//˽������;
        setGeometry(m_pData->rect);

        if(m_pPriData->bDispPwd)
            setEchoMode(QLineEdit::Password);

        //[���ݸ�ʽ]
        if(m_pData->bVar)//��ʾ����;
        {
            m_pSimulate = g_pArchiveModule->simulateMap.value(m_pData->nTextID, NULL);//��ȡ��Ӧ�ı���;
            if(!m_pSimulate)
                return;
            m_pSimulate->getFmt(&m_nMax, &m_nMin, &m_nDecimal, m_strMax, m_strMin);
//            int temp = qPow(10, m_nDecimal);
//            QDoubleValidator *pVal = new QDoubleValidator((double)m_nMax/temp , (double)m_nMin/temp, m_nDecimal, this);
//            pVal->setNotation(QDoubleValidator::StandardNotation);
//            m_pValidator = pVal;
//            setValidator(m_pValidator);//ò�ƶ�m_pValidator�Ĳ������ڴ���������������г�������;
            //�󶨱������ݸ����źŲ�
            connect(m_pSimulate, SIGNAL(updateData(QString,SimulateMan*,QObject*)), this, SLOT(onUpdateData(QString,SimulateMan*,QObject*)));
            m_pSimulate->trigle();

            m_pSimulate->addToMonitorList();

        }

        //�Ƿ�̬��ʾ;
        if(m_pData->bDynamic)
        {
            SimulateMan *pSimulateMan = g_pArchiveModule->simulateMap.value(m_pData->nDynamicID, NULL);//��ȡ��Ӧ�ı���;
            if(!pSimulateMan)
                return;
            if(pSimulateMan)
               connect(pSimulateMan, SIGNAL(updateData(int,SimulateMan*,QObject*)), this, SLOT(onUpdateData(int,SimulateMan*,QObject*)));
            //��ȡ��̬��ʾ��Ӧ�ı�����ֵ;
            int temp = pSimulateMan->readInt();
            if( temp == m_pData->nDynamicCondition )
                show();
            else
                hide();
        }
        else
            show();

		setAttribute( Qt::WA_DeleteOnClose, true);
        setAttribute(Qt::WA_TranslucentBackground);

    }

    //connect(this, SIGNAL(textChanged(QString)), this, SLOT(fmText(QString)) );
}

KJLEditBox::~KJLEditBox()
{
//    if(m_pValidator)
//    {
//        delete m_pValidator;
//        m_pValidator = NULL;
//    }
    qDebug()<<"kjleditbox release";

}

//�������ݸ�ʽ;
void KJLEditBox::setDataFmt(const int nDecimal, const QString &min, const QString &max, const QString &iniText)
{
    m_nDecimal = nDecimal;
    if(min.indexOf("$") == -1)
        m_strMin = min;
    else
    {
        QString strTemp = min;
        strTemp.remove(0,1);
        SimulateMan *pSimulate = g_pArchiveModule->simulateMap.value(strTemp.toInt(), NULL);//��ȡ��Ӧ�ı���;
        if(!pSimulate)
            return;
        //pSimulate->getFmt(NULL, NULL, NULL, strTemp, m_strMin);
		m_strMin = pSimulate->read();
    }
    if(max.indexOf("$") == -1)
        m_strMax = max;
    else
    {
        QString strTemp = max;
        strTemp.remove(0,1);
        SimulateMan *pSimulate = g_pArchiveModule->simulateMap.value(strTemp.toInt(), NULL);//��ȡ��Ӧ�ı���;
        if(!pSimulate)
            return;
        m_strMax = pSimulate->read();
    }
    m_strDisp = iniText;
    setText(m_strDisp);
}

void KJLEditBox::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
//        qDebug()<<"return";
        //������д���ڴ�;
        if(!m_pSimulate)
            return;
        m_pSimulate->write(m_strDisp);
    }
    else
        QLineEdit::keyPressEvent(event);
}

void KJLEditBox::mouseReleaseEvent(QMouseEvent *e)
{
    KeyBoardDialog dlg(gMainWindow);
    double dXfactor = (double)g_pResManModule->m_pProjectParm->m_nWidth / 800;//��Ϊ��UI�ļ��в���ʱ���Ǽ�������СΪ800*600;
    double dYfactor = (double)g_pResManModule->m_pProjectParm->m_nHeight / 600;//��Ϊ��UI�ļ��в���ʱ���Ǽ�������СΪ800*600;
    dlg.resize(dlg.width()*dXfactor, dlg.height()*dYfactor);
    if(dlg.exec() == QDialog::Accepted)
    {
        QString strResult = dlg.m_strResult;
        checkValidity(strResult);
    }

}

void KJLEditBox::closeEvent(QCloseEvent *event)
{
    m_pSimulate->delFromMonitorList();
}

//���������Ƿ�Ϸ�;
#include <QThread>
void KJLEditBox::checkValidity(QString &str)
{
    bool flag = true;
    QString strDisp;
	if(m_pSimulate)
		m_pSimulate->getFmt(NULL, NULL, NULL, m_strMax, m_strMin);
    if(m_nDecimal==0)//����;
    {
        //����Ƿ�ӵ�зǷ�С����;
        if( str.indexOf(QChar('.')) != -1)
           flag = false;
        else
        {
            //���ֵ�ķ�Χ�Ƿ�Ϸ�;
            int nTemp = str.toInt();
            int nMin = m_strMin.toInt();
            int nMax = m_strMax.toInt();
            if(nTemp > nMax || nTemp < nMin)
                flag = false;
            else
                strDisp = QString::number(nTemp);
        }

    }
    else//С��;
    {
        if(m_nDecimal < 0)
            return;

        QStringList strList = str.split(QChar('.'));
        if(strList.size()==2)
        {
            //���С��λ���Ƿ���ȷ;
            if(strList.at(1).size() > m_nDecimal )
                flag = false;
            else//���ֵ�ķ�Χ�Ƿ�Ϸ�;
            {
                double dMin = m_strMin.toDouble();
                double dMax = m_strMax.toDouble();
                double dTemp = str.toDouble();
                if(dTemp > dMax || dTemp < dMin)
                    flag = false;
                else
                    strDisp = QString::number(dTemp,'f',m_nDecimal);
            }
        }
        else//���ֵ�ķ�Χ�Ƿ�Ϸ�;
        {
            double dMin = m_strMin.toDouble();
            double dMax = m_strMax.toDouble();
            double dTemp = str.toDouble();
            if(dTemp > dMax || dTemp < dMin)
                flag = false;
            else
                strDisp = QString::number(dTemp,'f',m_nDecimal);
        }




    }

    if(!flag)
        showWarning();
    else
    {
        //qDebug()<<"settext"<<strDisp;
        m_strDisp = strDisp;
        this->setText(m_strDisp);
        //���ؼ��Ƿ��Զ�����;
        if(m_pPriData && m_pPriData->bAutoSave)
        {
            //qDebug()<<"autosave";
            if(!m_pSimulate)
                return;
            m_pSimulate->write(strDisp, this);
            qDebug()<<"thread id:"<<QThread::currentThreadId();
        }

    }
}

void KJLEditBox::showWarning()
{
    QMessageBox::warning(this, tr("input error"), tr("value out of range")+m_strMin+"~"+m_strMax);
}

void KJLEditBox::fmText(const QString &str)
{
    qDebug()<<m_strMax;

//    qDebug()<<str;
//    qDebug()<<(str > m_strMax);
    if(! (str > m_strMax) )
        m_strDisp = str;

    setText(m_strDisp);


}

void KJLEditBox::onUpdateTime(const QString time)
{
    setText(time);
}

void KJLEditBox::onUpdateData(QString data, SimulateMan *pVar, QObject *who)
{
    if(who == this)
        return;
    if(m_pPriData->bDispPwd)
    {
        clear();
    }
    else if(pVar == m_pSimulate)
        setText(data);
}

void KJLEditBox::onUpdateData(int data, SimulateMan *pVar, QObject *who)
{
    if(who == this)
        return;

    if(m_pPriData->bDispPwd)
    {
        clear();
    }
    else if(pVar != m_pSimulate)
    {
        if( data == m_pData->nDynamicCondition )
            show();
        else
            hide();
    }
}





