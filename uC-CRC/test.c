#include <stdio.h>
#include <stdint.h>
#include "ecc_hamming.h"

#include "rtthread.h"

typedef struct
{
	ECC_ERR err;
	char* str;
}err_str;

err_str s_err_str[]=
{
	{ECC_ERR_NONE,"No error."},
	{ECC_ERR_CORRECTABLE,"Correctable error detected in data."},
	{ECC_ERR_ECC_CORRECTABLE,"Correctable error detected in ECC."},
	{ECC_ERR_INVALID_ARG,"Argument passed invalid value. "},
	{ECC_ERR_INVALID_LEN,"Len argument passed invalid length."},
	{ECC_ERR_NULL_PTR,"Pointer argument passed NULL pointer."},
	{ECC_ERR_UNCORRECTABLE,"Uncorrectable error detected in data."}
};
		
uint8_t s_buffer[33];
uint8_t s_ecc[4];

int ecc_main(int argc, char* argv[])
{
	CPU_INT08U ecc[4];
	ECC_ERR_LOC err_loc[2]={{0,0},{0,0}};
	ECC_ERR err;
	for(int i=0; i< sizeof(s_buffer)/sizeof(s_buffer[0]); i++)
  {
		s_buffer[i] = i+1;
	}
	
	/* 打印原始数据 */
	for(int i=0; i< sizeof(s_buffer)/sizeof(s_buffer[0]); i++)
  {
		if(i % 16 == 0)
    {
			rt_kprintf("\r\n");
		}
		rt_kprintf("%#x ",s_buffer[i]);
	}
	rt_kprintf("\r\n");
	
	CPU_SIZE_T len = (sizeof(s_buffer)/sizeof(s_buffer[0]));
	CPU_SIZE_T len_buf     = (len / 32)*32;
	CPU_SIZE_T len_buf_ext = len % 32;
	CPU_INT08U* p_buf_ext   = (CPU_INT08U *)s_buffer + len_buf;
	Hamming_Calc(s_buffer,len_buf,p_buf_ext,len_buf_ext,s_ecc,&err);
	if(ECC_ERR_NONE != err)
  {
		rt_kprintf("Hamming_Calc err:%d\r\n",err);
		return -1;
	}
	rt_kprintf("Hamming_Calc:ecc %#x %#x %#x %#x\r\n",s_ecc[0],s_ecc[1],s_ecc[2],s_ecc[3]);
	
/*
 *  1位数据错误
 */
	/* DATA注入错误 */
	rt_kprintf("\r\n[DATA err test]\r\n");
	s_buffer[0] ^= 0x80;
	
  /* 打印错误数据 */
	for(int i=0; i< sizeof(s_buffer)/sizeof(s_buffer[0]); i++)
  {
		if(i % 16 == 0)
    {
			rt_kprintf("\r\n");
		}
		rt_kprintf("%#x ",s_buffer[i]);
	}
	rt_kprintf("\r\n");
	
	if(ECC_FAULT == Hamming_Chk(s_buffer,len_buf,p_buf_ext,len_buf_ext,s_ecc,err_loc,sizeof(err_loc)/sizeof(err_loc[0]),&err))
  {
		rt_kprintf("Hamming_Chk err:%d\r\n",err);
		return -2;
	}
	rt_kprintf("Hamming_Chk:loc B[%d].b[%d] B[%d].b[%d]\r\n",err_loc[0].LocOctet,err_loc[0].LocBit,err_loc[1].LocOctet,err_loc[1].LocBit);
	rt_kprintf("%s",s_err_str[err].str);
	
	Hamming_Correct(s_buffer,len_buf,p_buf_ext,len_buf_ext,s_ecc,&err);
  /* 打印修复后的数据 */
	for(int i=0; i< sizeof(s_buffer)/sizeof(s_buffer[0]); i++)
  {
		if(i % 16 == 0)
    {
			rt_kprintf("\r\n");
		}
		rt_kprintf("%#x ",s_buffer[i]);
	}
	rt_kprintf("\r\n");
	rt_kprintf("Hamming_Correct:ecc %#x %#x %#x %#x\r\n",s_ecc[0],s_ecc[1],s_ecc[2],s_ecc[3]);
	rt_kprintf("%s",s_err_str[err].str);
/*
 *  1位ECC错误
 */
	/* DATA注入错误 */
	rt_kprintf("\r\n[ECC err test]\r\n");
	s_ecc[1] ^= 0x02;
	
  /* 打印错误数据 */
	for(int i=0; i< sizeof(s_buffer)/sizeof(s_buffer[0]); i++)
  {
		if(i % 16 == 0)
    {
			rt_kprintf("\r\n");
		}
		rt_kprintf("%#x ",s_buffer[i]);
	}
	rt_kprintf("\r\n");
	
	if(ECC_FAULT == Hamming_Chk(s_buffer,len_buf,p_buf_ext,len_buf_ext,s_ecc,err_loc,sizeof(err_loc)/sizeof(err_loc[0]),&err))
  {
		rt_kprintf("Hamming_Chk err:%d\r\n",err);
		return -2;
	}
	rt_kprintf("Hamming_Chk:loc B[%d].b[%d] B[%d].b[%d]\r\n",err_loc[0].LocOctet,err_loc[0].LocBit,err_loc[1].LocOctet,err_loc[1].LocBit);
	rt_kprintf("%s",s_err_str[err].str);
	
	Hamming_Correct(s_buffer,len_buf,p_buf_ext,len_buf_ext,s_ecc,&err);

  /* 打印修复后的数据 */
	for(int i=0; i< sizeof(s_buffer)/sizeof(s_buffer[0]); i++)
  {
		if(i % 16 == 0)
    {
			rt_kprintf("\r\n");
		}
		rt_kprintf("%#x ",s_buffer[i]);
	}
	rt_kprintf("\r\n");
	rt_kprintf("Hamming_Correct:ecc %#x %#x %#x %#x\r\n",s_ecc[0],s_ecc[1],s_ecc[2],s_ecc[3]);
	rt_kprintf("%s",s_err_str[err].str);
/*
 *  2位数据错误
 */
	/* DATA注入错误 */
	rt_kprintf("\r\n[2DATA err test]\r\n");
	s_buffer[2] ^= 0x04;
	s_buffer[5] ^= 0x10;
	
  /* 打印错误数据 */
	for(int i=0; i< sizeof(s_buffer)/sizeof(s_buffer[0]); i++)
  {
		if(i % 16 == 0)
    {
			rt_kprintf("\r\n");
		}
		rt_kprintf("%#x ",s_buffer[i]);
	}
	rt_kprintf("\r\n");
	
	if(ECC_FAULT == Hamming_Chk(s_buffer,len_buf,p_buf_ext,len_buf_ext,s_ecc,err_loc,sizeof(err_loc)/sizeof(err_loc[0]),&err))
  {
		rt_kprintf("Hamming_Chk err:%d\r\n",err);
		return -2;
	}
	rt_kprintf("Hamming_Chk:loc B[%d].b[%d] B[%d].b[%d]\r\n",err_loc[0].LocOctet,err_loc[0].LocBit,err_loc[1].LocOctet,err_loc[1].LocBit);
	rt_kprintf("%s",s_err_str[err].str);
	
	Hamming_Correct(s_buffer,len_buf,p_buf_ext,len_buf_ext,s_ecc,&err);
  /* 打印修复后的数据 */
	for(int i=0; i< sizeof(s_buffer)/sizeof(s_buffer[0]); i++)
  {
		if(i % 16 == 0)
    {
			rt_kprintf("\r\n");
		}
		rt_kprintf("%#x ",s_buffer[i]);
	}
	rt_kprintf("\r\n");
	rt_kprintf("Hamming_Correct:ecc %#x %#x %#x %#x\r\n",ecc[0],ecc[1],ecc[2],ecc[3]);
	rt_kprintf("%s",s_err_str[err].str);
	return 0;
}