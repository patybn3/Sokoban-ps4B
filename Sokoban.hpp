/*
    Copyright 2023 Patricia Antlitz
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <map>

#include <SFML/Graphics.hpp>

enum Direction {
    Up, Down, Left, Right
};

class Sokoban : public sf::Drawable {
 public:
    std::vector<std::vector<char>> grid;
    std::vector<std::pair<int, int>> storageLocation;

    Sokoban();
    void loadLevel(const std::string& fileName);

    void movePlayer(Direction direction);
    void setGame(const std::string& level);

    int width() const;
    int height() const;

    void setPoints(float time);
    int getPoints();

    int getPlayerX() const { return playerX; }
    int getPlayerY() const { return playerY; }
    bool isWon();

    friend std::istream& operator>>(std::istream& in, Sokoban& soko);
    friend std::ostream& operator<<(std::ostream& out, const Sokoban& soko);

 protected:
    sf::Sprite playerSprite;
    std::map<std::string, sf::Texture> textures;

    void loadTexture(const std::string& file, const std::string& name);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void updatePosition(int x, int y);

 private:
    int height_;
    // player's position
    int playerX, playerY;
    int points;
    int tileSize_;
    int width_;

    Direction playerDirection;
    std::map<char, sf::Texture> playerTextures;
};

