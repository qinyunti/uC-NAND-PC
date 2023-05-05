#include <stdio.h>

#include "fs_dev_nand.h"
#include "fs_dev_nand_ctrlr_gen.h"
#include "fs_dev_nand_ctrlr_gen_soft_ecc.h"
#include "fs_dev_nand_part_static.h"
#include "ecc_hamming.h"

static  const  FS_NAND_FREE_SPARE_DATA  App_FS_NAND_FreeSpareMap[] = {{1,                   63},
                                                                      {(FS_NAND_PG_SIZE)-1, (FS_NAND_PG_SIZE)-1}};

uint8_t rd_buffer[512 * 10];
uint8_t wr_buffer[512 * 10];

extern const  FS_NAND_CTRLR_GEN_BSP_API  FS_NAND_BSP_TEMPLATE;

int main(int argc, char* argv[])
{
    int i;
    FS_ERR  err;
    FS_DEV  dev;
    const CPU_CHAR* name;

    memset(rd_buffer, 0, sizeof(rd_buffer));
    memset(wr_buffer, 0, sizeof(wr_buffer));
    /* NAND */
    FS_NAND_CFG nand_cfg=
    {
        .BSPPtr = (void*)&FS_NAND_BSP_TEMPLATE,
        .CtrlrPtr = DEF_NULL,     /**< 后面配置为FS_NAND_CtrlrGen          */
        .CtrlrCfgPtr = DEF_NULL,  /**< 后面配置为ctrlr_cfg                 */
        .PartPtr = DEF_NULL,      /**< 后面配置为FS_NAND_PartStatic        */
        .PartCfgPtr = DEF_NULL,   /**< 后面配置为part_cfg                  */
        .SecSize    = 512,        /**< sector 大小 单位字节                */
        .BlkCnt     = 1024,       /**< block数量                          */
        .BlkIxFirst = 0,          /**< block开始索引                      */
        .UB_CntMax  = 10,
        .RUB_MaxAssoc = 2,
        .AvailBlkTblEntryCntMax = FS_NAND_CFG_RSVD_AVAIL_BLK_CNT+1,    /* 设置为FS_NAND_CFG_DEFAULT(0)则选择10和FS_NAND_CFG_RSVD_AVAIL_BLK_CNT(3)+1的最大值,否则不能设置为小于FS_NAND_CFG_RSVD_AVAIL_BLK_CNT(3)+1的值 */
    };

    /* CTRLLR */
    FS_NAND_CTRLR_GEN_CFG           ctrlr_cfg;
    nand_cfg.CtrlrPtr          = (FS_NAND_CTRLR_API *)&FS_NAND_CtrlrGen;
    nand_cfg.CtrlrCfgPtr       = &ctrlr_cfg;

    /* ECC */
    FS_NAND_CTRLR_GEN_SOFT_ECC_CFG  soft_ecc_cfg;
    ctrlr_cfg.CtrlrExt         = &FS_NAND_CtrlrGen_SoftECC;
    ctrlr_cfg.CtrlrExtCfg      = &soft_ecc_cfg;
    soft_ecc_cfg.ECC_ModulePtr = &Hamming_ECC;

    /* PART */
    FS_NAND_PART_STATIC_CFG         part_cfg=
    {
        .BlkCnt = 1024,                                      /**< 1024个block                        */
        .PgPerBlk = 64,                                      /**< 每个block有64个page                 */
        .PgSize = 2048,                                      /**< PAGE大小 单位字节                   */
        .SpareSize= 64,                                      /**< 每个page额外的空间                  */
        .NbrPgmPerPg=4,                                      /**< 一个PAGE分几次编程,即分为几个sector  */
        .BusWidth = 8,                                       /**< 总线宽度SPI接口用不上  如果设置为16则App_FS_NAND_FreeSpareMap的偏移必须为偶数             */
        .ECC_NbrCorrBits = 1,                                /**<                                    */
        .ECC_CodewordSize =  528,                            /**<                                    */
        .DefectMarkType = DEFECT_SPARE_L_1_PG_1_OR_2,        /**<                                    */
        .MaxBadBlkCnt   = 40,                                                  /**< 设备中容许最大的坏块数             */
        .MaxBlkErase    = 100000,                                              /**< 块允许最大的擦除次数               */
        .FreeSpareMap   = (FS_NAND_FREE_SPARE_DATA*)App_FS_NAND_FreeSpareMap   /**<                                  */
    };
    nand_cfg.PartPtr           = (FS_NAND_PART_API *)&FS_NAND_PartStatic;
    nand_cfg.PartCfgPtr        = &part_cfg;

    printf("nand test\r\n");
    name = FS_NAND_NameGet();
    printf("NAME:%s\r\n", name);

    FS_NAND_Init(&err);
    if(err != FS_ERR_NONE)
    {
        printf("FS_NAND_Init err %d\r\n",err);
    }
    else
    {
        printf("FS_NAND_Init ok\r\n");
    }

    FS_NAND_Open (&dev, &nand_cfg, &err);
    if(err != FS_ERR_NONE)
    {
        printf("FS_NAND_Open err %d\r\n",err);
        if ((FS_ERR_DEV_INVALID_LOW_FMT == err) || (FS_ERR_DEV_CORRUPT_LOW_FMT == err))
        {
            FS_NAND_IO_Ctrl(&dev,FS_DEV_IO_CTRL_LOW_FMT,DEF_NULL,&err);
            if (err == FS_ERR_NONE) {
                printf("FS_DEV_IO_CTRL_LOW_FMT ok\r\n");
                FS_NAND_IO_Ctrl(&dev, FS_DEV_IO_CTRL_REFRESH, DEF_NULL, &err);
                if (err == FS_ERR_NONE) {
                    printf("FS_DEV_IO_CTRL_REFRESH ok\r\n");
                }
                else 
                {
                    printf("FS_DEV_IO_CTRL_REFRESH err %d\r\n", err);
                }
            }
            else 
            {
                printf("FS_DEV_IO_CTRL_LOW_FMT err %d\r\n", err);
            }
        }
        else 
        {
            //return -1;
        }
    }
    else
    {
        printf("FS_NAND_Open ok\r\n");
    }

    for (i = 0; i < sizeof(wr_buffer) / sizeof(wr_buffer[0]);  i++)
    {   
        wr_buffer[i] = i;
    }
    FS_NAND_Wr(&dev, wr_buffer, 0, 10, &err);
    if (err != FS_ERR_NONE)
    {
        printf("FS_NAND_Wr err %d\r\n", err);
    }
    else
    {
        printf("FS_NAND_Wr ok\r\n");
    }

    FS_NAND_Rd(&dev, rd_buffer, 0, 10, &err);
    if (err != FS_ERR_NONE)
    {
        printf("FS_NAND_Rd err %d\r\n", err);
    }
    else
    {
        printf("FS_NAND_Rd ok\r\n");
    }

    for (i = 0; i < sizeof(wr_buffer) / sizeof(wr_buffer[0]);  i++)
    {
        if (wr_buffer[i] != rd_buffer[i]) 
        {
            printf("test err\r\n");
            break;
        }
    }
    if (i == sizeof(wr_buffer) / sizeof(wr_buffer[0])) 
    {
        printf("test ok\r\n");
    }
    FS_NAND_Close(&dev);

//FS_NAND_Rd
//FS_NAND_Wr
//FS_NAND_Query
//FS_NAND_IO_Ctrl
    while(1);
    return 0;
}