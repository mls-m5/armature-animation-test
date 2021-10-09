#pragma once

#include "matmath/pi.h"
#include <string>
#include <vector>

struct Bone {
    std::string name;
    float length = 1;
    float angle = 0;
    std::vector<Bone> children;

    Bone *getBone(std::string_view name) {
        if (this->name == name) {
            return this;
        }

        for (auto &child : children) {
            if (auto bone = child.getBone(name)) {
                return bone;
            }
        }

        return nullptr;
    }
};

inline Bone createBody() {
    auto underarmL = Bone{"underarm l", .5, .2};
    auto underarmR = Bone{"underarm r", .5, .1};

    auto upperArmL = Bone{"upperarm l", .5, .1 + pi, {std::move(underarmL)}};
    auto upperArmR = Bone{"upperarm r", .5, .2 + pi, {std::move(underarmR)}};

    auto headNoseIsh = Bone{"nose", .1, -pi / 2};
    auto head = Bone{"head", .3, 0, {std::move(headNoseIsh)}};

    auto torso =
        Bone{"torso",
             .7,
             pi,
             {std::move(upperArmL), std::move(upperArmR), std::move(head)}};

    auto footl = Bone{"foot l", .1, pi / 2};
    auto footr = Bone{"foot r", .1, pi / 2};

    auto shinl = Bone{"shin l", .6, -.1, {std::move(footl)}};
    auto shinr = Bone{"shin r", .6, -.2, {std::move(footr)}};

    auto thighl = Bone{"thigh l", .7, .1, {std::move(shinl)}};
    auto thighr = Bone{"thigh r", .7, .2, {std::move(shinr)}};

    auto hip = Bone{"hip",
                    0.,
                    0.,
                    {std::move(torso), std::move(thighl), std::move(thighr)}};

    return hip;
}
