# Makefile

# プログラム名とオブジェクトファイル名
program = main
objsc   = Code.o
objscpp = main.o

# 定義済マクロの再定義
CC        = gcc
CPP       = g++
LD        = ld2
AR        = ar
#CFLAGS   = -g -Wall
CFLAGS    = 
#CPPFLAGS = -g -Wall
CPPFLAGS  = 
LDFLAGS   = -lstdc++
ARFLAGS   = rsv

# サフィックスルール適用対象の拡張子の定義
.SUFFIXES: .c .cpp .o

# プライマリターゲット
.PHONY: all
all: dependc dependcpp $(program)

# プログラムの生成ルール
$(program): $(objsc) $(objscpp)
	#$(CC)  -o $(program) $^
	$(CPP)  -o $(program) $^
	#$(LD)  -o $(program) $^ $(LDFLAGS)
	$(AR)      $(ARFLAGS) lib$(program).a $^

# サフィックスルール
{path}.c{path}.o:
	$(CC)  $(CFLAGS)   -c $<

{path}.cpp{path}.o:
	$(CPP) $(CPPFLAGS) -c $<

# ファイル削除用ターゲット
.PHONY: clean
clean:
	$(RM) $(program) $(program).exe $(program).dll lib$(program).a lib$(program).dll.a $(objsc) $(objscpp) dependc.inc dependcpp.inc

# ヘッダーファイルの依存関係
.PHONY: dependc
dependc: $(objsc:.o=.c)
	-@ $(RM) dependc.inc
	-@ for i in $^; do\
		cpp -MM $$i | sed "s/\ [_a-zA-Z0-9][_a-zA-Z0-9]*\.c//g" >> dependc.inc;\
	done

.PHONY: dependcpp
dependcpp: $(objscpp:.o=.cpp)
	-@ $(RM) dependcpp.inc
	-@ for i in $^; do\
		cpp -MM $$i | sed "s/\ [_a-zA-Z0-9][_a-zA-Z0-9]*\.cpp//g" >> dependcpp.inc;\
	done

-include dependc.inc dependcpp.inc
