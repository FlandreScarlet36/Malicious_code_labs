#ifndef _VM_UNPACK_H_
#define _VM_UNPACK_H_

//脱壳成功后的回调处理函数指针
typedef int (*pResultCallBack)(char *pFileName, char **pbuf, int *pnlen);

//脱壳失败原因
#define LOAD_ERROR	-1	//load失败
#define UNPACK_ERROR	-2	//执行过程中出错


//程序虚拟执行中，需要分配的内存信息
typedef struct tagPorcNeedMemInfo
{
	int		nHeadSize;			//堆大小，如果是0则从PE头信息中获取
	int		nStackSize;			//栈大小，如果是0则从PE头信息中获取
	int		nSystemDllSize;		//load dll用缓冲区大小
	int		nLoadSystemDll;		//是否load dll,anti007使用
	int		nAnalyseKernel32;	//仅仅加载kernel32.dll
}ProcNeedMemInfo, *PProcNeedMemInfo;


//脱壳函数，传入信息结构体
typedef struct tagUnpackInfo
{
	unsigned int		nExecuteStep;	//设置虚拟机执行步数
	char *				pInFileName;	//待脱程序全路径
	char *				pInBuf;			//待脱程序所在缓冲区
	int					nInBufLen;		//待脱程序长度
	PProcNeedMemInfo	pMemInfo;		//脱壳过程要分配内存大小
	char *				pOutBuf;		//脱壳后程序所在缓冲区
	int					nOutBufLen;		//脱壳后程序长度
	char *				pOutFileName;	//脱壳后回写文件全路径
	pResultCallBack		pResultFun;		//脱壳后回调处理函数
	int					nOEPUnpack;		//是否采用oep识别方式脱壳
}UnpackInfo, *PUnpackInfo;


//vmunpack.dll导出的函数原型
extern "C"
{
//初始化虚拟机CPU指令系统,寻址系统函数,在启用虚拟机脱壳前调用一次
typedef void (*pinit_vm)();
#define INIT_VM "init_vm"


//脱壳函数原型
typedef int (*pUnpacker)(PUnpackInfo pInfo);

//最大脱壳函数ID + 1
#define MAX_FUN_ID	72


//脱upx壳函数
typedef int (*pkill_upx)(PUnpackInfo pInfo);
#define UNPACK_UPX	"kill_upx"
#define UPX_INDEX	1


//脱aspack壳函数
typedef int (*pkill_aspack)(PUnpackInfo pInfo);
#define UNPACK_ASPACK	"kill_aspack"
#define ASPACK_INDEX	2


//脱PEcompac v0.90 v0.92 v0.93 v0.94 v0.97b壳函数
typedef int (*pkill_PEcompact090)(PUnpackInfo pInfo);
#define UNPACK_PECOMPACT1	"kill_PEcompact090"
#define PECOMPACT1_INDEX	3

//脱PEcompac v2.x壳函数
typedef int (*pkill_PEcompact_2x)(PUnpackInfo pInfo);
#define UNPACK_PECOMPACT2	"kill_PEcompact_2x"
#define PECOMPACT2_INDEX	4



//脱fsg v1.0 v1.1 v1.2 v1.3 v1.31 v1.33壳函数
typedef int (*pkill_fsg133)(PUnpackInfo pInfo);
#define UNPACK_FSG1	"kill_fsg133"
#define FSG1_INDEX	5

//脱fsg v2.0 函数
typedef int (*pkill_fsg20)(PUnpackInfo pInfo);
#define UNPACK_FSG2	"kill_fsg20"
#define FSG2_INDEX	6


//脱VGCrypt 0.75壳函数
typedef int (*pkill_vgcrypt075)(PUnpackInfo pInfo);
#define UNPACK_VGCRYPT	"kill_vgcrypt075"
#define VGCRYPT_INDEX	7


//脱Nspack壳函数
typedef int (*pkill_nspack)(PUnpackInfo pInfo);
#define UNPACK_NSPACK	"kill_nspack"
#define NSPACK_INDEX	8


//脱npack壳函数
typedef int (*pkill_npack)(PUnpackInfo pInfo);
#define UNPACK_NPACK	"kill_npack"
#define NPACK_INDEX	9


//脱expressor v1.0 v1.1 v1.2 v1.3 v1.4 v1.501函数
typedef int (*pkill_expressor)(PUnpackInfo pInfo);
#define UNPACK_EXPRESSOR	"kill_expressor"
#define EXPRESSOR_INDEX	10


//脱dxpack0.86壳函数
typedef int (*pkill_dxpack086)(PUnpackInfo pInfo);
#define UNPACK_DXPACK1	"kill_dxpack086"
#define DXPACK1_INDEX	11


//脱dxpack 1.0壳函数
typedef int (*pkill_dxpack10)(PUnpackInfo pInfo);
#define UNPACK_DXPACK2	"kill_dxpack10"
#define DXPACK2_INDEX	12



//脱!Epack1.0壳函数
typedef int (*pkill_epack10)(PUnpackInfo pInfo);
#define UNPACK_EPACK1	"kill_epack10"
#define EPACK1_INDEX	13

//脱!Epack1.4壳函数
typedef int (*pkill_epack14)(PUnpackInfo pInfo);
#define UNPACK_EPACK2	"kill_epack14"
#define EPACK2_INDEX	14


//脱bjfnt壳函数
typedef int (*pkill_bjfnt)(PUnpackInfo pInfo);
#define UNPACK_BJFNT	"kill_bjfnt"
#define BJFNT_INDEX	15


//脱mew v1.1壳函数
typedef int (*pkill_mew5)(PUnpackInfo pInfo);
#define UNPACK_MEW1	"kill_mew5"
#define MEW1_INDEX	16

//脱mew v1.0 v1.1壳函数
typedef int (*pkill_mew11)(PUnpackInfo pInfo);
#define UNPACK_MEW2	"kill_mew11"
#define MEW2_INDEX	17


//脱packMan v1.0壳函数
typedef int (*pkill_packMan10)(PUnpackInfo pInfo);
#define UNPACK_PACKMAN	"kill_packMan10"
#define PACKMAN_INDEX	18


//脱PEDiminisher0.1壳函数
typedef int (*pkill_PEDiminisher)(PUnpackInfo pInfo);
#define UNPACK_PEDIMINISHER	"kill_PEDiminisher"
#define PEDIMINISHER_INDEX	19


//脱pex壳函数
typedef int (*pkill_pex)(PUnpackInfo pInfo);
#define UNPACK_PEX	"kill_pex"
#define PEX_INDEX	20


//脱petite v1.2 v1.3 v1.4壳函数
typedef int (*pkill_petite1x)(PUnpackInfo pInfo);
#define UNPACK_PETITE1	"kill_petite1x"
#define PETITE1_INDEX	21

//脱petite v2.2 v2.3壳函数
typedef int (*pkill_petite2x)(PUnpackInfo pInfo);
#define UNPACK_PETITE2	"kill_petite2x"
#define PETITE2_INDEX	22


//脱winkript壳函数
typedef int (*pkill_winkript)(PUnpackInfo pInfo);
#define UNPACK_WINKRIPT	"kill_winkript"
#define WINKRIPT_INDEX	23


//脱pklite32壳函数
typedef int (*pkill_pklite32)(PUnpackInfo pInfo);
#define UNPACK_PKLITE32	"kill_pklite32"
#define PKLITE32_INDEX	24


//脱pepack v0.99 v1.0壳函数
typedef int (*pkill_pepack)(PUnpackInfo pInfo);
#define UNPACK_PEPACK	"kill_pepack"
#define PEPACK_INDEX	25


//脱pcshrinker0.71壳函数
typedef int (*pkill_pcshrinker)(PUnpackInfo pInfo);
#define UNPACK_PCSHRINKER	"kill_pcshrinker"
#define PCSHRINKER_INDEX	26


//脱wwpack32 1.0--1.2壳函数
typedef int (*pkill_wwpack32)(PUnpackInfo pInfo);
#define UNPACK_WWPACK32	"kill_wwpack32"
#define WWPACK32_INDEX	27


//脱upack 0.10--0.32壳函数
typedef int (*pkill_upack32)(PUnpackInfo pInfo);
#define UNPACK_UPACK1	"kill_upack32"
#define UPACK1_INDEX	28

//脱upack 0.33--0.399壳函数
typedef int (*pkill_upack36)(PUnpackInfo pInfo);
#define UNPACK_UPACK2	"kill_upack36"
#define UPACK2_INDEX	29


//脱rlpack v1.11 v1.12 v1.13 v1.14壳函数
typedef int (*pkill_rlpack111)(PUnpackInfo pInfo);
#define UNPACK_RLPACK1	"kill_rlpack111"
#define RLPACK1_INDEX	30

//脱rlpack v1.18 v1.15 v1.16 v1.17壳函数
typedef int (*pkill_rlpack118)(PUnpackInfo pInfo);
#define UNPACK_RLPACK2	"kill_rlpack118"
#define RLPACK2_INDEX	31


//脱exe32pack v1.42壳函数
typedef int (*pkill_exe32pack)(PUnpackInfo pInfo);
#define UNPACK_EXE32PACK	"kill_exe32pack"
#define EXE32PACK_INDEX	32


//脱kbys v0.22 壳函数
typedef int (*pkill_kbys22)(PUnpackInfo pInfo);
#define UNPACK_KBYS1	"kill_kbys22"
#define KBYS1_INDEX	33

//脱kbys v0.28, 涛涛压缩器壳函数
typedef int (*pkill_kbys28)(PUnpackInfo pInfo);
#define UNPACK_KBYS2	"kill_kbys28"
#define KBYS2_INDEX	34

 
//脱morphine v1.3壳函数
typedef int (*pkill_morphine13)(PUnpackInfo pInfo);
#define UNPACK_MORPHINE1	"kill_morphine13"
#define MORPHINE1_INDEX	35

//脱morphine v1.6壳函数
typedef int (*pkill_morphine16)(PUnpackInfo pInfo);
#define UNPACK_MORPHINE2	"kill_morphine16"
#define MORPHINE2_INDEX	36

//脱morphine v2.7壳函数
typedef int (*pkill_morphine27)(PUnpackInfo pInfo);
#define UNPACK_MORPHINE3	"kill_morphine27"
#define MORPHINE3_INDEX	37


//脱yoda's protector v1.02 v1.03.2壳函数
typedef int (*pkill_yp102)(PUnpackInfo pInfo);
#define UNPACK_YP1	"kill_yp102"
#define YP1_INDEX	38


//脱yoda's Crypt v1.1壳函数
typedef int (*pkill_yc11)(PUnpackInfo pInfo);
#define UNPACK_YC1	"kill_yc11"
#define YC1_INDEX	39

//脱yoda's Crypt v1.2 v1.3 仙剑系列壳函数
typedef int (*pkill_yc12)(PUnpackInfo pInfo);
#define UNPACK_YC2	"kill_yc12"
#define YC2_INDEX	40

//脱仙剑-望海潮壳函数
typedef int (*pkill_xjhaichao)(PUnpackInfo pInfo);
#define UNPACK_XJWHC	"kill_xjhaichao"
#define XJWHC_INDEX	41


//脱EXEStealth v2.72--v2.76壳函数
typedef int (*pkill_exestealth275)(PUnpackInfo pInfo);
#define UNPACK_EXESTEALTH	"kill_exestealth275"
#define EXESTEALTH_INDEX	42


//脱HidePE v1.0 v1.1壳函数
typedef int (*pkill_hidepe11)(PUnpackInfo pInfo);
#define UNPACK_HIDEPE	"kill_hidepe11"
#define HIDEPE_INDEX	43


//脱jdpack v1.01 v2.1 v2.13壳函数
typedef int (*pkill_jdpack)(PUnpackInfo pInfo);
#define UNPACK_JDPACK	"kill_jdpack"
#define JDPACK_INDEX	44


//脱PEncrypt v3.0壳函数
typedef int (*pkill_PEncrypt30)(PUnpackInfo pInfo);
#define UNPACK_PENCRYPT1	"kill_PEncrypt30"
#define PENCRYPT1_INDEX	45

//脱PEncrypt v3.1壳函数
typedef int (*pkill_PEncrypt31)(PUnpackInfo pInfo);
#define UNPACK_PENCRYPT2	"kill_PEncrypt31"
#define PENCRYPT2_INDEX	46

//脱PEncrypt v4.0壳函数
typedef int (*pkill_PEncrypt40)(PUnpackInfo pInfo);
#define UNPACK_PENCRYPT3	"kill_PEncrypt40"
#define PENCRYPT3_INDEX	47


//脱Stone's PE Crypt v1.13壳函数
typedef int (*pkill_StonePECrypt113)(PUnpackInfo pInfo);
#define UNPACK_SPECRYPT	"kill_StonePECrypt113"
#define SPECRYPT_INDEX	48


//脱telock v0.42壳函数
typedef int (*pkill_telock042)(PUnpackInfo pInfo);
#define UNPACK_TELOCK1	"kill_telock042"
#define TELOCK1_INDEX	49

//脱telock v0.51壳函数
typedef int (*pkill_telock051)(PUnpackInfo pInfo);
#define UNPACK_TELOCK2	"kill_telock051"
#define TELOCK2_INDEX	50

//脱telock v0.60  v0.70 v0.71壳函数
typedef int (*pkill_telock060)(PUnpackInfo pInfo);
#define UNPACK_TELOCK3	"kill_telock060"
#define TELOCK3_INDEX	51


//脱ezip壳函数
typedef int (*pkill_ezip)(PUnpackInfo pInfo);
#define UNPACK_EZIP	"kill_ezip"
#define EZIP_INDEX	52


//脱hmimys-packer v1.0壳函数
typedef int (*pkill_hmimys_pack)(PUnpackInfo pInfo);
#define UNPACK_HMIMYS_PACK	"kill_hmimys_pack"
#define HMIMYS_PACK_INDEX	53


//脱lamecrypt壳函数
typedef int (*pkill_lamecrypt)(PUnpackInfo pInfo);
#define UNPACK_LAMECRYPT	"kill_lamecrypt"
#define LAMECRYPT_INDEX	54


//脱upolyx壳函数
typedef int (*pkill_upolyx)(PUnpackInfo pInfo);
#define UNPACK_UPOLYX	"kill_upolyx"
#define UPOLYX_INDEX	55


//脱StealthPE 1.01壳函数
typedef int (*pkill_strealthpe101)(PUnpackInfo pInfo);
#define UNPACK_STREALTHPE1	"kill_strealthpe101"
#define STREALTHPE1_INDEX	56

//脱StealthPE 2.2壳函数
typedef int (*pkill_strealthpe22)(PUnpackInfo pInfo);
#define UNPACK_STREALTHPE2	"kill_strealthpe22"
#define STREALTHPE2_INDEX	57


//脱depack壳函数
typedef int (*pkill_depack)(PUnpackInfo pInfo);
#define UNPACK_DEPACK	"kill_depack"
#define DEPACK_INDEX	58


//脱polyene 0.01函数
typedef int (*pkill_polyene)(PUnpackInfo pInfo);
#define UNPACK_POLYENE	"kill_polyene"
#define POLYENE_INDEX	59

//脱DragonArmour函数
typedef int (*pkill_dragonArmour)(PUnpackInfo pInfo);
#define UNPACK_DRAGONARMOUR	"kill_dragonArmour"
#define DRAGONARMOUR_INDEX	60


//脱EP Protector v0.3函数
typedef int (*pkill_EPProtector)(PUnpackInfo pInfo);
#define UNPACK_EPPROTECTOR	"kill_EPProtector"
#define EPPROTECTOR_INDEX	61


//脱PackItBitch函数
typedef int (*pkill_PackItBitch)(PUnpackInfo pInfo);
#define UNPACK_PACKITBITCH	"kill_PackItBitch"
#define PACKITBITCH_INDEX	62


//脱木马彩衣函数
typedef int (*pkill_trojanpack)(PUnpackInfo pInfo);
#define UNPACK_TROJANPACK	"kill_trojanpack"
#define	TROJANPACK_INDEX	63


//脱anti007 v2.5 v2.6壳函数
typedef int (*pkill_anti007)(PUnpackInfo pInfo);
#define UNPACK_ANTI007	"kill_anti007"
#define ANTI007_INDEX	64


//脱mkfpack壳函数
typedef int (*pkill_mkfpack)(PUnpackInfo pInfo);
#define UNPACK_MKFPACK	"kill_mkfpack"
#define MKFPACK_INDEX	65


//脱yzpack v1.1壳函数
typedef int (*pkill_yzpack11)(PUnpackInfo pInfo);
#define UNPACK_YZPACK1	"kill_yzpack11"
#define YZPACK1_INDEX	66

//脱yzpack v2.0壳函数
typedef int (*pkill_yzpack20)(PUnpackInfo pInfo);
#define UNPACK_YZPACK2	"kill_yzpack20"
#define YZPACK2_INDEX	67


//脱spack_method1 v1.1壳函数
typedef int (*pkill_spack_method1)(PUnpackInfo pInfo);
#define UNPACK_SPACK1	"kill_spack_method1"
#define SPACK1_INDEX	68

//脱spack_method2 v1.1壳函数
typedef int (*pkill_spack_method2)(PUnpackInfo pInfo);
#define UNPACK_SPACK2	"kill_spack_method2"
#define SPACK2_INDEX	69



//脱mslrh0.31壳函数
typedef int (*pkill_mslrh)(PUnpackInfo pInfo);
#define UNPACK_MSLRH	"kill_mslrh"
#define	MSLRH_INDEX	70

//脱mslrh0.2 == [G!X]'s Protect壳函数
typedef int (*pkill_mslrh02)(PUnpackInfo pInfo);
#define UNPACK_GXP	"kill_mslrh02"
#define	GXP_INDEX	71
}


#endif //_VM_UNPACK_H_
