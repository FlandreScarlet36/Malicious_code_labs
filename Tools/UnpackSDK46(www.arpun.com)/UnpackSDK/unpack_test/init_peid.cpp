#include "stdafx.h"

#include "init_peid_vmpack.h"
#include "vm_peid.h"


//vmuppeid.dll句柄
HMODULE g_vmuppeid = NULL;

//从vmuppeid.dll中导出的4个函数
pinit_peid_engine g_init_peid_engine = NULL;	//初始化PEID检测规则函数
pload_peid_rule g_load_peid_rule = NULL;		//加载PEID规则库函数
pdestroy_peid_engine g_destroy_peid_engine = NULL;	//销毁PEID检测引擎函数
ppeid_check g_peid_check = NULL;				//检测壳信息函数


//功能:初始化PEID壳检测
//参数:
//		pDllPath dll路径
//返回:成功0,否则-1
int init_vmuppeid_dll(char * pDllPath)
{
	//加载dll
	g_vmuppeid = LoadLibrary(pDllPath);
	if(NULL == g_vmuppeid)
	{
		return -1;
	}

	//从vmuppeid.dll中导出函数
	g_init_peid_engine = (pinit_peid_engine)GetProcAddress(g_vmuppeid, INIT_PEID_ENGINE);
	g_load_peid_rule = (pload_peid_rule)GetProcAddress(g_vmuppeid, LOAD_PEID_RULE);
	g_destroy_peid_engine = (pdestroy_peid_engine)GetProcAddress(g_vmuppeid, DESTROY_PEID_ENGINE);
	g_peid_check = (ppeid_check)GetProcAddress(g_vmuppeid, PEID_CHECK);
	
	//是否有函数导出失败
	if(NULL == g_init_peid_engine || NULL == g_load_peid_rule ||
		NULL == g_destroy_peid_engine || NULL == g_peid_check)
	{
		FreeLibrary(g_vmuppeid);
		return -1;
	}

	//一切正常
	return 0;
}


//功能：释放壳检测dll
//参数：无
//返回：无
void destroy_vmuppeid_dll()
{
	if(NULL != g_vmuppeid)
	{
		FreeLibrary(g_vmuppeid);
	}	
}
