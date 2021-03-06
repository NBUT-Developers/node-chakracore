// Copyright Microsoft. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and / or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#include "v8.h"
#include "v8chakra.h"
#include "jsrtutils.h"

namespace v8 {

Template::Template() {
}

Object* GetTemplateProperties(Template* const templ) {
  ExternalData* externalData = nullptr;
  if (!ExternalData::TryGet(templ, &externalData)) {
    // This should never happen
    CHAKRA_ASSERT(false);
    return nullptr;
  }

  TemplateData *templateData = static_cast<TemplateData*>(externalData);
  return templateData->EnsureProperties();
}

void Template::Set(
    Local<Name> name, Local<Data> value, PropertyAttribute attributes) {
  Object* properties = GetTemplateProperties(this);
  if (properties != nullptr) {
    properties->ForceSet(name, value.As<Value>(), attributes);
  }
}

void Template::SetAccessorProperty(
    Local<Name> name,
    Local<FunctionTemplate> getter,
    Local<FunctionTemplate> setter,
    PropertyAttribute attribute,
    AccessControl access_control) {
  Object* properties = GetTemplateProperties(this);
  if (properties != nullptr) {
    properties->SetAccessorProperty(
        name,
        !getter.IsEmpty() ? getter->GetFunction() : Local<Function>(),
        !setter.IsEmpty() ? setter->GetFunction() : Local<Function>(),
        attribute,
        access_control);
  }
}

}  // namespace v8
