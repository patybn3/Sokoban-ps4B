/*
    Copyright 2023 Patricia Antlitz
*/
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#include "Sokoban.hpp"

BOOST_AUTO_TEST_CASE(playerMovement) {
    Sokoban sb;
    sb.setGame("./sokoban/level1.lvl");

    int initialPlayerX = sb.getPlayerX();
    int initialPlayerY = sb.getPlayerY();

    sb.movePlayer(Direction::Up);

    BOOST_CHECK_EQUAL(sb.getPlayerY(), initialPlayerY - 1);

    sb.movePlayer(Direction::Down);
    BOOST_CHECK_EQUAL(sb.getPlayerY(), initialPlayerY);

    sb.movePlayer(Direction::Left);

    BOOST_CHECK_EQUAL(sb.getPlayerX(), initialPlayerX - 1);

    sb.movePlayer(Direction::Right);
    BOOST_CHECK_EQUAL(sb.getPlayerX(), initialPlayerX);
}

BOOST_AUTO_TEST_CASE(boxPushingTest) {
    Sokoban sb;
    sb.setGame("./sokoban/level1.lvl");

    sb.movePlayer(Direction::Right);
    sb.movePlayer(Direction::Right);

    BOOST_CHECK_EQUAL(sb.grid[6][3], '.');  // previous position is now empty
    BOOST_CHECK_EQUAL(sb.grid[6][5], '@');  // player's new position
    BOOST_CHECK_EQUAL(sb.grid[6][6], 'A');  // box pushed

    sb.movePlayer(Direction::Left);

    BOOST_CHECK_EQUAL(sb.grid[6][4], '@');  // player returns to position
    BOOST_CHECK_EQUAL(sb.grid[6][3], '.');
    BOOST_CHECK_EQUAL(sb.grid[6][6], 'A');  // box pushed
}

BOOST_AUTO_TEST_CASE(gameResetTest) {
    Sokoban sb;
    sb.setGame("./sokoban/level1.lvl");

    sb.movePlayer(Direction::Right);
    sb.movePlayer(Direction::Right);
    sb.movePlayer(Direction::Left);

    BOOST_CHECK_EQUAL(sb.grid[6][4], '@');  // player returns to position
    BOOST_CHECK_EQUAL(sb.grid[6][3], '.');
    BOOST_CHECK_EQUAL(sb.grid[6][6], 'A');  // box pushed

    sb.setGame("./sokoban/level1.lvl");

    BOOST_CHECK_EQUAL(sb.grid[6][3], '@');  // player returns to position
    BOOST_CHECK_EQUAL(sb.grid[6][4], '.');
    BOOST_CHECK_EQUAL(sb.grid[6][6], 'A');  // box pushed
}

BOOST_AUTO_TEST_CASE(victoryTest) {
    Sokoban sb;
    sb.setGame("./sokoban/level1.lvl");

    sb.movePlayer(Direction::Right);
    sb.movePlayer(Direction::Right);
    sb.movePlayer(Direction::Right);
    sb.movePlayer(Direction::Right);

    sb.movePlayer(Direction::Up);
    sb.movePlayer(Direction::Right);
    sb.movePlayer(Direction::Down);

    sb.movePlayer(Direction::Up);
    sb.movePlayer(Direction::Up);
    sb.movePlayer(Direction::Up);
    sb.movePlayer(Direction::Up);

    sb.movePlayer(Direction::Left);
    sb.movePlayer(Direction::Left);
    sb.movePlayer(Direction::Down);
    sb.movePlayer(Direction::Left);
    sb.movePlayer(Direction::Up);

    BOOST_CHECK(sb.isWon());
}

BOOST_AUTO_TEST_CASE(pointsCalculationTest) {
    Sokoban sb;
    sb.setGame("./sokoban/level1.lvl");

    sb.movePlayer(Direction::Right);  // move to start timer

    // simulate 10 seconds
    for (int i = 0; i < 10; ++i) {
        sb.setPoints(static_cast<float>(i));
    }

    BOOST_CHECK_EQUAL(sb.getPoints(), 41);   // points are 50 points - 10 sec + 0 = 1
    // win
    sb.movePlayer(Direction::Right);
    sb.movePlayer(Direction::Right);
    sb.movePlayer(Direction::Right);
    sb.movePlayer(Direction::Right);

    sb.movePlayer(Direction::Up);
    sb.movePlayer(Direction::Right);
    sb.movePlayer(Direction::Down);

    sb.movePlayer(Direction::Up);
    sb.movePlayer(Direction::Up);
    sb.movePlayer(Direction::Up);
    sb.movePlayer(Direction::Up);

    sb.movePlayer(Direction::Left);
    sb.movePlayer(Direction::Left);
    sb.movePlayer(Direction::Down);
    sb.movePlayer(Direction::Left);
    sb.movePlayer(Direction::Up);

    BOOST_CHECK_EQUAL(sb.getPoints(), 41);
}



BOOST_AUTO_TEST_CASE(pointsCalculationAfterMinute) {
    Sokoban sb;
    sb.setGame("./sokoban/level1.lvl");

    sb.movePlayer(Direction::Right);  // move to start timer

    // simulate 60 seconds
    for (int i = 0; i < 60; ++i) {
        sb.setPoints(static_cast<float>(i));
    }

    // The program counts the points down from 50, one point per second, after 60 seconds
    // the player would have negative points. Any points less or equal to 0 = 1
    BOOST_CHECK_EQUAL(sb.getPoints(), 1);
    // win
    sb.movePlayer(Direction::Right);
    sb.movePlayer(Direction::Right);
    sb.movePlayer(Direction::Right);
    sb.movePlayer(Direction::Right);

    sb.movePlayer(Direction::Up);
    sb.movePlayer(Direction::Right);
    sb.movePlayer(Direction::Down);

    sb.movePlayer(Direction::Up);
    sb.movePlayer(Direction::Up);
    sb.movePlayer(Direction::Up);
    sb.movePlayer(Direction::Up);

    sb.movePlayer(Direction::Left);
    sb.movePlayer(Direction::Left);
    sb.movePlayer(Direction::Down);
    sb.movePlayer(Direction::Left);
    sb.movePlayer(Direction::Up);

    BOOST_CHECK_EQUAL(sb.getPoints(), 1);   // if points <= 0, points = 1
}
