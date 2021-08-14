




class VoidArray
{
public:


	template<typename T> T value() throw()
{
	return (T)this->voidData;
}

	float voidData;
};

