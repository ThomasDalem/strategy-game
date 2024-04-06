#ifndef INFOS_HPP
#define INFOS_HPP

#include <string>

// Singleton class
class Infos {
private:
    static Infos _infosInstance;
    Infos();

public:
    static Infos &getInstance() noexcept;
    const std::string &getExePath() const;

private:
    std::string _exePath;
};

#endif // INFOS_HPP