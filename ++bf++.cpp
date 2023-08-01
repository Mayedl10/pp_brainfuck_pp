#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string getFileContentAsString(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

char randChar() {
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate a random number between 0 and 255 (inclusive)
    int randomValue = std::rand() % 256;

    // Convert the random number to a char and return it
    return static_cast<char>(randomValue);
}
int interpret(std::string code, const int MEM_SIZE = 32768) {
    std::vector<char> memory(MEM_SIZE, 0);
    int pointer = 0;

    char temp;
    char var;


    for (size_t i = 0; i < code.length(); i++) {
        char command = code[i];
        switch (command) {
            case '>':
                pointer = (pointer + 1) % MEM_SIZE;
                break;
            case '<':
                pointer = (pointer - 1 + MEM_SIZE) % MEM_SIZE;
                break;
            case '+':
                memory[pointer] = (memory[pointer] + 1) % 256;
                break;
            case '-':
                memory[pointer] = (memory[pointer] - 1 + 256) % 256;
                break;
            case '.':
                std::cout << memory[pointer];
                break;
            case ',':
                std::cin >> temp;
                memory[pointer] = temp;
                break;
            case '{':
                if (memory[pointer] == 0) {
                    int loopLevel = 1;
                    while (loopLevel > 0) {
                        i++;
                        if (code[i] == '{')
                            loopLevel++;
                        else if (code[i] == '}')
                            loopLevel--;
                    }
                }
                break;
            case '}':
                if (memory[pointer] != 0) {
                    int loopLevel = 1;
                    while (loopLevel > 0) {
                        i--;
                        if (code[i] == '{')
                            loopLevel--;
                        else if (code[i] == '}')
                            loopLevel++;
                    }
                }
                break;

            case 'c':
                var = memory[pointer];
                break;

            case 'p':
                memory[pointer] = var;
                break;

            case 'o':
                memory[pointer] = 0;
                break;

            case 'e':
                return 0;
                break;

            case 'n':
                std::cout << static_cast<unsigned int>(static_cast<unsigned char>(memory[pointer]));
                break;

            case 'r':
                memory[pointer] = randChar();
                break;
                
            default:
                // Ignore any other characters (non-Brainfuck commands)
                break;
        }
    }

    // Return the last value in the memory pointer after execution.
    return 0;
}

void debugP() {
    std::cout <<"a"<<std::endl;
}

int main(int argc, char* argv[]) {
    //std::cout << "|" << argv[1] << "|" << argv[2] << "|" << std::endl;

    


    int result;
    if (argc != 3) {
        std::cout << "Syntax:\n\t++bf++ file [path]\n\t++bf++ direct [code]" << std::endl;
        return 1;
    }


    std::string f = "file";
    std::string d = "direct";

    if (argv[1] == f) {
        result = interpret(getFileContentAsString(argv[2]));

    } else if (argv[1] == d) {
        result = interpret(argv[2]);

    } else {
        std::cout << "Syntax:\n\t++bf++ file [path]\n\t++bf++ direct [code]" << std::endl;
        return 2;
    }

    
    return 0;
}