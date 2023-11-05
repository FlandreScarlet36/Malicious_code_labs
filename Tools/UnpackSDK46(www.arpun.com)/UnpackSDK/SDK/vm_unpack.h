#ifndef _VM_UNPACK_H_
#define _VM_UNPACK_H_

//�ѿǳɹ���Ļص�������ָ��
typedef int (*pResultCallBack)(char *pFileName, char **pbuf, int *pnlen);

//�ѿ�ʧ��ԭ��
#define LOAD_ERROR	-1	//loadʧ��
#define UNPACK_ERROR	-2	//ִ�й����г���


//��������ִ���У���Ҫ������ڴ���Ϣ
typedef struct tagPorcNeedMemInfo
{
	int		nHeadSize;			//�Ѵ�С�������0���PEͷ��Ϣ�л�ȡ
	int		nStackSize;			//ջ��С�������0���PEͷ��Ϣ�л�ȡ
	int		nSystemDllSize;		//load dll�û�������С
	int		nLoadSystemDll;		//�Ƿ�load dll,anti007ʹ��
	int		nAnalyseKernel32;	//��������kernel32.dll
}ProcNeedMemInfo, *PProcNeedMemInfo;


//�ѿǺ�����������Ϣ�ṹ��
typedef struct tagUnpackInfo
{
	unsigned int		nExecuteStep;	//���������ִ�в���
	char *				pInFileName;	//���ѳ���ȫ·��
	char *				pInBuf;			//���ѳ������ڻ�����
	int					nInBufLen;		//���ѳ��򳤶�
	PProcNeedMemInfo	pMemInfo;		//�ѿǹ���Ҫ�����ڴ��С
	char *				pOutBuf;		//�ѿǺ�������ڻ�����
	int					nOutBufLen;		//�ѿǺ���򳤶�
	char *				pOutFileName;	//�ѿǺ��д�ļ�ȫ·��
	pResultCallBack		pResultFun;		//�ѿǺ�ص�������
	int					nOEPUnpack;		//�Ƿ����oepʶ��ʽ�ѿ�
}UnpackInfo, *PUnpackInfo;


//vmunpack.dll�����ĺ���ԭ��
extern "C"
{
//��ʼ�������CPUָ��ϵͳ,Ѱַϵͳ����,������������ѿ�ǰ����һ��
typedef void (*pinit_vm)();
#define INIT_VM "init_vm"


//�ѿǺ���ԭ��
typedef int (*pUnpacker)(PUnpackInfo pInfo);

//����ѿǺ���ID + 1
#define MAX_FUN_ID	72


//��upx�Ǻ���
typedef int (*pkill_upx)(PUnpackInfo pInfo);
#define UNPACK_UPX	"kill_upx"
#define UPX_INDEX	1


//��aspack�Ǻ���
typedef int (*pkill_aspack)(PUnpackInfo pInfo);
#define UNPACK_ASPACK	"kill_aspack"
#define ASPACK_INDEX	2


//��PEcompac v0.90 v0.92 v0.93 v0.94 v0.97b�Ǻ���
typedef int (*pkill_PEcompact090)(PUnpackInfo pInfo);
#define UNPACK_PECOMPACT1	"kill_PEcompact090"
#define PECOMPACT1_INDEX	3

//��PEcompac v2.x�Ǻ���
typedef int (*pkill_PEcompact_2x)(PUnpackInfo pInfo);
#define UNPACK_PECOMPACT2	"kill_PEcompact_2x"
#define PECOMPACT2_INDEX	4



//��fsg v1.0 v1.1 v1.2 v1.3 v1.31 v1.33�Ǻ���
typedef int (*pkill_fsg133)(PUnpackInfo pInfo);
#define UNPACK_FSG1	"kill_fsg133"
#define FSG1_INDEX	5

//��fsg v2.0 ����
typedef int (*pkill_fsg20)(PUnpackInfo pInfo);
#define UNPACK_FSG2	"kill_fsg20"
#define FSG2_INDEX	6


//��VGCrypt 0.75�Ǻ���
typedef int (*pkill_vgcrypt075)(PUnpackInfo pInfo);
#define UNPACK_VGCRYPT	"kill_vgcrypt075"
#define VGCRYPT_INDEX	7


//��Nspack�Ǻ���
typedef int (*pkill_nspack)(PUnpackInfo pInfo);
#define UNPACK_NSPACK	"kill_nspack"
#define NSPACK_INDEX	8


//��npack�Ǻ���
typedef int (*pkill_npack)(PUnpackInfo pInfo);
#define UNPACK_NPACK	"kill_npack"
#define NPACK_INDEX	9


//��expressor v1.0 v1.1 v1.2 v1.3 v1.4 v1.501����
typedef int (*pkill_expressor)(PUnpackInfo pInfo);
#define UNPACK_EXPRESSOR	"kill_expressor"
#define EXPRESSOR_INDEX	10


//��dxpack0.86�Ǻ���
typedef int (*pkill_dxpack086)(PUnpackInfo pInfo);
#define UNPACK_DXPACK1	"kill_dxpack086"
#define DXPACK1_INDEX	11


//��dxpack 1.0�Ǻ���
typedef int (*pkill_dxpack10)(PUnpackInfo pInfo);
#define UNPACK_DXPACK2	"kill_dxpack10"
#define DXPACK2_INDEX	12



//��!Epack1.0�Ǻ���
typedef int (*pkill_epack10)(PUnpackInfo pInfo);
#define UNPACK_EPACK1	"kill_epack10"
#define EPACK1_INDEX	13

//��!Epack1.4�Ǻ���
typedef int (*pkill_epack14)(PUnpackInfo pInfo);
#define UNPACK_EPACK2	"kill_epack14"
#define EPACK2_INDEX	14


//��bjfnt�Ǻ���
typedef int (*pkill_bjfnt)(PUnpackInfo pInfo);
#define UNPACK_BJFNT	"kill_bjfnt"
#define BJFNT_INDEX	15


//��mew v1.1�Ǻ���
typedef int (*pkill_mew5)(PUnpackInfo pInfo);
#define UNPACK_MEW1	"kill_mew5"
#define MEW1_INDEX	16

//��mew v1.0 v1.1�Ǻ���
typedef int (*pkill_mew11)(PUnpackInfo pInfo);
#define UNPACK_MEW2	"kill_mew11"
#define MEW2_INDEX	17


//��packMan v1.0�Ǻ���
typedef int (*pkill_packMan10)(PUnpackInfo pInfo);
#define UNPACK_PACKMAN	"kill_packMan10"
#define PACKMAN_INDEX	18


//��PEDiminisher0.1�Ǻ���
typedef int (*pkill_PEDiminisher)(PUnpackInfo pInfo);
#define UNPACK_PEDIMINISHER	"kill_PEDiminisher"
#define PEDIMINISHER_INDEX	19


//��pex�Ǻ���
typedef int (*pkill_pex)(PUnpackInfo pInfo);
#define UNPACK_PEX	"kill_pex"
#define PEX_INDEX	20


//��petite v1.2 v1.3 v1.4�Ǻ���
typedef int (*pkill_petite1x)(PUnpackInfo pInfo);
#define UNPACK_PETITE1	"kill_petite1x"
#define PETITE1_INDEX	21

//��petite v2.2 v2.3�Ǻ���
typedef int (*pkill_petite2x)(PUnpackInfo pInfo);
#define UNPACK_PETITE2	"kill_petite2x"
#define PETITE2_INDEX	22


//��winkript�Ǻ���
typedef int (*pkill_winkript)(PUnpackInfo pInfo);
#define UNPACK_WINKRIPT	"kill_winkript"
#define WINKRIPT_INDEX	23


//��pklite32�Ǻ���
typedef int (*pkill_pklite32)(PUnpackInfo pInfo);
#define UNPACK_PKLITE32	"kill_pklite32"
#define PKLITE32_INDEX	24


//��pepack v0.99 v1.0�Ǻ���
typedef int (*pkill_pepack)(PUnpackInfo pInfo);
#define UNPACK_PEPACK	"kill_pepack"
#define PEPACK_INDEX	25


//��pcshrinker0.71�Ǻ���
typedef int (*pkill_pcshrinker)(PUnpackInfo pInfo);
#define UNPACK_PCSHRINKER	"kill_pcshrinker"
#define PCSHRINKER_INDEX	26


//��wwpack32 1.0--1.2�Ǻ���
typedef int (*pkill_wwpack32)(PUnpackInfo pInfo);
#define UNPACK_WWPACK32	"kill_wwpack32"
#define WWPACK32_INDEX	27


//��upack 0.10--0.32�Ǻ���
typedef int (*pkill_upack32)(PUnpackInfo pInfo);
#define UNPACK_UPACK1	"kill_upack32"
#define UPACK1_INDEX	28

//��upack 0.33--0.399�Ǻ���
typedef int (*pkill_upack36)(PUnpackInfo pInfo);
#define UNPACK_UPACK2	"kill_upack36"
#define UPACK2_INDEX	29


//��rlpack v1.11 v1.12 v1.13 v1.14�Ǻ���
typedef int (*pkill_rlpack111)(PUnpackInfo pInfo);
#define UNPACK_RLPACK1	"kill_rlpack111"
#define RLPACK1_INDEX	30

//��rlpack v1.18 v1.15 v1.16 v1.17�Ǻ���
typedef int (*pkill_rlpack118)(PUnpackInfo pInfo);
#define UNPACK_RLPACK2	"kill_rlpack118"
#define RLPACK2_INDEX	31


//��exe32pack v1.42�Ǻ���
typedef int (*pkill_exe32pack)(PUnpackInfo pInfo);
#define UNPACK_EXE32PACK	"kill_exe32pack"
#define EXE32PACK_INDEX	32


//��kbys v0.22 �Ǻ���
typedef int (*pkill_kbys22)(PUnpackInfo pInfo);
#define UNPACK_KBYS1	"kill_kbys22"
#define KBYS1_INDEX	33

//��kbys v0.28, ����ѹ�����Ǻ���
typedef int (*pkill_kbys28)(PUnpackInfo pInfo);
#define UNPACK_KBYS2	"kill_kbys28"
#define KBYS2_INDEX	34

 
//��morphine v1.3�Ǻ���
typedef int (*pkill_morphine13)(PUnpackInfo pInfo);
#define UNPACK_MORPHINE1	"kill_morphine13"
#define MORPHINE1_INDEX	35

//��morphine v1.6�Ǻ���
typedef int (*pkill_morphine16)(PUnpackInfo pInfo);
#define UNPACK_MORPHINE2	"kill_morphine16"
#define MORPHINE2_INDEX	36

//��morphine v2.7�Ǻ���
typedef int (*pkill_morphine27)(PUnpackInfo pInfo);
#define UNPACK_MORPHINE3	"kill_morphine27"
#define MORPHINE3_INDEX	37


//��yoda's protector v1.02 v1.03.2�Ǻ���
typedef int (*pkill_yp102)(PUnpackInfo pInfo);
#define UNPACK_YP1	"kill_yp102"
#define YP1_INDEX	38


//��yoda's Crypt v1.1�Ǻ���
typedef int (*pkill_yc11)(PUnpackInfo pInfo);
#define UNPACK_YC1	"kill_yc11"
#define YC1_INDEX	39

//��yoda's Crypt v1.2 v1.3 �ɽ�ϵ�пǺ���
typedef int (*pkill_yc12)(PUnpackInfo pInfo);
#define UNPACK_YC2	"kill_yc12"
#define YC2_INDEX	40

//���ɽ�-�������Ǻ���
typedef int (*pkill_xjhaichao)(PUnpackInfo pInfo);
#define UNPACK_XJWHC	"kill_xjhaichao"
#define XJWHC_INDEX	41


//��EXEStealth v2.72--v2.76�Ǻ���
typedef int (*pkill_exestealth275)(PUnpackInfo pInfo);
#define UNPACK_EXESTEALTH	"kill_exestealth275"
#define EXESTEALTH_INDEX	42


//��HidePE v1.0 v1.1�Ǻ���
typedef int (*pkill_hidepe11)(PUnpackInfo pInfo);
#define UNPACK_HIDEPE	"kill_hidepe11"
#define HIDEPE_INDEX	43


//��jdpack v1.01 v2.1 v2.13�Ǻ���
typedef int (*pkill_jdpack)(PUnpackInfo pInfo);
#define UNPACK_JDPACK	"kill_jdpack"
#define JDPACK_INDEX	44


//��PEncrypt v3.0�Ǻ���
typedef int (*pkill_PEncrypt30)(PUnpackInfo pInfo);
#define UNPACK_PENCRYPT1	"kill_PEncrypt30"
#define PENCRYPT1_INDEX	45

//��PEncrypt v3.1�Ǻ���
typedef int (*pkill_PEncrypt31)(PUnpackInfo pInfo);
#define UNPACK_PENCRYPT2	"kill_PEncrypt31"
#define PENCRYPT2_INDEX	46

//��PEncrypt v4.0�Ǻ���
typedef int (*pkill_PEncrypt40)(PUnpackInfo pInfo);
#define UNPACK_PENCRYPT3	"kill_PEncrypt40"
#define PENCRYPT3_INDEX	47


//��Stone's PE Crypt v1.13�Ǻ���
typedef int (*pkill_StonePECrypt113)(PUnpackInfo pInfo);
#define UNPACK_SPECRYPT	"kill_StonePECrypt113"
#define SPECRYPT_INDEX	48


//��telock v0.42�Ǻ���
typedef int (*pkill_telock042)(PUnpackInfo pInfo);
#define UNPACK_TELOCK1	"kill_telock042"
#define TELOCK1_INDEX	49

//��telock v0.51�Ǻ���
typedef int (*pkill_telock051)(PUnpackInfo pInfo);
#define UNPACK_TELOCK2	"kill_telock051"
#define TELOCK2_INDEX	50

//��telock v0.60  v0.70 v0.71�Ǻ���
typedef int (*pkill_telock060)(PUnpackInfo pInfo);
#define UNPACK_TELOCK3	"kill_telock060"
#define TELOCK3_INDEX	51


//��ezip�Ǻ���
typedef int (*pkill_ezip)(PUnpackInfo pInfo);
#define UNPACK_EZIP	"kill_ezip"
#define EZIP_INDEX	52


//��hmimys-packer v1.0�Ǻ���
typedef int (*pkill_hmimys_pack)(PUnpackInfo pInfo);
#define UNPACK_HMIMYS_PACK	"kill_hmimys_pack"
#define HMIMYS_PACK_INDEX	53


//��lamecrypt�Ǻ���
typedef int (*pkill_lamecrypt)(PUnpackInfo pInfo);
#define UNPACK_LAMECRYPT	"kill_lamecrypt"
#define LAMECRYPT_INDEX	54


//��upolyx�Ǻ���
typedef int (*pkill_upolyx)(PUnpackInfo pInfo);
#define UNPACK_UPOLYX	"kill_upolyx"
#define UPOLYX_INDEX	55


//��StealthPE 1.01�Ǻ���
typedef int (*pkill_strealthpe101)(PUnpackInfo pInfo);
#define UNPACK_STREALTHPE1	"kill_strealthpe101"
#define STREALTHPE1_INDEX	56

//��StealthPE 2.2�Ǻ���
typedef int (*pkill_strealthpe22)(PUnpackInfo pInfo);
#define UNPACK_STREALTHPE2	"kill_strealthpe22"
#define STREALTHPE2_INDEX	57


//��depack�Ǻ���
typedef int (*pkill_depack)(PUnpackInfo pInfo);
#define UNPACK_DEPACK	"kill_depack"
#define DEPACK_INDEX	58


//��polyene 0.01����
typedef int (*pkill_polyene)(PUnpackInfo pInfo);
#define UNPACK_POLYENE	"kill_polyene"
#define POLYENE_INDEX	59

//��DragonArmour����
typedef int (*pkill_dragonArmour)(PUnpackInfo pInfo);
#define UNPACK_DRAGONARMOUR	"kill_dragonArmour"
#define DRAGONARMOUR_INDEX	60


//��EP Protector v0.3����
typedef int (*pkill_EPProtector)(PUnpackInfo pInfo);
#define UNPACK_EPPROTECTOR	"kill_EPProtector"
#define EPPROTECTOR_INDEX	61


//��PackItBitch����
typedef int (*pkill_PackItBitch)(PUnpackInfo pInfo);
#define UNPACK_PACKITBITCH	"kill_PackItBitch"
#define PACKITBITCH_INDEX	62


//��ľ����º���
typedef int (*pkill_trojanpack)(PUnpackInfo pInfo);
#define UNPACK_TROJANPACK	"kill_trojanpack"
#define	TROJANPACK_INDEX	63


//��anti007 v2.5 v2.6�Ǻ���
typedef int (*pkill_anti007)(PUnpackInfo pInfo);
#define UNPACK_ANTI007	"kill_anti007"
#define ANTI007_INDEX	64


//��mkfpack�Ǻ���
typedef int (*pkill_mkfpack)(PUnpackInfo pInfo);
#define UNPACK_MKFPACK	"kill_mkfpack"
#define MKFPACK_INDEX	65


//��yzpack v1.1�Ǻ���
typedef int (*pkill_yzpack11)(PUnpackInfo pInfo);
#define UNPACK_YZPACK1	"kill_yzpack11"
#define YZPACK1_INDEX	66

//��yzpack v2.0�Ǻ���
typedef int (*pkill_yzpack20)(PUnpackInfo pInfo);
#define UNPACK_YZPACK2	"kill_yzpack20"
#define YZPACK2_INDEX	67


//��spack_method1 v1.1�Ǻ���
typedef int (*pkill_spack_method1)(PUnpackInfo pInfo);
#define UNPACK_SPACK1	"kill_spack_method1"
#define SPACK1_INDEX	68

//��spack_method2 v1.1�Ǻ���
typedef int (*pkill_spack_method2)(PUnpackInfo pInfo);
#define UNPACK_SPACK2	"kill_spack_method2"
#define SPACK2_INDEX	69



//��mslrh0.31�Ǻ���
typedef int (*pkill_mslrh)(PUnpackInfo pInfo);
#define UNPACK_MSLRH	"kill_mslrh"
#define	MSLRH_INDEX	70

//��mslrh0.2 == [G!X]'s Protect�Ǻ���
typedef int (*pkill_mslrh02)(PUnpackInfo pInfo);
#define UNPACK_GXP	"kill_mslrh02"
#define	GXP_INDEX	71
}


#endif //_VM_UNPACK_H_
