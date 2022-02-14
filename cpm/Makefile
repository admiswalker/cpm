#------------------------------------------------------------
# please set each item

# source files
SRC    = main.cpp
TARGET = exe

# remove files
RMs = *.stackdump __pycache__ tmpDir

# compilation options
CFLAGS += -L./sstd/lib -I./sstd/include -lsstd # sstd
CFLAGS += -std=c++14 # CFLAGS += -std=gnu++0x
CFLAGS += -Wall
#CFLAGS += -Wextra
CFLAGS += -O3

#------------------------------------------------------------

# when you need to check the change of files in lib, you need to change file name to a not-existing name like "FORCE_XXX".
#LIB_SSTD = FORCE_SSTD
LIB_SSTD  = ./sstd/lib/libsstd.a
LIB_ALL  += $(LIB_SSTD)


# generate exe file
TARGET_all = FORCE_MAKEALL
$(TARGET_all): $(LIB_ALL) $(TARGET)
	@echo "maked all"
$(TARGET): $(LIB_ALL) $(SRC)
	@echo ""
	@echo "------------------------------------------------------------"
	@echo "TARGET: \n$@\n"
	@echo "SRCS: \n$<"
	@echo "CFLAGS: \n$(CFLAGS)"
	@echo "------------------------------------------------------------"
	$(CXX) -o $@ $(SRC) $(CFLAGS)
	@echo ""


$(LIB_SSTD):
	@echo ""
	@unzip -n SubStandardLibrary-SSTD--master.zip
	@mv SubStandardLibrary-SSTD--master/sstd ./
	@rm -rf SubStandardLibrary-SSTD--master/
	@(cd ./sstd; make -j)


.PHONY: all
all:
	@(make clean)
	@(make)


.PHONY: clean
clean:
	-rm -rf sstd
	-rm -rf tmp
	-rm -rf *.exe
	-rm -rf out.md


.PHONY: test
test: # run_all_test
	@($(TARGET) ./input.md ./output.md)
#	./exe_test


.PHONY: updateLib
updateLib:
	wget https://github.com/admiswalker/SubStandardLibrary-SSTD-/archive/master.zip -O SubStandardLibrary-SSTD--master.zip
	-rm -rf sstd # remove previous versions of sstd


.PHONY: steps
steps: $(SRCS)
	@echo "$^" | xargs wc -l
	@echo ""
	@(cd ./sstd; make steps)

