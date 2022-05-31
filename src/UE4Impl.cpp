#include "UE4Genny.hpp"
#include "UObject/Class.h"
#include "UObject/UnrealType.h"
#include "UObject/EnumProperty.h"
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
    return (UClass*)find_object("Class /Script/CoreUObject.Struct");
}

UClass* UClass::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.Class");
}

UClass* UScriptStruct::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.ScriptStruct");
}

UClass* UEnum::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.Enum");
}

UClass* UFunction::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.Function");
}

UClass* UProperty::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.Property");
}

UClass* UByteProperty::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.ByteProperty");
}

UClass* UInt8Property::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.Int8Property");
}

UClass* UInt16Property::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.Int16Property");
}

UClass* UIntProperty::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.IntProperty");
}

UClass* UInt64Property::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.Int64Property");
}

UClass* UUInt16Property::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.UInt16Property");
}

UClass* UUInt32Property::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.UInt32Property");
}

UClass* UUInt64Property::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.UInt64Property");
}

UClass* UFloatProperty::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.FloatProperty");
}

UClass* UDoubleProperty::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.DoubleProperty");
}

UClass* UBoolProperty::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.BoolProperty");
}

UClass* UObjectProperty::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.ObjectProperty");
}

UClass* UNameProperty::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.NameProperty");
}

UClass* UStrProperty::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.StrProperty");
}

UClass* UArrayProperty::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.ArrayProperty");
}

UClass* UStructProperty::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.StructProperty");
}

UClass* UEnumProperty::GetPrivateStaticClass() {
    return (UClass*)find_object("Class /Script/CoreUObject.EnumProperty");
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