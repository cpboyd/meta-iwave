require u-boot-common_${PV}.inc
require u-boot-fw-utils.inc

SRC_URI += "file://default-gcc.patch"

do_compile () {
	oe_runmake ${UBOOT_MACHINE}
	oe_runmake env
}
