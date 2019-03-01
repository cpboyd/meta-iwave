require u-boot-common_${PV}.inc
require u-boot-fw-utils.inc

EXTRA_OEMAKE_class-cross = 'HOSTCC="${CC} ${CFLAGS} ${LDFLAGS}" V=1'

do_compile () {
	oe_runmake ${UBOOT_MACHINE}
	oe_runmake envtools
}