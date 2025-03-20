# Optimization
OPT = 3
LTO_ENABLE = yes

# Power optimization
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

# Custom matrix
CUSTOM_MATRIX = lite
SRC += matrix.c