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
	
	String reault = "";

	if (isNumber) {
		reault = "isNumber";
	} else if (isArray) {
		reault = "isArray";
	} else {
		reault = "the other thing";
	}
	
	return scope.Close(String::New(reault));
}

Handle<Value> plus(const Arguments& args) {
  	HandleScope scope;
  	Local<Value> arg = args[0];
  	Local<Number> number = arg->ToNumber();
  	number++;
	return scope.Close(Number::New(number));
}


void init(Handle<Object> target) {
	NODE_SET_METHOD(target, "hello", Method);
	NODE_SET_METHOD(target, "detect", detect);
}

NODE_MODULE(hello, init);
