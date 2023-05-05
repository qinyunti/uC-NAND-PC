#ifndef  NAND_PORT_H
#define  NAND_PORT_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#define CPU_SR_ALLOC()
#define CPU_CRITICAL_ENTER()
#define CPU_CRITICAL_EXIT()

#define FS_TRACE_LOG(msg) printf msg
#define FS_TRACE_DBG(msg) printf msg 
#define FS_TRACE_INFO(msg) printf msg



#define  CPU_SW_EXCEPTION(err_rtn_val)              do {                    \
                                                        ;									  \
                                                    } while (1)

#define  FS_CFG_MAX_DEV_NAME_LEN                           15u
#define  FS_ERR_DEV_INVALID                               310u
#define  FS_ERR_NULL_PTR                                   19u
#define  FS_ERR_NONE                                        0u
#define  FS_ERR_MEM_ALLOC                                  17u
#define  FS_ERR_DEV_INVALID_CFG                           311u
#define  FS_DEV_IO_CTRL_LOW_FMT                             2u				
#define  FS_ERR_DEV_INVALID_LOW_PARAMS                    315u
#define  FS_ERR_DEV_NAND_NO_AVAIL_BLK                     350u
#define  FS_ERR_DEV_INVALID_ECC                           312u
#define  FS_ERR_ECC_CRITICAL_CORR                         601u
#define  FS_ERR_ECC_UNCORR                                602u
#define  FS_ERR_INVALID_ARG                                10u		
#define  FS_ERR_DEV_TIMEOUT                               327u
#define  FS_ERR_DEV_INVALID_IO_CTRL                       313u
#define  FS_ERR_DEV_INVALID_LOW_FMT                       314u																										
#define  FS_ERR_DEV_INCOMPATIBLE_LOW_PARAMS               332u		
#define  FS_ERR_DEV_CORRUPT_LOW_FMT                       335u		
#define  FS_ERR_NAME_NULL                                 905u			
#define  FS_ERR_DEV_NAND_NO_SUCH_SEC                      351u 			
#define  FS_ERR_DEV_IO                                    323u
#define  FS_ERR_DEV_INVALID_METADATA                      333u
#define  FS_ERR_DEV_INVALID_OP                            318u
#define  FS_ERR_DEV_OP_ABORTED                            334u
#define  FS_ERR_DEV_INVALID_SIZE                          321u
#define  FS_ERR_ECC_CORR                                  600u
#define  FS_ERR_DEV_FULL                                  304u
#define  FS_ERR_DEV_OP_FAILED                             338u
#define  LIB_MEM_ERR_NONE                               10000u
#define  LIB_MEM_ERR_HEAP_EMPTY                         10210u

#define  DEF_INT_CPU_NBR_BITS                           (4 * 8)
#define  DEF_INT_CPU_U_MAX_VAL                      4294967295u

#define  DEF_INT_08_NBR_BITS                               8u
#define  DEF_INT_08U_MAX_VAL                             255u
#define  DEF_OCTET_MASK                                 0xFFu
#define  CRC_UTIL_POPCNT_MASK01010101_32  				0x55555555u
#define  CRC_UTIL_POPCNT_MASK00110011_32          0x33333333u
#define  CRC_UTIL_POPCNT_MASK00001111_32          0x0F0F0F0Fu

#define  DEF_BIT_00                                     0x01u
#define  DEF_BIT_01                                     0x02u
#define  DEF_BIT_02                                     0x04u
#define  DEF_BIT_06                                     0x40u

/*
*********************************************************************************************************
*                                     DEVICE I/O CONTROL DEFINES
*********************************************************************************************************
*/

                                                                /* ------------------ GENERIC OPTIONS ----------------- */
#define  FS_DEV_IO_CTRL_REFRESH                            1u   /* Refresh dev.                                         */
#define  FS_DEV_IO_CTRL_LOW_FMT                            2u   /* Low-level fmt dev.                                   */
#define  FS_DEV_IO_CTRL_LOW_MOUNT                          3u   /* Low-level mount dev.                                 */
#define  FS_DEV_IO_CTRL_LOW_UNMOUNT                        4u   /* Low-level unmount dev.                               */
#define  FS_DEV_IO_CTRL_LOW_COMPACT                        5u   /* Low-level compact dev.                               */
#define  FS_DEV_IO_CTRL_LOW_DEFRAG                         6u   /* Low-level defrag dev.                                */
#define  FS_DEV_IO_CTRL_SEC_RELEASE                        7u   /* Release data in sec.                                 */
#define  FS_DEV_IO_CTRL_PHY_RD                             8u   /* Read  physical dev.                                  */
#define  FS_DEV_IO_CTRL_PHY_WR                             9u   /* Write physical dev.                                  */
#define  FS_DEV_IO_CTRL_PHY_RD_PAGE                       10u   /* Read  physical dev page.                             */
#define  FS_DEV_IO_CTRL_PHY_WR_PAGE                       11u   /* Write physical dev page.                             */
#define  FS_DEV_IO_CTRL_PHY_ERASE_BLK                     12u   /* Erase physical dev blk.                              */
#define  FS_DEV_IO_CTRL_PHY_ERASE_CHIP                    13u   /* Erase physical dev.                                  */
#define  FS_DEV_IO_CTRL_RD_SEC                            14u   /* Read  physical dev sector.                           */
#define  FS_DEV_IO_CTRL_WR_SEC                            15u   /* Write physical dev sector.                           */
#define  FS_DEV_IO_CTRL_SYNC                              16u   /* Sync dev.                                            */
#define  FS_DEV_IO_CTRL_CHIP_ERASE                        17u   /* Erase all data on phy dev.                           */

                                                                /* ------------ SD-DRIVER SPECIFIC OPTIONS ------------ */
#define  FS_DEV_IO_CTRL_SD_QUERY                          64u   /* Get info about SD/MMC card.                          */
#define  FS_DEV_IO_CTRL_SD_RD_CID                         65u   /* Read SD/MMC card Card ID reg.                        */
#define  FS_DEV_IO_CTRL_SD_RD_CSD                         66u   /* Read SD/MMC card Card-Specific Data reg.             */

                                                                /* ----------- NAND-DRIVER SPECIFIC OPTIONS ----------- */
#define  FS_DEV_IO_CTRL_NAND_PARAM_PG_RD                  80u   /* Read parameter-page from ONFI device.                */
#define  FS_DEV_IO_CTRL_NAND_DUMP                         81u   /* Dump raw NAND dev.                                   */

#define  DEF_ENABLED                                         1
#define  DEF_DISABLED                                        0																						
#define  DEF_YES                                             1
#define  DEF_NO                                              0	
#define  DEF_OK                                              1			

#define  DEF_OCTET_NBR_BITS                                8u
#define  DEF_BIT(bit)                                                   (1uL << (bit))
#define  FS_CHAR_DEV_SEP                                   ':'					

#define  DEF_BIT_SET(val, mask)                        ((val) = ((val) | (mask)))
#define  DEF_BIT_SET_08(val, mask)                     (CPU_INT08U)DEF_BIT_SET((val), (CPU_INT08U)(mask))
#define  DEF_BIT_CLR_08(val, mask)                     ((val) = (CPU_INT08U)(((CPU_INT08U)(val)) & (CPU_INT08U)(~((CPU_INT08U)(mask)))))

#define  DEF_BIT_FIELD(bit_field, bit_shift)                                 ((((bit_field) >= DEF_INT_CPU_NBR_BITS) ? (DEF_INT_CPU_U_MAX_VAL)     \
                                                                                                                     : (DEF_BIT(bit_field) - 1uL)) \
                                                                                                                            << (bit_shift))

#define  DEF_GET_U_MAX_VAL(obj)                 ((sizeof(obj) == 1u) ? 255u :    \
                                                ((sizeof(obj) == 2u) ? 65535u :    \
                                                ((sizeof(obj) == 4u) ? 4294967295u : 0)))
																									
																							
#define  FS_UTIL_IS_PWR2(nbr)                     ((((nbr) != 0u) && (((nbr) & ((nbr) - 1u)) == 0u)) ? DEF_YES : DEF_NO)																								
#define  DEF_MAX(a,b)  ((a)>(b)?(a):(b))
typedef  uint8_t        CPU_BOOLEAN;                     /*  8-bit boolean or logical                            */
typedef  uint8_t        CPU_INT08U;                      /*  8-bit unsigned integer                              */
typedef  uint16_t       CPU_INT16U;                      /* 16-bit unsigned integer                              */
typedef  int16_t        CPU_INT16S;
typedef  uint32_t       CPU_INT32U;                      /* 32-bit unsigned integer                              */
typedef  int32_t        CPU_INT32S;                      /* 32-bit   signed integer                              */																							
typedef  size_t      CPU_ADDR;                                  /* CPU address type based on address bus size.          */
typedef  size_t      CPU_DATA;																	/* CPU data    type based on data    bus size.          */
typedef  CPU_ADDR    CPU_SIZE_T;                                /* Defines CPU standard 'size_t'   size.                */

#define  CPU_WORD_SIZE_32                          				 4u   /* 32-bit word size (in octets).                                */
#define  DEF_NULL    (void*)0  
typedef  CPU_INT08U  CPU_CHAR;
typedef  CPU_INT16U  FS_QTY;
typedef  CPU_INT32U  FS_SEC_QTY;
typedef  FS_SEC_QTY  FS_SEC_NBR;
typedef  CPU_INT32U  FS_SEC_SIZE;
typedef  CPU_INT32U  FS_ERR;
typedef  CPU_INT32U  FS_CTR;                                    /* Defines   max nbr of errs/stats to cnt.              */
typedef  CPU_INT16U  FS_STATE;
typedef  CPU_INT32U  FS_ID;
typedef  struct  fs_dev              FS_DEV;
typedef  struct  fs_dev_api          FS_DEV_API;
typedef  CPU_INT32U  LIB_ERR;

#define  CPU_CFG_DATA_SIZE              CPU_WORD_SIZE_32  
#define  DEF_INT_CPU_NBR_BITS_MAX                       (CPU_CFG_DATA_SIZE_MAX * DEF_OCTET_NBR_BITS)

#define  DEF_BIT08(bit)                        ((CPU_INT08U)((CPU_INT08U)1u  << (bit)))

#define  FS_CFG_BUF_ALIGN_OCTETS                 sizeof(CPU_DATA)

#define  DEF_BIT_IS_SET(val, mask)                    (((((val) & (mask)) == (mask)) && ((mask) != 0u)) ? (DEF_YES) : (DEF_NO))

#define  DEF_BIT_FIELD_08(bit_field, bit_shift)     ((CPU_INT08U)((((CPU_INT08U)(bit_field) >= (CPU_INT08U)DEF_INT_08_NBR_BITS) ? (CPU_INT08U)(DEF_INT_08U_MAX_VAL)                    \
                                                                                                                                : (CPU_INT08U)(DEF_BIT08(bit_field) - (CPU_INT08U)1u)) \
                                                                                                                                                     << (bit_shift)))

typedef  struct  fs_dev_info {
    FS_STATE      State;                                        /* Device state.                                        */
    FS_SEC_QTY    Size;                                         /* Size of dev (in secs).                               */
    FS_SEC_SIZE   SecSize;                                      /* Size of dev sec.                                     */
    CPU_BOOLEAN   Fixed;                                        /* Indicates whether device is fixed or removable.      */
} FS_DEV_INFO;

struct  fs_dev_api {
    const  CPU_CHAR  *(*NameGet)           (void);                        /* Get base name of driver.                             */

    void              (*Init)              (FS_ERR       *p_err);         /* Initialize driver.                                   */

    void              (*Open)              (FS_DEV       *p_dev,          /* Open        a  device instance.                      */
                                            void         *p_dev_cfg,
                                            FS_ERR       *p_err);

    void              (*Close)             (FS_DEV       *p_dev);         /* Close       a  device instance.                      */

    void              (*Rd)                (FS_DEV       *p_dev,          /* Read from   a  device instance.                      */
                                            void         *p_dest,
                                            FS_SEC_NBR    start,
                                            FS_SEC_QTY    cnt,
                                            FS_ERR       *p_err);

#if (FS_CFG_RD_ONLY_EN == DEF_DISABLED)
    void              (*Wr)                (FS_DEV       *p_dev,          /* Write to    a  device instance.                      */
                                            void         *p_src,
                                            FS_SEC_NBR    start,
                                            FS_SEC_QTY    cnt,
                                            FS_ERR       *p_err);
#endif

    void              (*Query)             (FS_DEV       *p_dev,          /* Get info about device instance.                      */
                                            FS_DEV_INFO  *p_dev_info,
                                            FS_ERR       *p_err);

    void              (*IO_Ctrl)           (FS_DEV       *p_dev,          /* Ctrl req to a  device instance.                      */
                                            CPU_INT08U    opt,
                                            void         *p_data,
                                            FS_ERR       *p_err);
};



struct  fs_dev {
    FS_ID          ID;                                          /* Dev ID.                                              */
    FS_STATE       State;                                       /* State.                                               */
    FS_CTR         RefCnt;                                      /* Ref cnts.                                            */
    FS_CTR         RefreshCnt;                                  /* Refresh cnts.                                        */

    CPU_CHAR       Name[FS_CFG_MAX_DEV_NAME_LEN + 1u];          /* Dev name.                                            */
    FS_QTY         UnitNbr;                                     /* Dev unit nbr.                                        */
    FS_SEC_QTY     Size;                                        /* Size of dev (in secs).                               */
    FS_SEC_SIZE    SecSize;                                     /* Size of dev sec.                                     */
    CPU_BOOLEAN    Fixed;                                       /* Indicates whether device is fixed or removable.      */

    FS_QTY         VolCnt;                                      /* Nbr of open vols on this dev.                        */

    FS_DEV_API    *DevDrvPtr;                                   /* Ptr to dev drv for this dev.                         */
    void          *DataPtr;                                     /* Ptr to data specific for a device driver.            */

#if (FS_CFG_CTR_STAT_EN == DEF_ENABLED)
    FS_CTR         StatRdSecCtr;                                /* Nbr rd secs.                                         */
    FS_CTR         StatWrSecCtr;                                /* Nbr wr secs.                                         */
#endif

};

#if (FS_CFG_CTR_ERR_EN == DEF_ENABLED)                          /* ------------------ ERR CTR MACRO'S ----------------- */

#define  FS_CTR_ERR_INC(err_ctr)                                FS_CTR_INC(err_ctr)

#else

#define  FS_CTR_ERR_CLR(err_ctr);

#define  FS_CTR_ERR_INC(err_ctr)

#endif

#if (FS_CFG_CTR_STAT_EN == DEF_ENABLED)                         /* ----------------- STAT CTR MACRO'S ----------------- */

#define  FS_CTR_STAT_INC(stat_ctr)                              FS_CTR_INC(stat_ctr)
#define  FS_CTR_STAT_ADD(stat_ctr, val)                         FS_CTR_ADD((stat_ctr), (val))

#else

#define  FS_CTR_STAT_INC(stat_ctr)
#define  FS_CTR_STAT_ADD(stat_ctr, val)

#endif

#define  DEF_OCTET_TO_BIT_NBR_BITS                         3u
#define  DEF_OCTET_TO_BIT_SHIFT                          DEF_OCTET_TO_BIT_NBR_BITS
#define  DEF_OCTET_TO_BIT_MASK                          0x07u
#define  FS_UTIL_BIT_NBR_TO_OCTET_NBR(bit_nbr)                ( ((bit_nbr) >> DEF_OCTET_TO_BIT_SHIFT) + \
                                                               (((bit_nbr) &  DEF_OCTET_TO_BIT_MASK) == 0u ? 0u : 1u))

#define  MEM_VAL_COPY_GET_INTU_LITTLE(addr_dest, addr_src, val_size)    do {                                                                                  \
                                                                            CPU_SIZE_T  _i;                                                                   \
                                                                                                                                                              \
                                                                            for (_i = 0; _i < (val_size); _i++) {                                             \
                                                                                (*(((CPU_INT08U *)(addr_dest)) + _i)) = (*(((CPU_INT08U *)(addr_src)) + _i)); \
                                                                            }                                                                                 \
                                                                        } while (0)

#define  MEM_VAL_COPY_GET_INT32U_LITTLE(addr_dest, addr_src)   do {                                                                             \
                                                                   CPU_INT08U  *destptr = (CPU_INT08U *)(addr_dest);                            \
                                                                   CPU_INT08U  *srcptr  = (CPU_INT08U *)(addr_src);                             \
                                                                   (*((destptr) + 0))   = (*((srcptr) + 0));                                    \
                                                                   (*((destptr) + 1))   = (*((srcptr) + 1));                                    \
                                                                   (*((destptr) + 2))   = (*((srcptr) + 2));                                    \
                                                                   (*((destptr) + 3))   = (*((srcptr) + 3)); } while (0)																																			

#define  MEM_VAL_COPY_SET_INTU_LITTLE(addr_dest, addr_src, val_size)    MEM_VAL_COPY_GET_INTU_LITTLE((addr_dest), (addr_src), (val_size))

#define  FS_UTIL_BITMAP_LOC_GET(bit_pos, octet_loc, bit_loc)    do {                                                    \
                                                                    (bit_loc)   = (bit_pos)  & DEF_OCTET_TO_BIT_MASK;   \
                                                                    (octet_loc) = (bit_pos) >> DEF_OCTET_TO_BIT_SHIFT;  \
                                                                } while (0)

#define  FS_ERR_CHK_EMPTY_RTN_ARG

#define  FS_ERR_CHK_RTNEXPR(call, callOnError, retExpr)  call; \
                                                         if (*p_err != FS_ERR_NONE) { \
                                                             callOnError; \
                                                             return retExpr; \
                                                         }

#define  FS_ERR_CHK_RTN(call, callOnError, retVal)       FS_ERR_CHK_RTNEXPR(call, callOnError, (retVal))

#define  FS_ERR_CHK(call, callOnError)                   FS_ERR_CHK_RTNEXPR(call, callOnError, FS_ERR_CHK_EMPTY_RTN_ARG)

void *Mem_HeapAlloc(CPU_SIZE_T size,CPU_SIZE_T align,CPU_SIZE_T *p_bytes_reqd, LIB_ERR *p_err);
CPU_INT16S  Str_Cmp_N (const  CPU_CHAR    *p1_str, const  CPU_CHAR    *p2_str, CPU_SIZE_T   len_max);
CPU_INT08U  FSUtil_Log2 (CPU_INT32U  val);
void  FSUtil_MapBitSet (CPU_INT08U  *p_bitmap, CPU_SIZE_T   offset_bit);
void  FSUtil_MapBitClr (CPU_INT08U  *p_bitmap, CPU_SIZE_T   offset_bit);
CPU_BOOLEAN  FSUtil_MapBitIsSet (CPU_INT08U  *p_bitmap, CPU_SIZE_T   offset_bit);
void  FSUtil_ValPack32 (CPU_INT08U  *p_dest,
                        CPU_SIZE_T  *p_offset_octet,
                        CPU_DATA    *p_offset_bit,
                        CPU_INT32U   val,
                        CPU_DATA     nbr_bits);
CPU_INT08U  NAND_CRCUtil_PopCnt_32 (CPU_INT32U  value);
CPU_INT32U  FSUtil_ValUnpack32 (CPU_INT08U  *p_src,
                                CPU_SIZE_T  *p_offset_octet,
                                CPU_DATA    *p_offset_bit,
                                CPU_DATA     nbr_bits);
CPU_DATA  CPU_CntTrailZeros32 (CPU_INT32U  val);
#endif