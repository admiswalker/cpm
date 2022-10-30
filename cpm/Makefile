#------------------------------------------------------------
# exe

# source files
SRC    = main.cpp
TARGET = exe

# remove files
RMs = *.stackdump __pycache__ tmpDir

# compilation options
CFLAGS += -L./sstd/lib -I./sstd/include -lsstd # sstd
CFLAGS += -std=c++14
CFLAGS += -Wall
#CFLAGS += -Wextra
CFLAGS += -O3

#------------------------------------------------------------
# src of exe

DIR  = ./src/*.

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
LIB_SSTD = ./sstd/lib/libsstd.a
LIB_ALL += $(LIB_SSTD)


# generate exe file
TARGET_all = FORCE_MAKEALL
$(TARGET_all): $(LIB_ALL) $(OBJS) $(TARGET) $(TARGET_t)
	@echo "maked all"
$(TARGET): $(LIB_ALL) $(OBJS) $(SRC)
	@echo ""
	@echo "------------------------------------------------------------"
	@echo "TARGET: \n$@\n"
	@echo "SRCS: \n$(SRC)\n"
	@echo "CFLAGS: \n$(CFLAGS)"
	@echo "------------------------------------------------------------"
	$(CXX) -o $@ $(SRC) $(OBJS) $(CFLAGS)
	@echo ""


$(LIB_SSTD):
	@echo ""
	@unzip -n SubStandardLibrary-SSTD--master.zip
	@mv SubStandardLibrary-SSTD--master/sstd ./
	@rm -rf SubStandardLibrary-SSTD--master/
	@(cd ./sstd; make -j)


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
	-rm -rf tmp
	-rm -rf *.exe
	-rm -rf out.md
	-rm -rf $(TARGET)
	-rm -rf $(TEMP_DIR)


.PHONY: updateLib
updateLib:
	wget https://github.com/admiswalker/SubStandardLibrary-SSTD-/archive/master.zip -O SubStandardLibrary-SSTD--master.zip
	-rm -rf sstd # remove previous versions of sstd


.PHONY: steps
steps: $(SRCS)
	@echo "$^" | xargs wc -l
	@echo ""
	@(cd ./sstd; make steps)


-include $(DEPS)
