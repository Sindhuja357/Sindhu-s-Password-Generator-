#include <iostream>
#include <string>
#include <random>
#include <ctime>

// Function to generate a random password
std::string GeneratePassword(int length, bool useLowercase, bool useUppercase, bool useDigits, bool useSpecialChars) {
    const std::string lowercaseChars = "abcdefghijklmnopqrstuvwxyz";
    const std::string uppercaseChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string digitChars = "0123456789";
    const std::string specialChars = "!@#$%^&*()_+";

    std::string charset = "";

    if (useLowercase) charset += lowercaseChars;
    if (useUppercase) charset += uppercaseChars;
    if (useDigits) charset += digitChars;
    if (useSpecialChars) charset += specialChars;

    if (charset.empty()) {
        return "Error: No character set selected.";
    }

    const int charsetSize = charset.length();
    std::string password;

    std::mt19937_64 rng(std::time(nullptr)); // Initialize a random number generator with the current time

    for (int i = 0; i < length; ++i) {
        int randomIndex = rng() % charsetSize;
        password += charset[randomIndex];
    }

    return password;
}

int main() {
    int passwordLength;
    bool useLowercase, useUppercase, useDigits, useSpecialChars;

    // Get password length from the user
    std::cout << "Enter the desired length of the password: ";
    while (!(std::cin >> passwordLength) || passwordLength <= 0) {
        std::cout << "Invalid input. Please enter a positive integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Get user preferences for character sets
    std::cout << "Include lowercase characters? (1 for yes, 0 for no): ";
    std::cin >> useLowercase;

    std::cout << "Include uppercase characters? (1 for yes, 0 for no): ";
    std::cin >> useUppercase;

    std::cout << "Include digits? (1 for yes, 0 for no): ";
    std::cin >> useDigits;

    std::cout << "Include special characters? (1 for yes, 0 for no): ";
    std::cin >> useSpecialChars;

    // Generate the password
    std::string password = GeneratePassword(passwordLength, useLowercase, useUppercase, useDigits, useSpecialChars);

    // Check for errors in password generation
    if (password.find("Error:") != std::string::npos) {
        std::cerr << "Error: " << password << std::endl;
        return 1;
    }

    // Display the generated password
    std::cout << "Generated Password: " << password << std::endl;

    return 0;
}
