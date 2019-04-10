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

#ifndef __MX6_IWG15M_SM_CONFIG_H
#define __MX6_IWG15M_SM_CONFIG_H

#include <asm/arch/imx-regs.h>
#include <asm/mach-imx/gpio.h>

#ifdef CONFIG_SPL
#define CONFIG_SPL_LIBCOMMON_SUPPORT
#define CONFIG_SPL_MMC_SUPPORT
#include "imx6_spl.h"
#endif

#define CONFIG_MXC_UART_BASE		UART2_BASE
#define CONSOLE_DEV			"ttymxc1"

#include "mx6_iwg15_common.h"
#include "mx6_common.h"

#define CONFIG_SYS_FSL_USDHC_NUM	2
#define CONFIG_SYS_MMC_ENV_DEV		1	/* SDHC3 */
#define CONFIG_SYS_MMC_ENV_PART		0	/* user partition */

#ifdef CONFIG_SYS_PROMPT
#undef CONFIG_SYS_PROMPT
#endif
#define CONFIG_SYS_PROMPT		"iWave-G15 > "

#ifdef IWCONFIG_SYS_USE_SPINOR
#define CONFIG_SF_DEFAULT_CS		0
#endif

/*
 * imx6 q/dl/solo pcie would be failed to work properly in kernel, if
 * the pcie module is iniialized/enumerated both in uboot and linux
 * kernel.
 * rootcause:imx6 q/dl/solo pcie don't have the reset mechanism.
 * it is only be RESET by the POR. So, the pcie module only be
 * initialized/enumerated once in one POR.
 * Set to use pcie in kernel defaultly, mask the pcie config here.
 * Remove the mask freely, if the uboot pcie functions, rather than
 * the kernel's, are required.
 */
/* #define CONFIG_CMD_PCI */
#ifdef CONFIG_CMD_PCI
#define CONFIG_PCI
#define CONFIG_PCI_PNP
#define CONFIG_PCI_SCAN_SHOW
#define CONFIG_PCIE_IMX
#define CONFIG_PCIE_IMX_PERST_GPIO	IMX_GPIO_NR(7, 12)
#define CONFIG_PCIE_IMX_POWER_GPIO	IMX_GPIO_NR(3, 19)
#endif

#define BSP_VERSION			"iW-PREPZ-SC-01-R3.0-REL1.0-Linux4.1.15"

/* PMIC */
#define CONFIG_POWER
#define CONFIG_POWER_I2C
#define CONFIG_POWER_PFUZE100
#define CONFIG_POWER_PFUZE100_I2C_ADDR	0x08

/* USB Configs */
#ifdef CONFIG_CMD_USB
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#define CONFIG_USB_ETHER_ASIX
#define CONFIG_MXC_USB_PORTSC		(PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS		0
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2 /* Enabled USB controller number */
#endif

#endif /* __MX6_IWG15M_SM_CONFIG_H */
