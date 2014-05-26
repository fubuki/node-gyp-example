#include <node.h>
#include <node_buffer.h>
#include <v8.h>
#include <string>
#include <ctime>

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


//加法
Handle<Value> Add(const Arguments& args) {
	HandleScope scope;
	if(args.Length() < 2) {
		ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if(!args[0]->IsNumber() || !args[1]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

	Local<Number> num = Number::New(args[0]->NumberValue() + 
	args[1]->NumberValue());
	return scope.Close(num);
}

Handle<Value> Subtract(const Arguments& args) {

}

Handle<Value> GetTime(const Arguments& args) {
	HandleScope scope;
	Local<Function> cb = Local<Function>::Cast(args[0]);
	const unsigned argc = 1;
	time_t stamp = time(0);
	Local<Value> argv[argc] = { 
	Local<Value>::New(Number::New(stamp)) 
	};
	cb->Call(Context::GetCurrent()->Global(), argc, argv);
	return scope.Close(Undefined());
}



void init(Handle<Object> target, Handle<Object> module) {
	NODE_SET_METHOD(target, "hello", Method);
	NODE_SET_METHOD(target, "detect", detect);
	NODE_SET_METHOD(target, "plusNumber", plusNumber);
	NODE_SET_METHOD(target, "length", length);
	NODE_SET_METHOD(target, "transfer", transfer);

	target->Set(String::NewSymbol("add"),
	FunctionTemplate::New(Add)->GetFunction());
	target->Set(String::NewSymbol("subtract"),
	FunctionTemplate::New(Subtract)->GetFunction());

	module->Set(String::NewSymbol("target"),
	FunctionTemplate::New(GetTime)->GetFunction());
}

NODE_MODULE(hello, init);
