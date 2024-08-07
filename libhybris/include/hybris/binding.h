
/**
 * Copyright (C) 2013 Simon Busch <morphis@gravedo.de>
 *               2012 Canonical Ltd
 *               2013 Jolla Ltd.
 *
 * Auto-generated via "generate_wrapper_macros.py"
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **/

#ifndef HYBRIS_BINDING_H_
#define HYBRIS_BINDING_H_

/* floating_point_abi.h defines FP_ATTRIB */
#include "floating_point_abi.h"

void *android_dlopen(const char *filename, int flag);
void *android_dlsym(void *name, const char *symbol);
int android_dlclose(void *handle);
const char *android_dlerror(void);
int android_dladdr(const void *addr, void *info);

/**
 *         XXX AUTO-GENERATED FILE XXX
 *
 * Do not edit this file directly, but update the templates in
 * utils/generate_wrapper_macros.py and run it again to build
 * an updated version of this header file:
 *
 *    python utils/generate_wrapper_macros.py > \
 *       hybris/include/hybris/common/binding.h
 *
 * If you need macros with more arguments, just customize the
 * MAX_ARGS variable in generate_wrapper_macros.py.
 *
 *         XXX AUTO-GENERATED FILE XXX
 **/

#define HYBRIS_DLSYSM(name, fptr, sym)                   \
  if (!name##_handle) hybris_##name##_initialize();      \
  if (*(fptr) == NULL)                                   \
  {                                                      \
    *(fptr) = (void *)android_dlsym(name##_handle, sym); \
  }

#define HYBRIS_LIBRARY_INITIALIZE(name, path)        \
  void *name##_handle;                               \
  void hybris_##name##_initialize()                  \
  {                                                  \
    name##_handle = android_dlopen(path, RTLD_LAZY); \
  }

#define HYBRIS_IMPLEMENT_FUNCTION0(name, return_type, symbol) \
  return_type symbol()                                        \
  {                                                           \
    static return_type (*f)() FP_ATTRIB = NULL;               \
    HYBRIS_DLSYSM(name, &f, #symbol);                         \
    return f();                                               \
  }

#define HYBRIS_IMPLEMENT_FUNCTION1(name, return_type, symbol, a1) \
  return_type symbol(a1 n1)                                       \
  {                                                               \
    static return_type (*f)(a1) FP_ATTRIB = NULL;                 \
    HYBRIS_DLSYSM(name, &f, #symbol);                             \
    return f(n1);                                                 \
  }

#define HYBRIS_IMPLEMENT_FUNCTION2(name, return_type, symbol, a1, a2) \
  return_type symbol(a1 n1, a2 n2)                                    \
  {                                                                   \
    static return_type (*f)(a1, a2) FP_ATTRIB = NULL;                 \
    HYBRIS_DLSYSM(name, &f, #symbol);                                 \
    return f(n1, n2);                                                 \
  }

#define HYBRIS_IMPLEMENT_FUNCTION3(name, return_type, symbol, a1, a2, a3) \
  return_type symbol(a1 n1, a2 n2, a3 n3)                                 \
  {                                                                       \
    static return_type (*f)(a1, a2, a3) FP_ATTRIB = NULL;                 \
    HYBRIS_DLSYSM(name, &f, #symbol);                                     \
    return f(n1, n2, n3);                                                 \
  }

#define HYBRIS_IMPLEMENT_FUNCTION4(name, return_type, symbol, a1, a2, a3, a4) \
  return_type symbol(a1 n1, a2 n2, a3 n3, a4 n4)                              \
  {                                                                           \
    static return_type (*f)(a1, a2, a3, a4) FP_ATTRIB = NULL;                 \
    HYBRIS_DLSYSM(name, &f, #symbol);                                         \
    return f(n1, n2, n3, n4);                                                 \
  }

#define HYBRIS_IMPLEMENT_FUNCTION5(name, return_type, symbol, a1, a2, a3, a4, \
                                   a5)                                        \
  return_type symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5)                       \
  {                                                                           \
    static return_type (*f)(a1, a2, a3, a4, a5) FP_ATTRIB = NULL;             \
    HYBRIS_DLSYSM(name, &f, #symbol);                                         \
    return f(n1, n2, n3, n4, n5);                                             \
  }

#define HYBRIS_IMPLEMENT_FUNCTION6(name, return_type, symbol, a1, a2, a3, a4, \
                                   a5, a6)                                    \
  return_type symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6)                \
  {                                                                           \
    static return_type (*f)(a1, a2, a3, a4, a5, a6) FP_ATTRIB = NULL;         \
    HYBRIS_DLSYSM(name, &f, #symbol);                                         \
    return f(n1, n2, n3, n4, n5, n6);                                         \
  }

#define HYBRIS_IMPLEMENT_FUNCTION7(name, return_type, symbol, a1, a2, a3, a4, \
                                   a5, a6, a7)                                \
  return_type symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7)         \
  {                                                                           \
    static return_type (*f)(a1, a2, a3, a4, a5, a6, a7) FP_ATTRIB = NULL;     \
    HYBRIS_DLSYSM(name, &f, #symbol);                                         \
    return f(n1, n2, n3, n4, n5, n6, n7);                                     \
  }

#define HYBRIS_IMPLEMENT_FUNCTION8(name, return_type, symbol, a1, a2, a3, a4, \
                                   a5, a6, a7, a8)                            \
  return_type symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8)  \
  {                                                                           \
    static return_type (*f)(a1, a2, a3, a4, a5, a6, a7, a8) FP_ATTRIB = NULL; \
    HYBRIS_DLSYSM(name, &f, #symbol);                                         \
    return f(n1, n2, n3, n4, n5, n6, n7, n8);                                 \
  }

#define HYBRIS_IMPLEMENT_FUNCTION9(name, return_type, symbol, a1, a2, a3, a4, \
                                   a5, a6, a7, a8, a9)                        \
  return_type symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8,  \
                     a9 n9)                                                   \
  {                                                                           \
    static return_type (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9) FP_ATTRIB =   \
        NULL;                                                                 \
    HYBRIS_DLSYSM(name, &f, #symbol);                                         \
    return f(n1, n2, n3, n4, n5, n6, n7, n8, n9);                             \
  }

#define HYBRIS_IMPLEMENT_FUNCTION10(name, return_type, symbol, a1, a2, a3, a4, \
                                    a5, a6, a7, a8, a9, a10)                   \
  return_type symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8,   \
                     a9 n9, a10 n10)                                           \
  {                                                                            \
    static return_type (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)           \
        FP_ATTRIB = NULL;                                                      \
    HYBRIS_DLSYSM(name, &f, #symbol);                                          \
    return f(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10);                         \
  }

#define HYBRIS_IMPLEMENT_FUNCTION11(name, return_type, symbol, a1, a2, a3, a4, \
                                    a5, a6, a7, a8, a9, a10, a11)              \
  return_type symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8,   \
                     a9 n9, a10 n10, a11 n11)                                  \
  {                                                                            \
    static return_type (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11)      \
        FP_ATTRIB = NULL;                                                      \
    HYBRIS_DLSYSM(name, &f, #symbol);                                          \
    return f(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11);                    \
  }

#define HYBRIS_IMPLEMENT_FUNCTION12(name, return_type, symbol, a1, a2, a3, a4, \
                                    a5, a6, a7, a8, a9, a10, a11, a12)         \
  return_type symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8,   \
                     a9 n9, a10 n10, a11 n11, a12 n12)                         \
  {                                                                            \
    static return_type (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) \
        FP_ATTRIB = NULL;                                                      \
    HYBRIS_DLSYSM(name, &f, #symbol);                                          \
    return f(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12);               \
  }

#define HYBRIS_IMPLEMENT_FUNCTION13(name, return_type, symbol, a1, a2, a3, a4, \
                                    a5, a6, a7, a8, a9, a10, a11, a12, a13)    \
  return_type symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8,   \
                     a9 n9, a10 n10, a11 n11, a12 n12, a13 n13)                \
  {                                                                            \
    static return_type (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                            a13) FP_ATTRIB = NULL;                             \
    HYBRIS_DLSYSM(name, &f, #symbol);                                          \
    return f(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13);          \
  }

#define HYBRIS_IMPLEMENT_FUNCTION14(name, return_type, symbol, a1, a2, a3, a4, \
                                    a5, a6, a7, a8, a9, a10, a11, a12, a13,    \
                                    a14)                                       \
  return_type symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8,   \
                     a9 n9, a10 n10, a11 n11, a12 n12, a13 n13, a14 n14)       \
  {                                                                            \
    static return_type (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                            a13, a14) FP_ATTRIB = NULL;                        \
    HYBRIS_DLSYSM(name, &f, #symbol);                                          \
    return f(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14);     \
  }

#define HYBRIS_IMPLEMENT_FUNCTION15(name, return_type, symbol, a1, a2, a3, a4, \
                                    a5, a6, a7, a8, a9, a10, a11, a12, a13,    \
                                    a14, a15)                                  \
  return_type symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8,   \
                     a9 n9, a10 n10, a11 n11, a12 n12, a13 n13, a14 n14,       \
                     a15 n15)                                                  \
  {                                                                            \
    static return_type (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                            a13, a14, a15) FP_ATTRIB = NULL;                   \
    HYBRIS_DLSYSM(name, &f, #symbol);                                          \
    return f(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14,      \
             n15);                                                             \
  }

#define HYBRIS_IMPLEMENT_FUNCTION16(name, return_type, symbol, a1, a2, a3, a4, \
                                    a5, a6, a7, a8, a9, a10, a11, a12, a13,    \
                                    a14, a15, a16)                             \
  return_type symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8,   \
                     a9 n9, a10 n10, a11 n11, a12 n12, a13 n13, a14 n14,       \
                     a15 n15, a16 n16)                                         \
  {                                                                            \
    static return_type (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                            a13, a14, a15, a16) FP_ATTRIB = NULL;              \
    HYBRIS_DLSYSM(name, &f, #symbol);                                          \
    return f(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15, \
             n16);                                                             \
  }

#define HYBRIS_IMPLEMENT_FUNCTION17(name, return_type, symbol, a1, a2, a3, a4, \
                                    a5, a6, a7, a8, a9, a10, a11, a12, a13,    \
                                    a14, a15, a16, a17)                        \
  return_type symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8,   \
                     a9 n9, a10 n10, a11 n11, a12 n12, a13 n13, a14 n14,       \
                     a15 n15, a16 n16, a17 n17)                                \
  {                                                                            \
    static return_type (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                            a13, a14, a15, a16, a17) FP_ATTRIB = NULL;         \
    HYBRIS_DLSYSM(name, &f, #symbol);                                          \
    return f(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15, \
             n16, n17);                                                        \
  }

#define HYBRIS_IMPLEMENT_FUNCTION18(name, return_type, symbol, a1, a2, a3, a4, \
                                    a5, a6, a7, a8, a9, a10, a11, a12, a13,    \
                                    a14, a15, a16, a17, a18)                   \
  return_type symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8,   \
                     a9 n9, a10 n10, a11 n11, a12 n12, a13 n13, a14 n14,       \
                     a15 n15, a16 n16, a17 n17, a18 n18)                       \
  {                                                                            \
    static return_type (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                            a13, a14, a15, a16, a17, a18) FP_ATTRIB = NULL;    \
    HYBRIS_DLSYSM(name, &f, #symbol);                                          \
    return f(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15, \
             n16, n17, n18);                                                   \
  }

#define HYBRIS_IMPLEMENT_FUNCTION19(name, return_type, symbol, a1, a2, a3, a4, \
                                    a5, a6, a7, a8, a9, a10, a11, a12, a13,    \
                                    a14, a15, a16, a17, a18, a19)              \
  return_type symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8,   \
                     a9 n9, a10 n10, a11 n11, a12 n12, a13 n13, a14 n14,       \
                     a15 n15, a16 n16, a17 n17, a18 n18, a19 n19)              \
  {                                                                            \
    static return_type (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                            a13, a14, a15, a16, a17, a18, a19) FP_ATTRIB =     \
        NULL;                                                                  \
    HYBRIS_DLSYSM(name, &f, #symbol);                                          \
    return f(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15, \
             n16, n17, n18, n19);                                              \
  }

#define HYBRIS_IMPLEMENT_VOID_FUNCTION0(name, symbol) \
  void symbol()                                       \
  {                                                   \
    static void (*f)() FP_ATTRIB = NULL;              \
    HYBRIS_DLSYSM(name, &f, #symbol);                 \
    f();                                              \
  }

#define HYBRIS_IMPLEMENT_VOID_FUNCTION1(name, symbol, a1) \
  void symbol(a1 n1)                                      \
  {                                                       \
    static void (*f)(a1) FP_ATTRIB = NULL;                \
    HYBRIS_DLSYSM(name, &f, #symbol);                     \
    f(n1);                                                \
  }

#define HYBRIS_IMPLEMENT_VOID_FUNCTION2(name, symbol, a1, a2) \
  void symbol(a1 n1, a2 n2)                                   \
  {                                                           \
    static void (*f)(a1, a2) FP_ATTRIB = NULL;                \
    HYBRIS_DLSYSM(name, &f, #symbol);                         \
    f(n1, n2);                                                \
  }

#define HYBRIS_IMPLEMENT_VOID_FUNCTION3(name, symbol, a1, a2, a3) \
  void symbol(a1 n1, a2 n2, a3 n3)                                \
  {                                                               \
    static void (*f)(a1, a2, a3) FP_ATTRIB = NULL;                \
    HYBRIS_DLSYSM(name, &f, #symbol);                             \
    f(n1, n2, n3);                                                \
  }

#define HYBRIS_IMPLEMENT_VOID_FUNCTION4(name, symbol, a1, a2, a3, a4) \
  void symbol(a1 n1, a2 n2, a3 n3, a4 n4)                             \
  {                                                                   \
    static void (*f)(a1, a2, a3, a4) FP_ATTRIB = NULL;                \
    HYBRIS_DLSYSM(name, &f, #symbol);                                 \
    f(n1, n2, n3, n4);                                                \
  }

#define HYBRIS_IMPLEMENT_VOID_FUNCTION5(name, symbol, a1, a2, a3, a4, a5) \
  void symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5)                          \
  {                                                                       \
    static void (*f)(a1, a2, a3, a4, a5) FP_ATTRIB = NULL;                \
    HYBRIS_DLSYSM(name, &f, #symbol);                                     \
    f(n1, n2, n3, n4, n5);                                                \
  }

#define HYBRIS_IMPLEMENT_VOID_FUNCTION6(name, symbol, a1, a2, a3, a4, a5, a6) \
  void symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6)                       \
  {                                                                           \
    static void (*f)(a1, a2, a3, a4, a5, a6) FP_ATTRIB = NULL;                \
    HYBRIS_DLSYSM(name, &f, #symbol);                                         \
    f(n1, n2, n3, n4, n5, n6);                                                \
  }

#define HYBRIS_IMPLEMENT_VOID_FUNCTION7(name, symbol, a1, a2, a3, a4, a5, a6, \
                                        a7)                                   \
  void symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7)                \
  {                                                                           \
    static void (*f)(a1, a2, a3, a4, a5, a6, a7) FP_ATTRIB = NULL;            \
    HYBRIS_DLSYSM(name, &f, #symbol);                                         \
    f(n1, n2, n3, n4, n5, n6, n7);                                            \
  }

#define HYBRIS_IMPLEMENT_VOID_FUNCTION8(name, symbol, a1, a2, a3, a4, a5, a6, \
                                        a7, a8)                               \
  void symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8)         \
  {                                                                           \
    static void (*f)(a1, a2, a3, a4, a5, a6, a7, a8) FP_ATTRIB = NULL;        \
    HYBRIS_DLSYSM(name, &f, #symbol);                                         \
    f(n1, n2, n3, n4, n5, n6, n7, n8);                                        \
  }

#define HYBRIS_IMPLEMENT_VOID_FUNCTION9(name, symbol, a1, a2, a3, a4, a5, a6, \
                                        a7, a8, a9)                           \
  void symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8, a9 n9)  \
  {                                                                           \
    static void (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9) FP_ATTRIB = NULL;    \
    HYBRIS_DLSYSM(name, &f, #symbol);                                         \
    f(n1, n2, n3, n4, n5, n6, n7, n8, n9);                                    \
  }

#define HYBRIS_IMPLEMENT_VOID_FUNCTION10(name, symbol, a1, a2, a3, a4, a5, a6, \
                                         a7, a8, a9, a10)                      \
  void symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8, a9 n9,   \
              a10 n10)                                                         \
  {                                                                            \
    static void (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) FP_ATTRIB =      \
        NULL;                                                                  \
    HYBRIS_DLSYSM(name, &f, #symbol);                                          \
    f(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10);                                \
  }

#define HYBRIS_IMPLEMENT_VOID_FUNCTION11(name, symbol, a1, a2, a3, a4, a5, a6, \
                                         a7, a8, a9, a10, a11)                 \
  void symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8, a9 n9,   \
              a10 n10, a11 n11)                                                \
  {                                                                            \
    static void (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) FP_ATTRIB = \
        NULL;                                                                  \
    HYBRIS_DLSYSM(name, &f, #symbol);                                          \
    f(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11);                           \
  }

#define HYBRIS_IMPLEMENT_VOID_FUNCTION12(name, symbol, a1, a2, a3, a4, a5, a6, \
                                         a7, a8, a9, a10, a11, a12)            \
  void symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8, a9 n9,   \
              a10 n10, a11 n11, a12 n12)                                       \
  {                                                                            \
    static void (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12)        \
        FP_ATTRIB = NULL;                                                      \
    HYBRIS_DLSYSM(name, &f, #symbol);                                          \
    f(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12);                      \
  }

#define HYBRIS_IMPLEMENT_VOID_FUNCTION13(name, symbol, a1, a2, a3, a4, a5, a6, \
                                         a7, a8, a9, a10, a11, a12, a13)       \
  void symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8, a9 n9,   \
              a10 n10, a11 n11, a12 n12, a13 n13)                              \
  {                                                                            \
    static void (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13)   \
        FP_ATTRIB = NULL;                                                      \
    HYBRIS_DLSYSM(name, &f, #symbol);                                          \
    f(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13);                 \
  }

#define HYBRIS_IMPLEMENT_VOID_FUNCTION14(name, symbol, a1, a2, a3, a4, a5, a6, \
                                         a7, a8, a9, a10, a11, a12, a13, a14)  \
  void symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8, a9 n9,   \
              a10 n10, a11 n11, a12 n12, a13 n13, a14 n14)                     \
  {                                                                            \
    static void (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13,   \
                     a14) FP_ATTRIB = NULL;                                    \
    HYBRIS_DLSYSM(name, &f, #symbol);                                          \
    f(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14);            \
  }

#define HYBRIS_IMPLEMENT_VOID_FUNCTION15(name, symbol, a1, a2, a3, a4, a5, a6, \
                                         a7, a8, a9, a10, a11, a12, a13, a14,  \
                                         a15)                                  \
  void symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8, a9 n9,   \
              a10 n10, a11 n11, a12 n12, a13 n13, a14 n14, a15 n15)            \
  {                                                                            \
    static void (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13,   \
                     a14, a15) FP_ATTRIB = NULL;                               \
    HYBRIS_DLSYSM(name, &f, #symbol);                                          \
    f(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15);       \
  }

#define HYBRIS_IMPLEMENT_VOID_FUNCTION16(name, symbol, a1, a2, a3, a4, a5, a6, \
                                         a7, a8, a9, a10, a11, a12, a13, a14,  \
                                         a15, a16)                             \
  void symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8, a9 n9,   \
              a10 n10, a11 n11, a12 n12, a13 n13, a14 n14, a15 n15, a16 n16)   \
  {                                                                            \
    static void (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13,   \
                     a14, a15, a16) FP_ATTRIB = NULL;                          \
    HYBRIS_DLSYSM(name, &f, #symbol);                                          \
    f(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15, n16);  \
  }

#define HYBRIS_IMPLEMENT_VOID_FUNCTION17(name, symbol, a1, a2, a3, a4, a5, a6, \
                                         a7, a8, a9, a10, a11, a12, a13, a14,  \
                                         a15, a16, a17)                        \
  void symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8, a9 n9,   \
              a10 n10, a11 n11, a12 n12, a13 n13, a14 n14, a15 n15, a16 n16,   \
              a17 n17)                                                         \
  {                                                                            \
    static void (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13,   \
                     a14, a15, a16, a17) FP_ATTRIB = NULL;                     \
    HYBRIS_DLSYSM(name, &f, #symbol);                                          \
    f(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15, n16,   \
      n17);                                                                    \
  }

#define HYBRIS_IMPLEMENT_VOID_FUNCTION18(name, symbol, a1, a2, a3, a4, a5, a6, \
                                         a7, a8, a9, a10, a11, a12, a13, a14,  \
                                         a15, a16, a17, a18)                   \
  void symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8, a9 n9,   \
              a10 n10, a11 n11, a12 n12, a13 n13, a14 n14, a15 n15, a16 n16,   \
              a17 n17, a18 n18)                                                \
  {                                                                            \
    static void (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13,   \
                     a14, a15, a16, a17, a18) FP_ATTRIB = NULL;                \
    HYBRIS_DLSYSM(name, &f, #symbol);                                          \
    f(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15, n16,   \
      n17, n18);                                                               \
  }

#define HYBRIS_IMPLEMENT_VOID_FUNCTION19(name, symbol, a1, a2, a3, a4, a5, a6, \
                                         a7, a8, a9, a10, a11, a12, a13, a14,  \
                                         a15, a16, a17, a18, a19)              \
  void symbol(a1 n1, a2 n2, a3 n3, a4 n4, a5 n5, a6 n6, a7 n7, a8 n8, a9 n9,   \
              a10 n10, a11 n11, a12 n12, a13 n13, a14 n14, a15 n15, a16 n16,   \
              a17 n17, a18 n18, a19 n19)                                       \
  {                                                                            \
    static void (*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13,   \
                     a14, a15, a16, a17, a18, a19) FP_ATTRIB = NULL;           \
    HYBRIS_DLSYSM(name, &f, #symbol);                                          \
    f(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15, n16,   \
      n17, n18, n19);                                                          \
  }

/**
 *         XXX AUTO-GENERATED FILE XXX
 *
 * Do not edit this file directly, but update the templates in
 * utils/generate_wrapper_macros.py and run it again to build
 * an updated version of this header file:
 *
 *    python utils/generate_wrapper_macros.py > \
 *       hybris/include/hybris/common/binding.h
 *
 * If you need macros with more arguments, just customize the
 * MAX_ARGS variable in generate_wrapper_macros.py.
 *
 *         XXX AUTO-GENERATED FILE XXX
 **/

#endif /* HYBRIS_BINDING_H_ */
