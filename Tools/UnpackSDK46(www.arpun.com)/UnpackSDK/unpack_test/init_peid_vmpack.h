#ifndef _INIT_PEID_VMPACK_H_
#define _INIT_PEID_VMPACK_H_

#include "vm_unpack.h"
#include "vm_peid.h"



#define MAX_UNPACK_NUM 100	//�ѿǺ������С



//���ܣ���ʼ���ѿ�dll����(���أ�������������ʼ���ѿǺ�����)
//������
//		pDllPath	dll·��
//���أ��ɹ�0������-1
int init_vmunpack_dll(char * pDllPath);


//���ܣ��ͷ��ѿ�dll
//��������
//���أ���
void destroy_vmunpack_dll();



//����:��ʼ��PEID�Ǽ��
//����:
//		pDllPath dll·��
//����:�ɹ�0,����-1
int init_vmuppeid_dll(char * pDllPath);


//���ܣ��ͷſǼ��dll
//��������
//���أ���
void destroy_vmuppeid_dll();




extern pinit_vm g_init_vm;							//��vmunpack.dll�е����ĳ�ʼ�������CPU����
extern pUnpacker g_unpack_fun[];					//�ѿǺ�����Ӧ��


extern pinit_peid_engine g_init_peid_engine;		//��ʼ��PEID��������
extern pload_peid_rule g_load_peid_rule;			//����PEID����⺯��
extern pdestroy_peid_engine g_destroy_peid_engine;	//����PEID������溯��
extern ppeid_check g_peid_check;					//������Ϣ����


#endif //_INIT_PEID_VMPACK_H_
