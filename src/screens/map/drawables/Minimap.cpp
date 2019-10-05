#include "Minimap.h"

void Minimap::render(RenderWindow *window) {
    window->draw(minimapBackground);
    window->draw(minimap);
}

Minimap::Minimap(float windowWidth, float windowHeight, float minZoom, DrawableGrid *drawableGrid) {
    minimapBackground.setTexture(*AssetLoader::get().getTexture("minimap_background"));
    minimapBackground.setScale(300.f / minimapBackground.getTexture()->getSize().x,
                               190.f / minimapBackground.getTexture()->getSize().y);
    minimapBackground.setPosition(windowWidth - 300, windowHeight - 190);
    // отдельный view для захвата текстуры миникарты
    View minimapView;
    minimapView.setSize(windowWidth / 2, windowHeight / 2);
    minimapView.setCenter(TILE_WIDTH * (0.5f + MAP_WIDTH) / 2, 0.125f * TILE_HEIGHT * (3 * MAP_HEIGHT - 1));
    minimapView.zoom(minZoom);
    minimapTexture = new RenderTexture();
    minimapTexture->create((unsigned) windowWidth, (unsigned) windowHeight);
    minimapTexture->setView(minimapView);
    drawableGrid->render(minimapTexture, MapMode::MINIMAP, 0, 0, MAP_WIDTH, MAP_HEIGHT);
    minimap.setTexture(minimapTexture->getTexture());
    minimap.setScale(300.f / minimapTexture->getTexture().getSize().x,
                     190.f / minimapTexture->getTexture().getSize().y);
    minimap.setPosition(windowWidth - 300, windowHeight - 190);
}