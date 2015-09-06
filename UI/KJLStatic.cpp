#include <QDebug>
#include <QRect>
#include "KJLStatic.h"
#include "ResMan/ResManager.h"

KJLStatic::KJLStatic(QWidget *parent/*=0*/, char *data/*=0*/)
    :QLabel(parent)
    ,m_pSimulate(NULL)
{
    setData(data);
	setAttribute( Qt::WA_DeleteOnClose, true);
    setAttribute(Qt::WA_TranslucentBackground);
}


KJLStatic::~KJLStatic()
{

}

void KJLStatic::setData(void *data, bool byHand)
{
    if( !data )//���������Ч;
        return;

    m_pData = (LPBaseCtrl)data;
    m_pPriData = (LPStaticPri)( (char *)m_pData + sizeof(BaseCtrl) );

    if(!byHand)//��ק���
    {
        QRect rect(m_pData->rect);
        if(rect.width() < 6)
            rect.setWidth(rect.width()/2);
        if(rect.height() < 6)
            rect.setHeight(rect.height()/2);
        setGeometry(rect);
    }


    if(!m_pData->bVar)//�̶��ı�;
    {
        QString *pStr = g_pResManModule->getString(m_pData->nTextID);
        if(pStr) 
            setText(*pStr);
    }
    else
    {
        m_pSimulate = g_pArchiveModule->simulateMap.value(m_pData->nTextID, NULL);//��ȡ��Ӧ�ı���;
        if(!m_pSimulate)
            return;
        connect(m_pSimulate, SIGNAL(updateData(QString,SimulateMan*,QObject*)), this, SLOT(onUpdateData(QString,SimulateMan*,QObject*)));
        m_pSimulate->trigle();
    }
    if(m_pData->bPen)//�߿�;
        setFrameShape(Box);
    if(m_pData->bBrush)
    {
        setAutoFillBackground(true);
        QPalette palette;
        QColor color(m_pData->logbrush.lbColor);
        palette.setColor(QPalette::Background, color);
        setPalette(palette);
    }

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


    //���ֶ��뷽ʽ;
    if(m_pPriData->m_nHorizantalAlign == 0)
    {
        setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    }else if(m_pPriData->m_nHorizantalAlign == 1)
    {
        setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }else
        setAlignment(Qt::AlignCenter);


}

void KJLStatic::onUpdateData(int data, SimulateMan *pVar, QObject *who)
{
    if(who == this)
        return;

    if(pVar != m_pSimulate)
    {
        if( data == m_pData->nDynamicCondition )
            show();
        else
            hide();
    }
}

void KJLStatic::onUpdateData(QString data, SimulateMan *pVar, QObject *who)
{
    if(who == this)
        return;
    if(pVar == m_pSimulate)
    {
        setText(data);
    }
}

