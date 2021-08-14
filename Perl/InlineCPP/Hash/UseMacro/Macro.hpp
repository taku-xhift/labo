

#define createHash(data) {\
						  HV* hash = newHV();\
						  hv_store(hash, "key", strlen("key"), newSViv(data.integer), 0);\
						  return hash;\
}


struct Test {
	int integer;
};


int getBig(int data1, int data2);

