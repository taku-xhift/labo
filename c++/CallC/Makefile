# Makefile

# �v���O�������ƃI�u�W�F�N�g�t�@�C����
program = main
objsc   = Code.o
objscpp = main.o

# ��`�σ}�N���̍Ē�`
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

# �T�t�B�b�N�X���[���K�p�Ώۂ̊g���q�̒�`
.SUFFIXES: .c .cpp .o

# �v���C�}���^�[�Q�b�g
.PHONY: all
all: dependc dependcpp $(program)

# �v���O�����̐������[��
$(program): $(objsc) $(objscpp)
	#$(CC)  -o $(program) $^
	$(CPP)  -o $(program) $^
	#$(LD)  -o $(program) $^ $(LDFLAGS)
	$(AR)      $(ARFLAGS) lib$(program).a $^

# �T�t�B�b�N�X���[��
{path}.c{path}.o:
	$(CC)  $(CFLAGS)   -c $<

{path}.cpp{path}.o:
	$(CPP) $(CPPFLAGS) -c $<

# �t�@�C���폜�p�^�[�Q�b�g
.PHONY: clean
clean:
	$(RM) $(program) $(program).exe $(program).dll lib$(program).a lib$(program).dll.a $(objsc) $(objscpp) dependc.inc dependcpp.inc

# �w�b�_�[�t�@�C���̈ˑ��֌W
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