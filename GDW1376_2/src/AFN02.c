/**
 ******************************************************************************
 * @file      AFN02.c
 * @brief     C Source file of AFN02.c.
 * @details   This file including all API functions's implement of AFN02.c.
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
 * @brief   ���ת��ͨ��Э������֡�����ַ���
 * @param[in]   dir         : ���䷽��:1����(ģ��->������)" 0����(������->ģ��)
 * @param[in]  *pin         : ���뱨��
 * @param[in]   len         : Ӧ�ò㱨�ĳ���
 * @param[in]  *pcb         : �ص�����
 * @param[in]  *pline_head  : ÿ����ʼ����ַ���
 * @param[in]  *pline_end   : ÿ�н�������ַ���
 *
 * @retval  ����������
 ******************************************************************************
 */
static int
AFN02_FN01(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;

    CHK_APP_LEN(len, pin[1] + 2);

    pcb(pline_head);
    pcb("ת��ͨ��Э������֡:");
    pcb(pline_end);
    pcb(pline_head);
    pcb(" Э������:");
    switch (pin[0])
    {
        case 0x00:
            pcb("͸������");
            break;
        case 0x01:
            pcb("DL/T645-1997");
            break;
        case 0x02:
            pcb("DL/T645-2007");
            break;
        case 0x03:
            pcb("DL/T698.45");
            break;
        default:
            pcb("����");
            break;
    }
    pcb(pline_end);
    sprintf(buf, "%s ���ĳ���:%d", pline_head, pin[1]);
    pcb(buf);

    CHK_APP_LEN(len, pin[1] + 2);
    pcb(pline_end);

    pcb(pline_head);
    pcb(" ��������:");
    pcb(pline_end);
    pcb(pline_head);
    for (i = 0; i < pin[1]; i++)
    {
        sprintf(buf, "%02X ", pin[i + 2]);
        pcb(buf);
        if (((i + 1) % 16) == 0)
        {
            pcb(pline_end);
            pcb(pline_head);
        }
    }
    pcb(pline_end);

    return 0;
}

/**
 ******************************************************************************
 * @brief   �������ת�������ַ���
 * @param[in]   dir         : ���䷽��:1����(ģ��->������)" 0����(������->ģ��)
 * @param[in]  *pin         : ���뱨��
 * @param[in]   len         : Ӧ�ò㱨�ĳ���
 * @param[in]  *pcb         : �ص�����
 * @param[in]  *pline_head  : ÿ����ʼ����ַ���
 * @param[in]  *pline_end   : ÿ�н�������ַ���
 *
 * @retval  ����������
 ******************************************************************************
 */
int
print_AFN02(unsigned char dir,
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
        case 1: //ת��ͨ��Э������֡
            return AFN02_FN01(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        default:
            break;
    }

    pcb(pline_head);
    pcb("ERROR:��֧�ֵ�FN!");
    pcb(pline_end);

    return -ERR_AFN_FN;
}

/*--------------------------------AFN02.c------------------------------------*/
