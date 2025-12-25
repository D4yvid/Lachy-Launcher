# Script to patch libfmod.so to remove executable stack requirement
# This is needed for modern Linux kernels with security restrictions

find_package(Python3 COMPONENTS Interpreter)

if(Python3_FOUND AND EXISTS "${NATIVES_PATH_DIR}/libs/native/libfmod.so.9.16")
    message(STATUS "Checking if libfmod needs patching...")
    
    execute_process(
        COMMAND ${Python3_EXECUTABLE} -c "
import struct
with open('${NATIVES_PATH_DIR}/libs/native/libfmod.so.9.16', 'rb') as f:
    data = f.read()
e_phoff = struct.unpack('<I', data[28:32])[0]
e_phentsize = struct.unpack('<H', data[42:44])[0]
e_phnum = struct.unpack('<H', data[44:46])[0]
for i in range(e_phnum):
    offset = e_phoff + i * e_phentsize
    p_type = struct.unpack('<I', data[offset:offset+4])[0]
    if p_type == 0x6474e551:
        p_flags = struct.unpack('<I', data[offset+24:offset+28])[0]
        exit(0 if (p_flags & 1) == 0 else 1)
exit(0)
"
        RESULT_VARIABLE FMOD_NEEDS_PATCH
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )
    
    if(FMOD_NEEDS_PATCH)
        message(STATUS "Patching libfmod.so to remove executable stack requirement...")
        execute_process(
            COMMAND ${Python3_EXECUTABLE} -c "
import struct
with open('${NATIVES_PATH_DIR}/libs/native/libfmod.so.9.16', 'rb') as f:
    data = bytearray(f.read())
e_phoff = struct.unpack('<I', data[28:32])[0]
e_phentsize = struct.unpack('<H', data[42:44])[0]
e_phnum = struct.unpack('<H', data[44:46])[0]
for i in range(e_phnum):
    offset = e_phoff + i * e_phentsize
    p_type = struct.unpack('<I', data[offset:offset+4])[0]
    if p_type == 0x6474e551:
        p_flags_offset = offset + 24
        p_flags = struct.unpack('<I', data[p_flags_offset:p_flags_offset+4])[0]
        data[p_flags_offset:p_flags_offset+4] = struct.pack('<I', p_flags & ~1)
        break
with open('${NATIVES_PATH_DIR}/libs/native/libfmod.so.9.16', 'wb') as f:
    f.write(data)
"
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        )
        message(STATUS "libfmod.so patched successfully")
    else()
        message(STATUS "libfmod.so already patched or doesn't need patching")
    endif()
endif()
