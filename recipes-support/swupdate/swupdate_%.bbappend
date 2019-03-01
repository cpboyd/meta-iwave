FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "file://swupdate.cfg \
            file://swupdate.default \
"

do_install_append() {
    # Config file for swupdate
    install -d ${D}${sysconfdir}/
    install -m 644 ${WORKDIR}/swupdate.cfg ${D}${sysconfdir}

    # Script to get hardware/software revisions, and load config file
    install -d ${D}${sysconfdir}/default/
    install -m 755 ${WORKDIR}/swupdate.default ${D}${sysconfdir}/default/swupdate
}