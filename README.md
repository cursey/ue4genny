# **UE4Genny**

**UE4Genny** is an SDK generator for Unreal Engine games (late UE4 versions and UE5 supported). It aims to provide a functional SDK that requires little to no editing after generation to use. Actual SDK generation is done via the sister project [SdkGenny](https://github.com/cursey/sdkgenny).

***UE4Genny is intended for MODDING games not CHEATING!***

## Usage

**UE4Genny** requires some assembly (work on your part). It does not function out of the box. It contains **NO** code from Unreal Engine, you must provide that yourself. Here are the general steps to get **UE4Genny** working:

1. Clone this repository.
2. Download the source code for the correct version of UE that the game you are targeting uses.
    * You should also try using the same compiler the game uses to compile **UE4Genny**. 
3. Copy the `Engine/Source/` directory from UE to your **UE4Genny** directory (`<UE4Genny directory>/Source/`). **UE4Genny** will use this copy of UE's source code.
    * If you already have a copy of UE somewhere else and you would prefer to use that, you can set the CMake variable `UE4_SOURCE_DIR` to the directory you want to use.
4. Compilation will likely fail at this point because some edits to the UE source is required. Namely:
    * `<UE4 Source>/Runtime/CoreUObject/Public/UObject/Class.h`: Make `UEnum::Names`, `UStruct::SuperStruct` public.
    * `<UE4 Source>/Runtime/CoreUObject/Public/UObject/UnrealType.h`: Make `FBoolProperty::FieldSize`, `FBoolProperty::ByteMask` and `FBoolProperty::FieldMask` public.
    * `<UE4 Source>/Runtime/CoreUObject/Public/UObject/UObjectBase.h`: Make `UObjectBase::ClassPrivate` public.
5. **UE4Genny** should now compile.
6. Make a new config header file for the game you are targeting (an example is provided in `src/DRGConfig.hpp` which works for the current Xbox Game Pass version of *Deep Rock Galactic*).
7. Set the CMake variable `CONFIG_HPP` to the newly created config header file.
8. Define the following constants in your newly created config header file (you need to find the values for these constants yourself):

```
// A memory pattern string that can be used to find the games GUObjectArray global variable.
constexpr char* GUOBJECTARRAY_PAT = "...";

// A memory pattern string that can be used to find the games FName::ToString() method.
constexpr char* FNAME_TOSTRING_PAT = "...";

// The VTable index of the games UObject::ProcessEvent virtual method.
constexpr int UOBJECT_PROCESSEVENT_INDEX = ...;
```

At this point you should be able to compile a game specific version of **UE4Genny** that will work with your target game. If it still does not work, attach a debugger and see what the problem is. Occasionally you will need to modify certain base structures so that they match what the game has (usually not required if you're using the correct version of UE's source for a given game). You may also need to edit or add UE specific compiler definitions in the `CMakeLists.txt`. If it isn't working now it's up to you to fiddle around and figure out what changes you need to make to get everything that **UE4Genny** uses to match up with what your target game is using.

At the end of this process, simply inject `UE4Genny.dll` into the target game and wait for an `sdk/` folder to appear.

## Note about compatibility

**UE4Genny** is only tested with fairly recent versions of UE4 and UE5. Older versions of UE4's reflection system was fairly different so **UE4Genny** won't work with those older versions. At least not by following the steps outlined above. For older versions you will likely need to make some minor changes to **UE4Genny** (basically `FProperty` was previously `UProperty` and so on for the various property types).
