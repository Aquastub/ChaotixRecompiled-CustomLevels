#include "campaigns.h"
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>

namespace chaotix::campaigns {
bool load(const std::string& path, std::vector<Campaign>& out) {
    out.clear();
    std::ifstream in(path);
    if (!in) return false;
    Campaign* current = nullptr;
    std::string line;
    while (std::getline(in, line)) {
        std::istringstream row(line);
        std::string kind;
        row >> kind;
        if (kind == "CAMPAIGN") {
            Campaign c;
            row >> std::quoted(c.name);
            if (c.name.empty()) c.name = "My Campaign";
            out.push_back(std::move(c));
            current = &out.back();
        } else if (kind == "LEVEL" && current) {
            unsigned place=0, level=0, time=0, player=0, partner=0, two=0;
            int solo=0;
            if (row >> place >> level >> time >> player >> partner >> two >> solo) {
                stage_select::Request r;
                r.place=uint8_t(place); r.level=uint16_t(level); r.attime=uint16_t(time);
                r.player=uint8_t(player); r.combi=uint16_t(partner); r.two_players=two != 0;
                if (stage_select::valid(r)) current->levels.push_back(r);
            }
        }
    }
    return true;
}
bool save(const std::string& path, const std::vector<Campaign>& campaigns) {
    std::error_code ec;
    const auto parent = std::filesystem::u8path(path).parent_path();
    if (!parent.empty()) std::filesystem::create_directories(parent, ec);
    std::ofstream out(path, std::ios::trunc);
    if (!out) return false;
    for (const auto& c : campaigns) {
        out << "CAMPAIGN " << std::quoted(c.name) << '\n';
        for (const auto& r : c.levels)
            out << "LEVEL " << unsigned(r.place) << ' ' << r.level << ' ' << unsigned(r.attime)
                << ' ' << unsigned(r.player) << ' ' << unsigned(r.combi) << ' '
                << (r.two_players ? 1 : 0) << " 0\n";
    }
    return bool(out);
}
}
