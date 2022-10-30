#------------------------------------------------------------
# exe_test

SRC_t    = main_test.cpp
TARGET_t = exe_test

HEADS_t += $(wildcard ./test/*.h  )
HEADS_t += $(wildcard ./test/*.hpp)

# compilation options
CFLAGS += -L./cpm/sstd/lib -I./cpm/sstd/include -lsstd # sstd
CFLAGS += -L./googletest-master/build/lib -I./googletest-master/googletest/include -lgtest -pthread # google test
CFLAGS += -std=c++14
CFLAGS += -Wall
#CFLAGS += -Wextra
CFLAGS += -O3

#------------------------------------------------------------

# Obj file for exe_test
DIR  = ./cpm/tmpMake/src/*.
OBJSDIR  = $(patsubst %., %.o, $(DIR))
OBJS     = $(wildcard $(OBJSDIR))

# when you need to check the change of files in lib, you need to change file name to a not-existing name like "FORCE_XXX".
#LIB_SSTD = FORCE_SSTD
LIB_CPM = ./cpm/exe
LIB_GOOGLETEST = ./googletest-master/build/lib/libgtest.a
LIB_ALL += $(LIB_CPM)
LIB_ALL += $(LIB_GOOGLETEST)


# generate exe_test file
TARGET_all = FORCE_MAKEALL
$(TARGET_all): $(LIB_ALL) $(TARGET_t)
	@echo "maked all"
$(TARGET_t): $(LIB_ALL) $(SRC_t)
	@echo ""
	@echo "------------------------------------------------------------"
	@echo "TARGET: \n$@\n"
	@echo "SRCS_t: \n$<\n"
	@echo "CFLAGS: \n$(CFLAGS)"
	@echo "------------------------------------------------------------"
	$(CXX) -o $@ $(SRC_t) $(OBJS) $(CFLAGS)
	@echo ""


$(LIB_CPM):
	cd cpm; make -j


$(LIB_GOOGLETEST):
	@echo ""
	@unzip -n googletest-master.zip
	@(cd ./googletest-master; mkdir -p build; cd build; cmake ..; make)


.PHONY: test
test: # run_all_test
	./exe_test


.PHONY: steps
steps: $(SRCS_t) $(HEADS_t)
	@(cd ./cpm; make steps)
	@echo ""
	@echo "$^" | xargs wc -l


clean:
	@cd cpm; make clean
	-rm -rf googletest-master
	-rm -rf $(TARGET_t)
#	@rm -fr cpm_env

