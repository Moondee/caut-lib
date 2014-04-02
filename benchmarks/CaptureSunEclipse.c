#include "caut.h"


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
ATTITUDEDATA   AttiData;

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
GYRODATA*       GyroData;

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



void    CaptureSunEclipse(TIME* Time,ATTI* Atti,SSDATA* SSData,CaptureSSDATA* CaptureSun,unsigned int SmodeNE5num,
	GYRODATA* GyroData,INPara* InPara)
{
        
	unsigned int i;
	float tmpSqrtSumDW=0, tmpSub, tmpT;

	if( Time==0 )
		return;
	if( Atti==0 )
		return;
	if( SSData==0)
		return;
	if(CaptureSun ==0 )
		return;
	if(GyroData ==0)
		return;
	if(InPara ==0 )
		return;
	
	
	tmpT = ((float)(Time->T-Time->tec1)) / 8.0f;
	int c;
	float result;

	c = (int)(tmpT/Time->Tec3);
	
	if(tmpT < 0)
	{
	   result = result + Time->Tec3;
	}
	else 
	result = tmpT - c * Time->Tec3;
   	 
  
	
	if(((Atti->BZ12 == 0)||(Atti->BZ12 == 1)||(Atti->BZ12 == 2)||(Atti->BZ12 == 4)||(Atti->BZ12 == 5))
     &&(SSData->Ls != 0))
	{
		CaptureSun->Eclipse = 0;
		SmodeNE5num ++;/* �������ۼ�30���Ӳ�ΪѲ����ģʽ�Ĺ��ϵļ�����������ģʽ=5ʱ����0 */
	}
	
	//else if(Time.Tec2 < fmod_s(tmpT, Time.Tec3))
	else if(Time->Tec2 < result)
	{
		CaptureSun->Eclipse = 0;
		SmodeNE5num ++;/* �������ۼ�30���Ӳ�ΪѲ����ģʽ�Ĺ��ϵļ�����������ģʽ=5ʱ����0 */
	}
	else
	{
		CaptureSun->Eclipse = 1;
		CaptureSun->Smode = 6;
	}

	for(i = 0; i < 3; i++)
	{
		tmpSub = GyroData->xw[i] -InPara->WT[i];
		tmpSqrtSumDW += tmpSub * tmpSub;
	}
	//CaptureSun.SqrtSumDW = sqrt_s(tmpSqrtSumDW);
        CaptureSun->SqrtSumDW =  tmpSqrtSumDW;
	return;
}
void testme(){

	TIME*    Time;
	ATTI*    Atti;
	SSDATA*         SSData;
	CaptureSSDATA*  CaptureSun;
	unsigned int    SmodeNE5num;
	GYRODATA*       GyroData;
	INPara*  InPara;
	
	CAUT_INPUT( Time);
	CAUT_INPUT(Atti);
	CAUT_INPUT(SSData);
	CAUT_INPUT(CaptureSun);
	CAUT_INPUT(SmodeNE5num);
	CAUT_INPUT(GyroData);
	CAUT_INPUT(InPara);


	CaptureSunEclipse(Time,Atti,SSData,CaptureSun,SmodeNE5num,
	GyroData,InPara);
}
