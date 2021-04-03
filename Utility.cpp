#include "Utility.hpp"

sf::Sprite spriteBranches[Configs::NUM_OF_BRANCHES];
side branchPos[Configs::NUM_OF_BRANCHES];
float tree_width = 0;

void updateBrnaches(int seed) {
    for (int i = Configs::NUM_OF_BRANCHES - 1; i > 0; i--) {
        branchPos[i] = branchPos[i - 1];
    }
    srand(time(0) + seed);
    switch (rand() % 5) {
    case 0:
        branchPos[0] = side::LEFT;
        break;
    case 1:
        branchPos[0] = side::RIGHT;
        break;
    case 2:
        branchPos[0] = side::NONE;
        break;
    }
}

void setSpriteAttributes(sf::Sprite& sprite, sf::Texture& texture, const std::string& path, const int& x, const int& y) {
    texture.loadFromFile(path);
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}


void setOriginToCentre(sf::Text& text) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
}


void setFontAttributes(sf::Text& text, sf::Font& font, const std::string& str, const sf::Color& color, const int& size, const int& x, const int& y, const bool& originFlag) {
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(x, y);
    if (originFlag) {
        setOriginToCentre(text);
    }
}

void setSoundAttributes(sf::SoundBuffer& buffer, sf::Sound& sound, const std::string& path) {
    buffer.loadFromFile(path);
    sound.setBuffer(buffer);
}

void setRectangleShapeAttributes(sf::RectangleShape& shape, const sf::Vector2f& v, const sf::Color& color, const int& x, const int& y) {
    shape.setSize(v);
    shape.setFillColor(color);
    shape.setPosition(x, y);
}

int yesOrNo() {
    return rand() % 2;
}

void randomizeTrees(sf::Sprite treeSprite[Configs::RANDOM_TREE_COUNT], int seed) {
    srand((int)(time(0)) + seed);
    int x = rand() % (Configs::WIDTH / Configs::RANDOM_TREE_COUNT) / 2;
    int y = rand() % Configs::RANDOM_TREE_OFFSET;
    int x_offset = 0;
    int y_offset = 0;
    for (int i = 0; i < Configs::RANDOM_TREE_COUNT; i++) {
        treeSprite[i].setPosition(x + x_offset, -(y + y_offset));
        int temp = rand() % (static_cast<int>(tree_width) + static_cast<int>(tree_width) / 2) + static_cast<int>(tree_width);
        if (temp + x_offset + x >= Coordinates::TREE_X && temp + x_offset + x <= Coordinates::TREE_X + tree_width) {
            x_offset += temp + (Coordinates::TREE_X - (temp + x_offset + x));
        }
        else if (temp + x_offset + x + tree_width >= Coordinates::TREE_X && temp + x_offset + x + tree_width <= Coordinates::TREE_X + tree_width) {
            x_offset += temp - std::abs(tree_width - (Coordinates::TREE_X - (temp + x_offset + x))) - (rand() % Configs::RANDOM_TREE_OFFSET + (Configs::RANDOM_TREE_OFFSET / 2));
        }
        else
            x_offset += temp;
        y_offset += (Configs::RANDOM_TREE_OFFSET / 10) * ((yesOrNo()) ? -1 : 1);
    }
}
