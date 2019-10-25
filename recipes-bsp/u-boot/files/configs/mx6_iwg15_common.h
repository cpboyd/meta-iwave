/*
 * Copyright (c) 2017 iWave Systems Technologies Pvt. Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * @file mx6_iwg15m_common.h
 *
 * @brief Common Config File for iMx6x base iwave boards
 *
 * @ingroup High level Configuration
 */


#ifndef __MX6_IWG15_COMMON_CONFIG_H
#define __MX6_IWG15_COMMON_CONFIG_H

#include "mx6_common.h"

#define IWCONFIG_MX6_IWG15

#define CONFIG_SYS_L2_PL310

/* uncomment for SECURE mode support */
/* #define CONFIG_SECURE_BOOT */

#ifdef CONFIG_SECURE_BOOT
#ifndef CONFIG_CSF_SIZE
#define CONFIG_CSF_SIZE SZ_16K
#endif
#endif

#define CONFIG_IMX_THERMAL

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(16 * SZ_1M)

#ifdef CONFIG_CMD_FUSE
#define CONFIG_MXC_OCOTP
#endif

/* MMC Configs */
#define CONFIG_FSL_ESDHC
#define CONFIG_FSL_USDHC
#define CONFIG_SYS_FSL_ESDHC_ADDR	0

#define CONFIG_DYNAMIC_MMC_DEVNO
#define CONFIG_BOUNCE_BUFFER

#define CONFIG_SUPPORT_EMMC_BOOT /* eMMC specific */

#define CONFIG_MII
#define IMX_FEC_BASE			ENET_BASE_ADDR
#define CONFIG_FEC_XCV_TYPE		RGMII
#define CONFIG_ETHPRIME			"FEC"
#define CONFIG_FEC_MXC_PHYADDR		0xFF

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE
#define CONFIG_CONS_INDEX		1
#define CONFIG_BAUDRATE			115200

#define CONFIG_LOADADDR			0x12000000

#define CONFIG_SYS_MMC_IMG_LOAD_PART	1

#ifdef CONFIG_MFG
#define CONFIG_MFG_ENV_SETTINGS \
	"mfgtool_args=setenv bootargs console=" CONSOLE_DEV ",115200 " \
		"rdinit=/linuxrc " \
		"g_mass_storage.stall=0 g_mass_storage.removable=1 " \
		"g_mass_storage.idVendor=0x066F g_mass_storage.idProduct=0x37FF "\
		"g_mass_storage.iSerialNumber=\"\" "\
		"enable_wait_mode=off "\
	"\0" \
	"initrd_addr=0x12C00000\0" \
	"initrd_high=0xffffffff\0" \
	"bootcmd_mfg=run mfgtool_args;bootz ${loadaddr} ${initrd_addr} ${fdt_addr};\0" \
	"bootcmd_mfg_pmic=run mfgtool_args;bootz ${loadaddr} ${initrd_addr} ${fdt_addr_pmic};\0" \

#define CONFIG_EXTRA_ENV_SETTINGS \
	CONFIG_MFG_ENV_SETTINGS \
	"fdt_addr=0x18000000\0" \
	"fdt_addr_pmic=0x1A000000\0" \
	"fdt_high=0xffffffff\0" \
	"uboot_ldo_bypass=1\0" \
	"ethaddr=00:01:02:03:04:05\0" \
	"\0"
#else

#define COMMON_CONFIG_EXTRA_ENV_SETTINGS \
	"fdt_file=" CONFIG_DEFAULT_FDT_FILE "\0" \
	"uboot_ldo_bypass=1\0" \
	"fdtforce=0\0" \
	"fdt_check=if test ${fdtforce} = \"0\"; then dynamicfdt;fi;\0" \
	"fdt_addr=0x18000000\0" \
	"fdt_high=0xffffffff\0"   \
	"ethaddr=00:01:02:03:04:05\0" \
	"kernel=zImage\0" \
	"bootpart=" __stringify(CONFIG_SYS_MMC_IMG_LOAD_PART) "\0" \
	"rootpart=" __stringify(CONFIG_SYS_MMC_IMG_LOAD_PART) "\0" \
	"bootpath=/boot/\0" \
	"bootargs_base=console="CONSOLE_DEV",115200n8\0" \
	"bootcmd_net=dhcp;run fdt_check;" \
		"tftpboot ${loadaddr} ${serverip}:${kernel};" \
		"tftpboot ${fdt_addr} ${serverip}:${fdt_file};" \
		"run bootargs_net;bootz ${loadaddr} - ${fdt_addr}\0" \
	"bootargs_net=setenv bootargs ${bootargs_base} " \
		"root=/dev/nfs ip=dhcp nfsroot=${serverip}:${nfsroot},v3,tcp ${lcd} ${hdmi}\0" \
	"bootargs_mmc=setenv bootargs ${bootargs_base} " \
		"root=/dev/${rootdev}p${rootpart} rootwait rw ${lcd} ${hdmi}\0" \
	"bootcmd_mmc=run bootargs_mmc;run fdt_check;mmc dev ${mmcdev};" \
		"ext2load mmc ${mmcdev}:${bootpart} ${loadaddr} ${bootpath}${kernel};" \
		"ext2load mmc ${mmcdev}:${bootpart} ${fdt_addr} ${bootpath}${fdt_file};" \
		"bootz ${loadaddr} - ${fdt_addr}\0" \

#ifdef CONFIG_TARGET_MX6_IWG15M_SM
#define CONFIG_EXTRA_ENV_SETTINGS \
	COMMON_CONFIG_EXTRA_ENV_SETTINGS \
	"mmcdev=1\0" \
	"rootdev=mmcblk3\0" \
	"bootcmd=run bootcmd_mmc\0" \
	"\0"
#else
#define CONFIG_EXTRA_ENV_SETTINGS \
	COMMON_CONFIG_EXTRA_ENV_SETTINGS \
	"mmcdev=2\0" \
	"rootdev=mmcblk2\0" \
	"bootcmd=run bootcmd_mmc\0" \
	"\0"
#endif

#define IWCONFIG_EXTRA_ENV_SETTINGS_SATA \
	COMMON_CONFIG_EXTRA_ENV_SETTINGS \
	"rootdev=sda\0" \
	"bootargs_sata=setenv bootargs ${bootargs_base} " \
		"root=/dev/${rootdev}${rootpart} rootwait rw ${lcd} ${hdmi}\0" \
	"bootcmd_sata=run bootargs_sata;run fdt_check;sata init;" \
		"ext2load sata 0:${bootpart} ${loadaddr} ${bootpath}${kernel};" \
		"ext2load sata 0:${bootpart} ${fdt_addr} ${bootpath}${fdt_file};" \
		"bootz ${loadaddr} - ${fdt_addr}\0" \
	"bootcmd=run bootcmd_sata\0" \
	"\0"

#ifdef CONFIG_TARGET_MX6_IWG15M_SM
#define IWCONFIG_EXTRA_ENV_SETTINGS_MSD \
	COMMON_CONFIG_EXTRA_ENV_SETTINGS \
	"mmcdev=0\0" \
	"rootdev=mmcblk0\0" \
	"bootcmd=run bootcmd_mmc\0" \
	"\0"
#else
#define IWCONFIG_EXTRA_ENV_SETTINGS_MSD \
	COMMON_CONFIG_EXTRA_ENV_SETTINGS \
	"mmcdev=1\0" \
	"rootdev=mmcblk1\0" \
	"bootcmd=run bootcmd_mmc\0" \
	"\0"
#endif

#define IWCONFIG_EXTRA_ENV_SETTINGS_SSD \
	COMMON_CONFIG_EXTRA_ENV_SETTINGS \
	"mmcdev=0\0" \
	"rootdev=mmcblk0\0" \
	"bootcmd=run bootcmd_mmc\0" \
	"\0"

#define IWCONFIG_EXTRA_ENV_SETTINGS_EMMC \
	CONFIG_EXTRA_ENV_SETTINGS \
	"\0"

#endif

#define CONFIG_ARP_TIMEOUT		200UL

/* Miscellaneous configurable options */
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "

/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE

#define CONFIG_SYS_MEMTEST_START	0x10000000
#define CONFIG_SYS_MEMTEST_END		0x10010000
#define CONFIG_SYS_MEMTEST_SCRATCH	0x10800000

#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR
#define CONFIG_SYS_HZ			1000

#define IWCONFIG_STACKSIZE		SZ_128K

/* Physical Memory Map */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM			MMDC0_ARB_BASE_ADDR

#define PHYS_SDRAM_SIZE			(1u * SZ_1G)
#define PHYS_SDRAM_SIZE_512MB		SZ_512M
#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* Environment organization */
#define CONFIG_ENV_SIZE			SZ_8K
#define CONFIG_ENV_SECT_SIZE		SZ_64K
#ifndef CONFIG_MFG
#define CONFIG_SYS_SATA_ENV_DEV		0
#define CONFIG_ENV_OFFSET		(768 * SZ_1K)
#define CONFIG_SYS_REDUNDAND_ENVIRONMENT
#define CONFIG_ENV_OFFSET_REDUND	CONFIG_ENV_OFFSET + CONFIG_ENV_SECT_SIZE
#define IWCONFIG_SYS_USE_SPINOR
#define CONFIG_ENV_SPI_BUS		CONFIG_SF_DEFAULT_BUS
#define CONFIG_ENV_SPI_CS		CONFIG_SF_DEFAULT_CS
#define CONFIG_ENV_SPI_MODE		CONFIG_SF_DEFAULT_MODE
#define CONFIG_ENV_SPI_MAX_HZ		CONFIG_SF_DEFAULT_SPEED
#define CONFIG_SYS_DCACHE_OFF
#endif

#ifdef CONFIG_CMD_SATA
#define CONFIG_DWC_AHSATA
#define CONFIG_SYS_SATA_MAX_DEVICE	1
#define CONFIG_DWC_AHSATA_PORT_ID	0
#define CONFIG_DWC_AHSATA_BASE_ADDR	SATA_ARB_BASE_ADDR
#define CONFIG_LBA48
#define CONFIG_LIBATA
#endif

#ifdef IWCONFIG_SYS_USE_SPINOR
#define CONFIG_CMD_SF
#define CONFIG_SPI_FLASH
#define CONFIG_SPI_FLASH_SST
#define CONFIG_MXC_SPI
#define CONFIG_SF_DEFAULT_BUS		0
#define CONFIG_SF_DEFAULT_SPEED		20000000
#define CONFIG_SF_DEFAULT_MODE		(SPI_MODE_0)
#endif


/* I2C Configs */
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_MXC_I2C1		/* enable I2C bus 1 */
#define CONFIG_SYS_I2C_MXC_I2C2		/* enable I2C bus 2 */
#define CONFIG_SYS_I2C_MXC_I2C3		/* enable I2C bus 3 */
#ifdef CONFIG_TARGET_MX6_IWG15M_SM
#define CONFIG_SYS_I2C_BASE		I2C1_BASE_ADDR
#else
#define CONFIG_SYS_I2C_BASE		I2C2_BASE_ADDR
#endif
#define CONFIG_SYS_I2C_SPEED		100000
#define CONFIG_SYS_I2C_SLAVE		0x8

/* PMIC */
#define CONFIG_POWER
#define CONFIG_POWER_I2C
#define CONFIG_POWER_PFUZE100
#define CONFIG_POWER_PFUZE100_I2C_ADDR	0x08

#ifndef CONFIG_SYS_DCACHE_OFF
#define CONFIG_CMD_CACHE
#endif
#endif /* __MX6_IWG15M_COMMON_CONFIG_H */
