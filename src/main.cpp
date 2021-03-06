

#include "armature.h"
#include "drawarmature.h"
#include "sdlpp/render.hpp"
#include "sdlpp/window.hpp"
#include <chrono>
#include <cmath>
#include <experimental/source_location>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

void expectTrue(bool condition,
                std::string errorString,
                std::experimental::source_location location =
                    std::experimental::source_location::current()) {
    if (!condition) {
        std::cerr << location.function_name() << "(...) in "
                  << location.file_name() << ": " << location.line() << ": "
                  << errorString << "\n";
        exit(1);
    }
}

int main(int argc, char **argv) {
    auto window = sdl::Window{"Hello there",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              800,
                              600,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE};

    expectTrue(window, "could not create window");

    auto renderer = sdl::Renderer{window, -1, SDL_RENDERER_ACCELERATED};

    expectTrue(renderer, "could not create renderer");

    auto body = createBody();
    auto thigh = body.getBone("thigh l");
    auto shin = body.getBone("shin l");

    auto now = std::chrono::high_resolution_clock::now();
    auto passedTime = std::chrono::duration<float>{};

    for (size_t i = 0; i < 1000; ++i) {
        auto newNow = std::chrono::high_resolution_clock::now();
        passedTime += (newNow - now);
        now = newNow;

        renderer.drawColor({100, 0, 0});
        renderer.fillRect();

        thigh->angle = sin(passedTime.count() * 2.);
        shin->angle = -cos(passedTime.count() * 2.) - 1.;

        //        renderer.drawColor({0, 0, 0});
        //        renderer.drawLine(0, 0, 200, 200);

        drawArmature(renderer, body, Vec2f{200, 200});

        renderer.present();

        std::this_thread::sleep_for(5ms);
    }
}
