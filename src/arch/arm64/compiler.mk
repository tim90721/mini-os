
# NEON is not enabled yet by now, we should disable float and SIMD instructions
# Otherwise, compiler will default use those instructions for functions like
# variadic function
# TODO: enable NEON by https://stackoverflow.com/questions/19231197/enable-neon-on-arm-cortex-a-series
#       more reference on https://stackoverflow.com/questions/37299524/neon-support-in-armv8-system-mode-qemu
CFLAGS += -march=armv8-a+nofp+nosimd
