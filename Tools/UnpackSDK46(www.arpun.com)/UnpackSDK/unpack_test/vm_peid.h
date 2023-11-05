#ifndef _VM_PEID_H_
#define _VM_PEID_H_


#define COMPILE_RULE -1		//�鵽�ı�������Ϣ��Ӧ�ѿǺ���ID,��ʵ����û�мӿ�

extern "C"
{
//���ܣ���ʼ��PEID���������ݽṹ
//��������
//���أ���
typedef void (*pinit_peid_engine)();
#define INIT_PEID_ENGINE "init_peid_engine"


//����: ����PEID�����
//����:
//		pLibFileName ���������ļ�·��
//����: �ɹ�0,����-1
typedef int (*pload_peid_rule)(char * pLibFileName);
#define LOAD_PEID_RULE "load_peid_rule"


//���ܣ�����PEID�������ռ�õ��ڴ�(��PEID�����õ��ڴ�)
//��������
//���أ���
typedef void (*pdestroy_peid_engine)();
#define DESTROY_PEID_ENGINE "destroy_peid_engine"


//���ܣ�������Ϣ
//������
//		buf �ļ�����ָ��
//		nLen PE�ļ�����
//		ppPackerName �������ؿ�����ָ�룬���Դ���NULL����ʾ����ȡ��������Ϣ
//���أ������⵽�ǣ������ѿǺ���ID������0��ʾû�ж�Ӧ�ѿǺ������߸����Ͳ���PE�ļ�
typedef int (*ppeid_check)(unsigned char * buf, unsigned int nLen, char ** ppPackerName);
#define PEID_CHECK "peid_check"
}

#endif //_VM_PEID_H_
