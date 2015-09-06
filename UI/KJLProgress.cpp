#include <QDebug>
#include <QPainter>
#include "KJLProgress.h"
#include "ResMan/ResManager.h"
#include "ResMan/ArchiveManager.h"

KJLProgress::KJLProgress(QWidget *parent/*=0*/, char *data/*=0*/):
    QLabel(parent)
    ,m_pSimulate(NULL)
    ,m_pPriData(NULL)
    ,m_nProgressFlag(0)
    ,m_nMax(0)
    ,m_nData(0)
    ,m_nMin(0)
    ,m_nUpAlarm(0)
    ,m_nDwnAlarm(0)
    ,m_nDecimal(0)
{
    if( data )//���˽��������Ч;
    {
        m_pData = (LPBaseCtrl)data;//��������;
        m_pPriData = (LPProgressPri)( (char *)m_pData + sizeof(BaseCtrl) ); //˽������;
        setGeometry(m_pData->rect);
        //�߿�;
        if(m_pData->bPen)
            setFrameShape(Box);
        //����;
        QPalette palette;
        if(m_pData->bBrush)
        {
            setAutoFillBackground(true);
            //QPalette palette;
            QColor color(m_pData->logbrush.lbColor);
            palette.setColor(QPalette::Background, color);
            setPalette(palette);
        }
        else
            setAttribute(Qt::WA_TranslucentBackground);
        //ǰ��ɫ;
        QColor fwColor(m_pData->forwardColor);
        palette.setColor(QPalette::Foreground, fwColor);
        setPalette(palette);
        //���뷽ʽ
        setAlignment(Qt::AlignCenter);

        if(m_pPriData->bSysOpt)//��ʾϵͳ״̬;
        {
             connect(g_pArchiveModule, SIGNAL(updateSys(SysStatus,int,QString)), this, SLOT(onUpdateSys(SysStatus,int,QString)));
        }
        else if(m_pData->bVar)
        {
            m_pSimulate = g_pArchiveModule->simulateMap.value(m_pData->nTextID, NULL);//��ȡ��Ӧ�ı���;
            if(m_pSimulate)
            {
                connect(m_pSimulate, SIGNAL(updateData(int,SimulateMan*,QObject*)), this, SLOT(onUpdateData(int,SimulateMan*,QObject*)));
                m_pSimulate->getFmt(&m_nMax, &m_nMin, &m_nDecimal, &m_nUpAlarm, &m_nDwnAlarm);
            }
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
        //setAttribute(Qt::WA_TranslucentBackground);
    }
}


KJLProgress::~KJLProgress()
{

}

void KJLProgress::paintEvent(QPaintEvent *event)
{
    //if(m_pPriData->bSysOpt)
    QLabel::paintEvent(event);

    if(m_pPriData->bSysOpt)//ϵͳ״̬;
        return;

    QPainter painter(this);
    //��ɫ;
    QRgb temp;
    if(m_nProgressFlag == NORMAL)
        temp = m_pPriData->colorNormal;
    else if(m_nProgressFlag == UPALARM)
        temp = m_pPriData->colorUpAlarm;
    else
        temp = m_pPriData->colorDwnAlarm;
    QColor bkColor(temp);

    //����;
    int nPercent;
    if(m_pPriData->nOreintation == 0)//ˮƽ;
    {
        nPercent = (double)m_nData / (double)m_nMax *width();
        painter.fillRect(frameWidth(),frameWidth(),nPercent, height()-2*frameWidth() , QBrush(bkColor));
    }
    else
    {
        nPercent = (double)(m_nMax-m_nData) / (double)m_nMax *height();
        int nBottom = (double)(m_nData) / (double)m_nMax *height();
        painter.fillRect(frameWidth(), nPercent, width()-2*frameWidth(), nBottom, QBrush(bkColor));
    }
    return;
}

void KJLProgress::onUpdateTime(const QString time)
{
    setText(time);
}

void KJLProgress::onUpdateData(int data, SimulateMan *pVar, QObject *who)
{
    if(who == this)
        return;

    if(pVar == m_pSimulate)
    {
        m_nData = data;
        if(m_nData > m_nUpAlarm)
            m_nProgressFlag = 1;
        else if(m_nData < m_nDwnAlarm)
            m_nProgressFlag = 2;
        else
            m_nProgressFlag = 0;
        update();
    }
    else//m_pData->nDynamicID��̬��ʾID;
    {
        if( data == m_pData->nDynamicCondition )
            show();
        else
            hide();
    }

}

void KJLProgress::onUpdateSys(const SysStatus type, const int data, const QString str)
{
    if(type != m_pPriData->nSysOpt)
        return;

    if(type == PAGECHANGE)//ҳ��;
    {
        if(data > 100)//ϵͳҳ��;
        {
            if(data == 101)
                setText(tr("Record"));
        }
        else
        {
            LPPageHead pPageHead = g_pResManModule->m_pageStruct.pageVector.at(data);//��ȡ��ǰ��ҳ��ָ��;
            int id = pPageHead->nTitleID;
            QString *pStrTitle = g_pResManModule->getString(id);//����;
            if(pStrTitle)
                setText(*pStrTitle);
        }
    }
    else if(type == MOLDNAME)//����ģ������;
    {
        setText(str);
    }


}
