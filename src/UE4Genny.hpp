#pragma once

#include <string>

#include "UObject/UObjectArray.h"

FUObjectArray* get_GUObjectArray();
UObjectBase* find_uobject(const char* obj_path);
UObjectBase* find_uobject(size_t obj_path_hash);
std::string narrow(const FString& fstr);
std::string narrow(const FName& fname);

template <typename T, typename T2 = UObject*> T DCast(T2 In) {
    if (In && ((UObject*)In)->IsA<std::remove_pointer<T>::type>()) {
        return (T)In;
    }

    return nullptr;
}

