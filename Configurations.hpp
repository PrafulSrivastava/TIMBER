#pragma once
namespace Paths {
    constexpr auto BACKGROUND_PATH = "assets/graphics/background.png";
    constexpr auto TREE_PATH = "assets/graphics/tree.png";
    constexpr auto BEE_PATH = "assets/graphics/bee.png";
    constexpr auto CLOUD_PATH = "assets/graphics/cloud.png";
    constexpr auto BRANCH_PATH = "assets/graphics/branch.png";
    constexpr auto PLAYER_PATH = "assets/graphics/player.png";
    constexpr auto AXE_PATH = "assets/graphics/axe.png";
    constexpr auto RIP_PATH = "assets/graphics/rip.png";
    constexpr auto LOG_PATH = "assets/graphics/log.png";
    constexpr auto FONT_PATH = "assets/fonts/KOMIKAP_.ttf";
}

namespace Configs {
    constexpr auto AXE_POSITION_LEFT = 700;
    constexpr auto AXE_POSITION_RIGHT = 1075;
    constexpr auto NUM_OF_BRANCHES = 6;
    constexpr auto START_MSG = "Press Enter to Start!";
    constexpr auto SCORE_MSG = "Score = 0";
    constexpr auto DEATH_MSG = "Pounded like crap!";
    constexpr auto TIME_OVER_MSG = "TimeOver!";
    constexpr auto HEIGHT = 1080;
    constexpr auto WIDTH = 1920;
    constexpr float TIME_REMAINING = 6.0f;
    constexpr auto CLOUDS_NUM = 3;
    constexpr auto POS_OUTSIDE_VIEW = 2000;
    constexpr auto TIMEBAR_START_WIDTH = 400;
    constexpr auto TIMEBAR_HEIGTH = 80;
    constexpr auto LOG_SPEED_Y = -1500;
    constexpr auto LOG_SPEED_X = 1000;
    constexpr auto BRANCH_ORIGIN_X = 220;
    constexpr auto BRANCH_ORIGIN_Y = 20;
    constexpr auto CLOUD_SPEED_OFFSET = 300;
    constexpr auto BEE_SPEED_OFFSET = 300;
    constexpr auto BEE_HEIGHT_OFFSET = 500;
    constexpr auto REWARD = 0.15;
}

namespace Coordinates {
    constexpr auto BACKGROUND_X = 0;
    constexpr auto BACKGROUND_Y = 0;
    constexpr auto TREE_X = 810;
    constexpr auto TREE_Y = 0;
    constexpr auto BEE_X = 2000;
    constexpr auto BEE_Y = 1080;
    constexpr auto CLOUD_X = 0;
    constexpr auto CLOUD_Y = 0;
    constexpr auto BRANCH_X_LEFT = 610;
    constexpr auto BRANCH_X_RIGHT = 1330;
    constexpr auto BRANCH_X_OUTSIDE = 3000;
    constexpr auto PLAYER_X_LEFT = 580;
    constexpr auto PLAYER_X_RIGHT = 1200;
    constexpr auto PLAYER_Y = 720;
    constexpr auto AXE_X = 700;
    constexpr auto AXE_Y = 830;
    constexpr auto RIP_X = 675;
    constexpr auto RIP_Y = 680;
    constexpr auto LOG_X = 810;
    constexpr auto LOG_Y = 700;
    constexpr auto MSG_TEXT_X = Configs::WIDTH / 2.0f;
    constexpr auto MSG_TEXT_Y = Configs::HEIGHT / 2.0f;
    constexpr auto SCORE_TEXT_X = 20;
    constexpr auto SCORE_TEXT_Y = 20;
    constexpr auto TIMEBAR_Y = 980;
}