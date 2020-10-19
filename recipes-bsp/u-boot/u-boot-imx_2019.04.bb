# Copyright (C) 2020 Christopher Boyd
# Copyright 2017-2019 NXP

require recipes-bsp/u-boot/u-boot.inc
require u-boot-imx-common.inc

SRC_URI += " \
	file://0001-Add-target-to-generate-initial-environment.patch \
	file://0001-iwave.patch \
	file://board/ \
	file://configs/mx6_iwg15m_sm_defconfig \
	file://configs/mx6_iwg15_common.h \
	file://configs/mx6_iwg15m_sm.h \
"

PROVIDES += "u-boot"

do_configure_prepend() {
	# install config files
	cp ${WORKDIR}/configs/*_defconfig ${S}/configs
	cp ${WORKDIR}/configs/*.h ${S}/include/configs

	mkdir -p ${S}/board/freescale/mx6_iwg15m_sm
	cp ${WORKDIR}/board/* ${S}/board/freescale/mx6_iwg15m_sm
}

PACKAGE_ARCH = "${MACHINE_ARCH}"
COMPATIBLE_MACHINE = "(mx6|mx7|mx8)"
