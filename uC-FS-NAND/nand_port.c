#include <stdlib.h>

#include "nand_port.h"

void *Mem_HeapAlloc(CPU_SIZE_T size,CPU_SIZE_T align,CPU_SIZE_T *p_bytes_reqd, LIB_ERR *p_err)
{
    if(align < sizeof(void*))
    {
        align = sizeof(void*);  /* 保证p2[-1]是指针大小对齐避免非对齐访问导致Segmentation fault */
    }
    int offset = align - 1 + sizeof(void*);
    
    void* p1 = (void*)malloc(size + offset);
 
    if (p1 == NULL)
    {
        *p_err = LIB_MEM_ERR_HEAP_EMPTY;
        *p_bytes_reqd = 0;
        return NULL;
	}
    *p_bytes_reqd = size;
    *p_err = LIB_MEM_ERR_NONE;
    void** p2 = (void**)( ( (size_t)p1 + offset ) & ~((size_t)align - 1) );   /* (size_t)align 避免CPU_SIZE_T<(size_t)时数据截断 */
 
    p2[-1] = p1;
 
    return p2;
}

CPU_INT16S  Str_Cmp_N (const  CPU_CHAR    *p1_str,
                       const  CPU_CHAR    *p2_str,
                              CPU_SIZE_T   len_max)
{
    const  CPU_CHAR    *p1_str_cmp;
    const  CPU_CHAR    *p2_str_cmp;
    const  CPU_CHAR    *p1_str_cmp_next;
    const  CPU_CHAR    *p2_str_cmp_next;
           CPU_INT16S   cmp_val;
           CPU_SIZE_T   cmp_len;


    if (len_max < 1) {                                          /* If cmp len = 0,        rtn 0       (see Note #3d1A). */
        return (0);
    }

    if (p1_str == (const CPU_CHAR *)0) {
        if (p2_str == (const CPU_CHAR *)0) {
            return (0);                                         /* If BOTH str ptrs NULL, rtn 0       (see Note #3a1A). */
        }
        cmp_val = (CPU_INT16S)((CPU_INT16S)0 - (CPU_INT16S)(*p2_str));
        return (cmp_val);                                       /* If p1_str NULL, rtn neg p2_str val (see Note #3a1B1).*/
    }
    if (p2_str == (const CPU_CHAR *)0) {
        cmp_val = (CPU_INT16S)(*p1_str);
        return (cmp_val);                                       /* If p2_str NULL, rtn pos p1_str val (see Note #3a1B2).*/
    }


    p1_str_cmp      = p1_str;
    p2_str_cmp      = p2_str;
    p1_str_cmp_next = p1_str_cmp;
    p2_str_cmp_next = p2_str_cmp;
    p1_str_cmp_next++;
    p2_str_cmp_next++;
    cmp_len         = 0u;

    while ((*p1_str_cmp      == *p2_str_cmp)            &&      /* Cmp strs until non-matching chars (see Note #3c) ... */
           (*p1_str_cmp      != (      CPU_CHAR  )'\0') &&      /* ... or NULL chars                 (see Note #3b) ... */
           ( p1_str_cmp_next != (const CPU_CHAR *)  0 ) &&      /* ... or NULL ptr(s) found          (see Note #3a2).   */
           ( p2_str_cmp_next != (const CPU_CHAR *)  0 ) &&
           ( cmp_len         <  (      CPU_SIZE_T)len_max)) {   /* ... or max nbr chars cmp'd        (see Note #3d2).   */
        p1_str_cmp++;
        p2_str_cmp++;
        p1_str_cmp_next++;
        p2_str_cmp_next++;
        cmp_len++;
    }


    if (cmp_len == len_max) {                                   /* If strs     identical for max len nbr of chars, ...  */
        return (0);                                             /* ... rtn 0                 (see Note #3d2A).          */
    }

    if (*p1_str_cmp != *p2_str_cmp) {                           /* If strs NOT identical, ...                           */
                                                                /* ... calc & rtn char diff  (see Note #3c1).           */
         cmp_val = (CPU_INT16S)((CPU_INT16S)(*p1_str_cmp) - (CPU_INT16S)(*p2_str_cmp));

    } else if (*p1_str_cmp  == (CPU_CHAR)'\0') {                /* If NULL char(s) found, ...                           */
         cmp_val = (CPU_INT16S)0;                               /* ... strs identical; rtn 0 (see Note #3b).            */

    } else {
        if (p1_str_cmp_next == (const CPU_CHAR *)0) {
            if (p2_str_cmp_next == (const CPU_CHAR *)0) {       /* If BOTH next str ptrs NULL, ...                      */
                cmp_val = (CPU_INT16S)0;                        /* ... rtn 0                       (see Note #3a2A).    */
            } else {                                            /* If p1_str_cmp_next NULL, ...                         */
                                                                /* ... rtn neg p2_str_cmp_next val (see Note #3a2B1).   */
                cmp_val = (CPU_INT16S)((CPU_INT16S)0 - (CPU_INT16S)(*p2_str_cmp_next));
            }
        } else {                                                /* If p2_str_cmp_next NULL, ...                         */
            cmp_val = (CPU_INT16S)(*p1_str_cmp_next);           /* ... rtn pos p1_str_cmp_next val (see Note #3a2B2).   */
        }
    }


    return (cmp_val);
}

/*
*********************************************************************************************************
*                                            FSUtil_Log2()
*
* Description : Calculate ceiling of base-2 logarithm of integer.
*
* Argument(s) : val         Integer value.
*
* Return(s)   : Logarithm of value, if val > 0;
*               0,                  otherwise.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT08U  FSUtil_Log2 (CPU_INT32U  val)
{
    CPU_SIZE_T  log_val;
    CPU_SIZE_T  val_cmp;


    val_cmp = 1u;
    log_val = 0u;
    while (val_cmp < val) {
        val_cmp *= 2u;
        log_val += 1u;
    }

    return (log_val);
}

/*
*********************************************************************************************************
*                                           FSUtil_MapBitSet()
*
* Description : Set specified bit in bitmap.
*
* Argument(s) : p_bitmap        Pointer to bitmap.
*               --------        Argument validated by caller.
*
*               offset_bit      Offset of bit in bitmap to test.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  FSUtil_MapBitSet (CPU_INT08U  *p_bitmap,
                        CPU_SIZE_T   offset_bit)
{
    CPU_SIZE_T  offset_octet;
    CPU_DATA    offset_bit_in_octet;
    CPU_INT08U  bit_mask;


    offset_octet        = offset_bit >> DEF_OCTET_TO_BIT_SHIFT;
    offset_bit_in_octet = offset_bit &  DEF_OCTET_TO_BIT_MASK;

    bit_mask = DEF_BIT(offset_bit_in_octet);
    DEF_BIT_SET_08(p_bitmap[offset_octet], bit_mask);
}


/*
*********************************************************************************************************
*                                           FSUtil_MapBitClr()
*
* Description : Clear specified bit in bitmap.
*
* Argument(s) : p_bitmap        Pointer to bitmap.
*               --------        Argument validated by caller.
*
*               offset_bit      Offset of bit in bitmap to test.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  FSUtil_MapBitClr (CPU_INT08U  *p_bitmap,
                        CPU_SIZE_T   offset_bit)
{
    CPU_SIZE_T  offset_octet;
    CPU_DATA    offset_bit_in_octet;
    CPU_INT08U  bit_mask;


    offset_octet        = offset_bit >> DEF_OCTET_TO_BIT_SHIFT;
    offset_bit_in_octet = offset_bit &  DEF_OCTET_TO_BIT_MASK;

    bit_mask = DEF_BIT(offset_bit_in_octet);
    DEF_BIT_CLR_08(p_bitmap[offset_octet], bit_mask);
}

/*
*********************************************************************************************************
*                                          FSUtil_MapBitIsSet()
*
* Description : Determines if specified bit of bitmap is set.
*
* Argument(s) : p_bitmap        Pointer to bitmap.
*               --------        Argument validated by caller.
*
*               offset_bit      Offset of bit in bitmap to test.
*
* Return(s)   : DEF_YES, if bit is set;
*               DEF_NO , otherwise.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  FSUtil_MapBitIsSet (CPU_INT08U  *p_bitmap,
                                 CPU_SIZE_T   offset_bit)
{
    CPU_SIZE_T   offset_octet;
    CPU_DATA     offset_bit_in_octet;
    CPU_INT08U   bit_mask;
    CPU_BOOLEAN  bit_set;


    offset_octet        = offset_bit >> DEF_OCTET_TO_BIT_SHIFT;
    offset_bit_in_octet = offset_bit &  DEF_OCTET_TO_BIT_MASK;

    bit_mask = DEF_BIT(offset_bit_in_octet);
    bit_set  = DEF_BIT_IS_SET(p_bitmap[offset_octet], bit_mask);

    return (bit_set);
}


/*
*********************************************************************************************************
*                                            FSUtil_ValPack32()
*
* Description : Packs a specified number of least significant bits of a 32-bit value to a specified octet
*               and bit position within an octet array, in little-endian order.
*
* Argument(s) : p_dest          Pointer to destination octet array.
*
*               p_offset_octet  Pointer to octet offset into 'p_dest'. This function adjusts the pointee
*                               to the new octet offset within octet array.
*
*               p_offset_bit    Pointer to bit offset into initial 'p_dest[*p_offset_octet]'. This function
*                               adjusts the pointee to the new bit offset within octet.
*
*               val             Value to pack into 'p_dest' array.
*
*               nbr_bits        Number of least-significants bits of 'val' to pack into 'p_dest'.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  FSUtil_ValPack32 (CPU_INT08U  *p_dest,
                        CPU_SIZE_T  *p_offset_octet,
                        CPU_DATA    *p_offset_bit,
                        CPU_INT32U   val,
                        CPU_DATA     nbr_bits)
{
    CPU_INT32U  val_32_rem;
    CPU_DATA    nbr_bits_rem;
    CPU_DATA    nbr_bits_partial;
    CPU_INT08U  val_08;
    CPU_INT08U  val_08_mask;
    CPU_INT08U  dest_08_mask;
    CPU_INT08U  dest_08_mask_lsb;


#if (FS_CFG_ERR_ARG_CHK_DBG_EN == DEF_ENABLED)                  /* ------------------ VALIDATE ARGS ------------------- */
    if (p_dest == DEF_NULL) {                                   /* Validate dest  array  ptr.                           */
        CPU_SW_EXCEPTION(;);
    }

    if (p_offset_octet == DEF_NULL) {                           /* Validate octet offset ptr.                           */
        CPU_SW_EXCEPTION(;);
    }

    if (p_offset_bit == DEF_NULL) {                             /* Validate bit   offset ptr.                           */
        CPU_SW_EXCEPTION(;);
    }

    if (nbr_bits > (sizeof(val) * DEF_OCTET_NBR_BITS)) {        /* Validate bits nbr.                                   */
        CPU_SW_EXCEPTION(;);
    }

    if (*p_offset_bit >= DEF_OCTET_NBR_BITS) {                  /* Validate bit  offset.                                */
        CPU_SW_EXCEPTION(;);
    }
#endif  /* FS_CFG_ERR_ARG_CHK_EXT_EN */

    nbr_bits_rem = nbr_bits;
    val_32_rem   = val;


                                                                /* ------------ PACK LEADING PARTIAL OCTET ------------ */
    if (*p_offset_bit > 0) {
                                                                /* Calc nbr bits to pack in initial array octet.        */
        nbr_bits_partial = DEF_OCTET_NBR_BITS - *p_offset_bit;
        if (nbr_bits_partial > nbr_bits_rem) {
            nbr_bits_partial = nbr_bits_rem;
        }


        val_08_mask =  DEF_BIT_FIELD_08(nbr_bits_partial, 0u);  /* Calc  mask to apply on 'val_32_rem'.                 */
        val_08      =  val_32_rem & val_08_mask;                /* Apply mask.                                          */
        val_08    <<= *p_offset_bit;                            /* Shift according to bit offset in leading octet.      */


                                                                /* Calc mask for kept non-val bits from leading octet.  */
        dest_08_mask_lsb = *p_offset_bit + nbr_bits_partial;
        dest_08_mask     =  DEF_BIT_FIELD_08(DEF_OCTET_NBR_BITS - dest_08_mask_lsb, dest_08_mask_lsb);
        dest_08_mask    |=  DEF_BIT_FIELD_08(*p_offset_bit, 0u);

        p_dest[*p_offset_octet] &= dest_08_mask;                /* Keep      non-val bits from leading array octet.     */
        p_dest[*p_offset_octet] |= val_08;                      /* Merge leading val bits into leading array octet.     */

                                                                /* Update bit/octet offsets.                            */
       *p_offset_bit += nbr_bits_partial;
        if (*p_offset_bit >= DEF_OCTET_NBR_BITS) {              /* If bit offset > octet nbr bits, ...                  */
            *p_offset_bit  = 0u;                                /* ... zero bit offset (offset <= DEF_OCTET_NBR_BITS)   */
           (*p_offset_octet)++;                                 /* ... and inc octet offset.                            */
        }

                                                                /* Update rem'ing val/nbr bits.                         */
        val_32_rem   >>= nbr_bits_partial;
        nbr_bits_rem  -= nbr_bits_partial;
    }


                                                                /* ---------------- PACK FULL OCTET(S) ---------------- */
    while (nbr_bits_rem >= DEF_OCTET_NBR_BITS) {
        val_08                  = (CPU_INT08U)val_32_rem & DEF_OCTET_MASK;
        p_dest[*p_offset_octet] =  val_08;                      /* Merge full-octet val bits into array octet.          */
      (*p_offset_octet)++;                                      /* Update octet offset.                                 */

                                                                /* Update rem'ing val/nbr bits.                         */
        val_32_rem   >>= DEF_OCTET_NBR_BITS;
        nbr_bits_rem  -= DEF_OCTET_NBR_BITS;
    }


                                                                /* ----------- PACK TRAILING PARTIAL OCTET ------------ */
    if (nbr_bits_rem > 0) {
        val_08_mask  =  DEF_BIT_FIELD_08(nbr_bits_rem, 0u);
        val_08       = (CPU_INT08U)val_32_rem & val_08_mask;    /* Mask trailing val bits for merge.                    */

        dest_08_mask =  DEF_BIT_FIELD_08(DEF_OCTET_NBR_BITS - nbr_bits_rem,
                                         nbr_bits_rem);

        p_dest[*p_offset_octet] &= dest_08_mask;                /* Keep non-val bits of         trailing array octet.   */
        p_dest[*p_offset_octet] |= val_08;                      /* Merge trailing val bits into trailing array octet.   */

       *p_offset_bit += nbr_bits_rem;                           /* Update/rtn final bit offset.                         */
    }
}

/*
*********************************************************************************************************
*                                           CRCUtil_PopCnt_32()
*
* Description : Compute population count (hamming weight) for value (number of bits set).
*
* Argument(s) : value           Value to compute population count on.
*
*
* Return(s)   : value's population count.
*
* Caller(s)   : various.
*
* Note(s)     : (1) Algorithm taken from http://en.wikipedia.org/wiki/Hamming_weight
*********************************************************************************************************
*/

CPU_INT08U  NAND_CRCUtil_PopCnt_32 (CPU_INT32U  value)
{
    CPU_INT32U  even_cnt;
    CPU_INT32U  odd_cnt;
    CPU_INT32U  result;


    odd_cnt  = (value >> 1u) & CRC_UTIL_POPCNT_MASK01010101_32; /* 2-bits pieces.                                       */
    result   =  value - odd_cnt;                                /* Same result as result=odd_cnt+(value & 0x55555555).  */

    even_cnt =  result & CRC_UTIL_POPCNT_MASK00110011_32;       /* 4-bits pieces.                                       */
    odd_cnt  = (result >> 2u) & CRC_UTIL_POPCNT_MASK00110011_32;
    result   =  even_cnt + odd_cnt;

    even_cnt =  result & CRC_UTIL_POPCNT_MASK00001111_32;       /* 8-bits pieces.                                       */
    odd_cnt  = (result >> 4u) & CRC_UTIL_POPCNT_MASK00001111_32;
    result   =  even_cnt + odd_cnt;

#if CRC_UTIL_POPCNT_METHOD == CRC_UTIL_POPCNT_METHOD_SLOW_MULT
    result  +=  result >> 8u;                                   /* 16-bits pieces into their lowest 8 bits              */
    result  +=  result >> 16u;                                  /* Add together both counts.                            */

    result  &=  0x3Fu;
    return (result);                                            /* Mask unwanted bits.                                  */
#else
    result = (result * CRC_UTIL_POPCNT_POWERSOF256_32) >> 24u;
    return (result);
#endif

}

/*
*********************************************************************************************************
*                                          FSUtil_ValUnpack32()
*
* Description : Unpacks a specified number of least-significant bits from a specified octet and bit
*               position within an octet array, in little-endian order to a 32-bit value.
*
* Argument(s) : p_src           Pointer to source octet array.
*
*               p_offset_octet  Pointer to octet offset into 'p_src'. This function adjusts the pointee
*                               to the new position within octet array.
*
*               p_offset_bit    Pointer to bit offset into initial 'p_src[*p_offset_octet]'. This function
*                               ajusts the pointee to the new position within octet array.
*
*               nbr_bits        Number of least-significants bits to unpack from 'p_src' into value.
*
* Return(s)   : Unpacked 32-bit value, if no errors;
*               DEF_INT_32U_MAX_VAL,   otherwise.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT32U  FSUtil_ValUnpack32 (CPU_INT08U  *p_src,
                                CPU_SIZE_T  *p_offset_octet,
                                CPU_DATA    *p_offset_bit,
                                CPU_DATA     nbr_bits)
{
    CPU_INT32U  val_32;
    CPU_DATA    nbr_bits_partial;
    CPU_DATA    nbr_bits_rem;
    CPU_INT08U  val_08;
    CPU_INT08U  val_08_mask;


#if (FS_CFG_ERR_ARG_CHK_DBG_EN == DEF_ENABLED)                  /* ------------------ VALIDATE ARGS ------------------- */
    if (p_src == DEF_NULL) {                                    /* Validate src ptr.                                    */
        CPU_SW_EXCEPTION(DEF_INT_32U_MAX_VAL);
    }

    if (p_offset_octet == DEF_NULL) {                           /* Validate octet offset ptr.                           */
        CPU_SW_EXCEPTION(DEF_INT_32U_MAX_VAL);
    }

    if (p_offset_bit == DEF_NULL) {                             /* Validate bit   offset ptr.                           */
        CPU_SW_EXCEPTION(DEF_INT_32U_MAX_VAL);
    }

    if (nbr_bits > (sizeof(val_32) * DEF_OCTET_NBR_BITS)) {     /* Validate bits nbr.                                   */
        CPU_SW_EXCEPTION(DEF_INT_32U_MAX_VAL);
    }

    if (*p_offset_bit >= DEF_OCTET_NBR_BITS) {                  /* Validate bit  offset.                                */
        CPU_SW_EXCEPTION(DEF_INT_32U_MAX_VAL);
    }
#endif  /* FS_CFG_ERR_ARG_CHK_EXT_EN */


    nbr_bits_rem = nbr_bits;
    val_32       = 0u;
                                                                /* ----------- UNPACK LEADING PARTIAL OCTET ----------- */
    if (*p_offset_bit > 0) {
                                                                /* Calc nbr of bits to unpack from first initial octet. */
        nbr_bits_partial = DEF_OCTET_NBR_BITS - *p_offset_bit;
        if (nbr_bits_partial > nbr_bits) {
            nbr_bits_partial = nbr_bits;
        }

        val_08_mask  =  DEF_BIT_FIELD_08(nbr_bits_partial, *p_offset_bit);
        val_08       =  p_src[*p_offset_octet];
        val_08      &=  val_08_mask;                            /* Keep val leading bits.                               */
        val_08     >>= *p_offset_bit;                           /* Shift bit offset to least sig of val.                */

        val_32      |= (CPU_INT32U)val_08;                      /* Merge leading val bits from leading array octet.     */

                                                                /* Update bit/octet offsets.                            */
       *p_offset_bit += nbr_bits_partial;
        if (*p_offset_bit >= DEF_OCTET_NBR_BITS) {              /* If bit offset > octet nbr bits, ...                  */
            *p_offset_bit  = 0u;                                /* ... zero bit offset (offset <= DEF_OCTET_NBR_BITS)   */
           (*p_offset_octet)++;                                 /* ... and inc octet offset.                            */
        }


        nbr_bits_rem -= nbr_bits_partial;                       /* Update rem'ing nbr bits.                             */
    }


                                                                /* -------------- UNPACK FULL OCTET(S) ---------------- */
    while (nbr_bits_rem >= DEF_OCTET_NBR_BITS) {
        val_08 = p_src[*p_offset_octet];
                                                                /* Merge full-octet val bits into array octet.          */
        if (nbr_bits >= nbr_bits_rem) {
            val_32 |= (val_08 << ((CPU_INT08U)nbr_bits - (CPU_INT08U)nbr_bits_rem));
        } else {
            CPU_SW_EXCEPTION(DEF_INT_08U_MAX_VAL);
        }

      (*p_offset_octet)++;                                      /* Update octet offset.                                 */

        nbr_bits_rem -= DEF_OCTET_NBR_BITS;                     /* Update rem'ing nbr bits.                             */
    }


                                                                /* ----------- UNPACK FINAL TRAILING OCTET ------------ */
    if (nbr_bits_rem  >  0) {
        val_08_mask   =  DEF_BIT_FIELD_08(nbr_bits_rem, 0u);
        val_08        =  p_src[*p_offset_octet];
        val_08       &=  val_08_mask;                           /* Keep val trailing bits.                              */

                                                                /* Merge trailing val bits from trailing array octet.   */
        if (nbr_bits >= nbr_bits_rem) {
            val_32 |= (val_08 << ((CPU_INT08U)nbr_bits - (CPU_INT08U)nbr_bits_rem));
        } else {
            CPU_SW_EXCEPTION(DEF_INT_08U_MAX_VAL);
        }


       *p_offset_bit += nbr_bits_rem;                           /* Update bit offset.                                   */
    }

    return (val_32);
}


/*
*********************************************************************************************************
*                                  CPU COUNT LEAD ZEROs LOOKUP TABLE
*
* Note(s) : (1) Index into bit pattern table determines the number of leading zeros in an 8-bit value :
*
*                         b07  b06  b05  b04  b03  b02  b01  b00    # Leading Zeros
*                         ---  ---  ---  ---  ---  ---  ---  ---    ---------------
*                          1    x    x    x    x    x    x    x            0
*                          0    1    x    x    x    x    x    x            1
*                          0    0    1    x    x    x    x    x            2
*                          0    0    0    1    x    x    x    x            3
*                          0    0    0    0    1    x    x    x            4
*                          0    0    0    0    0    1    x    x            5
*                          0    0    0    0    0    0    1    x            6
*                          0    0    0    0    0    0    0    1            7
*                          0    0    0    0    0    0    0    0            8
*********************************************************************************************************
*/

#if (!(defined(CPU_CFG_LEAD_ZEROS_ASM_PRESENT)) || \
      (CPU_CFG_DATA_SIZE_MAX > CPU_CFG_DATA_SIZE))
static  const  CPU_INT08U  CPU_CntLeadZerosTbl[256] = {                             /* Data vals :                      */
/*   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F   */
    8u,  7u,  6u,  6u,  5u,  5u,  5u,  5u,  4u,  4u,  4u,  4u,  4u,  4u,  4u,  4u,  /*   0x00 to 0x0F                   */
    3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  /*   0x10 to 0x1F                   */
    2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  /*   0x20 to 0x2F                   */
    2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  /*   0x30 to 0x3F                   */
    1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  /*   0x40 to 0x4F                   */
    1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  /*   0x50 to 0x5F                   */
    1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  /*   0x60 to 0x6F                   */
    1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  /*   0x70 to 0x7F                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0x80 to 0x8F                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0x90 to 0x9F                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0xA0 to 0xAF                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0xB0 to 0xBF                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0xC0 to 0xCF                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0xD0 to 0xDF                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0xE0 to 0xEF                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u   /*   0xF0 to 0xFF                   */
};
#endif

/*
*********************************************************************************************************
*                                        CPU_CntLeadZeros32()
*
* Description : Count the number of contiguous, most-significant, leading zero bits in a 32-bit data value.
*
* Argument(s) : val         Data value to count leading zero bits.
*
* Return(s)   : Number of contiguous, most-significant, leading zero bits in 'val'.
*
* Note(s)     : (1) Supports 32-bit values :
*
*                          b31  b30  b29  ...  b04  b03  b02  b01  b00    # Leading Zeros
*                          ---  ---  ---       ---  ---  ---  ---  ---    ---------------
*                           1    x    x         x    x    x    x    x            0
*                           0    1    x         x    x    x    x    x            1
*                           0    0    1         x    x    x    x    x            2
*                           :    :    :         :    :    :    :    :            :
*                           :    :    :         :    :    :    :    :            :
*                           0    0    0         1    x    x    x    x           27
*                           0    0    0         0    1    x    x    x           28
*                           0    0    0         0    0    1    x    x           29
*                           0    0    0         0    0    0    1    x           30
*                           0    0    0         0    0    0    0    1           31
*                           0    0    0         0    0    0    0    0           32
*
*
*                   See also 'CPU COUNT LEAD ZEROs LOOKUP TABLE  Note #1'.
*********************************************************************************************************
*/

CPU_DATA  CPU_CntLeadZeros32 (CPU_INT32U  val)
{
#if  (!((defined(CPU_CFG_LEAD_ZEROS_ASM_PRESENT)) && \
        (CPU_CFG_DATA_SIZE >= CPU_WORD_SIZE_32)))
    CPU_DATA  ix;
#endif
    CPU_DATA  nbr_lead_zeros;

                                                                                /* ---------- ASM-OPTIMIZED ----------- */
#if ((defined(CPU_CFG_LEAD_ZEROS_ASM_PRESENT)) && \
     (CPU_CFG_DATA_SIZE >= CPU_WORD_SIZE_32))
    nbr_lead_zeros  =  CPU_CntLeadZeros((CPU_DATA)val);
    nbr_lead_zeros -= (CPU_CFG_DATA_SIZE - CPU_WORD_SIZE_32) * DEF_OCTET_NBR_BITS;


#else                                                                           /* ----------- C-OPTIMIZED ------------ */
    if (val > 0x0000FFFFu) {
        if (val > 0x00FFFFFFu) {                                                /* Chk bits [31:24] :                   */
            val            >>= 24u;                                             /* .. Nbr lead zeros =               .. */
            ix               = (CPU_DATA)(val);                                 /* .. lookup tbl ix  = 'val' >> 24 bits */
            nbr_lead_zeros   = (CPU_DATA)(CPU_CntLeadZerosTbl[ix]);             /* .. plus nbr msb lead zeros =  0 bits.*/

        } else {                                                                /* Chk bits [23:16] :                   */
            val            >>= 16u;                                             /* .. Nbr lead zeros =               .. */
            ix               = (CPU_DATA)(val);                                 /* .. lookup tbl ix  = 'val' >> 16 bits */
            nbr_lead_zeros   = (CPU_DATA)((CPU_DATA)CPU_CntLeadZerosTbl[ix] +  8u);/* .. plus nbr msb lead zeros =  8 bits.*/
        }

    } else {
        if (val > 0x000000FFu) {                                                /* Chk bits [15:08] :                   */
            val            >>= 8u;                                              /* .. Nbr lead zeros =               .. */
            ix               = (CPU_DATA)(val);                                 /* .. lookup tbl ix  = 'val' >>  8 bits */
            nbr_lead_zeros   = (CPU_DATA)((CPU_DATA)CPU_CntLeadZerosTbl[ix] + 16u);/* .. plus nbr msb lead zeros = 16 bits.*/

        } else {                                                                /* Chk bits [07:00] :                   */
                                                                                /* .. Nbr lead zeros =               .. */
            ix               = (CPU_DATA)(val);                                 /* .. lookup tbl ix  = 'val' >>  0 bits */
            nbr_lead_zeros   = (CPU_DATA)((CPU_DATA)CPU_CntLeadZerosTbl[ix] + 24u);/* .. plus nbr msb lead zeros = 24 bits.*/
        }
    }
#endif


    return (nbr_lead_zeros);
}


/*
*********************************************************************************************************
*                                        CPU_CntTrailZeros32()
*
* Description : Count the number of contiguous, least-significant, trailing zero bits in a 32-bit data value.
*
* Argument(s) : val         Data value to count trailing zero bits.
*
* Return(s)   : Number of contiguous, least-significant, trailing zero bits in 'val'.
*
* Note(s)     : (1) Supports 32-bit values :
*
*                          b31  b30  b29  b28  b27  ...  b02  b01  b00    # Trailing Zeros
*                          ---  ---  ---  ---  ---       ---  ---  ---    ----------------
*                           x    x    x    x    x         x    x    1            0
*                           x    x    x    x    x         x    1    0            1
*                           x    x    x    x    x         1    0    0            2
*                           :    :    :    :    :         :    :    :            :
*                           :    :    :    :    :         :    :    :            :
*                           x    x    x    x    1         0    0    0           27
*                           x    x    x    1    0         0    0    0           28
*                           x    x    1    0    0         0    0    0           29
*                           x    1    0    0    0         0    0    0           30
*                           1    0    0    0    0         0    0    0           31
*                           0    0    0    0    0         0    0    0           32
*
*
*               (2) For non-zero values, the returned number of contiguous, least-significant, trailing
*                   zero bits is also equivalent to the bit position of the least-significant set bit.
*
*               (3) 'val' SHOULD be validated for non-'0' PRIOR to all other counting zero calculations :
*
*                   (a) For assembly-optimized implementations, CPU_CntTrailZeros() returns 'val's
*                       number of trailing zeros via CPU's native data size, 'CPU_CFG_DATA_SIZE'.
*                       If the returned number of zeros exceeds CPU_CntTrailZeros32()'s 32-bit return
*                       data size, then the returned number of zeros must be offset by the difference
*                       between CPU_CntTrailZeros()'s  & CPU_CntTrailZeros32()'s return data size :
*
*                           nbr_trail_zeros = CPU_CntTrailZeros((CPU_DATA)val);
*                           if (nbr_trail_zeros >  (CPU_WORD_SIZE_32  * DEF_OCTET_NBR_BITS)) {
*                               nbr_trail_zeros -= (CPU_CFG_DATA_SIZE - CPU_WORD_SIZE_32) * DEF_OCTET_NBR_BITS;
*                           }
*
*                       However, this ONLY occurs for an initial 'val' of '0' since all non-'0' 32-bit
*                       values would return a number of trailing zeros less than or equal to 32 bits.
*
*                       Therefore, initially validating all non-'0' values prior to calling assembly-
*                       optimized CPU_CntTrailZeros() avoids having to offset the number of returned
*                       trailing zeros by the difference in CPU data size and 32-bit data value bits.
*
*                   (b) For CPU_CntTrailZeros32()'s C implementation, the final conditional statement
*                       calculates 'val's number of trailing zeros based on CPU_CntTrailZeros32()'s
*                       32-bit return data size & 'val's calculated number of lead zeros ONLY if the
*                       initial 'val' is non-'0' :
*
*                           if (val != 0u) {
*                               nbr_trail_zeros = ((CPU_WORD_SIZE_32 * DEF_OCTET_NBR_BITS) - 1u) - nbr_lead_zeros;
*                           } else {
*                               nbr_trail_zeros = nbr_lead_zeros;
*                           }
*
*                       Therefore, initially validating all non-'0' values avoids having to conditionally
*                       execute the final 'if' statement.
*********************************************************************************************************
*/

CPU_DATA  CPU_CntTrailZeros32 (CPU_INT32U  val)
{
#if  (!((defined(CPU_CFG_TRAIL_ZEROS_ASM_PRESENT)) && \
        (CPU_CFG_DATA_SIZE >= CPU_WORD_SIZE_32)))
    CPU_INT32U  val_bit_mask;
    CPU_DATA    nbr_lead_zeros;
#endif
    CPU_DATA    nbr_trail_zeros;


    if (val == 0u) {                                            /* Rtn ALL val bits as zero'd (see Note #3).            */
        return ((CPU_DATA)(CPU_WORD_SIZE_32 * DEF_OCTET_NBR_BITS));
    }

                                                                /* ------------------ ASM-OPTIMIZED ------------------- */
#if ((defined(CPU_CFG_TRAIL_ZEROS_ASM_PRESENT)) && \
     (CPU_CFG_DATA_SIZE >= CPU_WORD_SIZE_32))
    nbr_trail_zeros = CPU_CntTrailZeros((CPU_DATA)val);

#else                                                           /* ------------------- C-OPTIMIZED -------------------- */
    val_bit_mask    = val & ((CPU_INT32U)~val + 1u);            /* Zero/clr all bits EXCEPT least-sig set bit.          */
    nbr_lead_zeros  = CPU_CntLeadZeros32(val_bit_mask);         /* Cnt  nbr lead  0s.                                   */
                                                                /* Calc nbr trail 0s = (nbr val bits - 1) - nbr lead 0s.*/
    nbr_trail_zeros = ((CPU_DATA)((CPU_WORD_SIZE_32 * DEF_OCTET_NBR_BITS) - 1u) - nbr_lead_zeros);
#endif


    return (nbr_trail_zeros);
}

