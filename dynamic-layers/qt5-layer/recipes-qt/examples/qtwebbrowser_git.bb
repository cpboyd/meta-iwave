DESCRIPTION = "Qt Web Browser"
LICENSE = "GPL-3.0 | The-Qt-Company-Commercial"
LIC_FILES_CHKSUM = "file://LICENSE.GPLv3;md5=a40e2bb02b1ac431f461afd03ff9d1d6"

inherit qmake5
require recipes-qt/qt5/qt5.inc
require recipes-qt/qt5/qt5-git.inc

SRC_URI = " \
    git://github.com/cpboyd/qtweb-kiosk.git;protocol=ssh \
"
SRCREV = "c6adf867bbff1bf7e4ee744d2c5af4c520211563"

DEPENDS = "qtwebengine"
RDEPENDS_${PN} = " \
	ttf-roboto \
	qtdeclarative-qmlplugins \
	qtquickcontrols-qmlplugins \
	qtvirtualkeyboard-qmlplugins \
    qtwebengine-qmlplugins \
"

do_install_append() {
	install -d ${D}${datadir}/${PN}
	mv ${D}/data/user/qt/qtwebbrowser-app/* ${D}${datadir}/${PN}
	rm -rf ${D}/data
}

FILES_${PN} += "${datadir}/${PN}"
FILES_${PN}-dbg += "${datadir}/${PN}/.debug"
