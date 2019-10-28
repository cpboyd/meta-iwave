/*
 * Copyright (c) 2017 iWave Systems Technologies Pvt. Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; If not, see <http://www.gnu.org/licenses/>.
 */

#include <asm/arch/clock.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/iomux.h>
#include <asm/arch/mx6-pins.h>
#include <asm/mach-imx/spi.h>
#include <linux/errno.h>
#include <asm/gpio.h>
#include <asm/mach-imx/mxc_i2c.h>
#include <asm/mach-imx/iomux-v3.h>
#include <asm/mach-imx/boot_mode.h>
#include <asm/mach-imx/video.h>
#include <mmc.h>
#include <fsl_esdhc.h>
#include <micrel.h>
#include <miiphy.h>
#include <netdev.h>
#include <asm/arch/mxc_hdmi.h>
#include <asm/arch/crm_regs.h>
#include <asm/io.h>
#include <asm/arch/sys_proto.h>
#include <i2c.h>
#include <input.h>
#include <power/pmic.h>
#include <power/pfuze100_pmic.h>
#include "../common/pfuze.h"
#include <usb.h>
#include <usb/ehci-ci.h>
#include <asm/arch/mx6-ddr.h>
#ifdef CONFIG_SATA
#include <asm/mach-imx/sata.h>
#endif
#ifdef CONFIG_FSL_FASTBOOT
#include <fsl_fastboot.h>
#endif /*CONFIG_FSL_FASTBOOT*/
#include "mx6_iwg15m_sm.h"

DECLARE_GLOBAL_DATA_PTR;

#define UART_PAD_CTRL  (PAD_CTL_PUS_100K_UP |			\
	PAD_CTL_SPEED_MED | PAD_CTL_DSE_40ohm |			\
	PAD_CTL_SRE_FAST  | PAD_CTL_HYS)

#define USDHC_PAD_CTRL (PAD_CTL_PUS_47K_UP |			\
	PAD_CTL_SPEED_LOW | PAD_CTL_DSE_80ohm |			\
	PAD_CTL_SRE_FAST  | PAD_CTL_HYS)

#define ENET_PAD_CTRL  (PAD_CTL_PUS_100K_UP |			\
	PAD_CTL_SPEED_MED | PAD_CTL_DSE_40ohm | PAD_CTL_HYS)

#define SPI_PAD_CTRL (PAD_CTL_HYS | PAD_CTL_SPEED_MED | \
	PAD_CTL_DSE_40ohm | PAD_CTL_SRE_FAST)

#define I2C_PAD_CTRL  (PAD_CTL_PUS_100K_UP |			\
	PAD_CTL_SPEED_MED | PAD_CTL_DSE_40ohm | PAD_CTL_HYS |	\
	PAD_CTL_ODE | PAD_CTL_SRE_FAST)

#define I2C_PMIC	0
#define I2C_PAD 	MUX_PAD_CTRL(I2C_PAD_CTRL)

#define BACKLIGHT_EN	IMX_GPIO_NR(1, 17)
#define LCD_PWR_EN	IMX_GPIO_NR(4, 13)
#define LCD_RESET	IMX_GPIO_NR(7, 11)
#define HDMI_CEC_EN	IMX_GPIO_NR(1, 21)
#define COM_RESET_GPIO	IMX_GPIO_NR(1, 11)

#define is_mx6dlsolo()	(is_mx6dl() || is_mx6solo())

int dram_init(void)
{
	if (is_mx6solo())
		gd->ram_size = get_ram_size((void *)PHYS_SDRAM, PHYS_SDRAM_SIZE_512MB);
	else
		gd->ram_size = get_ram_size((void *)PHYS_SDRAM, PHYS_SDRAM_SIZE);

	return 0;
}

static iomux_v3_cfg_t const uart2_pads[] = {
	IOMUX_PADS(PAD_EIM_D27__UART2_RX_DATA | MUX_PAD_CTRL(UART_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_D26__UART2_TX_DATA | MUX_PAD_CTRL(UART_PAD_CTRL)),
};

static iomux_v3_cfg_t const enet_pads[] = {
	IOMUX_PADS(PAD_ENET_MDIO__ENET_MDIO	| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_ENET_MDC__ENET_MDC	| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_TXC__RGMII_TXC	| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_TD0__RGMII_TD0	| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_TD1__RGMII_TD1	| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_TD2__RGMII_TD2	| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_TD3__RGMII_TD3	| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_TX_CTL__RGMII_TX_CTL | MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_ENET_REF_CLK__ENET_TX_CLK | MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_RXC__RGMII_RXC	| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_RD0__RGMII_RD0	| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_RD1__RGMII_RD1	| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_RD2__RGMII_RD2	| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_RD3__RGMII_RD3	| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_RX_CTL__RGMII_RX_CTL | MUX_PAD_CTRL(ENET_PAD_CTRL)),
};

static void setup_iomux_enet(void)
{
	SETUP_IOMUX_PADS(enet_pads);
}

static iomux_v3_cfg_t const usdhc3_pads[] = {
	IOMUX_PADS(PAD_SD3_DAT0__SD3_DATA0 | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD3_DAT1__SD3_DATA1 | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD3_DAT2__SD3_DATA2 | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD3_DAT3__SD3_DATA3 | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD3_CLK__SD3_CLK   | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD3_CMD__SD3_CMD   | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_D25__GPIO3_IO25 | MUX_PAD_CTRL(NO_PAD_CTRL)), /* CD */
};

static iomux_v3_cfg_t const usdhc4_pads[] = {
	IOMUX_PADS(PAD_SD4_CLK__SD4_CLK   | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD4_CMD__SD4_CMD   | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD4_DAT0__SD4_DATA0 | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD4_DAT1__SD4_DATA1 | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD4_DAT2__SD4_DATA2 | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD4_DAT3__SD4_DATA3 | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD4_DAT4__SD4_DATA4 | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD4_DAT5__SD4_DATA5 | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD4_DAT6__SD4_DATA6 | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD4_DAT7__SD4_DATA7 | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
};

#ifdef CONFIG_MXC_SPI
static iomux_v3_cfg_t const ecspi1_pads[] = {
	IOMUX_PADS(PAD_EIM_D16__ECSPI1_SCLK | MUX_PAD_CTRL(SPI_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_D17__ECSPI1_MISO | MUX_PAD_CTRL(SPI_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_D18__ECSPI1_MOSI | MUX_PAD_CTRL(SPI_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_EB2__GPIO2_IO30  | MUX_PAD_CTRL(NO_PAD_CTRL)),
};

static void setup_spi(void)
{
	SETUP_IOMUX_PADS(ecspi1_pads);
}

int board_spi_cs_gpio(unsigned bus, unsigned cs)
{
	return (bus == 0 && cs == 0) ? (IMX_GPIO_NR(2, 30)) : -1;
}
#endif

static iomux_v3_cfg_t const bl_pads[] = {
	IOMUX_PADS(PAD_SD1_DAT1__GPIO1_IO17 | MUX_PAD_CTRL(ENET_PAD_CTRL)),
};

static void setup_iomux_backlight_off(void)
{
	/* Setup backlight */
	SETUP_IOMUX_PADS(bl_pads);
	/* Turn off backlight until display is ready */
	gpio_request(BACKLIGHT_EN, "Display Backlight Enable");
	gpio_direction_output(BACKLIGHT_EN, 1);
}

#ifdef CONFIG_SYS_I2C
struct i2c_pads_info i2c_pad_dq_info0 = {
	.scl = {
		.i2c_mode = MX6Q_PAD_EIM_D21__I2C1_SCL | I2C_PAD,
		.gpio_mode = MX6Q_PAD_EIM_D21__GPIO3_IO21 | I2C_PAD,
		.gp = IMX_GPIO_NR(3, 21)
	},
	.sda = {
		.i2c_mode = MX6Q_PAD_EIM_D28__I2C1_SDA | I2C_PAD,
		.gpio_mode = MX6Q_PAD_EIM_D28__GPIO3_IO28 | I2C_PAD,
		.gp = IMX_GPIO_NR(3, 28)
	},
};

struct i2c_pads_info i2c_pad_dl_info0 = {
	.scl = {
		.i2c_mode = MX6DL_PAD_EIM_D21__I2C1_SCL | I2C_PAD,
		.gpio_mode = MX6DL_PAD_EIM_D21__GPIO3_IO21 | I2C_PAD,
		.gp = IMX_GPIO_NR(3, 21)
	},
	.sda = {
		.i2c_mode = MX6DL_PAD_EIM_D28__I2C1_SDA | I2C_PAD,
		.gpio_mode = MX6DL_PAD_EIM_D28__GPIO3_IO28 | I2C_PAD,
		.gp = IMX_GPIO_NR(3, 28)
	},
};

struct i2c_pads_info i2c_pad_dq_info2 = {
	.scl = {
		.i2c_mode = MX6Q_PAD_GPIO_3__I2C3_SCL | I2C_PAD,
		.gpio_mode = MX6Q_PAD_GPIO_3__GPIO1_IO03 | I2C_PAD,
		.gp = IMX_GPIO_NR(1, 3)
	},
	.sda = {
		.i2c_mode = MX6Q_PAD_GPIO_6__I2C3_SDA | I2C_PAD,
		.gpio_mode = MX6Q_PAD_GPIO_6__GPIO1_IO06 | I2C_PAD,
		.gp = IMX_GPIO_NR(1, 6)
	},
};

struct i2c_pads_info i2c_pad_dl_info2 = {
	.scl = {
		.i2c_mode = MX6DL_PAD_GPIO_3__I2C3_SCL | I2C_PAD,
		.gpio_mode = MX6DL_PAD_GPIO_3__GPIO1_IO03 | I2C_PAD,
		.gp = IMX_GPIO_NR(1, 3)
	},
	.sda = {
		.i2c_mode = MX6DL_PAD_GPIO_6__I2C3_SDA | I2C_PAD,
		.gpio_mode = MX6DL_PAD_GPIO_6__GPIO1_IO06 | I2C_PAD,
		.gp = IMX_GPIO_NR(1, 6)
	},
};
#endif

static void setup_iomux_uart(void)
{
	SETUP_IOMUX_PADS(uart2_pads);
}

#ifdef CONFIG_FSL_ESDHC
struct fsl_esdhc_cfg usdhc_cfg[2] = {
	{USDHC3_BASE_ADDR},
	{USDHC4_BASE_ADDR},
};

#define USDHC3_CD_GPIO	IMX_GPIO_NR(3, 25)

int board_mmc_get_env_dev(int devno)
{
	return (devno > 1) ? devno - 1 : devno;
}

int mmc_map_to_kernel_blk(int devno)
{
	return devno + 2;
}

int board_mmc_getcd(struct mmc *mmc)
{
	struct fsl_esdhc_cfg *cfg = (struct fsl_esdhc_cfg *)mmc->priv;
	int ret = 0;

	switch (cfg->esdhc_base) {
	case USDHC3_BASE_ADDR:
		ret = !gpio_get_value(USDHC3_CD_GPIO);
		break;
	case USDHC4_BASE_ADDR:
		ret = 1; /* eMMC/uSDHC4 is always present */
		break;
	}

	return ret;
}

int board_mmc_init(bd_t *bis)
{
	int ret;
	int i;

	/*
	 * According to the board_mmc_init() the following map is done:
	 * (U-boot device node)    (Physical Port)
	 * mmc0                    SD3
	 * mmc1                    eMMC
	 */
	for (i = 0; i < CONFIG_SYS_FSL_USDHC_NUM; i++) {
		switch (i) {
		case 0:
			SETUP_IOMUX_PADS(usdhc3_pads);
			gpio_direction_input(USDHC3_CD_GPIO);
			usdhc_cfg[0].sdhc_clk = mxc_get_clock(MXC_ESDHC3_CLK);
			break;
		case 1:
			SETUP_IOMUX_PADS(usdhc4_pads);
			usdhc_cfg[1].sdhc_clk = mxc_get_clock(MXC_ESDHC4_CLK);
			break;
		default:
			printf("Warning: you configured more USDHC controllers"
				"(%d) then supported by the board (%d)\n",
				i + 1, CONFIG_SYS_FSL_USDHC_NUM);
			return -EINVAL;
		}

		ret = fsl_esdhc_initialize(bis, &usdhc_cfg[i]);
		if (ret)
			return ret;
	}

	return 0;
}
#endif

#define MII_KSZ9031_EXT_MMD_ADD2	0x02
int mx6_rgmii_rework(struct phy_device *phydev)
{
	if (strcasecmp(phydev->drv->name, "Micrel ksz9031") == 0 &&
			((phydev->drv->uid & phydev->drv->mask) ==
			(phydev->phy_id & phydev->drv->mask))) {

		printf("Configuring PHY skew timing for %s\n",
			phydev->drv->name);

		/* IWG15M: ETHERNET: Final Skew settings for Rev4.0 PHY9031 */
		/* min rx/tx control */
		if (ksz9031_phy_extended_write(phydev,MII_KSZ9031_EXT_MMD_ADD2,
				MII_KSZ9031_EXT_RGMII_CTRL_SIG_SKEW, MII_KSZ9031_MOD_DATA_POST_INC_RW,0x0080) < 0)
			return -1;

		/* min rx data delay */
		if (ksz9031_phy_extended_write(phydev,MII_KSZ9031_EXT_MMD_ADD2,
				MII_KSZ9031_EXT_RGMII_RX_DATA_SKEW, MII_KSZ9031_MOD_DATA_POST_INC_RW,0x7787) < 0)
			return -1;
		/* min tx data delay */
		if (ksz9031_phy_extended_write(phydev,MII_KSZ9031_EXT_MMD_ADD2,
				MII_KSZ9031_EXT_RGMII_TX_DATA_SKEW, MII_KSZ9031_MOD_DATA_POST_INC_RW, 0x0000 ) < 0)
			return -1;
		/* max rx/tx clock delay */
		if (ksz9031_phy_extended_write(phydev,MII_KSZ9031_EXT_MMD_ADD2,
				MII_KSZ9031_EXT_RGMII_CLOCK_SKEW, MII_KSZ9031_MOD_DATA_POST_INC_RW,0x03ff) < 0)
			return -1;

		}

	return 0;
}

int board_phy_config(struct phy_device *phydev)
{
	mx6_rgmii_rework(phydev);

	if (phydev->drv->config)
		phydev->drv->config(phydev);

	return 0;
}

/* Check the u-boot LDO regultor mode set in u-boot 
 * 0 - ldo active mode
 * 1 - ldo bypass mode
 */
int check_uboot_ldobypass(void)
{
	char *ldo_check = NULL;
	ldo_check = env_get("uboot_ldo_bypass");
	ulong uboot_ldobypass = 0;
	if (NULL == ldo_check) {
		puts("env uboot_ldo_bypass not found!\n");
		return 0;
	}
	uboot_ldobypass = simple_strtoul(ldo_check, NULL, 16);
	if (uboot_ldobypass)
		return 1;
	return 0;
}

char *get_fdt_dev(void)
{
	char *fdt_dev = env_get("fdt_dev");
	if (fdt_dev == NULL) {
		return (is_mx6dq()) ? "imx6qd-iwg15m-sm" : "imx6dls-iwg15m-sm";
	}
	return fdt_dev;
}

int dynamic_fdt_file_selection(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	const int MAX_STR_LEN = 32;
	char filename[MAX_STR_LEN];
	char *mode = (check_1_2G() || !check_uboot_ldobypass()) ? "active" : "bypass";

	snprintf(filename, MAX_STR_LEN, "%s_ldo%s.dtb", get_fdt_dev(), mode);
	printf ("using %s\n", filename);
	env_set("fdt_file", filename);
	return 0;
}

U_BOOT_CMD(
	dynamicfdt, 1, 0, dynamic_fdt_file_selection,
	"Loading Device tree by checking Processor",
	""
);

static void unused_gpio_setup(void)
{
	int i;
	SETUP_IOMUX_PADS(unused_gpio_pads_pmic);
	for (i=0;i<ARRAY_SIZE(unused_gpio_pads_pmic);i++)
	{
		gpio_request(unused_gpio_pads_pmic[i], "unusedgpio");
		gpio_direction_input(unused_gpio_pmic[i]);
	}

}

static int get_som_revision(void)
{
	int i, rev=0;
	SETUP_IOMUX_PADS(board_config_pads_som);
	for (i=0;i<ARRAY_SIZE(board_config_pads_som);i++)
	{
		if (rev == 0x2)
			continue;
		gpio_request(board_config_pads_som[i], "SOM-Revision-GPIO");
		gpio_direction_input(board_config_gpio_som[i]);
		rev |= (gpio_get_value(board_config_gpio_som[i]) << i);
	}

	return rev;
}

static int get_bom_revision(int som_rev)
{
	int i, rev=0,bit_shift=0;
	SETUP_IOMUX_PADS(board_config_pads_bom);
	for (i=0;i<ARRAY_SIZE(board_config_pads_bom);i++) {
		/* Skip one bit for 3.0 SOM */
		if (som_rev > 2) {
			som_rev = 0;
			bit_shift=1;
			continue;
		}

		gpio_request(board_config_pads_bom[i], "BOM-Revision-GPIO");
		gpio_direction_input(board_config_gpio_bom[i]);
		/* Skip one bit for 3.0 SOM */
		if (bit_shift == 1)
			rev |= (gpio_get_value(board_config_gpio_bom[i]) << (i-1));
		else
			rev |= (gpio_get_value(board_config_gpio_bom[i]) << i);
	}

	return rev;
}

static void print_board_info(void)
{
	u32 unique_id1, unique_id2;

	struct ocotp_regs *ocotp = (struct ocotp_regs *)OCOTP_BASE_ADDR;
	struct fuse_bank *bank = &ocotp->bank[0];
	struct fuse_bank0_regs *fuse_bank0 =
		(struct fuse_bank0_regs *)bank->fuse_regs;

	unique_id1 = readl(&fuse_bank0->uid_low);
	unique_id2 = readl(&fuse_bank0->uid_high);

	printf ("\n");
	printf ("Board Info:\n");
	printf ("\tBSP Version     : %s\n", BSP_VERSION);
	printf ("\tSOM Version     : iW-PREPZ-AP-01-R%x.%x\n",get_som_revision()+1,get_bom_revision(get_som_revision()+1));
	printf ("\tCPU Unique ID   : 0x%08x%08x \n", unique_id2, unique_id1);
	printf ("\n");

}

/*
 * Do not overwrite the console
 * Use always serial for U-Boot console
 */
int overwrite_console(void)
{
	return 1;
}

int board_eth_init(bd_t *bis)
{
	setup_iomux_enet();
	return cpu_eth_init(bis);
}

int board_usb_phy_mode(int port)
{
	return USB_INIT_HOST;
}

int board_early_init_f(void)
{
	setup_iomux_uart();

	/* Power OFF the LCD Backlight */
	setup_iomux_backlight_off();

	return 0;
}

int board_init(void)
{
	/* address of boot parameters */
	gd->bd->bi_boot_params = PHYS_SDRAM + 0x100;

#ifdef CONFIG_MXC_SPI
	setup_spi();
#endif

#ifdef CONFIG_SYS_I2C
	if (is_mx6dq()) {
		setup_i2c(0, CONFIG_SYS_I2C_SPEED,
				CONFIG_SYS_I2C_SLAVE, &i2c_pad_dq_info0);
		setup_i2c(2, CONFIG_SYS_I2C_SPEED,
				CONFIG_SYS_I2C_SLAVE, &i2c_pad_dq_info2);
	} else if (is_mx6dlsolo()) {
		setup_i2c(0, CONFIG_SYS_I2C_SPEED,
				CONFIG_SYS_I2C_SLAVE, &i2c_pad_dl_info0);
		setup_i2c(2, CONFIG_SYS_I2C_SPEED,
				CONFIG_SYS_I2C_SLAVE, &i2c_pad_dl_info2);
	}
#endif

#ifdef CONFIG_SATA
	setup_sata();
#endif

	unused_gpio_setup();

	return 0;
}

#ifdef CONFIG_POWER
int power_init_board(void)
{
	struct pmic *pfuze;
	unsigned int reg;
	int ret;

	pfuze = pfuze_common_init(I2C_PMIC);
	if (!pfuze)
		return -ENODEV;

	ret = pfuze_mode_init(pfuze, APS_PFM);
	if (ret < 0)
		return ret;

	/* set SW1AB staby volatage 0.975V*/
	pmic_reg_read(pfuze, PFUZE100_SW1ABSTBY, &reg);
	reg &= ~0x3f;
	reg |= 0x1b;
	pmic_reg_write(pfuze, PFUZE100_SW1ABSTBY, reg);

	/* set SW1AB/VDDARM step ramp up time from 16us to 4us/25mV */
	pmic_reg_read(pfuze, PFUZE100_SW1ABCONF, &reg);
	reg &= ~0xc0;
	reg |= 0x40;
	pmic_reg_write(pfuze, PFUZE100_SW1ABCONF, reg);

	/* set SW1C staby volatage 0.975V*/
	pmic_reg_read(pfuze, PFUZE100_SW1CSTBY, &reg);
	reg &= ~0x3f;
	reg |= 0x1b;
	pmic_reg_write(pfuze, PFUZE100_SW1CSTBY, reg);

	/* set SW1C/VDDSOC step ramp up time to from 16us to 4us/25mV */
	pmic_reg_read(pfuze, PFUZE100_SW1CCONF, &reg);
	reg &= ~0xc0;
	reg |= 0x40;
	pmic_reg_write(pfuze, PFUZE100_SW1CCONF, reg);
	
      /* Since in IWG15M-SM, VGEN1, VGEN2, VGEN3, VGEN6 and SWBST is not used,
	 * disabling VGEN1, VGEN2, VGEN3, VGEN 6 and SWBST
	*/
	/* Disabli0ng VGEN1 */
	pmic_reg_read(pfuze, PFUZE100_VGEN1VOL, &reg);
	reg &= ~0x1f;
	pmic_reg_write(pfuze, PFUZE100_VGEN1VOL, reg);

	/* Disabling VGEN2 */
	pmic_reg_read(pfuze, PFUZE100_VGEN2VOL, &reg);
	reg &= ~0x1f;
	pmic_reg_write(pfuze, PFUZE100_VGEN2VOL, reg);

	/* Disabling VGEN3 */
	pmic_reg_read(pfuze, PFUZE100_VGEN3VOL, &reg);
	reg &= ~0x1f;
	pmic_reg_write(pfuze, PFUZE100_VGEN3VOL, reg);

	/* Disabling VGEN6 */
	pmic_reg_read(pfuze, PFUZE100_VGEN6VOL, &reg);
	reg &= ~0x1f;
	pmic_reg_write(pfuze, PFUZE100_VGEN6VOL, reg);

	/* Disabling SWBST */
	pmic_reg_read(pfuze, PFUZE100_SWBSTCON1, &reg);
	reg &= ~0x6f;
	pmic_reg_write(pfuze, PFUZE100_SWBSTCON1, reg);

	return 0;
}
#endif

#ifdef CONFIG_LDO_BYPASS_CHECK
#ifdef CONFIG_POWER
void ldo_mode_set(int ldo_bypass)
{
	unsigned int value;
	int is_400M;
	unsigned char vddarm;
	struct pmic *p = pmic_get("PFUZE100");

	if (!p) {
		printf("No PMIC found!\n");
		return;
	}

	/* increase VDDARM/VDDSOC to support 1.2G chip */
	if (check_1_2G()) {
		ldo_bypass = 0;	/* ldo_enable on 1.2G chip */
		printf("1.2G chip, increase VDDARM_IN/VDDSOC_IN\n");
		/* increase VDDARM to 1.425V */
		pmic_reg_read(p, PFUZE100_SW1ABVOL, &value);
		value &= ~0x3f;
		value |= 0x2d;
		pmic_reg_write(p, PFUZE100_SW1ABVOL, value);
		/* increase VDDSOC to 1.425V */
		pmic_reg_read(p, PFUZE100_SW1CVOL, &value);
		value &= ~0x3f;
		value |= 0x2d;
		pmic_reg_write(p, PFUZE100_SW1CVOL, value);
	}
	/* switch to ldo_bypass mode , boot on 800Mhz */
	if (ldo_bypass) {
		prep_anatop_bypass();
		/* decrease VDDARM for 400Mhz DQ:1.1V, DL:1.275V */
		pmic_reg_read(p, PFUZE100_SW1ABVOL, &value);
		value &= ~0x3f;
		if (is_mx6dl())
			value |= 0x27;
		else
			value |= 0x20;

		pmic_reg_write(p, PFUZE100_SW1ABVOL, value);
		/* increase VDDSOC to 1.3V */
		pmic_reg_read(p, PFUZE100_SW1CVOL, &value);
		value &= ~0x3f;
		value |= 0x28;
		pmic_reg_write(p, PFUZE100_SW1CVOL, value);

		/*
		 * MX6Q/DQP:
		 * VDDARM:1.15V@800M; VDDSOC:1.175V@800M
		 * VDDARM:0.975V@400M; VDDSOC:1.175V@400M
		 * MX6DL:
		 * VDDARM:1.175V@800M; VDDSOC:1.175V@800M
		 * VDDARM:1.075V@400M; VDDSOC:1.175V@400M
		 */
		is_400M = set_anatop_bypass(2);
		if (is_400M) {
			if (is_mx6dl())
				vddarm = 0x1f;
			else
				vddarm = 0x1b;
		} else {
			if (is_mx6dl())
				vddarm = 0x23;
			else
				vddarm = 0x22;
		}
		pmic_reg_read(p, PFUZE100_SW1ABVOL, &value);
		value &= ~0x3f;
		value |= vddarm;
		pmic_reg_write(p, PFUZE100_SW1ABVOL, value);

		/* decrease VDDSOC to 1.175V */
		pmic_reg_read(p, PFUZE100_SW1CVOL, &value);
		value &= ~0x3f;
		value |= 0x23;
		pmic_reg_write(p, PFUZE100_SW1CVOL, value);

		finish_anatop_bypass();
		printf("switch to ldo_bypass mode!\n");
	}
}
#endif
#endif

#ifdef CONFIG_CMD_BMODE
static const struct boot_mode board_boot_modes[] = {
	/* 8 bit bus width */
	{"sd1-8", MAKE_CFGVAL(0x60, 0x40, 0x00, 0x00)},
	{"emmc",  MAKE_CFGVAL(0x60, 0x58, 0x00, 0x00)},
	/* 4 bit bus width */
	{"sd3",   MAKE_CFGVAL(0x40, 0x30, 0x00, 0x00)},
	{"sd1-4", MAKE_CFGVAL(0x40, 0x20, 0x00, 0x00)},
	/* spi flash */
	{"spi",   MAKE_CFGVAL(0x30, 0x00, 0x00, 0x08)},
	/* sata */
	{"sata",  MAKE_CFGVAL(0x20, 0x00, 0x00, 0x00)},
	{NULL,   0},
};
#endif

int board_late_init(void)
{
#ifdef CONFIG_CMD_BMODE
	add_board_boot_modes(board_boot_modes);
#endif

   print_board_info();

#ifdef CONFIG_ENV_IS_IN_MMC
	board_late_mmc_env_init();
#endif

	return 0;
}

int checkboard(void)
{
	u32 cpurev;

	cpurev = get_cpu_rev();
	if (is_mx6dqp())
		printf("Board: i.MX%sP iW-RAINBOW-G15M-SM\n",get_imx_type((cpurev & 0xFF000) >> 12));
	else
		printf("Board: i.MX%s iW-RAINBOW-G15M-SM\n",get_imx_type((cpurev & 0xFF000) >> 12));

	printf("Boot Device: ");
	switch (get_boot_device()) {
	case SATA_BOOT:
		printf("SATA\n");
		break;
	case SPI_NOR_BOOT:
		printf("SPI NOR\n");
		break;
	case SD1_BOOT:
		printf("STANDARD SD\n");
		break;
	case SD3_BOOT:
		printf("MICRO SD\n");
		break;
	case MMC4_BOOT:
		printf("MMC\n");
		break;
	case UNKNOWN_BOOT:
	default:
		printf("UNKNOWN\n");
		break;
	}

	return 0;
}
