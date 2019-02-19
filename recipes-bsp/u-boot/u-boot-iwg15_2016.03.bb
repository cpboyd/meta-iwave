# Copyright (c) 2015 iWave Systems Technologies Pvt. Ltd.

DESCRIPTION = "U-Boot provided by Freescale with focus on  i.MX reference boards."
require recipes-bsp/u-boot/u-boot.inc
require u-boot-common.inc

SRC_URI += " \
		file://PATCH001-iW-PREPZ-SC-01-R3.0-REL1.0-Linux4.1.15_UBoot_basic_customization.patch"

inherit fsl-u-boot-localversion

LOCALVERSION ?= "-${SRCBRANCH}"

PROVIDES += "u-boot"

PACKAGE_ARCH = "${MACHINE_ARCH}"
COMPATIBLE_MACHINE = "(imx6qdl-iwg15-sm)"

                                              
