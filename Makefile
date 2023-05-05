SRC = uC-FS-NAND/fs_dev_nand.c uC-FS-NAND/fs_dev_nand_ctrlr_gen.c uC-FS-NAND/fs_dev_nand_ctrlr_gen_soft_ecc.c uC-FS-NAND/fs_dev_nand_part_static.c uC-FS-NAND/nand_port.c\
	uC-FS-NAND/bsp_fs_dev_nand_ctrlr_gen.c uC-CRC/crc_util.c uC-CRC/ecc_hamming.c test.c
nand: $(SRC)
	gcc -g -o nand $(SRC) -I./uC-CRC -I./uC-FS-NAND