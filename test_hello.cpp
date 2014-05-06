#include <node.h>
#include <v8.h>
#include <string>

using namespace v8; 
using namespace std;

Handle<Value> Method(const Arguments& args) {
  	HandleScope scope;
  	return scope.Close(String::New("world"));
}

Handle<Value> detect(const Arguments& args) {
  	HandleScope scope;
  	Local<Value> arg = args[0];
  	bool isArray = arg->IsArray();
	bool isNumber = arg->IsNumber();

	std::string result ;
	
	if (isNumber) {
		result = "isNumber";
	} else if (isArray) {
		result = "isArray";
	} else {
		result = "the other type";
	}
	
	return scope.Close(String::New(result.c_str()));
}

Handle<Value> plusNumber(const Arguments& args) {
  	HandleScope scope;
  	Local<Value> arg = args[0];
  	Local<Number> number = arg->ToNumber();
  	int32_t seq = number->Value();
  	seq++;

	return scope.Close(Integer::New(seq));
}


void init(Handle<Object> target) {
	NODE_SET_METHOD(target, "hello", Method);
	NODE_SET_METHOD(target, "detect", detect);
	NODE_SET_METHOD(target, "plusNumber", plusNumber);
}

NODE_MODULE(hello, init);
