#include "TileMapParser.hpp"

TileMapParser::TileMapParser(const std::string& filename) : fileStream(filename) {
    if (!fileStream.is_open()) {
        throw std::runtime_error("Unable to open file");
    }
}

std::vector<std::vector<short>> TileMapParser::parseTileMap(short targetIndex) {
    std::vector<std::vector<short>> result;
    std::string line;
    bool found = false;

    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        if (line.empty()) {
            continue; // Skip empty lines
        }

        int index;
        if (!(std::istringstream(line) >> index)) {
            throw std::runtime_error("Invalid index format");
        }

        if (index == targetIndex) {
            found = true;
            break;
        }

        // Skip to the next TileMap block
        std::string brace;
        while (std::getline(fileStream, brace) && brace != "}") {
            // Skip lines until the closing brace
        }
    }

    if (!found) {
        throw std::runtime_error("Desired index not found");
    }

    std::string brace;
    if (!(std::getline(fileStream, brace)) || brace != "{") {
        throw std::runtime_error("Missing or invalid opening brace");
    }

    while (std::getline(fileStream, line) && line != "}") {
        std::istringstream ss(line);
        std::vector<short> row;
        short num;
        while (ss >> num) {
            row.push_back(num);
            char comma;
            if (!(ss >> std::ws >> comma) || comma != ',') {
                if (!ss.eof()) {
                    throw std::runtime_error("Invalid TileMap format");
                }
                break;
            }
        }
        result.push_back(row);
    }

    if (line != "}") {
        throw std::runtime_error("Missing closing brace");
    }

    return result;
}


void printTileMap(const std::vector<std::vector<short>>& tileMap) {
    for (const auto& row : tileMap) {
        for (short value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    //CORRECT THIS
    TileMapParser parser("C:/EMIN SALIH/Programming/C++ Projects/TileMapParser/TileMapParser/test.txt");

    try {
        std::vector<std::vector<short>> tileMap = parser.parseTileMap(2);
        printTileMap(tileMap);
        std::cout << "Bruh";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 12;
}