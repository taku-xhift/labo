#Makefile

# プログラム名とオブジェクトファイル名
program = Hello

# ls で ファイル、ディレクトリを検索させて、
# そうやって得られて結果の文字列  directory の d で検索させて、
# ディレクトリだけを抽出する http://osima.jp/memo/cygwin-get-directory-in-curdir.html
SUBDIR := $(shell ls -l | awk '{print $$1,$$9}' | grep "^d" | awk '{print $$2}')

SRCS = $(shell ls *.cpp)
OBJS = $(SRCS:.cpp=.o)
HEADS = $(shell ls *.hpp)

# 定義済みマクロの再定義
CC = gcc
CFLAGS = -g -Wall
CPPOPTION = -lstdc++

# サフィックスルール適用対象の拡張子の定義
.SUFFIXES: .c .cpp .o

#プライマリターゲット
# サブディレクトリの make を再帰的に呼び出し
subsystem: $(program)
	$(MAKE) -C subdir

$(program): $(OBJS)
	$(CC) -o $(program) $^ $(CPPOPTION)

# サフィックスルール
.c .cpp .o:
	$(CC) $(CFLAGS) -c $<

# サブディレクトリの make 呼び出し
subsystem:
	cd Macro && $(MAKE)

# ファイル削除用ターゲット
.PHONY: clean
clean:
	$(RM) *~ *.o $(OBJS)

# ヘッダファイルの依存関係
.PHONY: depend
depend: $(SRCS:.cpp=.o)
	-@ $(RM) depend.inc
	-@ for i in $^; do\
		cpp -MM $$i | sed "s/\ [_a-zA-Z0-9][_a-zA-Z0-9]*\.cpp//g" >> depend.inc;\
	done

-include depend.inc
