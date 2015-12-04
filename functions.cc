#include <node.h>
#include <nan.h>
#include "./functions.h"
#include <stdio.h>
#include <stdlib.h>
#include "tweetnacl.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef long long i64;
typedef i64 gf[16];

const int crypto_sign_BYTES = 64;
const uint8_t bug_offset = 64;

using v8::Local;
using v8::Object;
using v8::Boolean;
using v8::Integer;
using v8::Value;
using v8::Isolate;
using v8::HandleScope;
using v8::Array;

/**
* Crypto verification function (Ed25519)
*/
NAN_METHOD(verify) {
  // Reading clear message
  //v8::Local<v8::Object> msg = info[0]->ToObject();
  //u64 mlen = msg->GetIndexedPropertiesExternalArrayDataLength();
  //u8* m = static_cast<u8*>(msg->GetIndexedPropertiesExternalArrayData());
  Nan::TypedArrayContents<uint8_t> msg(info[0]);
  u64 mlen = msg.length();

  // Reading detached signature
  //v8::Local<v8::Object> sig = info[1]->ToObject();
  //u64 smlen = sig->GetIndexedPropertiesExternalArrayDataLength();
  //const u8* sm = static_cast<u8*>(sig->GetIndexedPropertiesExternalArrayData());
  Nan::TypedArrayContents<uint8_t> sig(info[1]);
  u64 smlen = sig.length();

  // Reading public key
  //v8::Local<v8::Object> pub = info[2]->ToObject();
  //const u8* pubk = static_cast<u8*>(pub->GetIndexedPropertiesExternalArrayData());
  Nan::TypedArrayContents<uint8_t> pubk(info[2]);

  // Verifying authenticity
  int res = crypto_sign_open((*msg), &mlen, (*sig), smlen, (*pubk));

  info.GetReturnValue().Set(res == 0);
}


/**
* Crypto signature function (Ed25519)
*/
NAN_METHOD(sign) {
  // Reading clear message
  //v8::Local<v8::Object> msg = info[0]->ToObject();
  //u64 mlen = msg->GetIndexedPropertiesExternalArrayDataLength() - bug_offset;
  //const u8* m = static_cast<u8*>(msg->GetIndexedPropertiesExternalArrayData());
  //const u8* m2 = m + bug_offset;
  Nan::TypedArrayContents<uint8_t> msg(info[0]);
  uint64_t mlen = msg.length() - bug_offset;
  const uint8_t* m2 = (*msg) + bug_offset;

  // Reading public key
  //v8::Local<v8::Object> sec = info[1]->ToObject();
  //const u8* seck = static_cast<u8*>(sec->GetIndexedPropertiesExternalArrayData());
  Nan::TypedArrayContents<uint8_t> seck(info[1]);

  u8* sm;
  u64 smlen = 0;

  sm = (u8*) malloc(mlen + crypto_sign_BYTES);

  // Signing
  crypto_sign(sm, &smlen, m2, mlen, (*seck));

  // Result
  v8::Local<v8::Object> array = Nan::New<v8::Array>(smlen);

  for (uint8_t i = 0; i < smlen; i++) {
    array->Set(i, Nan::New<v8::Integer>(sm[i]));
  }

  // Free memory
  free(sm);

  info.GetReturnValue().Set(array);
}
