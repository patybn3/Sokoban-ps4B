/*
    Copyright 2023 Patricia Antlitz
*/
#include "Sokoban.hpp"

Sokoban::Sokoban() : points(50) {
    loadTexture("./sokoban/block_06.png", "wall");
    loadTexture("./sokoban/ground_01.png", "background");
    loadTexture("./sokoban/ground_04.png", "storage");
    loadTexture("./sokoban/crate_03.png", "box");

    tileSize_ = 60;

    loadTexture("./sokoban/player_05.png", "player_05");
    loadTexture("./sokoban/player_08.png", "player_08");
    loadTexture("./sokoban/player_17.png", "player_17");
    loadTexture("./sokoban/player_20.png", "player_20");
}

void Sokoban::loadLevel(const std::string& fileName) {
    std::ifstream loadFile(fileName);

    if (!loadFile) {
        std::cout << "Error. Level file not loaded" << std::endl;
        return;
    }

    loadFile >> height_ >> width_;
    grid.resize(height_, std::vector<char>(width_));

    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            loadFile >> grid[i][j];

            if (grid[i][j] == 'a') {
                storageLocation.emplace_back(j, i);
            }
        }
    }
    loadFile.close();
}

void Sokoban::loadTexture(const std::string& file, const std::string& name) {
    sf::Texture oneTexture;
    oneTexture.loadFromFile(file);
    textures[name] = oneTexture;
}

void Sokoban::setGame(const std::string& level) {
    playerY = 0;
    playerX = 0;

    loadLevel(level);

    // player initial position
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j <width_; ++j) {
            if (grid[i][j] == '@') {
                playerX = j;
                playerY = i;
                break;
            }
        }
    }

    playerSprite.setTexture(textures["player_05"]);
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (unsigned int i = 0; i < grid.size(); ++i) {
        for (unsigned int j = 0; j < grid[i].size(); ++j) {
            char cell = grid[i][j];
            sf::Sprite localSprite;

            switch (cell) {
            case '#':
                if (textures.find("wall") != textures.end()) {
                    localSprite.setTexture(textures.at("wall"));
                } else {
                    std::cout << "Error: Texture 'wall' not found" << std::endl;
                }
                break;
            case '.':
                if (textures.find("background") != textures.end()) {
                    localSprite.setTexture(textures.at("background"));
                } else {
                    std::cout << "Error: Texture 'background' not found" << std::endl;
                }
                break;
            case 'A':
                if (textures.find("box") != textures.end()) {
                localSprite.setTexture(textures.at("box"));
                } else {
                    std::cout << "Error: Texture 'box' not found" << std::endl;
                }
                break;
            case 'a':
                if (textures.find("storage") != textures.end()) {
                    localSprite.setTexture(textures.at("storage"));
                } else {
                    std::cout << "Error: Texture 'storage' not found" << std::endl;
                }
                break;
            case '@':
                localSprite = playerSprite;
                break;
            default:
                break;
            }

            localSprite.setPosition(j * tileSize_, i * tileSize_);
            target.draw(localSprite);
        }
    }
}

void Sokoban::updatePosition(int x, int y) {
    // check if new position is open, a storage area or a box
    if (x >= 0 && y >= 0 && x < width_ && y < height_ && grid[y][x] != '#') {
        char target = grid[y][x];

        // target is an open space
        if (target == '.' || target == 'a') {
            grid[playerY][playerX] = '.';
            grid[y][x] = '@';
            playerX = x;
            playerY = y;
        } else if (target == 'A' &&
                    x + (x - playerX) >= 0 && x + (x - playerX) < width_ &&
                    y + (y - playerY) >= 0 && y + (y - playerY) < height_ &&
                    (grid[y + (y - playerY)][x + (x - playerX)] == '.' ||
                    grid[y + (y - playerY)][x + (x - playerX)] == 'a')) {
            grid[playerY][playerX] = '.';
            grid[y][x] = '@';
            grid[y + (y - playerY)][x + (x - playerX)] = 'A';
            playerX = x;
            playerY = y;
        }

        for (const auto& location : storageLocation) {
            int xLoc = location.first;
            int yLoc = location.second;

            if (grid[yLoc][xLoc] == '.') {
                grid[yLoc][xLoc] = 'a';
            }
        }
    }
}

void Sokoban::movePlayer(Direction direction) {
    int x = playerX;
    int y = playerY;

    if (direction == Direction::Up) {
        // player_05 for front
        playerSprite.setTexture(textures["player_08"]);
        y--;
    } else if (direction == Direction::Down) {
        // player_08 for back
        playerSprite.setTexture(textures["player_05"]);
        y++;
    } else if (direction == Direction::Left) {
        // player_20 for left
        playerSprite.setTexture(textures["player_20"]);
        x--;
    } else if (direction == Direction::Right) {
        // player_17 for right
        playerSprite.setTexture(textures["player_17"]);
        x++;
    }

    updatePosition(x, y);
}

int Sokoban::width() const {
    return width_ * tileSize_;
}

int Sokoban::height() const {
    return height_ * tileSize_;
}

void Sokoban::setPoints(float time) {
    points = std::max(0, 50 - static_cast<int>(time));
    if (points <= 0) {
        points = 1;  // the lowest score possible, 1 for participation
    }
}

int Sokoban::getPoints() {
    return points;
}

bool Sokoban::isWon() {
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            if (grid[i][j] == 'A') {
                if (std::find(storageLocation.begin(), storageLocation.end(),
                    std::make_pair(j, i)) == storageLocation.end()) {
                    return false;
                }
            }
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& out, const Sokoban& game) {
    out << game.width_ << " " << game.height_ << '\n';

    for (const auto& row : game.grid) {
        for (char cell : row) {
            out << cell;
        }
        out << '\n';
    }
    return out;
}

std::istream& operator>>(std::istream& in, Sokoban& game) {
    int width, height;
    in >> width >> height;

    game.grid.clear();
    game.grid.resize(height, std::vector<char>(width));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            in >> game.grid[i][j];
        }
    }

    return in;
}
