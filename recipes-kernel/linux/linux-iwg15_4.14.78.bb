# Copyright (C) 2013-2016 Freescale Semiconductor
# Released under the MIT license (see COPYING.MIT for the terms)

SUMMARY = "Linux Kernel provided and supported by Freescale"
DESCRIPTION = "Linux Kernel provided and supported by Freescale with focus on \
i.MX Family Reference Boards. It includes support for many IPs such as GPU, VPU and IPU."

require recipes-kernel/linux/linux-imx.inc

DEPENDS += "lzop-native bc-native"

KERNEL_SRC ?= "git://source.codeaurora.org/external/imx/linux-imx;protocol=https"
SRCBRANCH = "imx_4.14.78_1.0.0_ga"
LOCALVERSION = "-${SRCBRANCH}"
SRCREV = "94da7bdc489ba686d868bcf80678a37cae22673e"
SRC_URI = "${KERNEL_SRC};branch=${SRCBRANCH} \
        file://0001-custom-dts.patch \
        file://0001-iwave-linux_${PV}.patch \
        file://defconfig \
"

DEFAULT_PREFERENCE = "1"

# Pull in the devicetree files into the rootfs
RDEPENDS_${KERNEL_PACKAGE_NAME}-base += "kernel-devicetree"

COMPATIBLE_MACHINE = "(mx6|mx7|mx8)"
