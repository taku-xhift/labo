#Makefile

# プログラム名とオブジェクトファイル名
program = Hello
objs = Hello.o Edajima.o

# 定義済みマクロの再定義
CC = gcc
CFLAGS = -g -Wall

# C++ 用のオプションの宣言
CPPOPTION = -lstdc++

# サフィックスルール適用対象の拡張子の定義
.SUFFIXES: .c .cpp .o


# プライマリターゲット
$(program): $(objs)
	$(CC) -o $(program) $^ $(CPPOPTION)


# サフィックスルール
.c.cpp.o:
	$(CC) $(CFLAGS) -c $<


# ファイル削除用ターゲット
.PHONY: clean
clean:
	$(RM) $(program) $(objs)
