#include "UE4Genny.hpp"
#include "UObject/Class.h"
#include "kanan/core/Scan.hpp"
#include CONFIG_HPP

void FMemory::Free(void* mem) {
    // Big leaks.
}

void* FMemory::Realloc(void* mem, size_t size, uint32_t) {
    return realloc(mem, size);
}

size_t FMemory::QuantizeSize(size_t size, uint32_t) {
    return size;
}

UClass* UStruct::GetPrivateStaticClass() {
    return (UClass*)find_uobject("Class /Script/CoreUObject.Struct");
}

UClass* UClass::GetPrivateStaticClass() {
    return (UClass*)find_uobject("Class /Script/CoreUObject.Class");
}

UClass* UScriptStruct::GetPrivateStaticClass() {
    return (UClass*)find_uobject("Class /Script/CoreUObject.ScriptStruct");
}

UClass* UEnum::GetPrivateStaticClass() {
    return (UClass*)find_uobject("Class /Script/CoreUObject.Enum");
}

UClass* UFunction::GetPrivateStaticClass() {
    return (UClass*)find_uobject("Class /Script/CoreUObject.Function");
}

FString FName::ToString() const {
    FString out;

    static void (*toString)(const FName*, FString&){};

    if (toString == nullptr) {
        OutputDebugString(L"Finding FName::ToString...");

        toString = (decltype(toString))kanan::scan(FNAME_TOSTRING_PAT).value_or(0);

        if (toString == nullptr) {
            OutputDebugString(L"Failed to find FName::ToString!");
        } else {
            OutputDebugString(L"Found FName::ToString!");
        }
    }

    toString(this, out);
    return out;
}