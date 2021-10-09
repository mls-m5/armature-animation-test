#pragma once

#include "armature.h"
#include "matmath/vec2.h"
#include "sdlpp/render.hpp"

void drawArmature(sdl::RendererView renderer,
                  const Bone &root,
                  Vec2f pos,
                  float angle = 0,
                  float scale = 100);
