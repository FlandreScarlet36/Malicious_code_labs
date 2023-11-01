#include "stdafx.h"

#include "init_peid_vmpack.h"
#include "vm_unpack.h"



//壳ID跟脱壳函数对应关系表
pUnpacker g_unpack_fun[MAX_UNPACK_NUM];

//vmunpack.dll句柄
HMODULE g_vmunpack = NULL;

//从vmunpack.dll中导出的初始化虚拟机CPU函数
pinit_vm g_init_vm = NULL;



//功能：初始化脱壳dll函数(加载，导出函数，初始化脱壳函数表)
//参数：
//		pDllPath	dll路径
//返回：成功0，否则-1
int init_vmunpack_dll(char * pDllPath)
{
	int nIndex;

	//加载dll
	g_vmunpack = LoadLibrary(pDllPath);
	if(NULL == g_vmunpack)
	{
		return -1;
	}

	//清空脱壳函数表
	memset(&g_unpack_fun, 0, sizeof(g_unpack_fun));

	//导出dll中的脱壳函数
	g_unpack_fun[UPX_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_UPX); //1
	g_unpack_fun[ASPACK_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_ASPACK);
	g_unpack_fun[PECOMPACT1_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_PECOMPACT1);
	g_unpack_fun[PECOMPACT2_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_PECOMPACT2);
	g_unpack_fun[FSG1_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_FSG1);
	g_unpack_fun[FSG2_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_FSG2);
	g_unpack_fun[VGCRYPT_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_VGCRYPT);
	g_unpack_fun[NSPACK_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_NSPACK);
	g_unpack_fun[NPACK_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_NPACK);
	g_unpack_fun[EXPRESSOR_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_EXPRESSOR);

	g_unpack_fun[DXPACK1_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_DXPACK1); //11
	g_unpack_fun[DXPACK2_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_DXPACK2);
	g_unpack_fun[EPACK1_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_EPACK1);
	g_unpack_fun[EPACK2_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_EPACK2);
	g_unpack_fun[BJFNT_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_BJFNT);
	g_unpack_fun[MEW1_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_MEW1);
	g_unpack_fun[MEW2_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_MEW2);
	g_unpack_fun[PACKMAN_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_PACKMAN);
	g_unpack_fun[PEDIMINISHER_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_PEDIMINISHER);
	g_unpack_fun[PEX_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_PEX);

	g_unpack_fun[PETITE1_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_PETITE1); //21
	g_unpack_fun[PETITE2_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_PETITE2);
	g_unpack_fun[WINKRIPT_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_WINKRIPT);
	g_unpack_fun[PKLITE32_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_PKLITE32);
	g_unpack_fun[PEPACK_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_PEPACK);
	g_unpack_fun[PCSHRINKER_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_PCSHRINKER);
	g_unpack_fun[WWPACK32_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_WWPACK32);
	g_unpack_fun[UPACK1_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_UPACK1);
	g_unpack_fun[UPACK2_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_UPACK2);
	g_unpack_fun[RLPACK1_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_RLPACK1);

	g_unpack_fun[RLPACK2_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_RLPACK2); //31
	g_unpack_fun[EXE32PACK_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_EXE32PACK);
	g_unpack_fun[KBYS1_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_KBYS1);
	g_unpack_fun[KBYS2_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_KBYS2);
	g_unpack_fun[MORPHINE1_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_MORPHINE1);
	g_unpack_fun[MORPHINE2_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_MORPHINE2);
	g_unpack_fun[MORPHINE3_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_MORPHINE3);
	g_unpack_fun[YP1_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_YP1);
	g_unpack_fun[YC1_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_YC1);
	g_unpack_fun[YC2_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_YC2);

	g_unpack_fun[XJWHC_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_XJWHC); //41
	g_unpack_fun[EXESTEALTH_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_EXESTEALTH);
	g_unpack_fun[HIDEPE_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_HIDEPE);
	g_unpack_fun[JDPACK_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_JDPACK);
	g_unpack_fun[PENCRYPT1_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_PENCRYPT1);
	g_unpack_fun[PENCRYPT2_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_PENCRYPT2);
	g_unpack_fun[PENCRYPT3_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_PENCRYPT3);
	g_unpack_fun[SPECRYPT_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_SPECRYPT);
	g_unpack_fun[TELOCK1_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_TELOCK1);
	g_unpack_fun[TELOCK2_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_TELOCK2);

	g_unpack_fun[TELOCK3_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_TELOCK3); //51
	g_unpack_fun[EZIP_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_EZIP);
	g_unpack_fun[HMIMYS_PACK_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_HMIMYS_PACK);
	g_unpack_fun[LAMECRYPT_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_LAMECRYPT);
	g_unpack_fun[UPOLYX_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_UPOLYX);
	g_unpack_fun[STREALTHPE1_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_STREALTHPE1);
	g_unpack_fun[STREALTHPE2_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_STREALTHPE2);
	g_unpack_fun[DEPACK_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_DEPACK);
	g_unpack_fun[POLYENE_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_POLYENE);
	g_unpack_fun[DRAGONARMOUR_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_DRAGONARMOUR);
	
	g_unpack_fun[EPPROTECTOR_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_EPPROTECTOR); //61
	g_unpack_fun[PACKITBITCH_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_PACKITBITCH);
	g_unpack_fun[TROJANPACK_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_TROJANPACK);
	g_unpack_fun[ANTI007_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_ANTI007);
	g_unpack_fun[MKFPACK_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_MKFPACK);
	g_unpack_fun[YZPACK1_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_YZPACK1);
	g_unpack_fun[YZPACK2_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_YZPACK2);
	g_unpack_fun[SPACK1_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_SPACK1);
	g_unpack_fun[SPACK2_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_SPACK2);
	g_unpack_fun[MSLRH_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_MSLRH);

	g_unpack_fun[GXP_INDEX] = (pUnpacker)GetProcAddress(g_vmunpack, UNPACK_GXP); //71

	//效验是否所有函数均导出成功
	for(nIndex = 1; nIndex < MAX_FUN_ID; nIndex++)
	{
		if(NULL == g_unpack_fun[nIndex]) //有脱壳函数导出失败
		{
			FreeLibrary(g_vmunpack);
			return -1;
		}
	}

	//导出init_vm函数
	g_init_vm = (pinit_vm)GetProcAddress(g_vmunpack, INIT_VM);
	if(NULL == g_init_vm)
	{
		FreeLibrary(g_vmunpack);
		return -1;
	}

	//一切正常
	return 0;
}


//功能：释放脱壳dll
//参数：无
//返回：无
void destroy_vmunpack_dll()
{
	if(NULL != g_vmunpack)
	{
		FreeLibrary(g_vmunpack);
	}
}

