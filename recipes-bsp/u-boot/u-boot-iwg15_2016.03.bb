# Copyright (c) 2015 iWave Systems Technologies Pvt. Ltd.

DESCRIPTION = "U-Boot provided by Freescale with focus on  i.MX reference boards."
require recipes-bsp/u-boot/u-boot.inc

PROVIDES += "u-boot"

LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://Licenses/gpl-2.0.txt;md5=b234ee4d69f5fce4486a80fdaf4a4263"

SRCBRANCH = "imx_v2016.03_4.1.15_2.0.0_ga"
UBOOT_SRC ?= "git://git.freescale.com/imx/uboot-imx.git;protocol=git"
SRCREV = "0ec2a019117bb2d59b9672a145b4684313d92782"
SRC_URI = "${UBOOT_SRC};branch=${SRCBRANCH} \
		file://PATCH001-iW-PREPZ-SC-01-R3.0-REL1.0-Linux4.1.15_UBoot_basic_customization.patch"

S = "${WORKDIR}/git"

inherit fsl-u-boot-localversion

LOCALVERSION ?= "-${SRCBRANCH}"

PACKAGE_ARCH = "${MACHINE_ARCH}"
COMPATIBLE_MACHINE = "(mx6|mx6ul|mx7)"

                                              