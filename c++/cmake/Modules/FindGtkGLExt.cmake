SET(GTKGLEXT_FOUND 0)

INCLUDE(K3DFindPkgConfig)
PKG_CHECK_MODULES(GTKGLEXT gtkglext-1.0)

IF(GTKGLEXT_FOUND)
	SET(GTKGLEXT_INCLUDE_DIRS
		${GTKGLEXT_INCLUDE_DIRS}
		)

	SET(GTKGLEXT_LIB_DIRS
		${GTKGLEXT_LIBRARY_DIRS}
		)

	SET(GTKGLEXT_LIBS
		${GTKGLEXT_LIBRARIES}
		)

	SET(GTKGLEXT_FOUND 1)
ENDIF(GTKGLEXT_FOUND)

