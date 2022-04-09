#------------------------------------------------------------
# exe

# source files
SRC    = main.cpp
TARGET = exe

# remove files
RMs = *.stackdump __pycache__ tmpDir

# compilation options
CFLAGS += -L./sstd/lib -I./sstd/include -lsstd # sstd
CFLAGS += -L./googletest-master/build/lib -I./googletest-master/googletest/include -lgtest -pthread # google test
CFLAGS += -std=c++14
CFLAGS += -Wall
#CFLAGS += -Wextra
CFLAGS += -O3

#------------------------------------------------------------
# exe_test

SRC_t    = main_test.cpp
TARGET_t = exe_test

HEADS_t += $(wildcard ./test/*.h  )
HEADS_t += $(wildcard ./test/*.hpp)

#------------------------------------------------------------
# exe and exe_test

DIR  = ./src/*.
DIR += ./test/*.

#------------------------------------------------------------

SRCDIR   = $(patsubst %., %.cpp, $(DIR))
SRCS     = $(wildcard $(SRCDIR))

HDIR     = $(patsubst %., %.h, $(DIR))
HEADS    = $(wildcard $(HDIR))

HPPDIR   = $(patsubst %., %.hpp, $(DIR))
HEADppS  = $(wildcard $(HPPDIR))

TEMP_DIR = tmpMake
OBJS     = $(addprefix $(TEMP_DIR)/, $(patsubst %.cpp, %.o, $(SRCS)))
DEPS     = $(addprefix $(TEMP_DIR)/, $(patsubst %.cpp, %.d, $(SRCS)))


# when you need to check the change of files in lib, you need to change file name to a not-existing name like "FORCE_XXX".
#LIB_SSTD = FORCE_SSTD
LIB_SSTD       = ./sstd/lib/libsstd.a
LIB_GOOGLETEST = ./googletest-master/build/lib/libgtest.a
LIB_ALL += $(LIB_SSTD)
LIB_ALL += $(LIB_GOOGLETEST)


# generate exe file
TARGET_all = FORCE_MAKEALL
$(TARGET_all): $(LIB_ALL) $(OBJS) $(TARGET) $(TARGET_t)
	@echo "maked all"
$(TARGET): $(LIB_ALL) $(OBJS) $(SRC)
	@echo ""
	@echo "------------------------------------------------------------"
	@echo "TARGET: \n$@\n"
	@echo "SRCS: \n$<"
	@echo "CFLAGS: \n$(CFLAGS)"
	@echo "------------------------------------------------------------"
	$(CXX) -o $@ $(SRC) $(OBJS) $(CFLAGS)
	@echo ""
$(TARGET_t): $(LIB_ALL) $(OBJS) $(HEADS) $(HEADppS) $(SRC_t)
	@echo ""
	@echo "------------------------------------------------------------"
	@echo "TARGET: \n$@\n"
	@echo "SRCS: \n$<"
	@echo "CFLAGS: \n$(CFLAGS)"
	@echo "------------------------------------------------------------"
	$(CXX) -o $@ $(SRC_t) $(OBJS) $(CFLAGS)
	@echo ""


$(LIB_SSTD):
	@echo ""
	@unzip -n SubStandardLibrary-SSTD--master.zip
	@mv SubStandardLibrary-SSTD--master/sstd ./
	@rm -rf SubStandardLibrary-SSTD--master/
	@(cd ./sstd; make -j)


$(LIB_GOOGLETEST):
	@echo ""
	@unzip -n googletest-master.zip
	@(cd ./googletest-master; mkdir -p build; cd build; cmake ..; make)


# 各ファイルの分割コンパイル
$(TEMP_DIR)/%.o: %.cpp $(LIB_SSTD)
	@echo ""
	mkdir -p $(dir $@);\
	$(CXX) $< -c -o $@ $(CFLAGS)

# 「-include $(DEPS)」により，必要な部分のみ分割で再コンパイルを行うため，依存関係を記した *.d ファイルに生成する
$(TEMP_DIR)/%.d: %.cpp $(LIB_SSTD)
	@echo ""
	mkdir -p $(dir $@);\
	$(CXX) $< -MM $(CFLAGS)\
	| sed 's/$(notdir $*)\.o/$(subst /,\/,$(patsubst %.d,%.o,$@) $@)/' > $@;\
	[ -s $@ ] || rm -f $@
#	@echo $*	# for debug
#	@echo $@	# for debug


.PHONY: all
all:
	@(make clean)
	@(make)


.PHONY: clean
clean:
	-rm -rf sstd
	-rm -rf googletest-master
	-rm -rf tmp
	-rm -rf *.exe
	-rm -rf out.md
	-rm -rf $(TARGET)
	-rm -rf $(TARGET_t)
	-rm -rf $(TEMP_DIR)


.PHONY: test
test: # run_all_test
	@($(TARGET) ./input.md ./output.md)
#	./exe_test


.PHONY: updateLib
updateLib:
	wget https://github.com/admiswalker/SubStandardLibrary-SSTD-/archive/master.zip -O SubStandardLibrary-SSTD--master.zip
	-rm -rf sstd # remove previous versions of sstd


.PHONY: steps
steps: $(SRCS) $(SRCS_t) $(HEADS_t)
	@echo "$^" | xargs wc -l
	@echo ""
	@(cd ./sstd; make steps)


-include $(DEPS)
