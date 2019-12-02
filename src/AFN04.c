/**
 ******************************************************************************
 * @file      AFN04.c
 * @brief     C Source file of AFN04.c.
 * @details   This file including all API functions's implement of AFN04.c.
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
/* NONE */

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
 * @brief   ������Ͳ���(��/�ӽڵ�������)�����ַ���
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
AFN04_FN01(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("���Ͳ���(��/�ӽڵ�������)");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        sprintf(buf, "%s����ʱ��:%d%s", pline_head, pin[0], pline_end);
        pcb(buf);
    }
    else    //����
    {
        //��
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ����ӽڵ�����ַ���
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
AFN04_FN02(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("�ӽڵ����");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        sprintf(buf, "%s�����ݵ�Ԫ%s", pline_head, pline_end);
        pcb(buf);
    }
    else    //����
    {
        //��
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   �������ͨ��ģ�鱨��ͨ�Ų��Խ����ַ���
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
AFN04_FN03(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;
    const char * const type[] =
    {
        "͸������",
        "DL/T645-1997",
        "DL/T645-2007",
    };

    pcb(pline_head);
    pcb("����ͨ��ģ�鱨��ͨ�Ų���");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        sprintf(buf, "%s����ͨ�����:%d%s", pline_head, pin[0], pline_end);
        pcb(buf);
        sprintf(buf, "%sĿ���ַ:[%02X %02X %02X %02X %02X %02X]%s",
                pline_head, pin[1], pin[2], pin[3], pin[4], pin[5], pin[6],
                pline_end);
        pcb(buf);
        sprintf(buf, "%sͨ��Э������[%d]:%s%s",
                pline_head, pin[7],
                (pin[7] < 3) ? type[pin[7]] : "��Ч",
                pline_end);
        pcb(buf);

        sprintf(buf, "%s���ĳ���L:%d%s", pline_head, pin[8], pline_end);
        pcb(buf);

        pcb(pline_head);
        pcb(" ��������:");
        pcb(pline_end);
        pcb(pline_head);
        for (i = 0; i < pin[8]; i++)
        {
            sprintf(buf, "%02X ", pin[i + 9]);
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
        //�����б���
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   �����·�������ַ���
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
print_AFN04(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    unsigned char DT1 = pin[0];
    unsigned char DT2 = pin[1];
    int fn = get_clear_fn(&DT1, &DT2);

    if (dir)
    {
        pcb(pline_head);
        pcb("ERROR:���б���Ϊȷ��/���ϱ���,���5.5.1");
        pcb(pline_end);
        return -1;
    }

    switch (fn)
    {
        case 1: //���Ͳ���(��/�ӽڵ�������)
            return AFN04_FN01(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 2: //�ӽڵ����
            return AFN04_FN02(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 3: //����ͨ��ģ�鱨��ͨ�Ų���
            return AFN04_FN03(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        default:
            break;
    }

    pcb(pline_head);
    pcb("ERROR:��֧�ֵ�FN!");
    pcb(pline_end);

    return -ERR_AFN_FN;
}

/*--------------------------------AFN04.c------------------------------------*/
