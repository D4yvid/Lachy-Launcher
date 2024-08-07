#pragma once

#include <cstring>

class ResourcePack;
class ResourcePackRepository;
class PackSettings;

struct PackInstance
{
  char filler[0x9C];

  PackInstance(ResourcePack*, int, bool, PackSettings*);
};

struct ResourcePackStack
{
  /// @symbol _ZTV17ResourcePackStack
  static void** vtable_sym;

  void** vtable;
  char filler[0x10];

  ResourcePackStack()
  {
    vtable = vtable_sym + 2;
    memset(filler, 0, sizeof(filler));
  }

  /// @symbol
  /// _ZN17ResourcePackStack3addE12PackInstanceRK22ResourcePackRepositoryb
  void add(PackInstance const& i, ResourcePackRepository const& r, bool b);
};