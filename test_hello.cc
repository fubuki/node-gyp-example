#include <node.h>
#include <v8.h>

using namespace v8;

Handle<Value> Method(const Arguments& args) {
  	HandleScope scope;
  	return scope.Close(String::New("world"));
}

Handle<Value> detect(const Arguments& args) {
  	HandleScope scope;
  	Local<Value> arg = args[0];
  	bool isArray = arg->IsArray();
	bool isBoolean = arg->IsBoolean();
	bool isNumber = arg->IsNumber();
	bool isInt32 = arg->IsInt32();

	if (isNumber) {

		return scope.Close(String::New("isNumber"));
	} else if (isArray) {
		return scope.Close(String::New("isArray"));
	} else {
		return scope.Close(String::New("the other thing"));
	}


  	
}


void init(Handle<Object> target) {
	NODE_SET_METHOD(target, "hello", Method);
	NODE_SET_METHOD(target, "detect", detect);
}

NODE_MODULE(hello, init);
