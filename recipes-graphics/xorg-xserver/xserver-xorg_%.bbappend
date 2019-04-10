# Invert Y-axis for iWave dev kit touchscreen
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append_mx6iwave = " \
    file://conf/11-stmpe.conf \
    file://conf/99-stmpe.conf \
"

do_install_append_mx6iwave () {
    install -m 0644 ${WORKDIR}/conf/11-stmpe.conf ${D}/${datadir}/X11/xorg.conf.d/
    install -m 0644 ${WORKDIR}/conf/99-stmpe.conf ${D}/${datadir}/X11/xorg.conf.d/
}
