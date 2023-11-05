#include "stdafx.h"

#include "init_peid_vmpack.h"
#include "vm_peid.h"


//vmuppeid.dll���
HMODULE g_vmuppeid = NULL;

//��vmuppeid.dll�е�����4������
pinit_peid_engine g_init_peid_engine = NULL;	//��ʼ��PEID��������
pload_peid_rule g_load_peid_rule = NULL;		//����PEID����⺯��
pdestroy_peid_engine g_destroy_peid_engine = NULL;	//����PEID������溯��
ppeid_check g_peid_check = NULL;				//������Ϣ����


//����:��ʼ��PEID�Ǽ��
//����:
//		pDllPath dll·��
//����:�ɹ�0,����-1
int init_vmuppeid_dll(char * pDllPath)
{
	//����dll
	g_vmuppeid = LoadLibrary(pDllPath);
	if(NULL == g_vmuppeid)
	{
		return -1;
	}

	//��vmuppeid.dll�е�������
	g_init_peid_engine = (pinit_peid_engine)GetProcAddress(g_vmuppeid, INIT_PEID_ENGINE);
	g_load_peid_rule = (pload_peid_rule)GetProcAddress(g_vmuppeid, LOAD_PEID_RULE);
	g_destroy_peid_engine = (pdestroy_peid_engine)GetProcAddress(g_vmuppeid, DESTROY_PEID_ENGINE);
	g_peid_check = (ppeid_check)GetProcAddress(g_vmuppeid, PEID_CHECK);
	
	//�Ƿ��к�������ʧ��
	if(NULL == g_init_peid_engine || NULL == g_load_peid_rule ||
		NULL == g_destroy_peid_engine || NULL == g_peid_check)
	{
		FreeLibrary(g_vmuppeid);
		return -1;
	}

	//һ������
	return 0;
}


//���ܣ��ͷſǼ��dll
//��������
//���أ���
void destroy_vmuppeid_dll()
{
	if(NULL != g_vmuppeid)
	{
		FreeLibrary(g_vmuppeid);
	}	
}
