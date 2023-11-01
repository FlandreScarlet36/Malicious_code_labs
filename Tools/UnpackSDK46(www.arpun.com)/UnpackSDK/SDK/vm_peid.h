#ifndef _VM_PEID_H_
#define _VM_PEID_H_


#define COMPILE_RULE -1		//查到的编译器信息对应脱壳函数ID,其实就是没有加壳

extern "C"
{
//功能：初始化PEID检测规则数据结构
//参数：无
//返回：无
typedef void (*pinit_peid_engine)();
#define INIT_PEID_ENGINE "init_peid_engine"


//功能: 加载PEID规则库
//参数:
//		pLibFileName 规则所在文件路径
//返回: 成功0,否则-1
typedef int (*pload_peid_rule)(char * pLibFileName);
#define LOAD_PEID_RULE "load_peid_rule"


//功能：销毁PEID检测引擎占用的内存(含PEID规则用的内存)
//参数：无
//返回：无
typedef void (*pdestroy_peid_engine)();
#define DESTROY_PEID_ENGINE "destroy_peid_engine"


//功能：检测壳信息
//参数：
//		buf 文件正文指针
//		nLen PE文件长度
//		ppPackerName 用来返回壳名称指针，可以传入NULL，表示不获取壳名称信息
//返回：如果检测到壳，返回脱壳函数ID，如是0表示没有对应脱壳函数或者根本就不是PE文件
typedef int (*ppeid_check)(unsigned char * buf, unsigned int nLen, char ** ppPackerName);
#define PEID_CHECK "peid_check"
}

#endif //_VM_PEID_H_
