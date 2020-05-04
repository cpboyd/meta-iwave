# Copyright (C) 2012-2019 O.S. Systems Software LTDA.
# Released under the MIT license (see COPYING.MIT for the terms)

inherit fsl-u-boot-localversion

DESCRIPTION = "i.MX U-Boot suppporting i.MX reference boards."

LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://Licenses/gpl-2.0.txt;md5=b234ee4d69f5fce4486a80fdaf4a4263"

SRCBRANCH = "lf-5.4.y_v2019.04"
UBOOT_SRC ?= "git://source.codeaurora.org/external/imx/uboot-imx.git;protocol=https"
SRCREV = "228843cdf5435d4bd69f42a6015f78761ff4cc0d"
SRC_URI = "${UBOOT_SRC};branch=${SRCBRANCH} \
	file://0001-iwave.patch \
	file://board/ \
	file://configs/mx6_iwg15m_sm_defconfig \
	file://configs/mx6_iwg15_common.h \
	file://configs/mx6_iwg15m_sm.h \
"

DEPENDS += "flex-native bison-native bc-native dtc-native"

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

inherit fsl-u-boot-localversion

LOCALVERSION ?= "-${SRCBRANCH}"

BOOT_TOOLS = "imx-boot-tools"

do_configure_prepend() {
	# install config files
	cp ${WORKDIR}/configs/*_defconfig ${S}/configs
	cp ${WORKDIR}/configs/*.h ${S}/include/configs

	mkdir -p ${S}/board/freescale/mx6_iwg15m_sm
	cp ${WORKDIR}/board/* ${S}/board/freescale/mx6_iwg15m_sm
}
