# Copyright (C) 2013-2016 Freescale Semiconductor
# Released under the MIT license (see COPYING.MIT for the terms)

SUMMARY = "Linux Kernel provided and supported by Freescale"
DESCRIPTION = "Linux Kernel provided and supported by Freescale with focus on \
i.MX Family Reference Boards. It includes support for many IPs such as GPU, VPU and IPU."

require recipes-kernel/linux/linux-imx.inc

DEPENDS += "lzop-native bc-native"

SRCBRANCH = "imx_4.1.15_2.0.0_ga"
LOCALVERSION = "-${SRCBRANCH}"
KERNEL_SRC ?= "git://source.codeaurora.org/external/imx/linux-imx.git;protocol=https"
SRCREV = "30278abfe0977b1d2f065271ce1ea23c0e2d1b6e"
SRC_URI = "${KERNEL_SRC};branch=${SRCBRANCH} \
	    file://PATCH002-iW-PREPZ-SC-01-R3.0-REL1.0-Linux4.1.15_Kernel_basic_customization.patch"

DEFAULT_PREFERENCE = "1"

KERNEL_DEFCONFIG_imx6qdl-iwg15-sm = "${S}/arch/arm/configs/iw_rainbowg15m_sm_defconfig"

# Pull in the devicetree files into the rootfs
RDEPENDS_${KERNEL_PACKAGE_NAME}-base += "kernel-devicetree"

DO_CONFIG_V7_COPY = "no"
DO_CONFIG_V7_COPY_mx6 = "yes"
DO_CONFIG_V7_COPY_mx6ul = "yes"
DO_CONFIG_V7_COPY_mx7 = "yes"

do_copy_defconfig () {
   # copy latest defconfig for iw_rainbowg15_defconfig to use
   cp ${KERNEL_DEFCONFIG} ${B}/.config
   cp ${KERNEL_DEFCONFIG} ${B}/../defconfig
}
addtask copy_defconfig before do_preconfigure after do_patch

COMPATIBLE_MACHINE = "(imx6qdl-iwg15-sm)"

