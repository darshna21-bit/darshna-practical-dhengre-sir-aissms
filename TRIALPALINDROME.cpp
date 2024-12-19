#include <iostream>
#include <stack>
#include <cctype>
using namespace std;

// Function to clean the string (remove non-alphanumeric characters and convert to lowercase)
string cleanString(const string &str) {
    string result;
    for (char ch : str) {
        if (isalnum(ch)) {
            result += tolower(ch);
        }
    }
    return result;
}

// Function to reverse the string using a stack
string reverseString(const string &str) {
    stack<char> s;
    string rev;

    for (char ch : str) {
        s.push(ch);
    }

    while (!s.empty()) {
        rev += s.top();
        s.pop();
    }

    return rev;
}

// Function to check if the string is a palindrome
bool checkPalindrome(const string &str) {
    string clean = cleanString(str);    // Clean the input string
    string reversed = reverseString(clean);  // Reverse the cleaned string

    return clean == reversed;  // Check if both strings are identical
}

int main() {
    string input;

    cout << "Enter a string to check if it's a palindrome: ";
    getline(cin, input);

    cout << "Original string: " << input << endl;
    cout << "Reversed string: " << reverseString(input) << endl;

    if (checkPalindrome(input)) {
        cout << "The string is a palindrome." << endl;
    } else {
        cout << "The string is not a palindrome." << endl;
    }

    return 0;
}

