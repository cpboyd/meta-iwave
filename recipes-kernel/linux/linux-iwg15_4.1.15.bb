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
        file://0001-custom-dts.patch \
        file://0001-iwave-linux_${PV}.patch \
        file://0001-mmc-block-Use-the-mmc-host-device-index.patch \
        file://0001-pwm-imx-Add-polarity-inversion-support.patch \
        file://0002-specify-arm-arch-for-modules.patch \
        file://defconfig \
"

DEFAULT_PREFERENCE = "1"

# Pull in the devicetree files into the rootfs
RDEPENDS_${KERNEL_PACKAGE_NAME}-base += "kernel-devicetree"

COMPATIBLE_MACHINE = "(imx6qdl-iwg15-sm)"

