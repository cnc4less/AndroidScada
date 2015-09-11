#include "MainWindow.h"
#include <QApplication>
#include <QtScript/QScriptable>
#include <QtScript/QScriptEngine>
#include <QMessageBox>
#include <QTextCodec>
#include <QDebug>
#include <QDesktopWidget>
#include "ResMan/ResManager.h"
#include "ResMan/ArchiveManager.h"
#include "ArchivePage.h"
#include <QTimer>



ResManager *g_pResManModule;            //��Դ����ģ��;
ArchiveManager *g_pArchiveModule;       //��������ģ��;
QScriptEngine *pGlobalScriptEngine;     //ȫ�ֽű�����;
QMainWindow *gMainWindow = 0;           //ȫ�������ھ��;

void setupGlobalScriptEngine();         //����ȫ�ֽű�����,��Ӹ����Զ���Ľű�����;
void globalScriptEngineTest();          //���Խű�ģ���Ƿ�������;





int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));//���ñ��ر���;
    ResManager resManModule;             //��Դ����ģ��{�ṩͼƬ���ַ�����������Ϣ�����ԡ�����};
    ArchiveManager archiveModule;        //��������ģ��;{������������������ַ����}
    setupGlobalScriptEngine();           //�����ű�����ģ��{�����˸��ֹ����Խű�����};
    MainWindow w;//�������ڹ���;

    Q_UNUSED(resManModule);
    Q_UNUSED(archiveModule);
    //��������;
#ifdef WINLINUX
    QFont font;
    font.setPointSize(16);
    font.setFamily(("wenquanyi"));
    a.setFont(font);
#endif
#ifdef MYANDROID
    w.setWindowFlags(Qt::FramelessWindowHint);//ȥ�����ڱ߿�;
    QFont f = a.font();
    f.setPointSize(20);
    a.setFont(f);
    w.showFullScreen();
#else
    w.show();
#endif

	a.exec();
	delete pGlobalScriptEngine;
}










/*******************************�ű�����********************************/
//�ű�������Ӧ��CPP����:
//��Ӧ�Ľű�����ΪreadIntVar();
QScriptValue readIntVar(QScriptContext *context, QScriptEngine *engine)
{
	QString var = context->argument(0).toString();
	var.remove(0,1);//ȥ��$����;
	int id = var.toInt();//����ID;
    SimulateMan *pSimulate = g_pArchiveModule->simulateMap.value(id, NULL);//��ȡ��Ӧ�ı���;
	if(pSimulate == NULL)
		return engine->nullValue();
	else
		return pSimulate->readInt();
	//    return context->argument(0).toString();
}


//��Ӧ�Ľű�����ΪreadIntVar();
QScriptValue writeVar(QScriptContext *context, QScriptEngine *engine)
{
	QString var = context->argument(0).toString();
	QString val = context->argument(1).toString();
	var.remove(0,1);//ȥ��$����;
	int id = var.toInt();//����ID;
    SimulateMan *pSimulate = g_pArchiveModule->simulateMap.value(id, NULL);//��ȡ��Ӧ�ı���;
	if(pSimulate != NULL)
	{
		pSimulate->write(val);
	}
	return engine->nullValue();
}

//��Ӧ�Ľű�����Ϊioctl();
QScriptValue ioctlFunc(QScriptContext *context, QScriptEngine *engine)
{
	QString type = context->argument(0).toString();
	int cmd = context->argument(1).toNumber();
	int arg = context->argument(1).toNumber();
	qDebug()<<"fuck ioctrl";
	return engine->nullValue();
}

//��Ӧ�Ľű�����ΪchangeLanguage();
QScriptValue changeLanguage(QScriptContext *context, QScriptEngine *engine)
{
	int which = context->argument(0).toInt32();
    g_pResManModule->changeLanguage(which);
	return engine->nullValue();
}

//��Ӧ�Ľű�����ΪchangePwd();
QScriptValue changePwd(QScriptContext *context, QScriptEngine *engine)
{
	int who = context->argument(0).toInt32();
	int oldPwd = context->argument(1).toInt32();
	int newPwd = context->argument(2).toInt32();
    g_pArchiveModule->changePwd(who, oldPwd, newPwd);
	return engine->nullValue();
}

//��Ӧ�Ľű�����ΪbackupData();
QScriptValue backupData(QScriptContext *context, QScriptEngine *engine)
{
	int which = context->argument(0).toInt32();
	if(which == 0)
	{
        ArchivePage::copyMoldData(g_pArchiveModule->getMoldName(), QString("backupMoldData") , QString(".bin"));
		qDebug()<<"backup machine data";
		//������u��!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	else if(which == 1)
	{
        ArchivePage::copyMoldData(g_pArchiveModule->getPanelName(), QString("backupPanelData") , QString(".param"));
		qDebug()<<"backup sys data";
	}
	else
	{
		engine->evaluate("backupData(0);backupData(1);");
		qDebug()<<"backup all";
	}


	return engine->nullValue();
}

//��Ӧ�Ľű�����ΪrestoreData();
QScriptValue restoreData(QScriptContext *context, QScriptEngine *engine)
{
	int which = context->argument(0).toInt32();
	if(which == 0)
	{
        QString strMold = g_pArchiveModule->getMoldName();
		QString strTemp = strMold;
		strTemp.prepend(MOLDDIR);
		strTemp.append(".bin");
		//��backupMoldData.bin��U�̿�����moldĿ¼;

		//��backupMoldData.bin����Ϊ��ǰģ��.bin;
		QFile::remove(strTemp);
		QFile::rename(MOLDDIR+QString("backupMoldData.bin"), strTemp);
		//���¼���ģ������;
        g_pArchiveModule->changeMold(strMold, true);
		qDebug()<<"restore machine data";
	}
	else if(which == 1)
	{
        QString strTemp = g_pArchiveModule->getPanelName();
		strTemp.prepend(MOLDDIR);
		strTemp.append(".param");
		//��backupMoldData.bin��U�̿�����moldĿ¼;

		//��backupMoldData.bin����Ϊ��ǰģ��.bin;
		QFile::remove(strTemp);
		QFile::rename(MOLDDIR+QString("backupPanelData.param"), strTemp);
        g_pArchiveModule->loadPanel(g_pArchiveModule->getPanelName());
		qDebug()<<"restore sys data "<<strTemp;

	}
	else
	{
		engine->evaluate("restoreData(0);restoreData(1);");
		qDebug()<<"restore all";
	}


	return engine->nullValue();
}



//��Ӧ�Ľű�����ΪShowMessage();
void ShowMessage(QString strText)
{
	QMessageBox::information(NULL, ("��ʾ"), strText, ("ȷ��(&O)"));
}
QScriptValue ShowMessageFunc(QScriptContext *context, QScriptEngine *engine)
{
	QString strMsg = context->argument(0).toString();
	ShowMessage(strMsg);
	return engine->nullValue();
}

//���U��;
QScriptValue probeUsb(QScriptContext *context, QScriptEngine *engine)
{
#ifdef WINLINUX
	QFile uFile("/udisk");
	if(uFile.exists())
		pGlobalScriptEngine->evaluate("writeVar(\"$322\",\"1\")");
#endif
	return engine->nullValue();
}



//Ϊ������ӽӿں���;
void setupGlobalScriptEngine()
{
    pGlobalScriptEngine = new QScriptEngine();

	QScriptValue fun = pGlobalScriptEngine->newFunction(readIntVar);
	pGlobalScriptEngine->globalObject().setProperty("readIntVar", fun);

	fun = pGlobalScriptEngine->newFunction(writeVar);
	pGlobalScriptEngine->globalObject().setProperty("writeVar", fun);

	fun = pGlobalScriptEngine->newFunction(ioctlFunc);
	pGlobalScriptEngine->globalObject().setProperty("ioctl", fun);

	fun = pGlobalScriptEngine->newFunction(changeLanguage);
	pGlobalScriptEngine->globalObject().setProperty("changeLanguage", fun);

	fun = pGlobalScriptEngine->newFunction(changePwd);
	pGlobalScriptEngine->globalObject().setProperty("changePwd", fun);

	fun = pGlobalScriptEngine->newFunction(backupData);
	pGlobalScriptEngine->globalObject().setProperty("backupData", fun);

	fun = pGlobalScriptEngine->newFunction(restoreData);
	pGlobalScriptEngine->globalObject().setProperty("restoreData", fun);

	fun = pGlobalScriptEngine->newFunction(ShowMessageFunc);
	pGlobalScriptEngine->globalObject().setProperty("ShowMessage", fun);

	fun = pGlobalScriptEngine->newFunction(probeUsb);
	pGlobalScriptEngine->globalObject().setProperty("probeUsb", fun);
}

//���Խű�����;
void globalScriptEngineTest()
{
	qDebug()<<"script engine test";
	pGlobalScriptEngine->evaluate("x=readIntVar('$27');print(x);");
}
