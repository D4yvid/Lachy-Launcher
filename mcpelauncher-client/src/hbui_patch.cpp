#include "hbui_patch.h"

#include <hybris/dlfcn.h>
#include <log.h>
#include <mcpelauncher/patch_utils.h>

void HbuiPatch::install(void* handle)
{
  void* ptr = hybris_dlsym(handle, "_ZN6cohtml17VerifiyLicenseKeyEPKc");
  if (ptr) PatchUtils::patchCallInstruction(ptr, (void*)returnTrue, true);
  ptr = hybris_dlsym(
      handle, "_ZN4hbui10LogHandler8WriteLogEN6cohtml7Logging8SeverityEPKcj");
  if (ptr) PatchUtils::patchCallInstruction(ptr, (void*)writeLog, true);
}

void HbuiPatch::writeLog(void* th, int level, const char* what,
                         unsigned int length)
{
  Log::log((LogLevel)level, "Cohtml", "%.*s", length, what);
}