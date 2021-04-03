#pragma once

#include "Configuration.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

enum class side { LEFT, RIGHT, NONE };
void updateBrnaches(int seed);
void setSpriteAttributes(sf::Sprite& sprite, sf::Texture& texture, const std::string& path, const int& x, const int& y);
void setOriginToCentre(sf::Text& text);
void setFontAttributes(sf::Text& text, sf::Font& font, const std::string& str, const sf::Color& color, const int& size, const int& x, const int& y, const bool& originFlag);
void setSoundAttributes(sf::SoundBuffer& buffer, sf::Sound& sound, const std::string& path);
void setRectangleShapeAttributes(sf::RectangleShape& shape, const sf::Vector2f& v, const sf::Color& color, const int& x, const int& y);
int yesOrNo();
void randomizeTrees(sf::Sprite treeSprite[Configs::RANDOM_TREE_COUNT], int seed);
