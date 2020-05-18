# Copyright (C) 2020 Christopher Boyd

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI += " \
	file://0001-iwave.patch \
	file://board/ \
	file://configs/mx6_iwg15m_sm_defconfig \
	file://configs/mx6_iwg15_common.h \
	file://configs/mx6_iwg15m_sm.h \
"

do_configure_prepend() {
	# install config files
	cp ${WORKDIR}/configs/*_defconfig ${S}/configs
	cp ${WORKDIR}/configs/*.h ${S}/include/configs

	mkdir -p ${S}/board/freescale/mx6_iwg15m_sm
	cp ${WORKDIR}/board/* ${S}/board/freescale/mx6_iwg15m_sm
}
