#include "edge_common.h"

// The Callback Reference to use to force the next tick to happen
napi_ref CallbackHelper::callbackRef;

static napi_value NoOpFunction(napi_env env, napi_callback_info info) {
  return nullptr;
}

// Initialize the callback
napi_status CallbackHelper::Initialize(napi_env env) {
  DBG("CallbackHelper::Initialize");
  napi_status status;

  napi_value result;
  status = napi_create_function(env, "callbackHelper", NAPI_AUTO_LENGTH, NoOpFunction, nullptr, &result);
  status = napi_create_reference(env, result, 1, &callbackRef);

  return status;
}

// Make the no-op callback, forcing the next tick to execute
napi_status CallbackHelper::KickNextTick(napi_env env) {
  napi_status status;
  napi_value cb, result;
  status = napi_get_reference_value(env, callbackRef, &cb);
  status = napi_call_function(env, nullptr, cb, 0, nullptr, &result);

  return status;
}
