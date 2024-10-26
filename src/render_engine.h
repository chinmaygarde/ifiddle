#pragma once

#include "fml/macros.h"

namespace fiddle {

class RenderEngine {
 public:
  static RenderEngine& Get();

  ~RenderEngine();

 private:
  RenderEngine();

  FML_DISALLOW_COPY_AND_ASSIGN(RenderEngine);
};

}  // namespace fiddle
