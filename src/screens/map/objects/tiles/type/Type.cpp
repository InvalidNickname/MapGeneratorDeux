#include "Type.h"

Type::Type(string t, string at, vector<string> n, Color bic, vector<Color> bac, bool asl)
        : type(std::move(t)), archtype(std::move(at)), name(std::move(n)), biomeColor(bic), baseColor(std::move(bac)),
          aboveSeaLevel(asl) {}

string Type::getName(Level level) {
    switch (level) {
        case NO:
            return name.at(3);
        case SMALL:
            return name.at(2);
        case MEDIUM:
            return name.at(1);
        case HIGH:
            return name.at(0);
    }
}

Color Type::getBiomeColor() {
    return biomeColor;
}

Color Type::getBaseColor(Level level) {
    switch (level) {
        case NO:
            return baseColor.at(3);
        case SMALL:
            return baseColor.at(2);
        case MEDIUM:
            return baseColor.at(1);
        case HIGH:
            return baseColor.at(0);
    }
}

string Type::getArchtype() {
    return archtype;
}

string Type::getTypeName() {
    return type;
}

bool Type::isAboveSeaLevel() {
    return aboveSeaLevel;
}
