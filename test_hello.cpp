#include <node.h>
#include <node_buffer.h>
#include <v8.h>
#include <string>

using namespace v8;
using namespace node;  
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


Handle<Value> length(const Arguments &args) {
	HandleScope scope;
	Local<Value> arg = args[0];
  	if(!Buffer::HasInstance(arg)) { //判断是否是Buffer对象
    	ThrowException(v8::Exception::TypeError(v8::String::New("Bad argument!")));  //抛出js异常 
  	}
  	size_t size = Buffer::Length(arg->ToObject());  //获取Buffer长度
  	char *buf = Buffer::Data(arg->ToObject());      //获取Buffer内容
  	return scope.Close(v8::Integer::New(size));
}

Handle<Value> transfer(const Arguments& args) {
	HandleScope scope;
  	char a[6] = {13, 1, 1, 0, 0, -123};
  	//return scope.Close(Buffer::New(String::New(a))); //会被第四个字符0截断
  	return scope.Close(Buffer::New(String::New(a, 6))); //无法解析成utf-8或者iscii，转换错误
}

void init(Handle<Object> target) {
	NODE_SET_METHOD(target, "hello", Method);
	NODE_SET_METHOD(target, "detect", detect);
	NODE_SET_METHOD(target, "plusNumber", plusNumber);
	NODE_SET_METHOD(target, "length", length);
	NODE_SET_METHOD(target, "transfer", transfer);
}

NODE_MODULE(hello, init);
