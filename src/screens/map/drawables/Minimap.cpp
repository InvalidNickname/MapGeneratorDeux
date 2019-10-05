#include "Minimap.h"

void Minimap::render(RenderWindow *window) {
    window->draw(minimapBackground);
    window->draw(minimap);
}

Minimap::Minimap(float windowWidth, float windowHeight, DrawableGrid *drawableGrid) {
    minimapBackground.setTexture(*AssetLoader::get().getTexture("minimap_background"));
    minimapBackground.setScale(300.f / minimapBackground.getTexture()->getSize().x,
                               190.f / minimapBackground.getTexture()->getSize().y);
    minimapBackground.setPosition(windowWidth - 300, windowHeight - 190);

    float height = 0.25f * TILE_HEIGHT * (3 * MAP_HEIGHT);
    float width = TILE_WIDTH * (0.5f + MAP_WIDTH);
    float camX = width / 2;
    float camY = 0.125f * TILE_HEIGHT * (3 * MAP_HEIGHT);

    View view;
    view.setCenter(camX, camY);
    view.setSize(width, height);

    minimapTexture = new RenderTexture();
    minimapTexture->create((unsigned) windowWidth, (unsigned) windowHeight);
    minimapTexture->setView(view);

    drawableGrid->render(minimapTexture, MapMode::MINIMAP, 0, MAP_WIDTH);
    minimapTexture->display();

    minimap.setTexture(minimapTexture->getTexture());
    minimap.setScale(300.f / minimapTexture->getTexture().getSize().x,
                     190.f / minimapTexture->getTexture().getSize().y);
    minimap.setPosition(windowWidth - 300, windowHeight - 190);
}