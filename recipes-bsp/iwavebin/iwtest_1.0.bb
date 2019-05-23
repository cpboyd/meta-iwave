# Copyright (c) 2015 iWave Systems Technologies Pvt. Ltd.

DESCRIPTION = "iwtest binaries"
PROVIDES += "iwtest"
LICENSE = "GPLv2+"

COMPATIBLE_MACHINE = "(mx6|mx6ul|mx7)"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"
INHIBIT_PACKAGE_STRIP = "1"

LIC_FILES_CHKSUM = "file://GPL-2;md5=94d55d512a9ba36caa9b7df079bae19f"

SRC_URI = " \
	file://wvga.bin \
	file://svga.bin \
	file://wqvga.bin \
	file://720p.bin \
	file://1080p.bin \
	file://Cutie.mpeg \
	file://panda.mp4 \
	file://tfr.mp4 \
	file://dip-sw.c \
	file://led.c \
	file://GPL-2 \
"
FILES_${PN} = "iwtest"
S = "${WORKDIR}"

do_compile() {
	${CC} dip-sw.c  -o dip-sw.out
	${CC} led.c     -o led.out
}

do_install() {
	mkdir -p ${D}/iwtest
	install -m 0644 ${S}/wvga.bin ${D}/iwtest
	install -m 0644 ${S}/svga.bin ${D}/iwtest
	install -m 0644 ${S}/wqvga.bin ${D}/iwtest
	install -m 0644 ${S}/720p.bin ${D}/iwtest
	install -m 0644 ${S}/1080p.bin ${D}/iwtest
	install -m 0644 ${S}/Cutie.mpeg ${D}/iwtest
	install -m 0644 ${S}/panda.mp4 ${D}/iwtest
	install -m 0644 ${S}/tfr.mp4 ${D}/iwtest
	install -m 0644 ${S}/dip-sw.out ${D}/iwtest
	install -m 0644 ${S}/led.out ${D}/iwtest
	chmod   +x ${D}/iwtest/*.out
}
