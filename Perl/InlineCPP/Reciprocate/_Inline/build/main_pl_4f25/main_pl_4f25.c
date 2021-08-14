/*
 * This file was generated automatically by xsubpp version 1.9508 from the
 * contents of main_pl_4f25.xs. Do not edit this file, edit main_pl_4f25.xs instead.
 *
 *	ANY CHANGES MADE HERE WILL BE LOST!
 *
 */

#line 1 "main_pl_4f25.xs"
#ifndef bool
#include <iostream>
#endif
extern "C" {
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "INLINE.h"
}
#ifdef bool
#undef bool
#include <iostream>
#endif


#include <iostream>
#include "ReciprocateData.h"
#include "Storage.hpp"
#include "Parse.hpp"


//---------------------------------------------------------
//  declaration
//---------------------------------------------------------
ReciprocateData* converter(SV* reference_);


SV* convertReciprocateDataToPerlHash(const ReciprocateData& data_)
{
//    std::cout << "Call convertReciprocateDataToPerlHash()" << std::endl;
//    std::cout << "data_.key = " << data_.key << std::endl;
//    std::cout << "data_.num = " << data_.num << std::endl;
//    std::cout << "data_.type = " << data_.type << std::endl;
    SV* scalarData;

    switch (data_.type) {
		case DATATYPE_INT: {
//            std::cout << "through INT" << std::endl;
//            std::cout << "data_.value[0] = " << *reinterpret_cast<int*>(data_.value[0]) << std::endl;
        	scalarData = newSViv(*reinterpret_cast<int*>(data_.value[0]));
    		break;
		}
		case DATATYPE_FLOAT: {
//            std::cout << "through FLOAT" << std::endl;
//            std::cout << "data_.value[0] = " << *reinterpret_cast<float*>(data_.value[0]) << std::endl;
        	scalarData = newSVnv(*reinterpret_cast<float*>(data_.value[0]));
    		break;
		}
		case DATATYPE_STRING: {
//            std::cout << "through STRING" << std::endl;
//            std::cout << "data_.value[0] = " << reinterpret_cast<const char*>(data_.value[0]) << std::endl;
        	scalarData = newSVpv(reinterpret_cast<const char*>(data_.value[0]), strlen(reinterpret_cast<const char*>(data_.value[0])));
    		break;
		}
		case DATATYPE_INTARRAY: {
//            std::cout << "through INTARRAY" << std::endl;
			AV* array = newAV();
//        	hv_store(hash, data_.key, strlen(data_.key), newRV_noinc(reinterpret_cast<SV*>(array)), 0);
			for (int i = 0; i < data_.num; ++i) {
                av_push(array, newSViv(*reinterpret_cast<int*>(reinterpret_cast<ReciprocateData*>(data_.value[i])->value[0])));
			}
            scalarData = reinterpret_cast<SV*>(array);
    		break;
		}
		case DATATYPE_FLOATARRAY: {
//            std::cout << "through FLOATARRAY" << std::endl;
			AV* array = newAV();
//        	hv_store(hash, data_.key, strlen(data_.key), newRV_noinc(reinterpret_cast<SV*>(array)), 0);
			for (int i = 0; i < data_.num; ++i) {
                av_push(array, newSVnv(*reinterpret_cast<float*>(reinterpret_cast<ReciprocateData*>(data_.value[i])->value[0])));
			}
            scalarData = reinterpret_cast<SV*>(array);
    		break;
		}
		case DATATYPE_STRUCT: {
//            std::cout << "through STRUCT" << std::endl;
            HV* hash = newHV();
			for (int i = 0; i < data_.num; ++i) {
				hv_store(hash, reinterpret_cast<ReciprocateData*>(data_.value[i])->key, strlen(reinterpret_cast<ReciprocateData*>(data_.value[i])->key),
//                         newRV_inc(reinterpret_cast<SV*>(
//                             convertReciprocateDataToPerlHash(
//                                 *reinterpret_cast<ReciprocateData*>(data_.value[i])))),
                         reinterpret_cast<SV*>(
                             convertReciprocateDataToPerlHash(
                                 *reinterpret_cast<ReciprocateData*>(data_.value[i]))),
                         0);
			}
            scalarData = reinterpret_cast<SV*>(hash);
    		break;
		}
		default: {
			break;
		}
    }
    return scalarData;
}


SV* getCommand() {
    ReciprocateData* data = storage_String("name", "sample");
    return convertReciprocateDataToPerlHash(*data);
}


HV* makeHash() {
    HV* hash = newHV();
    hv_store(hash, "first", strlen("first"), newSViv(4), 0);
    return hash;
}

HV* makeInt() {
    ReciprocateData* data = storage_Int(3, "sample");

    SV* temp = convertReciprocateDataToPerlHash(*data);

    HV* hash = newHV();
    hv_store(hash, "sample", strlen("sample"), temp, 0);
    return hash;

// アクセス方法
//my $hash = makeInt;
//print Dumper hash{sample};
}

HV* makeString() {
    ReciprocateData* data = storage_String("namename", "sample");

    SV* temp = convertReciprocateDataToPerlHash(*data);

    HV* hash = newHV();
    hv_store(hash, "sample", strlen("sample"), temp, 0);
    return hash;

// アクセス方法
//my $hash = makeString;
//print Dumper hash{sample};
}

HV* makeIntArray() {
    std::vector<int> container;
    for (int i = 0; i < 4; ++i) {
        container.push_back(i);
    }

    ReciprocateData* data = storage_IntArray(container, "sample");
    SV* temp = convertReciprocateDataToPerlHash(*data);

    HV* hash = newHV();
    hv_store(hash, "array", strlen("array"), newRV_inc(temp), 0);
    return hash;

// アクセス方法
//my $array = makeIntArray;
//print Dumper @$array{"array"}->[1];
}

HV* makeStruct() {
    PlayerData player;
    player.number = 34;
    player.name = "testtest";
    ReciprocateData* data = storage_PlayerData(player, "player");

    SV* temp = convertReciprocateDataToPerlHash(*data);

    HV* hash = newHV();
    HV* hashsecond = newHV();
    hv_store(hash, "first", strlen("first"), newSViv(4), 0);
    hv_store(hash, "player", strlen("player"), newRV_inc(temp), 0);
    return hash;

// アクセス方法
//my $hash = makeStruct;
//#print Dumper hashHash;
//print Dumper $$hash{first};
//print Dumper $$hash{player}->{name};
//print Dumper $$hash{"player"}->{"number"};
}


void dump_hash(SV* hash_ref) {
    std::cout << "result Check!!" << std::endl;
    ReciprocateData* data = converter(hash_ref);
    data->type = DATATYPE_STRUCT;
    data->key = "sss";
//                std::cout << "data->type = " << data->type << std::endl;
//                std::cout << "data->num = " << data->num << std::endl;
//                std::cout << "data->key = " << data->key << std::endl;
//
//                std::cout << "data->value[0]->type = " << reinterpret_cast<ReciprocateData*>(data->value[0])->type << std::endl;
//                std::cout << "data->value[0]->num = " << reinterpret_cast<ReciprocateData*>(data->value[0])->num << std::endl;
//                std::cout << "data->value[0]->key = " << reinterpret_cast<ReciprocateData*>(data->value[0])->key << std::endl;
//
//                std::cout << "data->value[1]->type = " << reinterpret_cast<ReciprocateData*>(data->value[1])->type << std::endl;
//                std::cout << "data->value[1]->num = " << reinterpret_cast<ReciprocateData*>(data->value[1])->num << std::endl;
//                std::cout << "data->value[1]->key = " << reinterpret_cast<ReciprocateData*>(data->value[1])->key << std::endl;
//
//                std::cout << "data->value[1]->value[0]->type = " << reinterpret_cast<ReciprocateData*>(reinterpret_cast<ReciprocateData*>(data->value[1])->value[0])->type << std::endl;
//                std::cout << "data->value[1]->value[0]->num = " << reinterpret_cast<ReciprocateData*>(reinterpret_cast<ReciprocateData*>(data->value[1])->value[0])->num << std::endl;
//                std::cout << "data->value[1]->value[0]->key = " << reinterpret_cast<ReciprocateData*>(reinterpret_cast<ReciprocateData*>(data->value[1])->value[0])->key << std::endl;
//                std::cout << "data->value[1]->value[0]->value = " << (const char*)(reinterpret_cast<ReciprocateData*>(reinterpret_cast<ReciprocateData*>(data->value[1])->value[0])->value[0]) << std::endl;
//
//                std::cout << "data->value[1]->value[1]->type = " << reinterpret_cast<ReciprocateData*>(reinterpret_cast<ReciprocateData*>(data->value[1])->value[1])->type << std::endl;
//                std::cout << "data->value[1]->value[1]->num = " << reinterpret_cast<ReciprocateData*>(reinterpret_cast<ReciprocateData*>(data->value[1])->value[1])->num << std::endl;
//                std::cout << "data->value[1]->value[1]->key = " << reinterpret_cast<ReciprocateData*>(reinterpret_cast<ReciprocateData*>(data->value[1])->value[1])->key << std::endl;
//
//                std::cout << "data->value[2]->type = " << reinterpret_cast<ReciprocateData*>(data->value[2])->type << std::endl;
//                std::cout << "data->value[2]->num = " << reinterpret_cast<ReciprocateData*>(data->value[2])->num << std::endl;
//                std::cout << "data->value[2]->key = " << reinterpret_cast<ReciprocateData*>(data->value[2])->key << std::endl;





//    float fresult = *const_cast<float*>(reinterpret_cast<const float*>(getKeyValue(*data, "Floating")));
//    if (!fresult) {
//        std::cout << "NULL" << std::endl;
//        assert(0);
//    }
//    std::cout << fresult << std::endl;
//
//    // hash
//    int iresult = *const_cast<int*>(reinterpret_cast<const int*>(getKeyValue(*data, "Integer")));
//    std::cout << iresult << std::endl;
//    const char* cresult = reinterpret_cast<const char*>(getKeyValue(*data, "sample"));
//    std::cout << cresult << std::endl;


//    // array
//    int* array = new int[3];
//    std::vector<int> node;
//    for (int i = 0; i < 3; ++i) {
//        node.push_back(i);
//        array[i] = *const_cast<int*>(reinterpret_cast<const int*>(getKeyValue(*data, "Array", node)));
//        std::cout << array[i] << std::endl;
//        node.clear();
//    }


    // arrayHash
    ReciprocateData* array = new ReciprocateData[2];
    std::vector<int> node;
    for (int i = 0; i < 2; ++i) {
        node.push_back(i);
        array[i] = *const_cast<ReciprocateData*>(reinterpret_cast<const ReciprocateData*>(getKeyValue(*data, "HashArray", node)));
        //std::cout << array[i] << std::endl;
        node.clear();
    }
std::cout << "array[0]->key = " << array[0].key << std::endl;
std::cout << "array[0]->num = " << array[0].num << std::endl;
std::cout << "array[0]->type = " << array[0].type << std::endl;
std::cout << "array[0]->value[0]->key = " << reinterpret_cast<ReciprocateData*>(array[0].value[0])->key << std::endl;
std::cout << "array[0]->value[0]->num = " << reinterpret_cast<ReciprocateData*>(array[0].value[0])->num << std::endl;
std::cout << "array[0]->value[0]->type = " << reinterpret_cast<ReciprocateData*>(array[0].value[0])->type << std::endl;
std::cout << "array[0]->value[1]->key = " << reinterpret_cast<ReciprocateData*>(array[0].value[1])->key << std::endl;
std::cout << "array[0]->value[1]->num = " << reinterpret_cast<ReciprocateData*>(array[0].value[1])->num << std::endl;
std::cout << "array[0]->value[1]->type = " << reinterpret_cast<ReciprocateData*>(array[0].value[1])->type << std::endl;
std::cout << "array[1]->key = " << array[1].key << std::endl;
std::cout << "array[1]->num = " << array[1].num << std::endl;
std::cout << "array[1]->type = " << array[1].type << std::endl;
}

ReciprocateData* converter(SV* reference_) {
    HV* hash;
    HE* hash_entry;
    int num_keys, i;
    SV* sv_key;
    SV* sv_val;
    ReciprocateData* data = createReciprocateData();

    if (! SvROK(reference_))
        croak("reference_ is not a reference\n");

    hash = (HV*)SvRV(reference_);
    num_keys = hv_iterinit(hash);

    data->num = num_keys;
    data->value = reinterpret_cast<void**>(calloc(data->num, sizeof(void**)));


    for (i = 0; i < num_keys; i++) {
        hash_entry = hv_iternext(hash);
        sv_key = hv_iterkeysv(hash_entry);
        sv_val = hv_iterval(hash, hash_entry);

        if (SvTYPE(sv_val) == SVt_IV) {
            // 整数型
            //printf("Integer, %s => %d\n", SvPV(sv_key, PL_na), SvIV(sv_val));
            data->value[i] = storage_Int(SvIV(sv_val), SvPV(sv_key, PL_na));
        } else if (SvTYPE(sv_val) == SVt_NV) {
            // 浮動小数点型
            //printf("Natural, %s => %s\n", SvPV(sv_key, PL_na), SvPV(sv_val, PL_na));
            data->value[i] = storage_Float(SvNV(sv_val), SvPV(sv_key, PL_na));
        } else if (SvTYPE(sv_val) == SVt_PV) {
            // 文字列型
            //printf("Strings, %s => %s\n", SvPV(sv_key, PL_na), SvPV(sv_val, PL_na));
            data->value[i] = storage_String(SvPV(sv_val, PL_na), SvPV(sv_key, PL_na));
        } else {
            // 型判定の中でもリストとハッシュのリファレンスに関しては最後に判定しないとダンプだして終了する
            if (SvTYPE(SvRV(sv_val)) == SVt_PVAV) {
                //std::cout << "Array!!" << std::endl;

                AV* ar = (AV*)SvRV(sv_val);
                SV* temp;
                int size = av_len(ar);

                data->value[i] = createReciprocateData();
                reinterpret_cast<ReciprocateData*>(data->value[i])->value = reinterpret_cast<void**>(calloc(size, sizeof(void**)));

                for (int j = 0; av_len(ar) != -1; ++j) {
                    temp = av_shift(ar);

                    if (SvTYPE(temp) == SVt_IV) {
                        reinterpret_cast<ReciprocateData*>(data->value[i])->value[j] = storage_Int(SvIV(temp), SvPV(sv_key, PL_na));
                    } else if (SvTYPE(temp) == SVt_NV) {
                        reinterpret_cast<ReciprocateData*>(data->value[i])->value[j] = storage_Float(SvNV(temp), SvPV(sv_key, PL_na));
                    } else if (SvTYPE(temp) == SVt_PV) {
                        reinterpret_cast<ReciprocateData*>(data->value[i])->value[j] = storage_String(SvPV(temp, PL_na), SvPV(sv_key, PL_na));
                    } else {
                        reinterpret_cast<ReciprocateData*>(data->value[i])->value[j] = converter(temp);
                        reinterpret_cast<ReciprocateData*>(reinterpret_cast<ReciprocateData*>(data->value[i])->value[j])->type = DATATYPE_STRUCT;
                        reinterpret_cast<ReciprocateData*>(reinterpret_cast<ReciprocateData*>(data->value[i])->value[j])->key = SvPV(sv_key, PL_na);
                    }



//                    HV* localHash = newHV();
//                    std::cout << "key is " << SvPV(sv_key, PL_na) << std::endl;
//                    hv_store(localHash, SvPV(sv_key, PL_na), strlen(SvPV(sv_key, PL_na)), temp, 0);
//                    reinterpret_cast<ReciprocateData*>(data->value[i])->value[j] = (converter(newRV_inc(reinterpret_cast<SV*>(localHash))));
//                    reinterpret_cast<ReciprocateData*>(reinterpret_cast<ReciprocateData*>(data->value[i])->value[j])->key = SvPV(sv_key, PL_na);
//                    //printf("Array, %s => %s\n", SvPV(sv_key, PL_na), SvPV(temp, PL_na));
//                    std::cout << "data->value[i]->value["<<j<<"]->type = " << reinterpret_cast<ReciprocateData*>(reinterpret_cast<ReciprocateData*>(data->value[i])->value[j])->type << std::endl;
//                    std::cout << "data->value[i]->value["<<j<<"]->num = " << reinterpret_cast<ReciprocateData*>(reinterpret_cast<ReciprocateData*>(data->value[i])->value[j])->num << std::endl;
//                    std::cout << "data->value[i]->value["<<j<<"]->key = " << reinterpret_cast<ReciprocateData*>(reinterpret_cast<ReciprocateData*>(data->value[i])->value[j])->key << std::endl;
//                    std::cout << "data->value[i]->value["<<j<<"]->value[0] = " << *reinterpret_cast<int*>(reinterpret_cast<ReciprocateData*>(reinterpret_cast<ReciprocateData*>(data->value[i])->value[j])->value[0]) << std::endl;
//                    std::cout << "data->value[i]->value["<<j<<"]->value[0]->value[0] = " << *reinterpret_cast<int*>(reinterpret_cast<ReciprocateData*>(reinterpret_cast<ReciprocateData*>(reinterpret_cast<ReciprocateData*>(data->value[i])->value[j])->value[0])->value[0]) << std::endl;
                }

                int type = reinterpret_cast<ReciprocateData*>(reinterpret_cast<ReciprocateData*>(data->value[i])->value[0])->type;
                switch (type) {
                case DATATYPE_INT: {
                    reinterpret_cast<ReciprocateData*>(data->value[i])->type = DATATYPE_INTARRAY;
                    break;
                }
                case DATATYPE_FLOAT: {
                    reinterpret_cast<ReciprocateData*>(data->value[i])->type = DATATYPE_FLOATARRAY;
                    break;
                }
                case DATATYPE_STRUCT: {
                    reinterpret_cast<ReciprocateData*>(data->value[i])->type = DATATYPE_STRUCTARRAY;
                    break;
                }
                default: {
                    std::cout << "can't set a type : " << type << std::endl;
                    assert(0);
                    break;
                }
                }

                reinterpret_cast<ReciprocateData*>(data->value[i])->key = SvPV(sv_key, PL_na);
                reinterpret_cast<ReciprocateData*>(data->value[i])->num = size;




//                AV* ar = (AV*)SvRV(sv_val);
//                SV* temp;
//                ReciprocateData* localData;
//
//                localData->num = av_len(ar);
//                ReciprocateData* dataArray[av_len(ar)];
//
//                for (int j = 0; av_len(ar) != -1; ++j) {
//                    temp = av_shift(ar);
//                    dataArray[j] = converter(temp);
//                }
//
//                // temp に実際にデータが入っているのでそれを参考に何型の配列だったのかを探る
//                if (SvTYPE(temp) == SVt_IV) {
//                    localData->type = DATATYPE_INTARRAY;
//                } else if (SvTYPE(temp) == SVt_NV) {
//                    localData->type = DATATYPE_FLOATARRAY;
//                } else if (SvTYPE(temp) == SVt_PV) {
//                    localData->type = DATATYPE_STRING;
//                } else {
//                    // 配列の直後に配列のパターンは無いはずなので
//                    localData->type = DATATYPE_STRUCTARRAY;
//                }
//
//                localData->value = reinterpret_cast<void**>(dataArray);
//                data->value[i] = reinterpret_cast<void*>(localData);
            } else if (SvTYPE(SvRV(sv_val)) == SVt_PVHV) {
                //std::cout << "Hash!!" << std::endl;
                //std::cout << "key => " << SvPV(sv_key, PL_na) << std::endl;
                HV* temphash = (HV*)SvRV(sv_val);

                data->value[i] = converter(newRV_noinc((SV*)temphash));
                reinterpret_cast<ReciprocateData*>(data->value[i])->type = DATATYPE_STRUCT;
                reinterpret_cast<ReciprocateData*>(data->value[i])->key = SvPV(sv_key, PL_na);
            } else {
                assert(0);
                printf("Another, %s => %s\n", SvPV(sv_key, PL_na), SvPV(sv_val, PL_na));
                return NULL;
            }
        }
    }       //    for (i = 0; i < num_keys; i++);

    return data;
}

#line 421 "main_pl_4f25.c"
XS(XS_main_getCommand); /* prototype to pass -Wmissing-prototypes */
XS(XS_main_getCommand)
{
    dXSARGS;
    if (items != 0)
	Perl_croak(aTHX_ "Usage: main::getCommand()");
    {
	SV *	RETVAL;

	RETVAL = getCommand();
	ST(0) = RETVAL;
	sv_2mortal(ST(0));
    }
    XSRETURN(1);
}

XS(XS_main_makeHash); /* prototype to pass -Wmissing-prototypes */
XS(XS_main_makeHash)
{
    dXSARGS;
    if (items != 0)
	Perl_croak(aTHX_ "Usage: main::makeHash()");
    {
	HV *	RETVAL;

	RETVAL = makeHash();
	ST(0) = newRV((SV*)RETVAL);
	sv_2mortal(ST(0));
    }
    XSRETURN(1);
}

XS(XS_main_makeInt); /* prototype to pass -Wmissing-prototypes */
XS(XS_main_makeInt)
{
    dXSARGS;
    if (items != 0)
	Perl_croak(aTHX_ "Usage: main::makeInt()");
    {
	HV *	RETVAL;

	RETVAL = makeInt();
	ST(0) = newRV((SV*)RETVAL);
	sv_2mortal(ST(0));
    }
    XSRETURN(1);
}

XS(XS_main_makeString); /* prototype to pass -Wmissing-prototypes */
XS(XS_main_makeString)
{
    dXSARGS;
    if (items != 0)
	Perl_croak(aTHX_ "Usage: main::makeString()");
    {
	HV *	RETVAL;

	RETVAL = makeString();
	ST(0) = newRV((SV*)RETVAL);
	sv_2mortal(ST(0));
    }
    XSRETURN(1);
}

XS(XS_main_makeIntArray); /* prototype to pass -Wmissing-prototypes */
XS(XS_main_makeIntArray)
{
    dXSARGS;
    if (items != 0)
	Perl_croak(aTHX_ "Usage: main::makeIntArray()");
    {
	HV *	RETVAL;

	RETVAL = makeIntArray();
	ST(0) = newRV((SV*)RETVAL);
	sv_2mortal(ST(0));
    }
    XSRETURN(1);
}

XS(XS_main_makeStruct); /* prototype to pass -Wmissing-prototypes */
XS(XS_main_makeStruct)
{
    dXSARGS;
    if (items != 0)
	Perl_croak(aTHX_ "Usage: main::makeStruct()");
    {
	HV *	RETVAL;

	RETVAL = makeStruct();
	ST(0) = newRV((SV*)RETVAL);
	sv_2mortal(ST(0));
    }
    XSRETURN(1);
}

XS(XS_main_dump_hash); /* prototype to pass -Wmissing-prototypes */
XS(XS_main_dump_hash)
{
    dXSARGS;
    if (items != 1)
	Perl_croak(aTHX_ "Usage: main::dump_hash(hash_ref)");
    SP -= items;
    {
	SV *	hash_ref = ST(0);
#line 437 "main_pl_4f25.xs"
	I32 *	__temp_markstack_ptr;
#line 529 "main_pl_4f25.c"
#line 439 "main_pl_4f25.xs"
	__temp_markstack_ptr = PL_markstack_ptr++;
	dump_hash(hash_ref);
        if (PL_markstack_ptr != __temp_markstack_ptr) {
          /* truly void, because dXSARGS not invoked */
          PL_markstack_ptr = __temp_markstack_ptr;
          XSRETURN_EMPTY; /* return empty stack */
        }
        /* must have used dXSARGS; list context implied */
        return; /* assume stack size is correct */
#line 540 "main_pl_4f25.c"
	PUTBACK;
	return;
    }
}

#ifdef __cplusplus
extern "C"
#endif
XS(boot_main_pl_4f25); /* prototype to pass -Wmissing-prototypes */
XS(boot_main_pl_4f25)
{
    dXSARGS;
    char* file = __FILE__;

    XS_VERSION_BOOTCHECK ;

        newXS("main::getCommand", XS_main_getCommand, file);
        newXS("main::makeHash", XS_main_makeHash, file);
        newXS("main::makeInt", XS_main_makeInt, file);
        newXS("main::makeString", XS_main_makeString, file);
        newXS("main::makeIntArray", XS_main_makeIntArray, file);
        newXS("main::makeStruct", XS_main_makeStruct, file);
        newXS("main::dump_hash", XS_main_dump_hash, file);
    XSRETURN_YES;
}

