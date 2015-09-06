#include "KJLComboBox.h"
#include "ResMan/ResManager.h"
#include "ResMan/ArchiveManager.h"
#include "KJLBaseCtrl.h"
#include <QDebug>


KJLComboBox::KJLComboBox(QWidget *parent/*=0*/, char *data/*=0*/):
    QComboBox(parent)
    ,m_pOpt(NULL)
{
    if( data )//���˽��������Ч;
    {
        m_pData = (LPBaseCtrl)data;
        m_pPriData = (LPEditPri)( (char *)m_pData + sizeof(BaseCtrl) );

        setGeometry(m_pData->rect);

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

        //��ȡѡ���ַ���;
        m_pOpt = (int *)(m_pPriData + 1);
        int nMax = *m_pOpt;
        for(int i = 0; i < nMax; i++)
        {
            int off = m_pOpt[i+1];
            QString *pStr = g_pResManModule->getString(off);
            addItem(*pStr);
        }

        if(m_pData->bVar)//�Ƿ���ʾ����;
        {
            m_pSimulate = g_pArchiveModule->simulateMap.value(m_pData->nTextID, NULL);//��ȡ��Ӧ�ı���;
            if(m_pSimulate)
            {
                connect(m_pSimulate, SIGNAL(updateData(int,SimulateMan*,QObject*)), this, SLOT(onUpdateData(int,SimulateMan*,QObject*)));
                m_pSimulate->trigle();
            }
        }
        connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(int)));

    }

	setAttribute( Qt::WA_DeleteOnClose, true);
    setAttribute(Qt::WA_TranslucentBackground);
}


KJLComboBox::~KJLComboBox()
{

}

void KJLComboBox::onCurrentIndexChanged(int index)
{
    if(!m_pSimulate)
        return;
    if(m_pPriData->bAutoSave)//�Զ�����;
    {
        m_pSimulate->write(index, this);
       // qDebug()<<"combo autosave";
    }

    //�ı����;
    if(m_pPriData->bIndexChangeAct)
    {
        if(m_pPriData->m_indexChangeAct.nOption > RUNSCRIPT)
            return;
        KJLBaseCtrl *pKJLBaseCtrl = KJLBaseCtrl::getInstance();
        (pKJLBaseCtrl->*(pKJLBaseCtrl->m_pFundoAct[m_pPriData->m_indexChangeAct.nOption]))(m_pPriData->m_indexChangeAct.nVar, m_pPriData->m_indexChangeAct.nVal);
    }

}


void KJLComboBox::onUpdateData(int data, SimulateMan *pVar, QObject *who)
{
    if(who == this)
        return;

    if(pVar == m_pSimulate)
    {
        int *p = m_pOpt;
        int nMax = *p;
        if(nMax == 0)
            return;
        int nOff = (data) % nMax;
        setCurrentIndex(nOff);
    }
    else//m_pData->nDynamicID��̬��ʾID;
    {
        //if( data%m_pData->nDynamicCondition == 0 )
        if( data == m_pData->nDynamicCondition )
            show();
        else
            hide();
    }

}


