#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ResMan/ResManager.h>
#include <QtCore/QVector>
#include <QPushButton>
#include <QKeyEvent>
#include "UI/KJLSubWin.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT


public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
        virtual void paintEvent(QPaintEvent * event);
	void keyPressEvent(QKeyEvent * event);//ʵ�ַ��򰴼��л�����;
	void synchroNizeXfocus(void);//ͬ��x���򽹵�˳��;
	void synchroNizeYfocus(void);//ͬ��y���򽹵�˳��;

private:
	QVector<QWidget *>m_ctrlVec;//�ؼ��б�;
	QVector<QWidget *>m_pageCtrlVec;//ҳ��ؼ��б�;
	QVector<KJLSubWin *>m_subWinVec;//�Ӵ����б�;
	QVector<int>m_xFocus;//x�᷽�򽹵�˳��;
	QVector<int>m_yFocus;//y�᷽�򽹵�˳��;
	int m_nXfocus;//��ǰ����Ľ������;
	int m_nYfocus;//��ǰy�ἤ��Ľ������;
	int m_nWidgetFlag;//���ڱ�־;

signals:
	void subWinChangPage(int nPage);

	public slots:
		void onChangePage(int nPage);
		void onSubWinChangePage(int nSunWin, int nPage);
		void onUpdateDisp();

};

#endif // MAINWINDOW_H
