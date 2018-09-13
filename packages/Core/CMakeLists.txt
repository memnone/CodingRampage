###############################################################################
#
# CodingRampage Core
#
###############################################################################

option(RAMPAGE_BUILD_CORE "Build Coding Rampage Core libraries" YES)

IF (RAMPAGE_BUILD_CORE)
	SET(PACKAGE_CORE "${RAMPAGE_PROJECT_PACKAGES}/Core")
	PACKAGE_LIST("Core")
ENDIF (RAMPAGE_BUILD_CORE)

###############################################################################
