
Q	:= @
quiet	:= quiet_

ifeq ("$(origin V)","command line")
ifeq ($(V),1)
Q	:=
quiet	:=
endif # V == 1
endif # origin V == command line

export Q quiet
