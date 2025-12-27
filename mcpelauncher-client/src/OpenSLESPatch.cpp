#include "OpenSLESPatch.h"

#include <SLES/OpenSLES.h>
#include <hybris/hook.h>

namespace {

// Shared stub engine interface - all methods return success (0)
static SLEngineItf_ stubEngine = {
  .CreateLEDDevice = [](SLEngineItf, SLObjectItf*, SLuint32, SLuint32,
                        const SLInterfaceID*, const SLboolean*) -> SLresult { return 0; },
  .CreateVibraDevice = [](SLEngineItf, SLObjectItf*, SLuint32, SLuint32,
                          const SLInterfaceID*, const SLboolean*) -> SLresult { return 0; },
  .CreateAudioPlayer = [](SLEngineItf, SLObjectItf*, SLDataSource*, SLDataSink*,
                          SLuint32, const SLInterfaceID*, const SLboolean*) -> SLresult { return 0; },
  .CreateAudioRecorder = [](SLEngineItf, SLObjectItf*, SLDataSource*, SLDataSink*,
                            SLuint32, const SLInterfaceID*, const SLboolean*) -> SLresult { return 0; },
  .CreateMidiPlayer = [](SLEngineItf, SLObjectItf*, SLDataSource*, SLDataSource*,
                         SLDataSink*, SLDataSink*, SLDataSink*, SLuint32,
                         const SLInterfaceID*, const SLboolean*) -> SLresult { return 0; },
  .CreateListener = [](SLEngineItf, SLObjectItf*, SLuint32,
                       const SLInterfaceID*, const SLboolean*) -> SLresult { return 0; },
  .Create3DGroup = [](SLEngineItf, SLObjectItf*, SLuint32,
                      const SLInterfaceID*, const SLboolean*) -> SLresult { return 0; },
  .CreateOutputMix = [](SLEngineItf, SLObjectItf*, SLuint32,
                        const SLInterfaceID*, const SLboolean*) -> SLresult { return 0; },
  .CreateMetadataExtractor = [](SLEngineItf, SLObjectItf*, SLDataSource*, SLuint32,
                                const SLInterfaceID*, const SLboolean*) -> SLresult { return 0; },
  .CreateExtensionObject = [](SLEngineItf, SLObjectItf*, void*, SLuint32, SLuint32,
                              const SLInterfaceID*, const SLboolean*) -> SLresult { return 0; },
  .QueryNumSupportedInterfaces = [](SLEngineItf, SLuint32, SLuint32*) -> SLresult { return 0; },
  .QuerySupportedInterfaces = [](SLEngineItf, SLuint32, SLuint32, SLInterfaceID*) -> SLresult { return 0; },
  .QueryNumSupportedExtensions = [](SLEngineItf, SLuint32*) -> SLresult { return 0; },
  .QuerySupportedExtension = [](SLEngineItf, SLuint32, SLchar*, SLint16*) -> SLresult { return 0; },
  .IsExtensionSupported = [](SLEngineItf, const SLchar*, SLboolean*) -> SLresult { return 0; }
};

// Creates a stub SLObject with the given GetInterface handler
SLObjectItf createStubObject(SLresult (*getInterface)(SLObjectItf, const SLInterfaceID, void*))
{
  static SLObjectItf_* obj = new SLObjectItf_{
    .Realize = [](SLObjectItf, SLboolean) -> SLresult { return 0; },
    .Resume = [](SLObjectItf, SLboolean) -> SLresult { return 0; },
    .GetState = [](SLObjectItf, SLuint32*) -> SLresult { return 0; },
    .GetInterface = getInterface,
    .RegisterCallback = [](SLObjectItf, slObjectCallback, void*) -> SLresult { return 0; },
    .AbortAsyncOperation = [](SLObjectItf) {},
    .Destroy = [](SLObjectItf) {},
    .SetPriority = [](SLObjectItf, SLint32, SLboolean) -> SLresult { return 0; },
    .GetPriority = [](SLObjectItf, SLint32*, SLboolean*) -> SLresult { return 0; },
    .SetLossOfControlInterfaces = [](SLObjectItf, SLint16, SLInterfaceID*, SLboolean) -> SLresult { return 0; }
  };
  return new SLObjectItf_*(obj);
}

// Simple GetInterface that returns the stub engine
SLresult simpleGetInterface(SLObjectItf, const SLInterfaceID, void* pInterface)
{
  *((SLEngineItf_***)pInterface) = new SLEngineItf_*(&stubEngine);
  return 0;
}

// Interface IDs
static SLInterfaceID_ SL_IID_ENGINE_IMPL      = { 0, 0, 0, 0, { 1, 2, 3, 4, 5, 6 } };
static SLInterfaceID_ SL_IID_BUFFERQUEUE_IMPL = { 0, 0, 0, 0, { 2, 3, 4, 5, 6, 7 } };
static SLInterfaceID_ SL_IID_VOLUME_IMPL      = { 0, 0, 0, 0, { 1, 2, 3, 4, 5, 8 } };
static SLInterfaceID_ SL_IID_PLAY_IMPL        = { 0, 0, 0, 0, { 1, 2, 3, 4, 5, 9 } };

} // anonymous namespace

void OpenSLESPatch::install()
{
  // Hook interface IDs
  hybris_hook("SL_IID_ENGINE", (void*)&SL_IID_ENGINE_IMPL);
  hybris_hook("SL_IID_BUFFERQUEUE", (void*)&SL_IID_BUFFERQUEUE_IMPL);
  hybris_hook("SL_IID_VOLUME", (void*)&SL_IID_VOLUME_IMPL);
  hybris_hook("SL_IID_PLAY", (void*)&SL_IID_PLAY_IMPL);

  // Hook slCreateEngine to return a stub engine object
  hybris_hook("slCreateEngine",
    (void*)+[](SLObjectItf* pEngine, SLuint32, const SLEngineOption*,
               SLuint32, const SLInterfaceID*, const SLboolean*) -> SLresult
    {
      // Create the main engine object with a custom GetInterface
      // that handles CreateAudioPlayer and CreateOutputMix
      static SLObjectItf_* engineObj = new SLObjectItf_{
        .Realize = [](SLObjectItf, SLboolean) -> SLresult { return 0; },
        .Resume = [](SLObjectItf, SLboolean) -> SLresult { return 0; },
        .GetState = [](SLObjectItf, SLuint32*) -> SLresult { return 0; },
        .GetInterface = [](SLObjectItf, const SLInterfaceID, void* pInterface) -> SLresult
        {
          // Create an engine interface with working CreateAudioPlayer/CreateOutputMix
          static SLEngineItf_ mainEngine = {
            .CreateLEDDevice = stubEngine.CreateLEDDevice,
            .CreateVibraDevice = stubEngine.CreateVibraDevice,
            .CreateAudioPlayer = [](SLEngineItf, SLObjectItf* pPlayer, SLDataSource*,
                                    SLDataSink*, SLuint32, const SLInterfaceID*,
                                    const SLboolean*) -> SLresult
            {
              *pPlayer = createStubObject(simpleGetInterface);
              return 0;
            },
            .CreateAudioRecorder = stubEngine.CreateAudioRecorder,
            .CreateMidiPlayer = stubEngine.CreateMidiPlayer,
            .CreateListener = stubEngine.CreateListener,
            .Create3DGroup = stubEngine.Create3DGroup,
            .CreateOutputMix = [](SLEngineItf, SLObjectItf* pMix, SLuint32,
                                  const SLInterfaceID*, const SLboolean*) -> SLresult
            {
              *pMix = createStubObject(simpleGetInterface);
              return 0;
            },
            .CreateMetadataExtractor = stubEngine.CreateMetadataExtractor,
            .CreateExtensionObject = stubEngine.CreateExtensionObject,
            .QueryNumSupportedInterfaces = stubEngine.QueryNumSupportedInterfaces,
            .QuerySupportedInterfaces = stubEngine.QuerySupportedInterfaces,
            .QueryNumSupportedExtensions = stubEngine.QueryNumSupportedExtensions,
            .QuerySupportedExtension = stubEngine.QuerySupportedExtension,
            .IsExtensionSupported = stubEngine.IsExtensionSupported
          };
          *((SLEngineItf_***)pInterface) = new SLEngineItf_*(&mainEngine);
          return 0;
        },
        .RegisterCallback = [](SLObjectItf, slObjectCallback, void*) -> SLresult { return 0; },
        .AbortAsyncOperation = [](SLObjectItf) {},
        .Destroy = [](SLObjectItf) {},
        .SetPriority = [](SLObjectItf, SLint32, SLboolean) -> SLresult { return 0; },
        .GetPriority = [](SLObjectItf, SLint32*, SLboolean*) -> SLresult { return 0; },
        .SetLossOfControlInterfaces = [](SLObjectItf, SLint16, SLInterfaceID*, SLboolean) -> SLresult { return 0; }
      };
      
      *pEngine = new SLObjectItf_*(engineObj);
      return 0;
    });
}