/*
 * Copyright 2018 Axel Isouard <axel@isouard.fr>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <uv.h>
#include <string>

#include "common/module/module.h"
#include "public/moduleabstract.h"
#include "public/ustring.h"

using Public::ModuleAbstract;
using Public::UString;

namespace Common {
ModuleAbstract *Module::Load(const UString &path) {
  std::string str;
  uv_lib_t *lib = new uv_lib_t;
  ModuleAbstract *module;

  path.toUTF8String(str);
  if (uv_dlopen(str.c_str(), lib)) {
    return NULL;
  }

  ModuleAbstract *(*CreateModuleInstance)(void *);
  if (uv_dlsym(lib, "CreateModuleInstance",
               reinterpret_cast<void **>(&CreateModuleInstance))) {
    return NULL;
  }

  module = CreateModuleInstance(NULL);
  module->SetHandle(reinterpret_cast<void *>(lib));

  return module;
}

void Module::Unload(ModuleAbstract *module) {
  uv_lib_t *lib = reinterpret_cast<uv_lib_t *>(module->GetHandle());

  void (*DestroyModuleInstance)(void *);
  if (uv_dlsym(lib, "DestroyModuleInstance",
               reinterpret_cast<void **>(&DestroyModuleInstance))) {
    return;
  }

  DestroyModuleInstance(module);
  uv_dlclose(lib);

  delete lib;
}
}  // namespace Common
