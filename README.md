# 介绍
本库来源于https://github.com/weston-embedded/uC-FS.git （uC-FS/Dev/NAND）
将uC-FS的NAND驱动移植到PC上仿真,并进行修改,改为不依赖于其他模块可独立使用的库。

详细原理介绍可以关注公众号
![766ad473b1e8d3e19acb90df0243c0e](https://user-images.githubusercontent.com/31797371/236448810-22105246-8b0f-45e0-9075-9a104ab28140.jpg)


# Linux下使用
  Windows下的gcc工具链也一样。
- 编译
  `make`
- 创建测试bin文件代表FLASH
  `touch nand.bin`
- 运行测试
  `./nand`

打印如下:
```
nand test
NAME:nand
FS_NAND_Init ok
NAND FLASH FOUND: Name       : "nand:744:"
                  Sec Size   : 512 bytes
                  Size       : 247296 sectors
                  Update blks: 10
FS_NAND_LowMountHandler(): Can't read device header.
FS_NAND_Open err 314
FS_NAND_BlkEraseHandler(): Erase block 0.
FS_NAND_HdrWr(): Creating device header at block 0.
Marking blk 1 dirty.
Marking blk 2 dirty.
Marking blk 3 dirty.
Marking blk 4 dirty.
Marking blk 5 dirty.
Marking blk 6 dirty.
Marking blk 7 dirty.
Marking blk 8 dirty.
Marking blk 9 dirty.
... ...
Marking blk 1019 dirty.
Marking blk 1020 dirty.
Marking blk 1021 dirty.
Marking blk 1022 dirty.
Marking blk 1023 dirty.
Adding blk 1 to avail blk tbl at ix 0.
Adding blk 2 to avail blk tbl at ix 1.
Adding blk 3 to avail blk tbl at ix 2.
Adding blk 4 to avail blk tbl at ix 3.
FS_NAND_BlkGetAvailFromTbl(): Warning -- unable to get a committed available block table entry -- using an uncommitted entry.
FS_NAND_BlkEnsureErased(): No need to erase block 1 (not used).
Metadata sector 0 commit at offset 0 of block 1 (seq 0).
Removing blk 1 from avail blk tbl at ix 0.
Metadata sector 1 commit at offset 1 of block 1 (seq 0).
FS_NAND_LowFmtHandler(): Low-level fmt'ing complete.
Found meta block at physical block 1 with ID 0.
FS_NAND_MetaBlkFind(): Found metadata block at block index 1.
FS_NAND_LowMountHandler(): Low level mount succeeded.
FS_DEV_IO_CTRL_LOW_FMT ok
FS_DEV_IO_CTRL_REFRESH ok
FS_NAND_Wr: start=0, cnt=10.
Adding blk 5 to avail blk tbl at ix 0.
Metadata sector 0 commit at offset 2 of block 1 (seq 0).
FS_NAND_BlkEnsureErased(): No need to erase block 4 (not used).
Create UB 0 at phy ix 4.
Associate update blk 0 with blk ix logical 0.
Wr sector 0 in SUB 0 at sec offset 0.
Removing blk 4 from avail blk tbl at ix 3.
Wr sector 1 in SUB 0 at sec offset 1.
Wr sector 2 in SUB 0 at sec offset 2.
Wr sector 3 in SUB 0 at sec offset 3.
Wr sector 4 in SUB 0 at sec offset 4.
Wr sector 5 in SUB 0 at sec offset 5.
Wr sector 6 in SUB 0 at sec offset 6.
Wr sector 7 in SUB 0 at sec offset 7.
Wr sector 8 in SUB 0 at sec offset 8.
Wr sector 9 in SUB 0 at sec offset 9.
Metadata sector 0 commit at offset 3 of block 1 (seq 0).
Metadata sector 1 commit at offset 4 of block 1 (seq 0).
FS_NAND_Wr ok
FS_NAND_Rd ok
test ok

```
# Windows下使用
使用Visual Studio 2022
双击打开`NAND_VS\NAND_VS.sln`
选择`Debug`,`X86`目标构建,运行。
同样需要先在`NAND_VS`下创建空白文件`nand.bin`

