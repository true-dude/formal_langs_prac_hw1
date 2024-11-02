//
// Created by Евгений Тищенко on 09.11.2020.
//

#ifndef SOLUTION_H
#define SOLUTION_H

#include <iostream>
#include <string>
#include <stack>
#include <vector>

struct input {
    std::string regular;
    char symbol;
    int symbCount;

    input(const std::string &regular, char symbol, int count);
    bool isValid() const;
};

bool isLetter(char c);
bool is_reg_char(char c);

input getInput();
std::pair<std::vector<bool>, std::vector<bool>> getTopTwice(std::stack<std::vector<bool>> &st);

std::vector<bool> mskAND(std::vector<bool> &msk1, std::vector<bool> &msk2);
std::vector<bool> mskMUL(std::vector<bool> &msk1, std::vector<bool> &msk2);
std::vector<bool> mskITER(std::vector<bool> &msk);

void push_letter(std::stack<std::vector<bool>> &reg_st, char symb, input &inp);
void regAnd(std::stack<std::vector<bool>> &regStack);
void regMul(std::stack<std::vector<bool>> &regStack);
void regIter(std::stack<std::vector<bool>> &regStack);

bool getAnswer(input &data);
void solve();

#endif
