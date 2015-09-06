#ifndef BASECTRL
#define BASECTRL
#include <QtCore/QRect>
#include <QRgb>
#include <QtCore/QStringList>

//#define PARMSIZE            4352//ĥ�Ĳ�������������С��;
//#define MOLDSIZE            4096//ģ���ļ���С;
//#define PANELSIZE           255//��������С;

#define PARMSIZE            12288//ĥ�Ĳ�������������С��;
#define MOLDSIZE            10240//ģ���ļ���С;
#define PANELSIZE           2048//��������С;

#define D_COIL_OFFSET       0//D����Ԫ����ַƫ��;
#define M_COIL_OFFSET       4096//Mλ��Ԫ����ַƫ��;
#define X_COIL_OFFSET       6144//Xλ��Ԫ����ַƫ��;
#define Y_COIL_OFFSET       8192//Yλ��Ԫ����ַƫ��;



#define WINQT
#define WINLINUX
//#define MYANDROID
#ifdef MYANDROID
#define HEXFILE				"/data/data/org.qtproject.scada/files/fuck.hex"
#define OPTIONGFILE         "/data/data/org.qtproject.scada/files/Option.ini"
#define WARNINIFILE			"/data/data/org.qtproject.scada/files/warning.ini"
#define SCRIPTDIR           "/data/data/org.qtproject.scada/files/" //�ű��ļ�Ŀ¼;
#define MOLDDIR             "/data/data/org.qtproject.scada/files/" //ģ�Ų����ļ�Ŀ¼;
#define LAGNUAGEFILE        "/data/data/org.qtproject.scada/files/cn.qm"
//#elif WINLINUX
//#define HEXFILE				"./fuck.hex"
//#define OPTIONGFILE         "./Option.ini"
//#define WARNINIFILE			"./res/warning.ini"
//#define SCRIPTDIR           "./script/" //�ű��ļ�Ŀ¼;
//#define MOLDDIR             "./mold/" //ģ�Ų����ļ�Ŀ¼;
#else
#define HEXFILE				"E:\\WORKSPACE\\vc++\\KJL\\Drawer\\MyScada\\Debug\\project\\OutPut\\fuck.hex"
#define OPTIONGFILE         "E:\\WORKSPACE\\vc++\\KJL\\Drawer\\MyScada\\Debug\\project\\OutPut\\Option.ini"
#define WARNINIFILE			".\\res\\warning.ini"
#define SCRIPTDIR           ".\\script\\" //�ű��ļ�Ŀ¼;
#define MOLDDIR             ".\\mold\\" //ģ�Ų����ļ�Ŀ¼;
#define LAGNUAGEFILE        "cn.qm"
#endif

//�ؼ�����;
enum KJLCtrlType
{
  KJLBtnType,//��ť;
  KJLEditBoxType,//�༭��;
  KJLComboBoxType,//��Ͽ�;
  KJLLineType,//����;
  KJLGroupBoxType,//�����;
  KJLStaticType,//��̬;
  KJLStatusType,//״̬�ؼ�;
  KJLProgressType,//�������ؼ�;
  KJLSubWinType,//�Ӵ��ڿؼ�
};

//��������;
enum ActType{SINGLESET=0,SET,LINKPAGE,RUNTASK,LINKSUBWIN, RUNSCRIPT};

//״̬�ؼ�����;
enum StatType{ TextStat=0, ImgStat, DateStat};

//ϵͳ״̬;
enum SysStatus{PAGECHANGE, SYSPERMISSION, RUNTIME, MOLDNAME};


typedef struct tagLOGPEN { /* lgpn */
uint lopnStyle;
QPoint lopnWidth;
QRgb lopnColor;
} LOGPEN;

typedef struct tagLOGBRUSH
{
uint lbStyle;
QRgb lbColor;
long lbHatch;
} LOGBRUSH;

//�ؼ�����ͷ;
typedef struct _tagCtrlHead
{
    int ctrlType;//�ؼ�����;
    int ctrlSize;//�ؼ���С;
}CtrlHead, *LPCtrlHead;



//�ؼ���ͬ������;
typedef struct _tagBaseCtrl
{
    QRect rect;
    bool bPen;
    bool bBrush;
    LOGPEN logpen;
    LOGBRUSH logbrush;
    QRgb forwardColor;
    bool bVar;
    int nTextID;
    bool bDynamic;
    int nDynamicID;
    int nDynamicCondition;
    int nPermission;//�ؼ���Ȩ��0:���Ա, 1:����Ա, 2:ϵͳ����Ա;
}BaseCtrl, *LPBaseCtrl;


//����;
typedef struct _tagActDeal{
    int nOption;
    int nVar;
    int nVal;
}ActDeal, *LPActDeal;


//�ؼ�˽������;
//��ť˽������;
typedef struct _tagBtnPri
{
    // ��������ͼƬID;
    int m_nNormalPicID;
    // ��ý���ı���ͼƬID;
    int m_nHoverPicID;
    // �����µı���ͼƬID;
    int m_nPressPicID;
    // ����ʱ���Ƿ�ִ�ж���;
    bool m_bPressAct;
    // �Ƿ�ִ�е�����;
    bool m_bReleaseAct;
    // �Ƿ�ִ�н��㶯��;
    bool m_bHoverAct;
    // ��ť��̬:0��ͨ����1���߰�ť;
    int m_nBtnType;

    //���¶���;
    ActDeal m_pressAct;
    //������;
    ActDeal m_releaseAct;
    //���㶯��;
    ActDeal m_focusAct;

}BtnPri, *LPBtnPri;


//�༭��ؼ�˽������;
typedef struct _tagEditPri
{
    // �Ƿ���ʾ����;
    bool bText;
    //�Ƿ��Զ�����;
    bool bAutoSave;
    //�Ƿ���ʾ����;
    bool bDispPwd;
    // �Ƿ�ִ��ȷ�϶���;
    bool bIndexChangeAct;
    // �Ƿ�ִ�н��㶯��;
    bool bFocusAct;
    // �����ַ���ID;
    int nTitleTextID;
    // ���ⷽ��;
    int nTitleOrientation;
    //ȷ�϶���;
    ActDeal m_indexChangeAct;
    //���㶯��;
    ActDeal m_focusAct;
}EditPri, *LPEditPri;

//״̬�ؼ�˽������;
typedef struct _tagStatusPri
{
    //����:0-2�����֣�ͼƬ������;
    int m_nType;
    // ˮƽ���뷽ʽ:0-2���ҡ���;
    int m_nHorizantalAlign;
    //״̬��Ŀ��;
    int m_nStatCnt;
}StatusPri, *LPStatusPri;

//��̬�ؼ�˽������;
typedef struct _tagStaticPri
{
    // ˮƽ���뷽ʽ:0-2���ҡ���;
    int m_nHorizantalAlign;
}StaticPri, *LPStaticPri;

//�������ؼ�˽������;
typedef struct _tagProgressPri
{
    bool bSysOpt;
    int nSysOpt;
    int nOreintation;
    int colorNormal;
    int colorUpAlarm;
    int colorDwnAlarm;
}ProgressPri, *LPProgressPri;

//�Ӵ��ڿؼ�˽������;
typedef struct _tagSubWinPri
{
    int id;
    int nSubPageCnt;//�ӻ�������;
}SubWinPri, *LPSubWinPri;


/* @�̵���¼������,�ýṹ���Ǵ��͸�����������;
 * nStep:�����;
 * nType:�̵���¼����{����˵�Ƕ������ͱȽϺ����};
 * pData:�����̵���¼������;
*/
typedef struct _tagTutorRecord
{
    int nStep;
    int nType;
    void *pData;
}TutorRecord, *LPTutorRecord;

/* @�̵���¼����ʾ����,�ýṹ����Ҫ���ڽ�������ʾ�̵���¼�����ݵ��̵�������;
 * @strList:��ʾ���б���ϵ�һ���̵���¼�ַ���;
 * @record:�̵���¼����;
 *
*/
typedef struct _tagTutorRecordStr
{
    QStringList strList;
    TutorRecord record;

}TutorRecordStr, *LPTutorRecordStr;

//��¼�����ͺ�������;
#define AXIS_ACT_TUTOR_RECORD_TYPE          0//�ᶯ��;
#define LAYER_ACT_TUTOR_RECORD_TYPE         1//�ѵ�;
#define ZTOOL_ACT_TUTOR_RECORD_TYPE         2//�ξ�;
#define SIGNAL_ACT_TUTOR_RECORD_TYPE        3//�ܻ��ź�;
#define EXTRA_DEV_TUTOR_RECORD_TYPE         4//�����豸;
#define PRESERVE_TUTOR_RECORD_TYPE          5//Ԥ��;
#define CHECK_TUTOR_RECORD_TYPE             6//���;
#define WAIT_TUTOR_RECORD_TYPE              7//�ȴ�;
#define OTHER_TUTOR_RECORD_TYPE             8//����;
#define MOLD_END_TUTOR_RECORD_TYPE			9//ģ�����;




#define SYS_ADDR_PAGE 0x03






#endif // BASECTRL

