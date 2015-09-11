#include <QPainter>
#include <QLabel>
#include "MainWindow.h"
#include "ResMan/ResManager.h"
#include "UI/KJLButton.h"
#include "UI/KJLEditBox.h"
#include "UI/KJLComboBox.h"
#include "UI/KJLGroupBox.h"
#include "UI/KJLStatic.h"
#include "UI/KJLStatus.h"
#include "UI/KJLProgress.h"
#include "ArchivePage.h"
#include "WarningPage.h"
#include "TutorPage.h"

#include <QGraphicsView>

#include <QDebug>

#define POSY 60


extern  ResManager *g_pResManModule;//��Դ����ģ��;


MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
	m_nXfocus(0),
	m_nYfocus(0),
	m_nWidgetFlag(0)
{
    gMainWindow = this;

    //������Ч;
    QPushButton *btnAnimation =  new QPushButton(this);
    btnAnimation->setGeometry(550,650,100,100);
    btnAnimation->setStyleSheet("background-color: rgba(85, 170, 255, 35);");
    btnAnimation->show();
	//0:���ô��ڴ�С;
	//1:��ȡ��ǰ��ҳ��ָ��;
	//2:��ȡ��ǰ�Ŀؼ������б�;
	//3:ʶ�����еĿؼ����ͺ�����;
	//[0]
    resize(g_pResManModule->m_pProjectParm->m_nWidth, g_pResManModule->m_pProjectParm->m_nHeight);

	//[1]
    LPPageHead pPageHead = g_pResManModule->m_pageStruct.pageVector.at(0);//��ȡ��ǰ��ҳ��ָ��;
	int id = pPageHead->nTitleID;
    QString *pStrTitle = g_pResManModule->getString(id);//����;
	if(pStrTitle)
		setWindowTitle(*pStrTitle);

	//[2]
	int *pTemp = (int *)((char *)pPageHead + sizeof(PageHead));
	int *pTempNum = pTemp + 1;//��󽹵���;
	int maxFocus = *pTempNum;
	for(int i = 0 ; i < maxFocus; i++)
	{
		pTempNum++;
		m_xFocus.append(*(pTempNum));
		//qDebug()<<"x:"<<*pTempNum;
	}
	pTemp = (int *)((char *)pTemp + *pTemp);
	pTempNum = pTemp + 1;
	maxFocus = *pTempNum;
	for(int i = 0 ; i < maxFocus; i++)
	{
		pTempNum++;
		m_yFocus.append(*(pTempNum));
		//qDebug()<<"y:"<<*pTempNum;
	}

	//[3]
	LPCtrlHead pCtrlHead = (LPCtrlHead)((char *)pTemp + *pTemp);
    g_pArchiveModule->updateSysPage(0);
	for(int i = 0; i < pPageHead->nCtrlNum; i++)
	{
		char *pData = ((char *)pCtrlHead + sizeof(CtrlHead));
		switch (pCtrlHead->ctrlType)
		{
		case KJLBtnType:
			{
				KJLButton *pControl = new KJLButton(this,pData);
				m_ctrlVec.append(pControl);//����ؼ��б�;
				break;
			}
		case KJLEditBoxType:
			{
				KJLEditBox *pControl = new KJLEditBox(this,pData);
				m_ctrlVec.append(pControl);//����ؼ��б�;
				break;
			}
		case KJLComboBoxType:
			{
				KJLComboBox *pControl = new KJLComboBox(this,pData);
				m_ctrlVec.append(pControl);//����ؼ��б�;
				break;
			}
		case KJLGroupBoxType:
			{
				KJLGroupBox *pControl = new KJLGroupBox(this,pData);
				m_ctrlVec.append(pControl);//����ؼ��б�;
				break;
			}
		case KJLStaticType:
			{
                KJLStatic *pControl = new KJLStatic(this,pData);
//                QLabel *pControl = new QLabel(this);
//                pControl->setText("fuck");
				m_ctrlVec.append(pControl);//����ؼ��б�;
				break;
			}
		case KJLStatusType:
			{
				KJLStatus *pControl = new KJLStatus(this,pData);
				m_ctrlVec.append(pControl);//����ؼ��б�;
				break;
			}
		case KJLProgressType:
			{
				KJLProgress *pControl = new KJLProgress(this,pData);
				m_ctrlVec.append(pControl);//����ؼ��б�;
				break;
			}
		case KJLSubWinType:
			{
				KJLSubWin *pControl = new KJLSubWin(this,pData);
				m_ctrlVec.append(pControl);//����ؼ��б�;
				break;
			}
		default:
			break;
		}
		pCtrlHead = (LPCtrlHead)((char *)pCtrlHead + pCtrlHead->ctrlSize );
	}

	KJLBaseCtrl *pBase = KJLBaseCtrl::getInstance();
	connect(pBase, SIGNAL(changePage(int)), this, SLOT(onChangePage(int)) );
	connect(pBase, SIGNAL(subWinChangePage(int,int)), this, SLOT(onSubWinChangePage(int,int)) );
    connect(g_pResManModule, SIGNAL(updateDisp()), this, SLOT(onUpdateDisp()) );


    //ƽ��ѡ��Ч��;
    smoothXSelection = new QPropertyAnimation(btnAnimation, "geometry");
    if(m_animationButton.size()>0)
        startSmoothXSelection(m_animationButton.at(0)->geometry());


    //��תЧ��;


}

MainWindow::~MainWindow()
{
    qDebug()<<"~MainWindow()";
}

void MainWindow::startSmoothXSelection(const QRect &end)
{
    smoothXSelection->setEndValue(end.adjusted(-2,-2,2,2));
    smoothXSelection->start();
}

//!�����ػ�
/*!
 * ���ݱ���ģʽ
 * 0: ��ɫ����
 * 1: ���䱳��
 * 2: ͼƬ����
 */
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int nBkMode = g_pResManModule->m_pPanelParm->BkMode;
    if(nBkMode == 0)//��ɫ����;
    {
        painter.fillRect(0,0,width(), height() ,QBrush(QColor(g_pResManModule->m_pPanelParm->bkColor)));
    }
    else if(nBkMode == 1)//���䱳��;
    {

    }
    else//ͼƬ����;
    {
        QPixmap *pPixmap = g_pResManModule->getPanelBkPixmap();//��ȡ��屳��ͼƬ;
        if(pPixmap)
            painter.drawPixmap(0,0,width(),height(),*pPixmap );
    }


}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
	int nFocus = 0;
	if(event->key() == Qt::Key_W)
	{
		m_nYfocus>0 ? m_nYfocus-- : m_nYfocus = m_yFocus.size()-1;
		nFocus = m_yFocus.at(m_nYfocus);
		synchroNizeXfocus();
		//qDebug()<<"fuck up";
	}
	else if(event->key() == Qt::Key_S)
	{
		m_nYfocus = (++m_nYfocus) % m_yFocus.size();
		nFocus = m_yFocus.at(m_nYfocus);
		synchroNizeXfocus();
		//qDebug()<<"fuck down";
	}
	else if(event->key() == Qt::Key_A)
	{
		m_nXfocus>0 ? m_nXfocus-- : m_nXfocus = m_xFocus.size()-1;
		nFocus = m_xFocus.at(m_nXfocus);
		synchroNizeYfocus();
		//qDebug()<<"fuck left";
	}
	else if(event->key() == Qt::Key_D)
	{
		m_nXfocus = (++m_nXfocus) % m_xFocus.size();
		nFocus = m_xFocus.at(m_nXfocus);
		synchroNizeYfocus();
		//qDebug()<<"fuck right";
	}

	m_ctrlVec.at(nFocus)->setFocus();

}

//ͬ��x���򽹵�˳��;
void MainWindow::synchroNizeXfocus()
{
	int i = 0;
	for(QVector<int>::ConstIterator it = m_xFocus.begin(); it != m_xFocus.end(); it++)
	{
		if( *it == m_yFocus.at(m_nYfocus))
		{
			m_nXfocus = i;
			return;
		}
		i++;
	}
	m_nXfocus = 0;
}

//ͬ��y���򽹵�˳��;
void MainWindow::synchroNizeYfocus()
{
	int i = 0;
	for(QVector<int>::ConstIterator it = m_yFocus.begin(); it != m_yFocus.end(); it++)
	{
		if( *it == m_xFocus.at(m_nXfocus) )
		{
			m_nYfocus = i;
			return;
		}
		i++;
	}
	m_nYfocus = 0;
}

//�л�ҳ��;
void MainWindow::onChangePage(int nPage)
{
	//[0]��յ�ǰҳ��;
	m_subWinVec.clear();//�Ӵ����б����;
	for(QVector<QWidget *>::const_iterator it = m_pageCtrlVec.begin(); it != m_pageCtrlVec.end(); it++)
	{
		if(m_nWidgetFlag)
			(*it)->close();
		else
		{
			(*it)->close();//delete (*it);
		}

		m_nWidgetFlag = 0;
	}
	m_pageCtrlVec.clear();

	/****************ϵͳҳ��**********************/
	if(nPage>100)
	{
        const double dXfactor = g_pResManModule->getdXfactor();
        const double dYfactor = g_pResManModule->getdYfactor();
		int nYPos = POSY*dYfactor;
		qDebug()<<"sys page:"<<nPage;
        g_pArchiveModule->updateSysPage(nPage);
		m_nWidgetFlag = 1;
		if(nPage == 101)//��������;
		{
			ArchivePage *pPage = new ArchivePage(this);
			pPage->setAttribute( Qt::WA_DeleteOnClose, true);
			pPage->move(0,nYPos);
			pPage->resize(pPage->size().width()*dXfactor, pPage->size().height()*dYfactor);
			pPage->show();
			m_pageCtrlVec.append(pPage);
		}
		else if(nPage == 102)//����ҳ��;
		{
			WarningPage *pPage = new WarningPage(this);
			pPage->setAttribute( Qt::WA_DeleteOnClose, true);
			pPage->move(0,nYPos);
			pPage->resize(pPage->size().width()*dXfactor, pPage->size().height()*dYfactor);
			pPage->show();
			m_pageCtrlVec.append(pPage);
		}
		else if(nPage == 103 )//�̵�ҳ��;
		{
			TutorPage *pPage = new TutorPage(this);
			pPage->setAttribute( Qt::WA_DeleteOnClose, true);
			pPage->move(0,nYPos);
			pPage->resize(pPage->size().width()*dXfactor, pPage->size().height()*dYfactor);
			pPage->show();
			m_pageCtrlVec.append(pPage);
		}
		return;
	}
	/*********************************************/


	/****************��ͨ�û�ҳ��**********************/
	//[1]��ȡ��ǰҳ��ָ��;
    LPPageHead pPageHead = g_pResManModule->m_pageStruct.pageVector.at(nPage);//��ȡ��ǰ��ҳ��ָ��;
	int id = pPageHead->nTitleID;
    QString *pStrTitle = g_pResManModule->getString(id);//����;
	if(pStrTitle)
		setWindowTitle(*pStrTitle);
    g_pArchiveModule->updateSysPage(nPage);


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
				m_pageCtrlVec.append(pControl);//����ؼ��б�;
				break;
			}
		case KJLEditBoxType:
			{
				KJLEditBox *pControl = new KJLEditBox(this,pData);
				m_pageCtrlVec.append(pControl);//����ؼ��б�;
				break;
			}
		case KJLComboBoxType:
			{
				KJLComboBox *pControl = new KJLComboBox(this,pData);
				m_pageCtrlVec.append(pControl);//����ؼ��б�;
				break;
			}
		case KJLGroupBoxType:
			{
				KJLGroupBox *pControl = new KJLGroupBox(this,pData);
				m_pageCtrlVec.append(pControl);//����ؼ��б�;
				break;
			}
		case KJLStaticType:
			{
				KJLStatic *pControl = new KJLStatic(this,pData);
				m_pageCtrlVec.append(pControl);//����ؼ��б�;
				break;
			}
		case KJLStatusType:
			{
				KJLStatus *pControl = new KJLStatus(this,pData);
				m_pageCtrlVec.append(pControl);//����ؼ��б�;
				break;
			}
		case KJLProgressType:
			{
				KJLProgress *pControl = new KJLProgress(this,pData);
				m_pageCtrlVec.append(pControl);//����ؼ��б�;
				break;
			}
		case KJLSubWinType:
			{
				KJLSubWin *pControl = new KJLSubWin(this,pData);
				m_pageCtrlVec.append(pControl);//����ؼ��б�;
				m_subWinVec.append(pControl);
				break;
			}
		default:
			break;
		}
		pCtrlHead = (LPCtrlHead)((char *)pCtrlHead + pCtrlHead->ctrlSize );
	}

    g_pArchiveModule->m_pCommunication->printMonitor();
    g_pArchiveModule->m_pCommunication->updateMonitorToHost();



    //��Ч��ת;

}

void MainWindow::onSubWinChangePage(int nSunWin, int nPage)
{
	qDebug()<<"MainWindow::onSubWinChangePage"<<nSunWin<<":"<<nPage<<"subWin cnt:"<<m_subWinVec.size();
	if(nSunWin >= m_subWinVec.size())
		return;

	m_subWinVec.at(nSunWin)->onChangePage(nPage);

    g_pArchiveModule->m_pCommunication->printMonitor();
    g_pArchiveModule->m_pCommunication->updateMonitorToHost();
}

void MainWindow::onUpdateDisp()
{
    int nPage = g_pArchiveModule->getSysPage();
	onChangePage(nPage);
	update();
}



