###############################################################################
#
# Coding Rampage UI
#
###############################################################################

option(RAMPAGE_BUILD_UI "Build Rampage UI libraries" YES)

IF (RAMPAGE_BUILD_UI)
	SET(PACKAGE_UI "${RAMPAGE_PROJECT_PACKAGES}/UI")
	PACKAGE_LIST("UI")
ENDIF (RAMPAGE_BUILD_UI)

###############################################################################
