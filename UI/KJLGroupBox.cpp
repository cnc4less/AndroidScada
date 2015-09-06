#include "KJLGroupBox.h"
#include "ResMan/ResManager.h"
#include "ResMan/ArchiveManager.h"

KJLGroupBox::KJLGroupBox(QWidget *parent/*=0*/, char *data/*=0*/)
    :QGroupBox(parent)
    ,m_pSimulate(NULL)
{
    if( data )//���˽��������Ч;
    {
        m_pData = (LPBaseCtrl)data;
        setGeometry(m_pData->rect);
        setTitle(QString("GroupBox"));
        //����;
        if(m_pData->bBrush)
        {
            setAutoFillBackground(true);
            QPalette palette;
            QColor color(m_pData->logbrush.lbColor);
            palette.setColor(QPalette::Background, color);
            setPalette(palette);
        }
        else
            setAttribute(Qt::WA_TranslucentBackground);

        //����;
        if(!m_pData->bVar)//�̶��ı�;
        {
            QString *pStr = g_pResManModule->getString(m_pData->nTextID);
            if(pStr)
            {
                QStringList strList = pStr->split("_");
                setTitle(strList.at(0));
            }else
                setTitle("");
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
}


KJLGroupBox::~KJLGroupBox()
{

}

void KJLGroupBox::onUpdateData(int data, SimulateMan *pVar, QObject *who)
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

