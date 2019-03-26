# Invert Y-axis for iWave dev kit touchscreen
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append_imx6qdl-iwg15-sm = " \
    file://conf/11-stmpe.conf \
    file://conf/99-stmpe.conf \
"

do_install_append_imx6qdl-iwg15-sm () {
    install -m 0644 ${WORKDIR}/conf/11-stmpe.conf ${D}/${datadir}/X11/xorg.conf.d/
    install -m 0644 ${WORKDIR}/conf/99-stmpe.conf ${D}/${datadir}/X11/xorg.conf.d/
}
