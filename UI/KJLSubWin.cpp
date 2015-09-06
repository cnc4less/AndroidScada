#include "KJLSubWin.h"
#include <QDebug>
#include "UI/KJLButton.h"
#include "UI/KJLEditBox.h"
#include "UI/KJLComboBox.h"
#include "UI/KJLGroupBox.h"
#include "UI/KJLStatic.h"
#include "UI/KJLStatus.h"
#include "UI/KJLProgress.h"


KJLSubWin::KJLSubWin(QWidget *parent/* = 0*/, char *data/*=0*/)
    : QWidget(parent)
    , m_pSimulate(NULL)
    , m_pSubPage(NULL)
    , m_nCurSubPage(0)
{
    if( data )//���˽��������Ч;
    {
        //[����λ��]
        m_pData = (LPBaseCtrl)data;
        m_pPriData = (LPSubWinPri)( (char *)m_pData + sizeof(BaseCtrl) );//˽������;
        setGeometry(m_pData->rect);

        if(m_pPriData->nSubPageCnt > 0)
        {
            m_pSubPage = (int *)(m_pPriData + 1);
//            for(int i= 0; i < m_pPriData->nSubPageCnt; i++)
                //qDebug()<<m_pSubPage[i];
            onChangePage(2);//��ҳ;

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

        setAttribute( Qt::WA_DeleteOnClose, true);
        setAttribute(Qt::WA_TranslucentBackground);
    }
}

KJLSubWin::~KJLSubWin()
{
    //clearCtrlVec();
    qDebug()<<"~KJLSubWin()";
}

void KJLSubWin::clearCtrlVec()
{
    for(QVector<QWidget *>::const_iterator it = m_ctrlVec.begin(); it != m_ctrlVec.end(); it++)
    {
        //delete *it;
		(*it)->close();
    }
    m_ctrlVec.clear();

}

void KJLSubWin::closeEvent(QCloseEvent *event)
{
    clearCtrlVec();
}


void KJLSubWin::onChangePage(int nPage)
{
    qDebug()<<"fuckchange"<<nPage;
    //��������Ч��;
    if(!m_pSubPage)//����Ƿ�����Ч���ӻ����б�;
        return;
    if(m_pPriData->nSubPageCnt == 0)
        return;
    int nCurPage = g_pArchiveModule->getSysPage();

    //[0]��յ�ǰҳ��;
    clearCtrlVec();

    //[1]��ȡ��ǰҳ��ָ��;
    if(nPage == 0)//ǰһҳ;
        m_nCurSubPage>0 ? m_nCurSubPage-- : m_nCurSubPage = m_pPriData->nSubPageCnt-1;
    else if(nPage == 1)
        m_nCurSubPage = ++m_nCurSubPage%m_pPriData->nSubPageCnt;
    else
        m_nCurSubPage = nPage-2;
    int nOff = m_pSubPage[m_nCurSubPage];
    //if(nOff >= resManModule.m_pageStruct.pSubPageVector[nCurPage].size())
	if(nOff >= g_pResManModule->m_pageStruct.pSubPageVector.at(nCurPage).size())
        return;
    //LPPageHead pPageHead = resManModule.m_pageStruct.pSubPageVector[nCurPage].at(nOff);//��ȡ��ǰ���ӻ���ָ��;
	LPPageHead pPageHead = g_pResManModule->m_pageStruct.pSubPageVector.at(nCurPage).at(nOff);//��ȡ��ǰ���ӻ���ָ��;

    //[3]������������;
    int *pTemp = (int *)((char *)pPageHead + sizeof(PageHead));
    int *pTempNum = pTemp + 1;//��󽹵���;
//    int maxFocus = *pTempNum;
//    for(int i = 0 ; i < maxFocus; i++)
//    {
//        pTempNum++;
//        m_xFocus.append(*(pTempNum));
//        //qDebug()<<"x:"<<*pTempNum;
//    }
    pTemp = (int *)((char *)pTemp + *pTemp);
    pTempNum = pTemp + 1;
//    maxFocus = *pTempNum;
//    for(int i = 0 ; i < maxFocus; i++)
//    {
//        pTempNum++;
//        m_yFocus.append(*(pTempNum));
//        //qDebug()<<"y:"<<*pTempNum;
//    }

    //[4]���ɿؼ�;
    LPCtrlHead pCtrlHead = (LPCtrlHead)((char *)pTemp + *pTemp);
    for(int i = 0; i < pPageHead->nCtrlNum; i++)
    {
        char *pData = ((char *)pCtrlHead + sizeof(CtrlHead));
        switch (pCtrlHead->ctrlType)
        {
            case KJLBtnType:
            {
                KJLButton *pControl = new KJLButton(this,pData);
                m_ctrlVec.append(pControl);//����ؼ��б�;
                //connect(pControl, SIGNAL(changePage(int)), this, SLOT(onChangePage(int)));
                //pControl->show();
                break;
            }
            case KJLEditBoxType:
            {
                KJLEditBox *pControl = new KJLEditBox(this,pData);
                //connect(pControl, SIGNAL(changePage(int)), this, SLOT(onChangePage(int)));
                m_ctrlVec.append(pControl);//����ؼ��б�;
                //pControl->show();
                break;
            }
            case KJLComboBoxType:
            {
                KJLComboBox *pControl = new KJLComboBox(this,pData);
                //connect(pControl, SIGNAL(changePage(int)), this, SLOT(onChangePage(int)));
                m_ctrlVec.append(pControl);//����ؼ��б�;
                //pControl->show();
                break;
            }
            case KJLGroupBoxType:
            {
                KJLGroupBox *pControl = new KJLGroupBox(this,pData);
                //connect(pControl, SIGNAL(changePage(int)), this, SLOT(onChangePage(int)));
                m_ctrlVec.append(pControl);//����ؼ��б�;
                //pControl->show();
                break;
            }
            case KJLStaticType:
            {
                KJLStatic *pControl = new KJLStatic(this,pData);
                //connect(pControl, SIGNAL(changePage(int)), this, SLOT(onChangePage(int)));
                m_ctrlVec.append(pControl);//����ؼ��б�;
                //pControl->show();
                break;
            }
            case KJLStatusType:
            {
                KJLStatus *pControl = new KJLStatus(this,pData);
                //connect(pControl, SIGNAL(changePage(int)), this, SLOT(onChangePage(int)));
                m_ctrlVec.append(pControl);//����ؼ��б�;
                //pControl->show();
                break;
            }
            case KJLProgressType:
            {
                KJLProgress *pControl = new KJLProgress(this,pData);
                //connect(pControl, SIGNAL(changePage(int)), this, SLOT(onChangePage(int)));
                m_ctrlVec.append(pControl);//����ؼ��б�;
                //pControl->show();
                break;
            }
            case KJLSubWinType:
            {
                KJLSubWin *pControl = new KJLSubWin(this,pData);
                //connect(pControl, SIGNAL(changePage(int)), this, SLOT(onChangePage(int)));
                m_ctrlVec.append(pControl);//����ؼ��б�;
                //pControl->show();
                break;
            }
            default:
                break;
        }
       pCtrlHead = (LPCtrlHead)((char *)pCtrlHead + pCtrlHead->ctrlSize );
    }

    qDebug()<<"fuckchange done"<<nPage;
}

void KJLSubWin::onUpdateData(int data, SimulateMan *pVar, QObject *who)
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
