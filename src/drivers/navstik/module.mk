#
# Interface driver for the NAVSTIK board
#

MODULE_COMMAND	 = fmu
SRCS		 = fmu.cpp

MODULE_STACKSIZE = 1200

EXTRACXXFLAGS	= -Weffc++
