

namespace any_detail
{
    template<class ValueType>
    struct dummy {
    	static char p;
    };
    template<class ValueType>
    char dummy<ValueType>::p;
}

typedef void* type_id;
template<class ValueType>
type_id get_type_id() { return &any_detail::dummy<ValueType>::p; }


class Any {

};


int main() {
	Any any;
	any = 100;
	std::cout << any_cast<int>(any) << std::endl;
}

