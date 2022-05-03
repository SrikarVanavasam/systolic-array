######################################################################
#
# DESCRIPTION: Verilator Example: Small Makefile
#
# This calls the object directory makefile.  That allows the objects to
# be placed in the "current directory" which simplifies the Makefile.
#
# This file ONLY is placed under the Creative Commons Public Domain, for
# any use, without warranty, 2020 by Wilson Snyder.
# SPDX-License-Identifier: CC0-1.0
#
######################################################################
# Check for sanity to avoid later confusion

ifneq ($(words $(CURDIR)),1)
 $(error Unsupported: GNU Make cannot build in directories containing spaces, build elsewhere: '$(CURDIR)')
endif

######################################################################

# This is intended to be a minimal example.  Before copying this to start a
# real project, it is better to start with a more complete example,
# e.g. examples/make_tracing_c.

# If $VERILATOR_ROOT isn't in the environment, we assume it is part of a
# package install, and verilator is in your path. Otherwise find the
# binary relative to $VERILATOR_ROOT (such as when inside the git sources).
ifeq ($(VERILATOR_ROOT),)
VERILATOR = verilator
else
export VERILATOR_ROOT
VERILATOR = $(VERILATOR_ROOT)/bin/verilator
endif

default:
	@echo "-- VERILATE & BUILD --------"
	$(VERILATOR) -cc --trace --exe -sv systolic_array_frame.sv systolic_array.sv scheduler.sv input_skewer.sv systolic_pe.sv madd.sv VX_multiplier.sv VX_shift_register.sv sim_main.cpp
	@echo "-- COMPILE -----------------"
	$(MAKE) -j 4 -C obj_dir -f Vsystolic_array_frame.mk 
	@echo "-- RUN ---------------------"
	obj_dir/Vsystolic_array_frame
	@echo "-- DONE --------------------"

temp:
	@echo "-- VERILATE & BUILD --------"
	$(VERILATOR) -cc --trace --exe -sv systolic_array_frame_temp.sv systolic_array.sv scheduler.sv input_skewer.sv systolic_pe.sv madd.sv VX_multiplier.sv VX_shift_register.sv sim_temp.cpp
	@echo "-- COMPILE -----------------"
	$(MAKE) -j 4 -C obj_dir -f Vsystolic_array_frame_temp.mk 
	@echo "-- RUN ---------------------"
	obj_dir/Vsystolic_array_frame_temp
	@echo "-- DONE --------------------"

pe:
	@echo "-- VERILATE & BUILD --------"
	$(VERILATOR) -cc --exe --trace -sv systolic_pe.sv madd.sv VX_multiplier.sv VX_shift_register.sv sim_pe.cpp
	@echo "-- COMPILE -----------------"
	$(MAKE) -j 4 -C obj_dir -f Vsystolic_pe.mk 
	@echo "-- RUN ---------------------"
	obj_dir/Vsystolic_pe
	@echo "-- DONE --------------------"

skew:
	@echo "-- VERILATE & BUILD --------"
	$(VERILATOR) -cc --exe --trace -sv input_skewer.sv VX_shift_register.sv sim_skew.cpp
	@echo "-- COMPILE -----------------"
	$(MAKE) -j 4 -C obj_dir -f Vinput_skewer.mk 
	@echo "-- RUN ---------------------"
	obj_dir/Vinput_skewer
	@echo "-- DONE --------------------"

sched:
	@echo "-- VERILATE & BUILD --------"
	$(VERILATOR) -cc --trace --exe -sv scheduler.sv sim_sched.cpp
	@echo "-- COMPILE -----------------"
	$(MAKE) -j 4 -C obj_dir -f Vscheduler.mk 
	@echo "-- RUN ---------------------"
	obj_dir/Vscheduler
	@echo "-- DONE --------------------"

array:
	@echo "-- VERILATE & BUILD --------"
	$(VERILATOR) -cc --trace --exe -sv systolic_array.sv systolic_pe.sv madd.sv VX_multiplier.sv VX_shift_register.sv sim_array.cpp
	@echo "-- COMPILE -----------------"
	$(MAKE) -j 4 -C obj_dir -f Vsystolic_array.mk 
	@echo "-- RUN ---------------------"
	obj_dir/Vsystolic_array
	@echo "-- DONE --------------------"

data_fetcher:
	@echo "-- VERILATE & BUILD --------"
	$(VERILATOR) -cc --trace --exe -sv data_fetcher.sv sim_data_fetcher.cpp
	@echo "-- COMPILE -----------------"
	$(MAKE) -j 4 -C obj_dir -f Vdata_fetcher.mk 
	@echo "-- RUN ---------------------"
	obj_dir/Vdata_fetcher
	@echo "-- DONE --------------------"

######################################################################

maintainer-copy::
clean mostlyclean distclean maintainer-clean::
	-rm -rf obj_dir *.log *.dmp *.vpd core