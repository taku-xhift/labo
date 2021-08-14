

typedef struct {
	const char* strings;
} Character;


void out(const char* strings_) {
	printf("%s\n", strings_);
}


int main()
{
	Character character;
	character.strings = "Hello World!!";
	character.strings = "Goodbye World!!";

	out(character.strings);

	return 0;
}

