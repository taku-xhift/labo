
#include <exception>

#ifdef __cplusplus
//extern "C" {
#endif


void sayHello(const char* hello_) throw(std::exception);

void sayWorld(const char* world_) throw(std::exception);

//void sayHello();
//
//void sayWorld();


#ifdef __cplusplus
//}
#endif
