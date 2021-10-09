#include "drawarmature.h"
#include "sdlpp/render.hpp"
#include <cmath>
#include <vector>

void drawArmature(sdl::RendererView renderer,
                  const Bone &root,
                  Vec2f pos,
                  float angle,
                  float scale) {

    auto newAngle = angle + root.angle;
    auto length = scale * root.length;
    auto newPos = pos + Vec2f{sin(newAngle) * length, cos(newAngle) * length};

    renderer.drawColor({255, 255, 255});
    renderer.drawLine(pos.x, pos.y, newPos.x, newPos.y);

    for (auto &child : root.children) {
        drawArmature(renderer, child, newPos, newAngle);
    }
}
