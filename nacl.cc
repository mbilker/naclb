#include <node.h>
#include <nan.h>
#include "functions.h"

using v8::Object;
using v8::String;

NAN_MODULE_INIT(InitAll) {
  Nan::Set(target, Nan::New<v8::String>("verify").ToLocalChecked(), Nan::GetFunction(Nan::New<v8::FunctionTemplate>(verify)).ToLocalChecked());
  Nan::Set(target, Nan::New<String>("sign").ToLocalChecked(), Nan::GetFunction(Nan::New<v8::FunctionTemplate>(sign)).ToLocalChecked());
}

NODE_MODULE(nacl, InitAll)
