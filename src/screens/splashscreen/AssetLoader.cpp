#include "AssetLoader.h"

AssetLoader &AssetLoader::get() {
    static AssetLoader s;
    return s;
}

AssetLoader::AssetLoader() {
    auto *t1 = new Texture();
    t1->loadFromFile("graphics/interface/map_mode_default.png", IntRect(0, 0, 41, 31));
    t1->setSmooth(true);
    textureMap.insert(pair("map_mode_default_0", t1));
    auto *t2 = new Texture();
    t2->loadFromFile("graphics/interface/map_mode_default.png", IntRect(0, 0, 41, 31));
    t2->setSmooth(true);
    textureMap.insert(pair("map_mode_default_1", t2));
    auto *t3 = new Texture();
    t3->loadFromFile("graphics/interface/map_mode_biomes.png", IntRect(0, 0, 41, 31));
    t3->setSmooth(true);
    textureMap.insert(pair("map_mode_biomes_0", t3));
    auto *t4 = new Texture();
    t4->loadFromFile("graphics/interface/map_mode_biomes.png", IntRect(0, 0, 41, 31));
    t4->setSmooth(true);
    textureMap.insert(pair("map_mode_biomes_1", t4));
}

Texture *AssetLoader::getTexture(const string &name) {
    return textureMap.at(name);
}
