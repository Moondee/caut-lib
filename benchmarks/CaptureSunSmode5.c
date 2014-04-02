#include "caut.h"
 
#define INT2Status        (volatile unsigned int *)0x1300C004  /* �ж�2���жϼĴ��� */
#define INT2Mask          (volatile unsigned int *)0x1300C000  /* �ж�2���жϼĴ��� */
#define INT2Clear         (volatile unsigned int *)0x1300C008  /* �ж�2���жϼĴ��� */
unsigned int WorkModeFlg;
/* SIO�� */
/* ����������4·������ */
#define START_MW1_DA_CS       ((volatile unsigned int *)(0x10000000))   /* ������1·�����ֵ�ѹ���� ��д */
#define START_MW2_DA_CS       ((volatile unsigned int *)(0x10000004))   /* ������2·�����ֵ�ѹ���� ��д */
#define START_MW3_DA_CS       ((volatile unsigned int *)(0x10000008))   /* ������3·�����ֵ�ѹ���� ��д */
#define START_MW4_DA_CS       ((volatile unsigned int *)(0x1000000C))   /* ������4·�����ֵ�ѹ���� ��д */
/* 8252�ڵ�ַ */
#define LTU_TBR_CS            ( *((volatile int * )0x10000040) )
#define LTU_RBR_CS            ( *((volatile int * )0x10000040) )
#define LTU_UCR_CS            ( *((volatile int * )0x10000044) )
#define LTU_USR_CS            ( *((volatile int * )0x10000044) )
#define LTU_MCR_CS            ( *((volatile int * )0x10000048) )
#define LTU_BRSR_CS           ( *((volatile int * )0x1000004C) )
#define LTU_MSR_CS            ( *((volatile int * )0x1000004C) )

/* ͨ����·ѡ����ѡ��LTUͨ�����������ߵ�D[3:0]��������ѡ��ӳ���ϵΪ0000-1110:LTU1-LTU15,1111:�Բ��� ��д */
#define LTU_SELECT_CS         (*((volatile unsigned int *)(0x10000050)))
#define RD_MW1_COUNT          ((volatile unsigned int *)(0x10000064) )   /* ����1·�����ּ�����     ��� */
#define RD_MW2_COUNT          ((volatile unsigned int *)(0x1000006C) )   /* ����2·�����ּ�����     ��� */
#define RD_MW3_COUNT          ((volatile unsigned int *)(0x10000074) )   /* ����3·�����ּ�����     ��� */
#define RD_MW4_COUNT          ((volatile unsigned int *)(0x1000007C) )   /* ����4·�����ּ�����     ��� */
#define START_GD_COUNT        ((volatile unsigned int *)(0x10000080) )   /* ������������������      ��д */
#define START_FY_COUNT        ((volatile unsigned int *)(0x10000084) )   /* ������������������      ��д */
#define START_PH_COUNT        ((volatile unsigned int *)(0x10000088) )   /* ����ƫ������������      ��д */
#define START_GK_COUNT        ((volatile unsigned int *)(0x1000008C) )   /* ������ط���������      ��д */

/* PIO�� */
#define RD_SLSP_CS1           ((volatile unsigned int *)(0x11000000) )   /* �����Ǽ������ź�     ��� */
#define RD_SLSP_CS2           ((volatile unsigned int *)(0x11000004) )   /* �����Ǽ������ź�     ��� */
#define RD_SLSP_CS3           ((volatile unsigned int *)(0x11000008) )   /* �����Ǽ������ź�     ��� */
#define RD_UPS_STATUS_CS      ((volatile unsigned int *)(0x11000010) )   /* �ƽ�ϵͳ��7λ״̬��     ��� */
#define OPEN_VALVE_CS         ((volatile unsigned int *)(0x11000014) )   /* ���ƽ�ϵͳ3·���������д򿪲��� ��д */
#define CLOSE_VALVE_CS        ((volatile unsigned int *)(0x11000018) )   /* ���ƽ�ϵͳ3·���������йرղ�����д */
#define CONNECT_B_BRANCH_CS   ((volatile unsigned int *)(0x1100001C) )   /* ����B��֧��������ͨ     ��д */
#define BOOT_490N_CS          ((volatile unsigned int *)(0x11000020) )   /* ����490N�������Ĵ�    ��д */
#define SHUTDOWN_490N_CS      ((volatile unsigned int *)(0x11000024) )   /* ����490N�������Ĺر�    ��д */
#define POWER_ON_490N_CS      ((volatile unsigned int *)(0x11000028) )   /* ��UPS��Դ            ��д */
#define POWER_OFF_490N_CS     ((volatile unsigned int *)(0x1100002C) )   /* �ر�UPS��Դ            ��д */
#define CONTROL_10N_CS        ((volatile unsigned int *)(0x11000030) )   /* ����12·10N������������  ��д */
#define READ_MW_DIR_CS        ((volatile unsigned int *)(0x11000040) )   /* ��4·�����ֵ�ת�ٷ���   ���*/
#define READ_EE_FLAG_CS       ((volatile unsigned int *)(0x11000050) )   /* ��Ӧ����־              ��� */
#define READ_SDC_LSTATUS_CS   ((volatile unsigned int *)(0x11000060) )   /* ��SDC��16λ״̬         ��� */
#define READ_SDC_HSTATUS_CS   ((volatile unsigned int *)(0x11000064) )   /* ��SDC��16λ״̬         ��� */
#define CONTROL_SDC_CS        ((volatile unsigned int *)(0x1100006C) )   /* 6·SDC���ؿ���          ��д */
#define RD_DUTY_MACHINE_CS    (*(volatile unsigned int *)(0x11000070) )  /* �������������Ϣ        ��� */


/* 1553b�Ĵ�����ַ���� */
#define INTERRUPT_MASK_REG              (0x0000)
#define CONFIGURATION_1_REG             (0x0001)
#define CONFIGURATION_2_REG             (0x0002)
#define START_RESET_REG                 (0x0003)
#define COMMAND_STACK_POINTER_REG       (0x0003)
#define BC_CONTROLL_WORD_REG            (0x0004)
#define RT_SUBADDR_CONTROL_WORD_REG     (0x0004)
#define TIME_TAG_REG                    (0x0005)
#define INTERRUPT_STATUS_REG            (0x0006)
#define CONFIGURATION_3_REG             (0x0007)
#define CONFIGURATION_4_REG             (0x0008)
#define CONFIGURATION_5_REG             (0x0009)
#define RT_DATA_STACK_ADDR_REG          (0x000A)
#define MONITOR_DATA_STACK_ADDR_REG     (0x000A)
#define BC_FRAME_TIME_REMAINING_REG     (0x000B)
#define BC_MESSAGE_TIME_REMAINING_REG   (0x000C)
#define BC_FRAME_TIME_REG               (0x000D)
#define RT_LAST_COMMAND_REG             (0x000D)
#define MT_TRIGGER_REG                  (0x000D)
#define RT_STATUS_WORD_REG              (0x000E)
#define RT_BIT_WORD_REG                 (0x000F)
#define RT_COMMAND_STACK_POINT_A        (0x0100)
/* 1553b�û������MEM�ռ䶨�� */
#define RT_A_RECEIVE_SUBADDR(i)         ( 0x0140 + (i) )
#define RT_A_TRANSMIT_SUBADDR(i)        ( 0x0160 + (i) )
#define RT_A_BROADCAST_SUBADDR(i)       ( 0x0180 + (i) )
#define RT_A_CONTROL_WORD_SUBADDR(i)    ( 0x01A0 + (i) )

#define AddrLastCmd         (volatile unsigned int *)0x13000000  /* ����ָ���ŵ�ַ */
#define Address_1_1553b     (volatile unsigned int *)0x13005080  /* ���ͽ���OBDH��Ҫ����1�ĵ�ַ */
#define Address_2_1553b     (volatile unsigned int *)0x13005100  /* ���ͽ���OBDH��Ҫ����2�ĵ�ַ */
#define Address_3_1553b     (volatile unsigned int *)0x13005180  /* ���ͽ���OBDH��Ҫ����3�ĵ�ַ */
#define Address_4_1553b     (volatile unsigned int *)0x13005200  /* ���ͽ���OBDH��Ҫ����4�ĵ�ַ */
#define Address_5_1553b     (volatile unsigned int *)0x13005280  /* ���ͽ���OBDH��Ҫ����5�ĵ�ַ */
#define Address_6_1553b     (volatile unsigned int *)0x13005300  /* ���ͽ���OBDH��Ҫ����6�ĵ�ַ */
#define Address_7_1553b     (volatile unsigned int *)0x13005380  /* ���ͽ���OBDH��Ҫ����7�ĵ�ַ */
#define Address_8_1553b     (volatile unsigned int *)0x13005400  /* ���ͽ���OBDH��Ҫ����8�ĵ�ַ */
#define Address_9_1553b     (volatile unsigned int *)0x13005480  /* ���ͽ���OBDH��Ҫ����9�ĵ�ַ */
#define Address_10_1553b    (volatile unsigned int *)0x13005500  /* ���ͽ���GNC��Ҫ����1�ĵ�ַ */
#define Address_11_1553b    (volatile unsigned int *)0x13005580  /* ���ͽ���GNC��Ҫ����2�ĵ�ַ */
#define Address_12_1553b    (volatile unsigned int *)0x13005600  /* ���ͽ���GNC��Ҫ����3�ĵ�ַ */
#define Address_13_1553b    (volatile unsigned int *)0x13005680  /* ���ͽ���GNC��Ҫ����4�ĵ�ַ */
#define Address_TR18_1553b  (volatile unsigned int *)0x13005780  /* ��OBDH���͵�ʱ�����ַ */
#define Address_TR19_1553b  (volatile unsigned int *)0x13005800  /* ������̬���ݵ�ַ */
#define Address_TR20_1553b  (volatile unsigned int *)0x13005880  /* ����GNC����ң����������ַ 296�ֽ� */
#define Address_TR21_1553b  (volatile unsigned int *)0x13005C80  /* ����GNC�ڴ����ݵ�ַ 1088�ֽ� */
#define Address_RE18_1553b  (volatile unsigned int *)0x13006C80  /* ����ʱ�����ַ */
#define Address_RE21_1553b  (volatile unsigned int *)0x13006D80  /* ����ң��ע�����ݵ�ַ */
#define Address_RE26_1553b  (volatile unsigned int *)0x13006F80  /* �����ڴ��ַ������ */
#define Address_RE31_1553b  (volatile unsigned int *)0x13007000  /* �ӵ�ַ31ָ���ŵ�ַ */
#define Address_TR31_1553b  (volatile unsigned int *)0x13007080  /* �ӵ�ַ31ָ���ŵ�ַ */
/*  ʱ���ַ*/
#define Address_TIME_GPT    (volatile unsigned int *)0x01F80088  /* �ڲ���ʱ���ڵ�ַ */

#define FIRSTWORKMODE     (unsigned int *)0x2017000  /* ����ģʽ��3ȡ2֮һ */
#define SECONDWORKMODE    (unsigned int *)0x2019400  /* ����ģʽ��3ȡ2֮�� */
#define THIRDWORKMODE     (unsigned int *)0x201b800  /* ����ģʽ��3ȡ2֮�� */

#define TR32_WORKMODE              Tr32_uint(WorkModeFlg)//(Tr32_uint(FIRSTWORKMODE,SECONDWORKMODE,THIRDWORKMODE))/* ����ģʽ��3ȡ2 */
#define TR32_WORKMODE_VALUE(x)     WorkModeFlg=x//(Tr32_uint_value(FIRSTWORKMODE,SECONDWORKMODE,THIRDWORKMODE,(x)))/* ����ģʽ��д3�� */

/* ���Ǻ���ֵ */
#define COS15           0.9659258263f
#define COS45           0.7071067812f
#define COS46P92        0.6830188573f
#define COS75           0.2588190451f
#define COS79P45        0.1830935078f
#define COS90           0.0f
#define COS100P54       -0.1829219225f
#define COS133P08       -0.6830188573f
#define SIN_epsilon     0.3963196067f         /* ��=23.3483�� */
#define COS_epsilon     0.9181126125f         /* ��=23.3483�� */
#define FloatZero       1e-7f
#define RAD_DEGREE      57.2957795f

#define CONST_2PI       6.2831853f
#define CONST_PI        3.1415927f
#define CONST_HalfPI    1.5707963f

#define CONST_ae        384747981.0f
#define CONST_as        1.49598e11f
#define CONST_DMl      	2.6392045e-6f     /* �׵�ƽ����Ǳ仯��(Ml)'=2.6392045e-6 rad/s */
#define CONST_DMs      	1.99096875e-7f    /* (Ms)'=1.99096875e-7 */
#define CONST_ee       	0.054880f         /* ee = 0.054880 */
#define CONST_eeee      0.0030118144f     /* ee*ee = 0.0030118144f */
#define CONST_es       	0.016705291f      /* es=0.016705291f */
#define CONST_eses     	0.0002790667f     /* es*es=0.016705291f */
#define CONST_Gm        4.902800269e12f   /* ��������������4.902800269e12 ��3/��2 */
#define CONST_ie      	0.08953251f       /* ie=0.08953251 rad */
#define CONST_Rm        1738000.0f        /* ����ο��������뾶��1738000 �� */
#define CONST_ws       -1.3426259f        /* ��s=-1.3426259frad */
#define CONST_we        0.806342f         /* ��e=0.806342rad */
#define DELAYNUM        1500              /* LTUͨѶ��ʱ�ȴ����� */

#define flg_valid       0xeb90146f       /* ��Ч */
#define flg_invalid     0xCCCCCCCC       /* ��Ч */
#define Switch_Cmd_Valid  0x5aeb         /* �л������֣��л� */

#define IDTask64msOr256ms       1        /* ������������ */       
#define IDStarDirection         2        /* ���Ƕ��� */ 
#define IDInertialAdjustAtti    3        /* ���Ե��� */ 
#define IDOrbitDirection        4        /* ��ض��� */ 
#define IDUVAroundMoon          5        /* ���⻷�� */ 
#define IDSTSAroundMoon         6        /* �ǹ⻷�� */       
#define IDGyroAroundMoon        7        /* ���ݻ��� */ 
#define IDSunDirection          8        /* ̫������ */ 
#define IDMWControl             9        /* �����ֿ��� */ 
#define IDWorkModeFlgManage     10       /* ����ģʽ����ת���Ĺ������ */ 
#define IDJetPhase              11       /* ��ƽ����� */       
#define IDPulseJet              12       /* ������� */ 
#define IDCaptureAndPointSun    13       /* ̫�����񼰶��ն��� 4.6 */ 
#define IDModifySTS             14       /* ������������̬���� */ 
#define IDDiagnoseLTU           15       /* ������������ */ 
#define IDNOControl           16         /* �޿�ģʽ */

/* ���ٶȼ� */
typedef struct
{
    float   as[2];              /* ���ٶȼ���� */
    float   as0[2];             /* ���ٶȼ���λƫ�� */
}ACCELERATE;
ACCELERATE  Acce;

/*��̬���ݿ������*/
typedef struct
{
    unsigned int    BZ0;
    unsigned int    BZ1;
    unsigned int    BZ2;
    unsigned int    BZ3;
    unsigned int    BZ4;
    unsigned int    BZ5;
    unsigned int    BZ5a;
    unsigned int    BZ6;
    unsigned int    BZ7;
    unsigned int    BZ8;
    unsigned int    BZ9;
    unsigned int    BZ10;
    unsigned int    BZ11;
    unsigned int    BZ12;
    unsigned int    BZ13;
    unsigned int    BZ14;
    unsigned int    BZ15;
    unsigned int    BZ16;
    unsigned int    BZ17;
    unsigned int    BZ18;
    unsigned int    BZ19;
    unsigned int    BZ20;
    unsigned int    BZ21;
    unsigned int    BZ22;
    unsigned int    BZ23;
    unsigned int    BZ24;
    unsigned int    BZ25;
    unsigned int    BZ26;
	unsigned int    ZT10;
	unsigned int    ZT14;
	unsigned int    BZUV;
    unsigned int    PR1;
    unsigned int    PR2;
    unsigned int    PR3;
    unsigned int    PR4;
    unsigned int    PR5;
    unsigned int    PR6;
    unsigned int    PR7;
    unsigned int    PR8;
    unsigned int    PR9;
    unsigned int    PR10;
    unsigned int    PR11;
    unsigned int    PR12;
    unsigned int    PR13;
    unsigned int    PR14;
    unsigned int    PR15;
    unsigned int    PR16;

    float       q[4];
	float       qg[4];
    float       qTI[4];
    float       qOI[4];
    float       qBT[4];
    float       qBO[4];
    float       qGI[4];
    float       Deltaq[4];
    float       A0[3];
    float       AOI[3][3];
    float       ABO[3][3];
    float       ABI[3][3];
    float       ABT[3][3];
} ATTI;
ATTI    Atti;

/* ��̬���ٶ����ݽṹ */
typedef struct
 {
    float  A[3];             /* ��̬�ǹ�ֵ */
    float  Rate[3];          /* ��̬���ٶȹ�ֵ */
    float  AC[3];            /* ��̬�ǿ����� */
    float  RateC[3];         /* ��̬���ٶȿ����� */

    float  As[3];            /* ����̫������ģʽ�� */
    float  At[3];            /* ��̬�� */
    float  RateC0[3];        /* ��̬���ٶ� */

    float  Az[3];            /* ������� */
	float  Az1[3];           /* ������� */
	float  Az2[3];           /* ������� */
    float  DeltaAz[3];       /* ���������� */
    float  DeltaA[3];        /* ����������̬ƫ�� */
    float  DeltaAsz[3];      /*  */
    float  DeltaAszS[3];     /*  */
    float  Asz[3];           /*  */
}ATTITUDEDATA;


/* �������� */
typedef struct
 {
    float DeltaAlphaF1; /* A�鷫��ת����� */
    float DeltaAlphaF2; /* B�鷫��ת����� */
    float DeltaAlphaF1Star;
    float DeltaAlphaF2Star;
    float WF1;          /* A�鷫����������ָ����ٶ� */
    float WF2;          /* B�鷫����������ָ����ٶ� */
    unsigned int AlphaFT;/* ����ת������ */
    unsigned int WFT;    /* ������ٶ����� */
}BAPTADATA;
BAPTADATA      BAPTAData;

/* ����������� */
typedef struct
{
	unsigned int    channelL;        /* �󷫰�ͨ���� */
	unsigned int    channelR;        /* �ҷ���ͨ���� */
	unsigned int    CmdL[2];		 /* �󷫰����ָ�� */
	unsigned int    CmdR[2];         /* �󷫰����ָ�� */
}BAPTACTRL;
BAPTACTRL	   BAPTACtrl;

/* ��������ǹ�����ݽṹ */
typedef struct
{

	float  f;                /* ���Ǹ���֮������ */
	float  w0;               /* ���ǹ�����ٶȦ�0 */
	float  rho;              /* ������ŽǦ� rad*/
	float  rEM;              /* ���¾� */
	float  rES;              /*  */
	float  r;                /* ���ľ� �� */
	float  u;                /*  */
	float  M;                /*  */
	float  E;                /*  */
	float  dt;               /*  */
	float  LOmegae;          /*  */
	float  we;               /*  */
	float  Me;               /*  */
	float  ue;               /*  */
	float  Ms;               /* ̫���ڹ�������ϵ�ķ��� */
	float  us;               /* ̫���ڹ�������ϵ�ķ��� */
	float  Ei[3];			 /* ����ʸ�������ĵ�������������ϵ�еķ��� */
	float  Eo[3];            /* ���ķ���λʸ��Eox,Eoy,Eoz */
	float  Si[3];            /* ̫��ʸ�������ĵ�������������ϵ�ķ�λ */
	float  So[3];            /* ̫�������ڹ������ϵ�ķ�λSox,Soy,Soz */
}CalOrbitDATA;
CalOrbitDATA   CalOrbit;

/* ̫���������� */
typedef struct
{
	unsigned int Smode;         /*  */
	unsigned int TCount;        /*  */
	unsigned int TSmode;        /*  */
	unsigned int Eclipse;       /*  */
	float		 SqrtSumDW;     /*  */
}CaptureSSDATA;
      /* ̫���������� */

typedef struct
{
    volatile unsigned int Address;     /* �´������׵�ַ */
    volatile unsigned int num;         /* �´������ֽڵĳ��� */
}DOWNLOAD;
DOWNLOAD  DownLoad;                    /* �´����� */

/* �˲�ϵ���� */
typedef struct
{
    float   mKSAq;          /* �˲�ϵ��KSAǰ������������ */
    float   mKSAb;          /* �˲�ϵ��KSA�������������� */
    float   mKSBq;          /* �˲�ϵ��KSBǰ������������ */
    float   mKSBb;          /* �˲�ϵ��KSB�������������� */
    float   mKSCq;          /* �˲�ϵ��KSCǰ������������ */
    float   mKSCb;          /* �˲�ϵ��KSC�������������� */
}FILTER;
FILTER  Filter;

/* �������� */
typedef struct
{
    float   Bae;        /*  */
    float   Bbe;        /* ��ae;��be */
    float   Es[3];      /*  */
    float   Eb[3];      /*  */
    float   Baf;        /*  */
    float   Bbf;        /* ���߽Ƕȿ���ָ���af;��bf */
    float   Gda0_a;     /* ����A����λ����ָ�� */
    float   Gda0_b;     /* ����B����λ����ָ�� */
    unsigned int Bafcmd;
    unsigned int Bbfcmd;
    float   Bm;         /* ע��������ֵ90�� */
    unsigned int ABKeepZeroNum;     /*  */
    float   BaeT;
    float   BbeT;
    unsigned int ZeroFlg;/* ����˫���ѹ���ı�־ */
}GDADATA;
GDADATA        GDAData;

/* �������ݽṹ */
typedef struct
{
    float  DeltaG[8];          /* ������һ���������ڽǶ�����,+2�����ٶȼ� */
    float  b[3];               /* XYZ�����ݳ�ֵƯ�� */
    float  xw[3];              /* �����������������ٶ� */
    float  xwTI[3];            /*  */
    float  xwBT[3];            /*  */
    float  DG[3];
    int    GC[6];              /* ���ݹ�����ϵĻ��� */
    unsigned int WorkStatus[6];/* ���������ݹ���״̬��־ */
    float  NormW;              /* ���ݽ��ٶȵ�ģ */     
}GYRODATA;
GYRODATA       GyroData;

/* ע������ǹ�����ݽṹ */
typedef struct
 {
	unsigned int  t0;        /* ��ʼ����ע��ʱ�� */
	float  a0;          		 /* ע��ʱ��ѡȡ�Ĳο��������֮�볤�� */
	float  a;                /* ע���һ�����������֮�볤�� */
	float  e;                /* ע���һ�����������֮ƫ���� */
	float  i;                /* ע���һ�����������֮��� */
	float  LOmega;           /* ע���һ�����������֮������ྶ */
	float  w;                /* ע���һ�����������֮���ص���� */
	float  M;                /* ע���һ�����������֮��ʼƽ����� */
}InOrbitDATA;
InOrbitDATA    InOrbit;

/* ����ע����� */
typedef struct
{
	float mg;                   /* ���ݹ����б�ֵ���� */
	float mqa;                  /* ϵͳ�����б�ֵ���� */
	float LOmegal0;             /* ��� */
	float Ms0;                  /* ��� */
	float Orbit[74];            /* ��� */
	float WT[3];
	float ul0;
	float Dul0;
	float ie;                   /* �׵���Գ����ƽ����� */
}INPara;


/* �������Ƶ����ݽṹ */
typedef struct
 {
	float           TJ[3];                  /* ������������ */
	float           Thetapst[3];            /* ����������ʱ����̬���� */
	float           Jet_TotalTime_Temp[6];  /* ���������ܼ����� */
	unsigned int    Jet_TotalTime[6];       /* ���������ܼ����� */
	unsigned int    Jet_Num[6];             /* ������������ */
	unsigned int    StFlag[3];              /* ��������״̬ 1 ���磬���������� */
	float           PW[3];                  /* ������������ */
	unsigned int	ALL[3];					/* ���ȫ����־ */
}JPC_DATA;
JPC_DATA       JPCData;

/* K���� */
typedef struct
 {
    float A[3];              /* �����˲�ϵ������������ Phi,Theta,Psi */
    float d[3];              /* �����˲�ϵ������������ dx,dy,dz */
    float RY[5][3];          /* ����-̫������ϵ���������� */
    float P[3][2];           /* ����-̫������ϵ���������� */
}KPara;
KPara          K;


/* ѡͨLTU�ı�־ */
typedef struct
{
	unsigned int GyroAcce1; /* ����Ԫ������ */
	unsigned int GyroAcce2;	/* ����Ԫ������ */
	unsigned int IdleAcce1;	/* �ա����ÿձ�����ԭ��LTUSelect()��ʹ��forѭ����
	                           ��Ҫ�˽ṹ�ڱ���˳����LTUPowerStatusFlg��Ӧλ���Ӧ */
	unsigned int IdleAcce2;	/* �� */
	unsigned int SS1;       /* ̫������ */
	unsigned int SS2;       /* ̫������ */
	unsigned int UV1;       /* ����1 */
	unsigned int UV2;       /* ����2 */
	unsigned int STS1;      /* ����1 */
	unsigned int STS2;      /* ����2 */
	unsigned int STS3;	    /* ����3 */
	unsigned int IdleMW1;	/* �� */
	unsigned int IdleMW2;	/* �� */
	unsigned int IdleMW3;	/* �� */
	unsigned int IdleMW4;	/* �� */
	unsigned int BAPTAL;    /* �󷫰� flg_valid/flg_invalid������/���� */
	unsigned int BAPTAR;    /* �ҷ��� flg_valid/flg_invalid������/���� */
	unsigned int GDA;       /* ����   flg_valid/flg_invalid������/���� */
}LTUSelectFlg;
LTUSelectFlg   LTUSelect;       /* LTUѡͨ�ı�־ */

/* LTU��ͨѶ���� */
typedef struct
 {
	unsigned int SS1[12];        /* ̫������ */
	unsigned int SS2[12];        /* ̫������ */
	unsigned int GyroAcce1[33];  /* ����Ԫ�����ݲɼ����� */
	unsigned int GyroAcce2[33];	 /* ����Ԫ�����ݲɼ����� */
	int 		 GyroAcceTele1[8];   /* ����Ԫ�����ݲɼ����� */
	int 		 GyroAcceTele2[8];	 /* ����Ԫ�����ݲɼ����� */
	unsigned int GyroAcce1Old[18];   /* ����Ԫ�������ϴδ������������ */
	unsigned int GyroAcce2Old[18];	 /* ����Ԫ�������ϴδ������������ */
	unsigned int UV1[8];         /* ����1 */
	unsigned int UV2[8];         /* ����2 */
	unsigned int STS1[30];       /* ����1 */
	unsigned int STS2[30];       /* ����2 */
	unsigned int STS3[30];	     /* ����3 */
	unsigned int BAPTAL1[3];     /* �󷫰�����*/
	unsigned int BAPTAL2[3];     /* �󷫰屸�� */
	unsigned int BAPTAR1[3];     /* �ҷ������� */
	unsigned int BAPTAR2[3];     /* �ҷ��屸�� */
	unsigned int GDA1[5];        /* �������� */
	unsigned int GDA2[5];        /* ���߱��� */
}LTUDATA;
LTUDATA        LTUData;			 /* LTUͨѶ���� */

/* LTU��ͨѶ���������־ */
typedef struct
 {
	unsigned int GyroAcce1; 	/* ����Ԫ������ */
	unsigned int GyroAcce2;		/* ����Ԫ������ */
	unsigned int IdleAcce1;		/* �� */
	unsigned int IdleAcce2;		/* �� */
	unsigned int SS1;       	/* ̫������ */
	unsigned int SS2;       	/* ̫������ */
	unsigned int UV1;       	/* ����1 */
	unsigned int UV2;       	/* ����2 */
	unsigned int STS1;      	/* ����1 */
	unsigned int STS2;      	/* ����2 */
	unsigned int STS3;	    	/* ����3 */
	unsigned int BAPTAL1;   	/* �󷫰����� */
	unsigned int BAPTAL2;   	/* �󷫰屸�� */
	unsigned int BAPTAR1;   	/* �ҷ������� */
	unsigned int BAPTAR2;   	/* �ҷ��屸�� */
	unsigned int GDA1;      	/* �������� */
	unsigned int GDA2;      	/* ���߱��� */

	unsigned int OldGyroAcce1; 	/* ����Ԫ������ */
	unsigned int OldGyroAcce2;	/* ����Ԫ������ */
	unsigned int OldIdleAcce1;	/* �� */
	unsigned int OldIdleAcce2;	/* �� */
	unsigned int OldSS1;       	/* ̫������ */
	unsigned int OldSS2;       	/* ̫������ */
	unsigned int OldUV1;       	/* ����1 */
	unsigned int OldUV2;       	/* ����2 */
	unsigned int OldSTS1;      	/* ����1 */
	unsigned int OldSTS2;      	/* ����2 */
	unsigned int OldSTS3;	    /* ����3 */
	unsigned int OldBAPTAL1;   	/* �󷫰����� */
	unsigned int OldBAPTAL2;   	/* �󷫰屸�� */
	unsigned int OldBAPTAR1;   	/* �ҷ������� */
	unsigned int OldBAPTAR2;   	/* �ҷ��屸�� */
	unsigned int OldGDA1;      	/* �������� */
	unsigned int OldGDA2;      	/* ���߱��� */

	unsigned int ValveGyroAcce1;/* ����Ԫ������ */
	unsigned int ValveGyroAcce2;/* ����Ԫ������ */
	unsigned int ValveIdleAcce1;/* �� */
	unsigned int ValveIdleAcce2;/* �� */
	unsigned int ValveSS1;      /* ̫������ */
	unsigned int ValveSS2;      /* ̫������ */
	unsigned int ValveUV1;      /* ����1 */
	unsigned int ValveUV2;      /* ����2 */
	unsigned int ValveSTS1;     /* ����1 */
	unsigned int ValveSTS2;     /* ����2 */
	unsigned int ValveSTS3;	    /* ����3 */
	unsigned int ValveBAPTAL1;  /* �󷫰����� */
	unsigned int ValveBAPTAL2;  /* �󷫰屸�� */
	unsigned int ValveBAPTAR1;  /* �ҷ������� */
	unsigned int ValveBAPTAR2;  /* �ҷ��屸�� */
	unsigned int ValveGDA1;     /* �������� */
	unsigned int ValveGDA2;     /* ���߱��� */
	
	unsigned int IdleGyroAcce1;	/* ������Ҫ���д�������ۼ�ʱ���������Ĵ���ѻ���Idle */
	unsigned int IdleGyroAcce2;
	unsigned int Idle;
}LTUError;
LTUError       LTUErrorNum;      /* LTUͨѶ������� */

/* LTU���Լ���Ϣ */
typedef struct
 {
	unsigned int    SS1[2];        /* ���յ���̫��1���Լ����� */
	unsigned int    SS2[2];        /* ���յ���̫��2���Լ����� */
	unsigned int    GyroAcce1[3];  /* ���յ��Ĺ��Ե�Ԫ1���Լ����� */
	unsigned int    GyroAcce2[3];  /* ���յ��Ĺ��Ե�Ԫ2���Լ����� */
	unsigned int    UV1[4];        /* ���յ�������1���Լ����� */
	unsigned int    UV2[4];        /* ���յ�������2���Լ����� */
	unsigned int    STS1[9];       /* ���յ�������1���Լ����� */
	unsigned int    STS2[9];       /* ���յ�������2���Լ����� */
	unsigned int    STS3[9];       /* ���յ�������3���Լ����� */
	unsigned int    BAPTAL1[2];    /* ���յ���̫������1���ݵ��Լ����� */
	unsigned int    BAPTAL2[2];    /* ���յ���̫������1���ݵ��Լ����� */
	unsigned int    BAPTAR1[2];    /* ���յ���̫������2���ݵ��Լ����� */
	unsigned int    BAPTAR2[2];    /* ���յ���̫������2���ݵ��Լ����� */
	unsigned int    GDA1[3];       /* ���յ�������1���Լ����� */
	unsigned int    GDA2[3];       /* ���յ�������2���Լ����� */
}LTUSelfCheck;
LTUSelfCheck   LTUCheck;


/* ���������� */
typedef struct
{
    float  H[4];                /* Hx,Hy,Hz,Hs */
    float  V[4];                /* Vx,Vy,Vz,Vs */
    float  Vh[4];               /* Vhx,Vhy,Vhz,Vhs */
    float  Vf[4];               /* Vfx,Vfy,Vfz,Vfs */
    float  Ih[4];               /* Ihx,Ihy,Ihz,Ihs */
    float  DeltaH[4];           /* ��Hx,��Hy,��Hz,��Hs */
    float  I[3];                /* I��,I��,I��*/
    float  IStar[3];            /* I��*,I��*,I��* */
    float  K_IC[3][3];          /* K_ICx,K_ICy,K_ICz */
    float  K_PC[3][3];          /* K_PCx,K_PCy,K_PCz */
    float  K_DC[3][3];          /* K_DCx,K_DCy,K_DCz */
    float  Vc[3];               /* Vcx,Vcy,Vcz*/
    float  Cv;
    float  Kf[4];               /* �����ֵĶ�Ħ������ϵ�� */
    float  Vf0[4];              /* Vf0>=0,��ʾ�����־�Ħ��������Ӧ�Ĳ�����ѹ */
    float  Kfv[4];              /*  */
    float  VcStar[3];
    float  HT[3];
    float  J0[3][3];
    float  CwhXYZS[3][4];
    float  DwhXYZS[4][3];
	float  CwhXYZ[3][4];
    float  DwhXYZ[4][3];
	float  CwhXYS[3][4];
    float  DwhXYS[4][3];
	float  CwhXZS[3][4];
    float  DwhXZS[4][3];
	float  CwhYZS[3][4];
    float  DwhYZS[4][3];
    unsigned int StartInitFlg;  /* ���������뱣�ּ����л����������־ */
    unsigned int PIDInitFlg;    /* ����PID���Ƽ����л����������־ */
/* ������ϵ���� 2 ˳��̶� */
    float  C_UT;            /* ���ֵ�ѹ-����ϵ�� */
    float  Tf;              /* �ֿ��˲�ʱ�䳣�� */
    float  K_PH;            /* ���ֽǶ������ֿ���P���� */
    float  K_IH;            /* ���ֽǶ������ֿ���I���� */
    float  mDeltaH;         /* ��������ж�ط�ֵ���������� */
    float  H0[4];           /* Hx0,Hy0,Hz0,Hs0 */
}MWDATA;
MWDATA         MWData;


/* �������飬������ظ�ʱ���������������̬��������̬ */
typedef struct
{
    unsigned int Tgon;
    unsigned int Thon;
    unsigned int Tgi;           /* ���ģʽ��ʼʱ�� */
    unsigned int TFireon;       /* ��ؿ���ʱ�� */
    float   Tprohoff;           /* ��ؿ��ػ�ʱ����� */
    float   TFireoff;           /* ��ؿ��ػ�ʱ����� */
    float   DeltaVs;            /* ʣ���ٶ����� */
    float   wGK[3];             /* ���ϵ��  */
    float   PhiGK1;             /* ���ϵ�� */
    float   PhiGK;              /* ���ϵ�� */
	int 	DeltaV1;            /* ����ٶ����� */
	int 	DeltaV2;            /* ����ٶ����� */
    unsigned int St_offm;
    unsigned int Gmode;
    unsigned int Tsmode;
    float   Toff;               /*  */
    float   Tc;
}ORBITCOMMAND;
ORBITCOMMAND  OrbitCmd;

/* ��ƽ��ϵ�����ݽṹ */
typedef struct
{
    float   mThetaDL;       /* ��ƽ�����ٷ�ֵ�������� */
    float   mThetaD;        /* ��ƽ��������ֵ�������� */
    float   mThetaV;        /* ��ƽ�沽����ֵ�������� */
    float   mThetaDV;       /* ��ƽ�沽������ֵ�������� */
    float   mKJ2;           /* ��ƽ�����KJ2����ϵ�� */
}PHASE;
PHASE   InPhase;


/* ������Ƶ����ݽṹ */
typedef struct
 {
    float   A11[3];           /*  */
    float   H1[3];            /*  */
    float   A32[3];           /*  */
    float   A33[3];           /*  */
    float   H2[3];            /*  */
    float   H3[3];            /*  */
    float   D2[3];            /*  */
    float   A54[3];           /*  */
    float   A55[3];           /*  */
    float   H4[3];            /*  */
    float   H5[3];            /*  */
    float   D3[3];            /*  */
    float   A76[3];           /*  */
    float   A77[3];           /*  */
    float   H6[3];            /*  */
    float   H7[3];            /*  */
    float   D4[3];            /*  */
    float   Kp[3];            /* ����������Pϵ�� */
    float   Kd[3];            /* ����������Iϵ�� */
    float   Ki[3];            /* ����������Dϵ��*/
    float   HH1[3];           /* α���ʵ��������Ʋ��� */
    float   HH2[3];           /* α���ʵ��������Ʋ��� */
    float   Tm[3];            /* α���ʵ��������Ʋ��� */
    float   X82[2];
    float   X83[2];
    float   X1[3];            /*  */
    float   X2[3];            /*  */
    float   X3[3];            /*  */
    float   X4[3];            /*  */
    float   X5[3];            /*  */
    float   X6[3];            /*  */
    float   X7[3];            /*  */
    float   X8[3];            /*  */
    float   PWI[3];
    float   Y[3];
}PULSEDATA;
PULSEDATA      PulseData;

/* ����������ƽ�����ݽṹ */
typedef struct
 {
	float  Thetapst;           /* ��һ���ڸ������̬�� */
	float  ThetaD;             /* ���� */
	float  ThetaV;             /* ���� */
	float  DThetaL;          /* ���� */
	float  DThetaLL;
	float  AlphaJS;         /* ���� */
	float  DThetaV;          /* ���� */
	float  KJ2;             /*  */
}PHASEPLANE;
PHASEPLANE     JPCPara; 		/* ����������ƽ�����ݽṹ */

typedef union
{
    volatile unsigned int    Word;

    struct
    {
        volatile unsigned High       : 16;
        volatile unsigned GNC        : 5;        /* 0-4 Զ���ն˵�ַ */
        volatile unsigned tr         : 1;        /* 5    ����/����λ */
        volatile unsigned Address    : 5;        /* 6-10 �ӵ�ַ����ʽ */
        volatile unsigned Number     : 5;        /* 11��15 �����ּ�������ʽ���� */
    } Bit;
}RCV_COMMAND;

/* ̫������ */
typedef struct
 {
    float        DSSAngle[2];          /* ����̫���������̬�Ǧ���,���� */
	float        DSSAngleOld[2];       /* ����̫���������̬�Ǧ���,���� */
	float        ASSAngle[5];          /* ģ��̫���������̬�Ǧ�A1,��A21,��A22,��A31,��A32*/
	float        ASSAngleOld[5];       /* ģ��̫���������̬�Ǧ�A1,��A21,��A22,��A31,��A32*/
    float        AlphaF[2];            /*  */
    float        AlphaFS;              /*  */
    float        SbMatrix[3][3];       /* �����ӳ������ */
    float        Sb[3];                /* ̫��������ֵ */
    float        STheta[3];            /*  */
    float        SPsi[3];              /*  */
    unsigned int DSSDataValidFlg[2];   /* ����̫�������Ƿ���Ч */
    unsigned int ASSSightValidFlg[5];  /* ģ��̫���Ƿ��ӳ���ЧSA1,SA21+SA22,SA31+SA32 */
    unsigned int LSSSightValidFlg[6];  /* 0-1̫����ϢL11+L15,L12+L14,L14+L22,L23+L25,L13,L21*/
    unsigned int IsThetea1;            /*  */
    unsigned int IsPsi1;               /*  */
    unsigned int IsThetea2;            /* ��������̫������ӳ��� */
    unsigned int IsPsi2;               /* ƫ������̫������ӳ��� */
    unsigned int Ise;                  /*  */
    unsigned int SSValid;              /* ̫���������жϱ�־ */
	unsigned int Ls;
	unsigned int BAPTAZero[2];         /* ��������λ��־ */
}SSDATA;



/* �������� */
typedef struct
{
    float AB[3][3];
    float BB[3][3];
    float CB[3][3];
    float ZAI[3];
    float ZBI[3];
    float ZCI[3];
    float XAI[3];
    float XBI[3];
    float XCI[3];
    float DAB[3][3];
    float DBB[3][3];
    float DCB[3][3];
    float KSA[6][3];
    float KSB[6][3];
    float KSC[6][3];
    float DeltaZA[3];
    float DeltaZB[3];
    float DeltaZC[3];
    float DeltaZR[3]; 
    float DeltaZpst[3];                
}STSDATA;
STSDATA STS;


typedef union
{
    unsigned int    Word;
    float   Float;
    struct
    {
        unsigned High   : 16;           /* ��16λ */
        unsigned Low    : 16;           /* ��16λ */
    } Half;

    struct
    {
        unsigned High_h :8;             /* ��16λ�еĸ�8λ */
        unsigned High_l :8;             /* ��16λ�еĵ�8λ */
        unsigned Low_h  :8;             /* ��16λ�еĸ�8λ */
        unsigned Low_l  :8;             /* ��16λ�еĵ�8λ */
    } Byte;

    struct
    {
        unsigned BZ1    : 4;  /* ��0��3 */
        unsigned BZ2    : 4;  /* ��4��7 */
        unsigned BZ3    : 4;  /* ��8��11 */
        unsigned BZ4    : 4;  /* ��12��15 */
        unsigned BZ5    : 4;  /* ��0��3 */
        unsigned BZ6    : 4;  /* ��4��7 */
        unsigned BZ7    : 4;  /* ��8��11 */
        unsigned BZ8    : 4;  /* ��12��15 */
    } Bit4;
}USED_WORD;
USED_WORD   GNC_Data[150];    /* GNC������ң�����ݻ����� */
USED_WORD   Task_GNCData[150];/* ��OBDH�յ����������ݿ� */
USED_WORD   Task_Now[255];    /* �յ����������ݿ� */
USED_WORD   Task_GNCOrbitData[150];/* ��OBDH�յ������й�����ݿ� */
USED_WORD   SendAttiData[9];  /* Ҫ���͵���̬���� */

/*ʱ������ݽṹ*/
typedef struct
{
    unsigned int    MS;                 /* ��ʱ�ĺ��� */
    unsigned int    S;                  /* ��ʱ���� */
    unsigned int    GPT_Old;            /* ��GPT������ֵOld */
    volatile unsigned int    GPT_Now;   /* ��GPT������ֵnew */
    unsigned int    T;
    unsigned int    tec1;               /* ����Ӱʱ�� */
    float           Tec2;               /* ��Ӱʱ�� */
    float           Tec3;               /* ��Ӱ���� */
	int			    STS[3];             /* ����ң��ʱ�� */
    unsigned int    STSflg;             /* ����ʱ����Уʱ��־ */
    unsigned int    CorrectSTS;         /* ����Уʱʱ�� */
    unsigned int    deltaMS;            /*  */   
    volatile unsigned int    MSInt;        /* ��ʱ�ĺ��� ,���յ���Уʱ��*/
    volatile unsigned int    SInt;         /* ��ʱ���� ,���յ���Уʱ�� */ 
    volatile unsigned int    GPT_OldInt;   /* ��GPT������ֵOld ,����Уʱ��ʱ��oldֵ */ 
} TIME;
TIME    Time;


/* �ж���ʹ�õı��� */
volatile unsigned int    JetStatus;      /* ��ܵ�ǰ״̬ */
volatile unsigned int    GNCDataflg;     /* �յ�����ע�����ݱ�־ */
volatile unsigned int    TeleMode;       /* ң��ģʽ */
volatile unsigned int    flgSetFire80;   /* 80s����־ */

unsigned int    ASSBadNum2122; 	        /* �������ڼ��� */
unsigned int    ASSBadNum3132; 	        /* �������ڼ��� */
        /* Ѳ��ģʽ��ģ��̫��������� */
unsigned int    AttiBadNum;             /* ��̬��������� */
unsigned int    AttiGoodNum;            /* ��̬�ü����� */
unsigned int    BBranchPowerOnFlg;
unsigned int    BBranchPowerOnNum;      /* ��B��֧���� */
unsigned int    BAPTATimeNum;
unsigned int    BOOT_490Nnum;           /* �رչ�ط������������ */
unsigned int    CloseLV5Num;            /* �ر�LV5���� */
unsigned int    CmdAddrOLD;
unsigned int    Cyc_Flag;               /* �������� */
float           DeltaT;
float           DeltaTOld;
        /* ����̫��������� */
unsigned int    ErrorOBDHNum;           /* 4s��OBDHͨѶ���ϼ��� */
unsigned int    FaultFlg1;              /* �쳣���ݿ�1��ű�־ */
unsigned int    FaultFlg2;              /* �쳣���ݿ�2��ű�־ */
unsigned int    FaultNum1;              /* �쳣���ݿ�1��ż��� */
unsigned int    FaultNum2;              /* �쳣���ݿ�2��ż��� */
unsigned int    FailureFlag;            /* ���жι��ϱ�־ */
unsigned int    flgAllTOEE;             /* ̫������ģʽ�У�֪ͨ���ǽ�Ӧ����־*/	
unsigned int    flgOrbitData;           /* ������ݿ�ע���־ */
unsigned int    flgOpenLV14Num;         /* ��LV1,4���� */
unsigned int    flgCLoseValve;          /* 80��������,����ܱ�־ */
unsigned int    flgOpenLV14;            /* ��������1,4�ı�־ */
unsigned int    flgCloseLV5;            /* ��������5�ı�־ */
unsigned int	flgReceiveTime;         /* ���յ�Уʱ�ı�־ */
unsigned int    flgRequirData;          /* ������Ҫ���ݻָ���־ */
unsigned int    flgSaveData;            /* ������Ҫ���ݱ����־ */
unsigned int    flgProgramm;            /* �յ�ע������Ƿ���ȷ��־ */
unsigned int    GKFlag;
unsigned int 	GNCDataNumber;          /* ��Ч���ݳ��� */
unsigned int 	GNCDataSequenceSave;    /* ע�������ݳ����� */
unsigned int    GDACtrlCmd[5];
unsigned int    GyroZT10;				/* ���ݹ������ݴ���ZT10 */
unsigned int    GyroAcceTNum1;          /* �������ݴ����������� */
unsigned int    GyroAcceTNum2;          /* �������ݴ����������� */
int             GyroAcceTele1[8];
unsigned int    ImpDataRecErrorFlg;     /* ������Ҫ���ݴ����־ */
unsigned int    ImpGNC2[16];            /* GNC��Ҫ����2 */
unsigned int    ImpGNC3[16];            /* GNC��Ҫ����3 */
unsigned int    ImpGNC4[16];            /* GNC��Ҫ����4 */
float	        InparaGyro[6];          /* Gyro�ɼ�������С�뵱�� */
float	        InparaAcceK[2];         /* Acce�ɼ�������С�뵱�� */
unsigned int    JetBadNum[3]; 	        /* ��ͨ�������������� */
unsigned int    JetGoodFlg;
float           Kit[3];
unsigned int    LTUPowerStatusFlg;
unsigned int 	LTUSelfCheckNum;		/* LTU�Լ�˳����� */
unsigned int    MannerData;             /* ��ʽ�����־ */
float           MatrixVG[6][3];
float           mkpLimit;               /* ������Ʊ����������޷�ֵ */       
unsigned int    numEE;                  /* Ӧ���ӵ����>=5��Ч */
unsigned int    numRequirData;          /* ������Ҫ���ݼ��� */
unsigned int    numWM4STS;              /* ���������ɼ�����ģʽ4�еļ��� */
unsigned int    num80s;                 /* 80s������ */
unsigned int    numAttiRate;            /* ������������4�εļ��� */
unsigned int    numDeltaZ;              /* ����2�δ���0.017 */
unsigned int 	numFireOff;             /* ����ļ�ʱʱ�� */
float           numSTSTime;             /* ����30SУʱ���� */
unsigned int 	NumZm00875[3];
unsigned int    numImpGNCData;          /* ��Ҫ���ݶ��ڱ������ 10s */
unsigned int	OldInOrbitPointer;      /* ע�������ݵĴ��ָ�� */
unsigned int	OldProgrammPointer;     /* ע�����Ĵ��ָ�� */
unsigned int 	ProgrammSequenceSave;   /* ע���������� */
float           qBTabs;
unsigned int    RecInSlowRotateCommNum; /* ע�������ָ����� 0.256s */
unsigned int 	Rec8252CommErrorFlg; 	/* LTUͨѶ8252�� */
unsigned int 	RecOverTimeErrorFlg; 	/* LTUͨѶ��ʱ�� */
unsigned int    Switch_Cmd;             /* ��ϵͳ����ӿ�,�л������� */
unsigned int    SLSPFlg;                /* �Ǽ�����ı�־ */
unsigned int    SDCOutputFlg;           /* ע���SDC���Ƿ���Ӧ�ı�־ */
unsigned int    SDCOutput;              /* ע���SDC������� */
unsigned int    SHUT_490Nnum;           /* �ع�ط������������ */
unsigned int    SendTeleMode;           /* ��ʽ�� */
unsigned int 	SDCOutputZZFlg;		    /* �����жϳ�����ӵ粿���ı�־ */
unsigned int 	Shut490PowerNum;	    /* �Ͽ�490Nĸ�ߵ�Դ�ļ��� */

unsigned int    SmodeEQU5Lnum;
unsigned int    SmodeEQU5Rnum;
unsigned int    SLSPSignalNum;          /* �����������ڵõ��ķ������ */
unsigned int    St_of[3];
unsigned int    STSDataValidFlg[3];	    /* ����������Ч��־ */
unsigned int    STSqFlag;	            /* ������������ģʽ���Ƿ����¼���q��ֵ�ı�־ */
unsigned int    *Task_TmpData;		    /* ��OBDH�յ����������ݿ� */
unsigned int    *Task_ProgramData;	    /* �������еĳ���ע���� */
unsigned int    *Task_FaultData1;	    /* �쳣���ݼ�¼��1 */
unsigned int    *Task_FaultData2;	    /* �쳣���ݼ�¼��2 */
unsigned int    *Task_FaultEndAddr1;	/* �쳣���ݼ�¼��1������ַ */
unsigned int    *Task_FaultEndAddr2;	/* �쳣���ݼ�¼��2������ַ */
float	        TeleAttiData[17][3];    /* ң����̬���ݼ��һ�����õĻ����� */
unsigned int 	UV1DataValidFlg;	    /* ����1������Ч��־ */
unsigned int 	UV2DataValidFlg;	    /* ����2������Ч��־ */
unsigned int    UnloadMode;             /* ����ж�ر�־ */
unsigned int    ULS;                    /* ����ж�ر�־ */
unsigned int    WM4Cycle;               /* ���64ms�������ڼ�256ms  */
unsigned int    WMInertiaAttiCycleNum;  /* ���Ե���ģʽ������ 600S */
unsigned int    WMCycleNum;
unsigned int    WMInitFlg;
extern unsigned int OSTM_Frame0;
extern unsigned int OSTM_Frame1;
extern unsigned int OSTM_Frame2;
extern unsigned int Task1024Flag;
unsigned int    ForInProgram1;
unsigned int    ForInProgram2;
unsigned int    ForInProgram3;
unsigned int    ForInProgram4;
unsigned int    ForInProgram5;
float		    ForInProgram6;
float		    ForInProgram7;
float		    ForInProgram8;
float		    ForInProgram9;
float		    ForInProgram10;
unsigned int    ForInProgramArray[30];
float		    ForInProgramArrayF[30];

	
void    CaptureSunSmode5(CaptureSSDATA*  CaptureSun,
		ATTITUDEDATA*   AttiData,
		INPara*  InPara,
		unsigned int    SmodeNE5num,
		SSDATA*         SSData,
		unsigned int    DSSErrorNum[2],
		unsigned int    ASSErrorNum[5])
{
	unsigned int i, tmpFlg=flg_invalid;
	float tmpDSSAngle[2], tmpASSAngle[5];

	if(CaptureSun==0) return;
	if(AttiData==0) return;
	if(InPara==0) return;
	if(SSData ==0) return ;

	if(CaptureSun->Smode == 5)
	{
		//if((fabs_s(AttiData->A[1]) > 0.0875f) || (fabs_s(AttiData->A[2]) > 0.0875f))
		if(( (AttiData->A[1]) > 0.0875f) || ( (AttiData->A[2]) > 0.0875f))
		{
			tmpFlg = flg_valid;
		}
		if((CaptureSun->TSmode <= 2) || ((CaptureSun->TSmode < 500) && (tmpFlg == flg_valid)))
		{
			for(i = 0; i < 3; i++)
			{
				AttiData->RateC0[i] = 0.0f;
			}
		}
		else
		{
			for(i = 0; i < 3; i++)
			{
				AttiData->RateC0[i] = InPara->WT[i];
			}
		}

		if(SmodeNE5num > 0)
		{
			SmodeNE5num--;
		}
		SmodeEQU5Lnum++;
		SmodeEQU5Rnum++;
		/* ��̫�������������ֵ������Ұ���� */
		if(CaptureSun->TSmode == 0)
		{
			SSData->DSSAngleOld[0] = SSData->DSSAngle[0];
			SSData->DSSAngleOld[1] = SSData->DSSAngle[1];
			for(i = 0; i < 5; i++)
			{
				SSData->ASSAngleOld[i] = SSData->ASSAngle[i];
			}
		}			
			
		for(i = 0; i < 2; i++)
		{
			//tmpDSSAngle[i] = fabs_s(SSData->DSSAngle[i] - SSData->DSSAngleOld[i]);
			tmpDSSAngle[i] =  (SSData->DSSAngle[i] - SSData->DSSAngleOld[i]);
			if(tmpDSSAngle[i] > 0.01745329f) /* 1.0f/RAD_DEGREE */
			{
				DSSErrorNum[i]++;
				if(DSSErrorNum[i] < 5)
				{
					SSData->DSSAngle[i] = SSData->DSSAngleOld[i];
				}
			}
			else
			{
				DSSErrorNum[i] = 0;
			}
			SSData->DSSAngleOld[i] = SSData->DSSAngle[i];
		}

		for(i = 0; i < 5; i++)
		{
			//tmpASSAngle[i] = fabs_s(SSData->ASSAngle[i] - SSData->ASSAngleOld[i]);
			tmpASSAngle[i] =  (SSData->ASSAngle[i] - SSData->ASSAngleOld[i]);
			if(tmpASSAngle[i] > 0.05235988f) /* 3.0f/RAD_DEGREE */
			{
				ASSErrorNum[i]++;
				if(ASSErrorNum[i] < 5)
				{
					SSData->ASSAngle[i] = SSData->ASSAngleOld[i];
				}
			}
			else
			{
				ASSErrorNum[i]=0;
			}

			SSData->ASSAngleOld[i] = SSData->ASSAngle[i];
		}
	}
	else
	{
		SmodeEQU5Lnum = 0;
		SmodeEQU5Rnum = 0;
	}
	return;
}

void testme(){

	CaptureSSDATA*  CaptureSun;
	ATTITUDEDATA*   AttiData;
	INPara*  InPara;
	unsigned int    SmodeNE5num;
	SSDATA*         SSData;
	unsigned int    DSSErrorNum[2];
	unsigned int    ASSErrorNum[5];

	CAUT_INPUT(CaptureSun);
	CAUT_INPUT(AttiData);
	CAUT_INPUT(InPara);
	CAUT_INPUT(SmodeNE5num);
	CAUT_INPUT(SSData);
	CAUT_INPUT(DSSErrorNum);
	CAUT_INPUT(ASSErrorNum);
	
	CaptureSunSmode5(CaptureSun, AttiData, InPara, SmodeNE5num, SSData, DSSErrorNum, ASSErrorNum);
}
