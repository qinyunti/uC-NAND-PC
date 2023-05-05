/*
*********************************************************************************************************
*                                                uC/CRC
*           ERROR DETECTING CODE (EDC) & ERROR CORRECTING CODE (ECC) CALCULATION UTILITIES
*
*                    Copyright 2007-2020 Silicon Laboratories Inc. www.silabs.com
*
*                                 SPDX-License-Identifier: APACHE-2.0
*
*               This software is subject to an open source license and is distributed by
*                Silicon Laboratories Inc. pursuant to the terms of the Apache License,
*                    Version 2.0 available at www.apache.org/licenses/LICENSE-2.0.
*
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                         CONFIGURATION FILE
*
*                                              TEMPLATE
*
* Filename : crc_cfg.h
* Version  : V1.10.00
*********************************************************************************************************
*/

#ifndef  CRC_CFG_H
#define  CRC_CFG_H

#include <stdint.h>
#include <stddef.h>

/*
*********************************************************************************************************
*                                                 PORT
*
* Note(s) : (1) 以下添加依赖部分移植
*               
*
*********************************************************************************************************
*/

                                                        /* ------------------ CPU WORD-ENDIAN ORDER ------------------- */
#define  CPU_ENDIAN_TYPE_NONE                      0u
#define  CPU_ENDIAN_TYPE_BIG                       1u   /* Big-   endian word order (see Note #1a).                     */
#define  CPU_ENDIAN_TYPE_LITTLE                    2u   /* Little-endian word order (see Note #1b).                     */

#define  CPU_CFG_ENDIAN_TYPE            CPU_ENDIAN_TYPE_LITTLE

typedef  uint8_t        CPU_BOOLEAN;                     /*  8-bit boolean or logical                            */
typedef  uint8_t        CPU_INT08U;                      /*  8-bit unsigned integer                              */
typedef  uint16_t       CPU_INT16U;                      /* 16-bit unsigned integer                              */
typedef  uint32_t       CPU_INT32U;                      /* 32-bit unsigned integer                              */
typedef  size_t      CPU_ADDR;                                  /* CPU address type based on address bus size.          */
typedef  size_t      CPU_DATA;																	/* CPU data    type based on data    bus size.          */
typedef  CPU_ADDR    CPU_SIZE_T;                                /* Defines CPU standard 'size_t'   size.                */

#define  CPU_WORD_SIZE_32                          				 4u   /* 32-bit word size (in octets).                                */


                                                                /* ----------------- BOOLEAN DEFINES ------------------ */
#ifndef DEF_NO
#define  DEF_NO                                            0u
#endif
#ifndef DEF_YES
#define  DEF_YES                                           1u
#endif
#ifndef DEF_DISABLED
#define  DEF_DISABLED                                      0u
#endif
#ifndef DEF_ENABLED
#define  DEF_ENABLED                                       1u
#endif
#ifndef DEF_INVALID
#define  DEF_INVALID                                       0u
#endif
#ifndef DEF_VALID
#define  DEF_VALID                                         1u
#endif

#define  DEF_OCTET_NBR_BITS                                8u
#define  DEF_BIT(bit)                                                   (1uL << (bit))

                                                                /* ------------------- BIT DEFINES -------------------- */
#define  DEF_BIT_00                                     0x01u
#define  DEF_BIT_01                                     0x02u
#define  DEF_BIT_02                                     0x04u
#define  DEF_BIT_03                                     0x08u
#define  DEF_BIT_04                                     0x10u
#define  DEF_BIT_05                                     0x20u
#define  DEF_BIT_06                                     0x40u
#define  DEF_BIT_07                                     0x80u
#define  DEF_BIT_08                                   0x0100u
#define  DEF_BIT_09                                   0x0200u
#define  DEF_BIT_10                                   0x0400u
#define  DEF_BIT_11                                   0x0800u
#define  DEF_BIT_12                                   0x1000u
#define  DEF_BIT_13                                   0x2000u
#define  DEF_BIT_15                                   0x8000u
#define  DEF_BIT_17                               0x00020000u
#define  DEF_BIT_19                               0x00080000u
#define  DEF_BIT_21                               0x00200000u
#define  DEF_BIT_23                               0x00800000u
#define  DEF_BIT_25                               0x02000000u
#define  DEF_BIT_27                               0x08000000u
#define  DEF_BIT_29                               0x20000000u
#define  DEF_BIT_31                               0x80000000u


#define  DEF_BIT_SET(val, mask)                        ((val) = ((val) | (mask)))

#define  DEF_BIT_IS_SET(val, mask)                    (((((val) & (mask)) == (mask)) && ((mask) != 0u)) ? (DEF_YES) : (DEF_NO))

#define  CPU_SW_EXCEPTION(err_rtn_val)              do {                    \
                                                        ;									  \
                                                    } while (1)


#define  MEM_VAL_COPY_GET_INT32U(addr_dest, addr_src)   do {                                                                             \
                                                                   CPU_INT08U  *destptr = (CPU_INT08U *)(addr_dest);                            \
                                                                   CPU_INT08U  *srcptr  = (CPU_INT08U *)(addr_src);                             \
                                                                   (*((destptr) + 0))   = (*((srcptr) + 0));                                    \
                                                                   (*((destptr) + 1))   = (*((srcptr) + 1));                                    \
                                                                   (*((destptr) + 2))   = (*((srcptr) + 2));                                    \
                                                                   (*((destptr) + 3))   = (*((srcptr) + 3)); } while (0)												

#define  MEM_VAL_COPY_GET_INTU(addr_dest, addr_src, val_size)    do {                                                                                  \
                                                                            CPU_SIZE_T  _i;                                                                   \
                                                                                                                                                              \
                                                                            for (_i = 0; _i < (val_size); _i++) {                                             \
                                                                                (*(((CPU_INT08U *)(addr_dest)) + _i)) = (*(((CPU_INT08U *)(addr_src)) + _i)); \
                                                                            }                                                                                 \
                                                                        } while (0)

#define  MEM_VAL_COPY_SET_INT32U(addr_dest, addr_src)    MEM_VAL_COPY_GET_INT32U(addr_dest, addr_src)
/*
*********************************************************************************************************
*                                                 EDC
*
* Note(s) : (1) Configure EDC_CRC_CFG_ERR_ARG_CHK_EXT_EN to enable/disable the CRC external argument
*               check feature
*
*           (2) Configure EDC_CRC_CFG_OPTIMIZE_ASM_EN to enable/disable optimized assembly-language
*               calculation.
*
*           (3) Each of these determine whether the associated table of pre-computed CRC values will
*               be included in the build.  For more information about the tables, the meaning of the
*               identifiers, and how these are used, please refer to the documentation.
*********************************************************************************************************
*/

#define  EDC_CRC_CFG_ERR_ARG_CHK_EXT_EN          DEF_ENABLED    /* See Note #1.                                         */
#define  EDC_CRC_CFG_OPTIMIZE_ASM_EN             DEF_DISABLED   /* See Note #2.                                         */

#define  EDC_CRC_CFG_CRC16_1021_EN               DEF_ENABLED    /* See Note #3.                                         */
#define  EDC_CRC_CFG_CRC16_8005_EN               DEF_ENABLED
#define  EDC_CRC_CFG_CRC16_8048_EN               DEF_ENABLED
#define  EDC_CRC_CFG_CRC32_EN                    DEF_ENABLED
#define  EDC_CRC_CFG_CRC16_1021_REF_EN           DEF_ENABLED
#define  EDC_CRC_CFG_CRC16_8005_REF_EN           DEF_ENABLED
#define  EDC_CRC_CFG_CRC16_8048_REF_EN           DEF_ENABLED
#define  EDC_CRC_CFG_CRC32_REF_EN                DEF_ENABLED

/*
*********************************************************************************************************
*                                                 ECC
*
* Note(s) : (1) Configure ECC_HAMMING_CFG_ARG_CHK_EXT_EN to enable/disable the Hamming code external
*               argument check feature
*
*********************************************************************************************************
*/

#define  ECC_HAMMING_CFG_ARG_CHK_EXT_EN          DEF_ENABLED    /* See Note #1.                                         */

																																
#endif
