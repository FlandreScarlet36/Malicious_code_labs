#ifndef _INIT_PEID_VMPACK_H_
#define _INIT_PEID_VMPACK_H_

#include "vm_unpack.h"
#include "vm_peid.h"



#define MAX_UNPACK_NUM 100	//脱壳函数表大小



//功能：初始化脱壳dll函数(加载，导出函数，初始化脱壳函数表)
//参数：
//		pDllPath	dll路径
//返回：成功0，否则-1
int init_vmunpack_dll(char * pDllPath);


//功能：释放脱壳dll
//参数：无
//返回：无
void destroy_vmunpack_dll();



//功能:初始化PEID壳检测
//参数:
//		pDllPath dll路径
//返回:成功0,否则-1
int init_vmuppeid_dll(char * pDllPath);


//功能：释放壳检测dll
//参数：无
//返回：无
void destroy_vmuppeid_dll();




extern pinit_vm g_init_vm;							//从vmunpack.dll中导出的初始化虚拟机CPU函数
extern pUnpacker g_unpack_fun[];					//脱壳函数对应表


extern pinit_peid_engine g_init_peid_engine;		//初始化PEID检测规则函数
extern pload_peid_rule g_load_peid_rule;			//加载PEID规则库函数
extern pdestroy_peid_engine g_destroy_peid_engine;	//销毁PEID检测引擎函数
extern ppeid_check g_peid_check;					//检测壳信息函数


#endif //_INIT_PEID_VMPACK_H_
