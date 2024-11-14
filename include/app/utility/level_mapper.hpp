#include <cstdint>
#include <map>
#include <string>

class LevelMapper {
  public:
    static LevelMapper &get_instance();
    LevelMapper(LevelMapper const &) = delete;
    void operator=(LevelMapper const &) = delete;

    uint8_t get_code(const std::string &name) const;
    const std::string &get_name(uint8_t code) const;

  private:
    LevelMapper();

    std::map<std::string, uint8_t> level_map;
    std::map<uint8_t, std::string> level_map_inverse;
};
