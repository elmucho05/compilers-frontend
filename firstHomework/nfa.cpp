#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>

struct NFA {
    std::vector<std::string> alphabet;
    std::set<int> finalStates;
    std::map<int, std::map<std::string, std::set<int>>> transitions;
};

NFA readNFA(const std::string& inputFilename) {
    NFA nfa;
    std::ifstream inputFile(inputFilename);
    
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file." << std::endl;
        exit(1);
    }

    std::string line;
    int stateIndex = 0;

    // Read and parse each line of the input file
    while (std::getline(inputFile, line)) {
        // Tokenize the line
        std::vector<std::string> tokens;
        std::string token;
        for (char c : line) {
            if (c == ' ' || c == '\t') {
                if (!token.empty()) {
                    tokens.push_back(token);
                    token.clear();
                }
            } else {
                token += c;
            }
        }
        if (!token.empty()) {
            tokens.push_back(token);
        }

        // Process the tokens based on their position
        if (stateIndex == 0) {
            // First line contains the alphabet
            nfa.alphabet = tokens;
            nfa.alphabet.insert(nfa.alphabet.begin(), ""); // Insert an empty string at the beginning
        } else if (stateIndex == 1) {
            // Second line contains final states
            for (const std::string& token : tokens) {
                nfa.finalStates.insert(std::stoi(token));
            }
        } else {
            // Lines for state transitions
            int alphabetIndex = 0;
            int numTokens = tokens.size();
            int currentState = stateIndex - 2;

            for (int i = 0; i < numTokens; i++) {
                try{
                        std::string symbol = nfa.alphabet[alphabetIndex];
                    nfa.transitions[currentState][symbol].clear();
                    
                    int numDestinations = std::stoi(tokens[i]);
                    for (int j = 0; j < numDestinations; j++) {
                        i++;
                        nfa.transitions[currentState][symbol].insert(std::stoi(tokens[i]));
                    }
                    alphabetIndex++;
                }catch(const std::invalid_argument& e) {
                    std::cerr << "Error parsing transitions on line " << i << ": " << e.what() << std::endl;
                    // Handle the error as needed (e.g., skip the line or exit the program)
                }
            }
        }
        stateIndex++;
    }

    inputFile.close();
    return nfa;
}

int main() {
    std::string inputFilename = "nfa_input.txt"; // Replace with your input file's name
    NFA nfa = readNFA(inputFilename);

    // Access and print the parsed NFA representation
    std::cout << "Alphabet: ";
    for (const std::string& symbol : nfa.alphabet) {
        std::cout << symbol << " ";
    }
    std::cout << std::endl;

    std::cout << "Final States: ";
    for (int state : nfa.finalStates) {
        std::cout << state << " ";
    }
    std::cout << std::endl;
    /*
    for (const auto& [state, transitions] : nfa.transitions) {
        for (const auto& [symbol, destinations] : transitions) {
            std::cout << "𝜹(" << state << ", " << symbol << ") = { ";
            for (int dest : destinations) {
                std::cout << dest << " ";
            }
            std::cout << "}" << std::endl;
        }
    }
    */

    return 0;
}
