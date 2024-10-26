#include "render_engine.h"

#include <mutex>

#include "fml/native_library.h"
#include "impeller.hpp"

namespace fiddle {

ProcTable gGlobalProcTable;

RenderEngine::RenderEngine() {
  static std::once_flag sOnceFlag;
  std::call_once(sOnceFlag, []() {
    gGlobalProcTable.Initialize([](const char* proc_name) -> void* {
      return const_cast<void*>(reinterpret_cast<const void*>(
          fml::NativeLibrary::CreateForCurrentProcess()->ResolveSymbol(
              proc_name)));
    });
  });
}

RenderEngine::~RenderEngine() = default;

RenderEngine& RenderEngine::Get() {
  static RenderEngine engine;
  return engine;
}

}  // namespace fiddle
