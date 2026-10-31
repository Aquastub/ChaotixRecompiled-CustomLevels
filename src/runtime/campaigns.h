// User-authored campaigns: ordered playlists of stages supported by the
// original game. Custom geometry is a separate engine feature; this format
// deliberately does not pretend that a playlist is a new ROM level.
#pragma once
#include "runtime/stage_select.h"
#include <string>
#include <vector>

namespace chaotix::campaigns {
struct Campaign {
    std::string name = "My Campaign";
    std::vector<stage_select::Request> levels;
};
bool load(const std::string& path, std::vector<Campaign>& out);
bool save(const std::string& path, const std::vector<Campaign>& campaigns);
}
