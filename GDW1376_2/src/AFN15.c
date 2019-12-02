/**
 ******************************************************************************
 * @file      AFN15.c
 * @brief     C Source file of AFN15.c.
 * @details   This file including all API functions's implement of AFN15.c.
 * @copyright
 ******************************************************************************
 */
 
/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <stdio.h>
#include "../inc/GDW1376_2.h"
#include "types.h"
#include "lib.h"
#include "maths.h"

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
#pragma pack(push, 1)

typedef struct
{
    uint8_t file_flag;          /**< �ļ���ʶ */
    uint8_t file_attr;          /**< �ļ����� */
    uint8_t file_instr;         /**< �ļ�ָ�� */
    uint16_t seg_count;         /**< �ܶ���n */
    uint32_t seg_flag;          /**< ��i�α�ʶ(i=0~n) */
    uint16_t seg_len;           /**< ��i�����ݳ��� */
} file_tran_req_t;

#pragma pack(pop)

/*-----------------------------------------------------------------------------
 Section: Constant Definitions
 ----------------------------------------------------------------------------*/
/* NONE */ 

/*-----------------------------------------------------------------------------
 Section: Global Variables
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Local Variables
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Local Function Prototypes
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Global Function Prototypes
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Function Definitions
 ----------------------------------------------------------------------------*/
/**
 ******************************************************************************
 * @brief   ����ļ����䷽ʽ1�����ַ���
 * @param[in]   dir         : ���䷽��:1����(ģ��->������)" 0����(������->ģ��)
 * @param[in]  *pin         : ���뱨��
 * @param[in]   len         : Ӧ�ò㱨�ĳ���
 * @param[in]  *pcb         : �ص�����
 * @param[in]  *pline_head  : ÿ����ʼ����ַ���
 * @param[in]  *pline_end   : ÿ�н�������ַ���
 *
 * @return  0 : �����ɹ�
 * @return -1 : ����ʧ��
 ******************************************************************************
 */
static int
AFN15_FN01(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;
    pcb(pline_head);
    pcb("�ļ����䷽ʽ1");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        if (len < (int)sizeof(file_tran_req_t))
        {
            sprintf(buf, "%s���뱨�ĳ��Ȳ������ʧ��!%s", pline_head,  pline_end);
            pcb(buf);
            return -1;
        }

        sprintf(buf, "%s�ļ���ʶ[%02X]:", pline_head, pin[0]);
        pcb(buf);
        switch (pin[0])
        {
            case 0:
                pcb("�����װ�ļ�\n");
                break;
            case 3:
                pcb("����ͨ��ģ�������ļ�\n");
                break;
            case 7:
                pcb("���ڵ���ӽڵ�ģ������\n");
                break;
            case 8:
                pcb("���ڵ�ģ������\n");
                break;
            default:
                pcb("����\n");
                break;
        }
        pcb(pline_end);

        sprintf(buf, "%s�ļ�����[%02X]:%s%s", pline_head, pin[1], !pin[1] ? "��ʼ֡���м�֡" : "����֡", pline_end);
        pcb(buf);
        sprintf(buf, "%s�ļ�ָ��[%02X]:%s%s", pline_head, pin[2], !pin[2] ? "���ķ�ʽ��װ" : "����", pline_end);
        pcb(buf);
        sprintf(buf, "%s�ܶ���[%02X %02X]:%d%s", pline_head, pin[3], pin[4], (pin[4] << 8) | pin[3], pline_end);
        pcb(buf);
        sprintf(buf, "%s��i�α�ʶ[%02X %02X %02X %02X]:%d%s", pline_head, pin[5], pin[6], pin[7], pin[8],
                (pin[8] << 24) | (pin[7] << 16) | (pin[6] << 8) | pin[5], pline_end);
        pcb(buf);
        sprintf(buf, "%s��i�����ݳ���[%02X %02X]:%d%s", pline_head, pin[9], pin[10], (pin[10] << 8) | pin[9], pline_end);
        pcb(buf);

        CHK_APP_LEN(len - sizeof(file_tran_req_t), ((pin[10] << 8) | pin[9]));

        pcb(pline_head);

        pcb("����:");
        pcb(pline_end);
        for (i = 0; i < ((pin[10] << 8) | pin[9]); i++)
        {
            sprintf(buf, "%02X ", pin[i + 11]);
            pcb(buf);
            if (((i + 1) % 16) == 0)
            {
                pcb(pline_end);
                pcb(pline_head);
            }
        }
        pcb(pline_end);
    }
    else    //����
    {
        CHK_APP_LEN(len, 4);
        sprintf(buf, "%s��ǰ�α�ʶ[%02X %02X %02X %02X]:%d%s", pline_head, pin[0], pin[1], pin[2], pin[3],
                (pin[3] << 24) | (pin[2] << 16) | (pin[1] << 8) | pin[0], pline_end);
        pcb(buf);
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ����ļ���������ַ���
 * @param[in]   dir         : ���䷽��:1����(ģ��->������)" 0����(������->ģ��)
 * @param[in]  *pin         : ���뱨��
 * @param[in]   len         : Ӧ�ò㱨�ĳ���
 * @param[in]  *pcb         : �ص�����
 * @param[in]  *pline_head  : ÿ����ʼ����ַ���
 * @param[in]  *pline_end   : ÿ�н�������ַ���
 *
 * @return  0 : �����ɹ�
 * @return -1 : ����ʧ��
 ******************************************************************************
 */
int
print_AFN15(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    unsigned char DT1 = pin[0];
    unsigned char DT2 = pin[1];
    int fn = get_clear_fn(&DT1, &DT2);

    switch (fn)
    {
        case 1: //�ļ����䷽ʽ1
            return AFN15_FN01(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        default:
            break;
    }

    pcb(pline_head);
    pcb("ERROR:��֧�ֵ�FN!");
    pcb(pline_end);

    return -ERR_AFN_FN;
}

/*--------------------------------AFN15.c------------------------------------*/
