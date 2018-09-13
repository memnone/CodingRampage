###############################################################################
#
# Rampage App
#
###############################################################################

option(RAMPAGE_BUILD_APP "Build Rampage applications" YES)

IF (RAMPAGE_BUILD_APP)
	SET(PACKAGE_APP "${RAMPAGE_PROJECT_PACKAGES}/App")
	PACKAGE_LIST("App")
ENDIF (RAMPAGE_BUILD_APP)

###############################################################################
#
# Rampage App/TESTS
#
###############################################################################

option(RAMPAGE_BUILD_APP_TESTS "Build Rampage TESTS based applications" NO)

IF (RAMPAGE_BUILD_APP_TESTS)
	SET(PACKAGE_APP_TESTS "${RAMPAGE_PROJECT_PACKAGES}/App/Tests")
	PACKAGE_LIST("App/Tests")
ENDIF (RAMPAGE_BUILD_APP_TESTS)
