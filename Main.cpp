#include <iostream>
#include <sstream>
#include <algorithm>
#include "Utility.hpp"

extern float tree_width;
extern sf::Sprite spriteBranches[Configs::NUM_OF_BRANCHES];
extern side branchPos[Configs::NUM_OF_BRANCHES];

void gamelogic() {
    srand((int)(time(0)));

    sf::VideoMode vm(Configs::WIDTH, Configs::HEIGHT);
    sf::RenderWindow window(vm, "TimBer!", sf::Style::Default);

    sf::Clock clock;
    int score = 0;
    sf::Text msgText, scoreText, fpsText;
    sf::Font font;

    font.loadFromFile(Paths::FONT_PATH);
    setFontAttributes(msgText, font, Configs::START_MSG, sf::Color::White, Configs::START_MSG_SIZE, Coordinates::MSG_TEXT_X, Coordinates::MSG_TEXT_Y, true);
    setFontAttributes(scoreText, font, Configs::SCORE_MSG, sf::Color::White, Configs::SCORE_MSG_SIZE, Coordinates::SCORE_TEXT_X, Coordinates::SCORE_TEXT_Y, false);
    setFontAttributes(fpsText, font, Configs::FPS_TEXT, sf::Color::White, Configs::FPS_MSG_SIZE, Coordinates::FPS_TEXT_X, Coordinates::FPS_TEXT_Y, false);

    sf::SoundBuffer bufferChop, bufferDeath, bufferOot;
    sf::Sound soundChop, soundDeath, soundOot;
    setSoundAttributes(bufferChop, soundChop, Paths::CHOP_AUDIO_PATH);
    setSoundAttributes(bufferDeath, soundDeath, Paths::DEATH_AUDIO_PATH);
    setSoundAttributes(bufferOot, soundOot, Paths::OUT_OF_TIME_AUDIO_PATH);

    sf::RectangleShape timeBar, rect1, rect2;
    float timeBarStartWidth = Configs::TIMEBAR_START_WIDTH;
    float timeBarHeight = Configs::TIMEBAR_HEIGTH;

    setRectangleShapeAttributes(timeBar, sf::Vector2f(timeBarStartWidth, timeBarHeight), sf::Color::Red, (Configs::WIDTH / 2) - timeBarStartWidth / 2, Coordinates::TIMEBAR_Y);
    setRectangleShapeAttributes(rect1, sf::Vector2f(Configs::HUD_SCORE_BOX_WIDTH, Configs::HUD_SCORE_BOX_HEIGHT), sf::Color(0, 0, 0, 150), 0, Coordinates::SCORE_TEXT_Y);
    setRectangleShapeAttributes(rect2, sf::Vector2f(Configs::HUD_FPS_BOX_WIDTH, Configs::HUD_FPS_BOX_HEIGHT), sf::Color(0, 0, 0, 150), Coordinates::FPS_TEXT_X - 20, Coordinates::FPS_TEXT_Y);

    sf::Time gameTotalTime;
    float timeRemaining = Configs::TIME_REMAINING;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    sf::Texture textureBackground, textureTree, textureBee, textureCloud, textureBranch, texturePlayer, textureRip, textureAxe, textureLog;
    sf::Sprite spriteBackground, spriteMainTree, spriteBee, spritePlayer, spriteRip, spriteAxe, spriteLog;
    sf::Sprite spriteClouds[Configs::CLOUDS_NUM];
    sf::Sprite spriteRandomTrees[Configs::RANDOM_TREE_COUNT];
    bool cloudActive[Configs::CLOUDS_NUM];
    float cloudSpeed[Configs::CLOUDS_NUM];

    side playerSide = side::LEFT;
    bool logActive = false;
    float logSpeedX = Configs::LOG_SPEED_X;
    float logSpeedY = Configs::LOG_SPEED_Y;
    bool beeActive = false;
    float beeSpeed = 0.0f;
    bool paused = true;
    bool acceptInput = false;

    setSpriteAttributes(spriteBackground, textureBackground, Paths::BACKGROUND_PATH, Coordinates::BACKGROUND_X, Coordinates::BACKGROUND_Y);
    setSpriteAttributes(spriteMainTree, textureTree, Paths::TREE_PATH, Coordinates::TREE_X, Coordinates::TREE_Y);
    setSpriteAttributes(spriteBee, textureBee, Paths::BEE_PATH, Coordinates::POS_OUTSIDE_VIEW, Coordinates::BEE_Y);
    setSpriteAttributes(spritePlayer, texturePlayer, Paths::PLAYER_PATH, Coordinates::PLAYER_X_LEFT, Coordinates::PLAYER_Y);
    setSpriteAttributes(spriteRip, textureRip, Paths::RIP_PATH, Coordinates::POS_OUTSIDE_VIEW, Coordinates::RIP_Y);
    setSpriteAttributes(spriteAxe, textureAxe, Paths::AXE_PATH, Coordinates::AXE_X, Coordinates::AXE_Y);
    setSpriteAttributes(spriteLog, textureLog, Paths::LOG_PATH, Coordinates::LOG_X, Coordinates::LOG_Y);


    tree_width = spriteMainTree.getLocalBounds().width;

    int pos = 0;
    int score_update_limiter = 0;
    for (int i = 0; i < Configs::CLOUDS_NUM; i++) {
        setSpriteAttributes(spriteClouds[i], textureCloud, Paths::CLOUD_PATH, Coordinates::CLOUD_X, Coordinates::CLOUD_Y + pos);
        cloudActive[i] = false;
        cloudSpeed[i] = 0.0f;
        pos += 250;
    }
    for (int i = 0; i < Configs::NUM_OF_BRANCHES; i++) {
        setSpriteAttributes(spriteBranches[i], textureBranch, Paths::BRANCH_PATH, -Coordinates::POS_OUTSIDE_VIEW, Coordinates::POS_OUTSIDE_VIEW);
        spriteBranches[i].setOrigin(Configs::BRANCH_ORIGIN_X, Configs::BRANCH_ORIGIN_Y);
    }
    for (int i = 0; i < Configs::RANDOM_TREE_COUNT; i++) {
        setSpriteAttributes(spriteRandomTrees[i], textureTree, Paths::TREE_PATH, Coordinates::TREE_X, Coordinates::TREE_Y);
    }

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyReleased && !paused) {
                acceptInput = true;
                spriteAxe.setPosition(Coordinates::POS_OUTSIDE_VIEW, spriteAxe.getPosition().y);
            }
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            randomizeTrees(spriteRandomTrees, score);
            paused = false;
            timeRemaining = 5;
            score = 0;
            for (int i = Configs::NUM_OF_BRANCHES - 1; i > 0; i--) {
                branchPos[i] = side::NONE;
            }
            spriteRip.setPosition(Coordinates::RIP_X, Coordinates::POS_OUTSIDE_VIEW);
            spritePlayer.setPosition(Coordinates::PLAYER_X_LEFT, Coordinates::PLAYER_Y);
            acceptInput = true;
        }

        if (acceptInput) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                playerSide = side::RIGHT;
                score++;
                timeRemaining += (2 / score) + Configs::REWARD;
                spriteAxe.setPosition(Configs::AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
                spritePlayer.setPosition(Coordinates::PLAYER_X_RIGHT, Coordinates::PLAYER_Y);
                updateBrnaches(score);
                spriteLog.setPosition(Coordinates::LOG_X, Coordinates::LOG_Y);
                logSpeedX = -5000;
                logActive = true;
                acceptInput = false;
                soundChop.play();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                playerSide = side::LEFT;
                score++;
                timeRemaining += (2 / score) + Configs::REWARD;
                spriteAxe.setPosition(Configs::AXE_POSITION_LEFT, spriteAxe.getPosition().y);
                spritePlayer.setPosition(Coordinates::PLAYER_X_LEFT, Coordinates::PLAYER_Y);
                updateBrnaches(score);
                spriteLog.setPosition(Coordinates::LOG_X, Coordinates::LOG_Y);
                logSpeedX = 5000;
                logActive = true;
                acceptInput = false;
                soundChop.play();
            }
        }


        if (!paused) {
            score_update_limiter++;
            sf::Time dt = clock.restart();

            timeRemaining -= dt.asSeconds();
            timeBar.setSize(sf::Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.0f) {
                paused = true;
                msgText.setString(Configs::TIME_OVER_MSG);
                sf::FloatRect msgtextRect = msgText.getLocalBounds();
                msgText.setOrigin(msgtextRect.left + msgtextRect.width / 2.0f, msgtextRect.top + msgtextRect.height / 2.0f);
                msgText.setPosition(Configs::WIDTH / 2.0f, Configs::HEIGHT / 2.0f);
                soundOot.play();
            }

            for (int i = 0; i < Configs::CLOUDS_NUM; i++) {
                auto posClouds = spriteClouds[i].getPosition();
                if (!cloudActive[i]) {
                    spriteClouds[i].setPosition(Coordinates::POS_OUTSIDE_VIEW, posClouds.y);
                    cloudSpeed[i] = rand() % Configs::CLOUD_SPEED_OFFSET + Configs::CLOUD_SPEED_OFFSET;
                    cloudActive[i] = true;
                }
                else {
                    if (posClouds.x < Configs::WIDTH) {
                        spriteClouds[i].setPosition(posClouds.x + (cloudSpeed[i] * dt.asSeconds()), posClouds.y);
                    }
                    else {
                        cloudActive[i] = false;
                    }
                }
            }
            if (!beeActive) {
                beeSpeed = rand() % Configs::BEE_SPEED_OFFSET + Configs::BEE_SPEED_OFFSET;
                float beeHeight = rand() % Configs::BEE_HEIGHT_OFFSET + Configs::BEE_HEIGHT_OFFSET;
                spriteBee.setPosition(Coordinates::POS_OUTSIDE_VIEW, beeHeight);
                beeActive = true;
            }
            else {
                auto posBee = spriteBee.getPosition();
                if (posBee.x > -100) {
                    spriteBee.setPosition(posBee.x - (beeSpeed * dt.asSeconds()), posBee.y);
                }
                else {
                    beeActive = false;
                }
            }

            for (int i = 0; i < Configs::NUM_OF_BRANCHES; i++) {
                float height = i * 150;
                if (branchPos[i] == side::LEFT) {
                    spriteBranches[i].setPosition(Coordinates::BRANCH_X_LEFT, height);
                    spriteBranches[i].setRotation(180);
                }
                else if (branchPos[i] == side::RIGHT) {
                    spriteBranches[i].setPosition(Coordinates::BRANCH_X_RIGHT, height);
                    spriteBranches[i].setRotation(0);
                }
                else {
                    spriteBranches[i].setPosition(Coordinates::BRANCH_X_OUTSIDE, height);
                }
            }

            if (logActive) {
                auto logPos = spriteLog.getPosition();
                spriteLog.setPosition(logPos.x + (logSpeedX * dt.asSeconds()), logPos.y + (logSpeedY * dt.asSeconds()));
                logPos = spriteLog.getPosition();
                if (logPos.x < -100 || logPos.y > Coordinates::POS_OUTSIDE_VIEW) {
                    logActive = false;
                    spriteLog.setPosition(Coordinates::LOG_X, Coordinates::LOG_Y);
                }
            }

            if (branchPos[5] == playerSide) {
                paused = true;
                acceptInput = false;
                auto playerPos = spritePlayer.getPosition();
                spriteRip.setPosition(playerPos.x, playerPos.y);
                spritePlayer.setPosition(Coordinates::POS_OUTSIDE_VIEW, Coordinates::PLAYER_Y);
                spriteLog.setPosition(Coordinates::POS_OUTSIDE_VIEW, Coordinates::LOG_Y);
                spriteAxe.setPosition(Coordinates::POS_OUTSIDE_VIEW, Coordinates::AXE_Y);
                msgText.setString(Configs::DEATH_MSG);
                sf::FloatRect msgtextRect = msgText.getLocalBounds();
                msgText.setOrigin(msgtextRect.left + msgtextRect.width / 2.0f, msgtextRect.top + msgtextRect.height / 2.0f);
                msgText.setPosition(Configs::WIDTH / 2.0f, Configs::HEIGHT / 2.0f);
                soundDeath.play();
            }
            if (score_update_limiter == Configs::UPDATE_LIMITER) {
                std::stringstream ssScore;
                ssScore << "Score = " << score;
                scoreText.setString(ssScore.str());

                std::stringstream ssFps;
                float fps = 1 / dt.asSeconds();
                ssFps << "FPS = " << fps;
                fpsText.setString(ssFps.str());

                score_update_limiter = 0;
            }
        }
        window.clear();
        for (int i = 0; i < Configs::CLOUDS_NUM; i++) {
            window.draw(spriteClouds[i]);
        }


        window.draw(spriteBackground);
        window.draw(spriteMainTree);
        for (int i = 0; i < Configs::RANDOM_TREE_COUNT; i++) {
            window.draw(spriteRandomTrees[i]);
        }

        for (int i = 0; i < Configs::NUM_OF_BRANCHES; i++) {
            window.draw(spriteBranches[i]);
        }
        window.draw(spritePlayer);
        window.draw(spriteAxe);
        window.draw(spriteLog);
        window.draw(spriteRip);
        window.draw(spriteBee);
        window.draw(rect1);
        window.draw(scoreText);
        window.draw(rect2);
        window.draw(fpsText);
        window.draw(timeBar);
        if (paused) {
            window.draw(msgText);
        }
        window.display();
    }
}

int main()
{
    gamelogic();   
    return 0;
} 