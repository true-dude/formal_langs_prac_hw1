#include "solution.h"

input::input(const std::string &regular, char symbol, int count): regular(regular),
                                                               symbol(symbol), symbCount(count) {}

bool input::isValid() const {
    for (char reg_char : regular) {
        if (!is_reg_char(reg_char)) {
            return false;
        }
    }
    return isLetter(symbol);
}

bool isLetter(char c) {
    return c >= 'a' && c <= 'c';
}

bool is_reg_char(char c) {
    return c == '.' || c == '*' || c == '+' || isLetter(c);
}

input getInput() {
    std::string regular;
    char symb;
    int count;
    std::cin >> regular >> symb >> count;
    input data(regular, symb, count);
    if (!data.isValid()) {
        throw std::invalid_argument("Invalid input");
    }
    return data;
}

void push_letter(std::stack<std::vector<bool>> &reg_st, char symb, input &inp) {
    std::vector<bool> mask(inp.symbCount + 1, false);
    if (symb == inp.symbol) {
        mask[1] = true;
    } else {
        mask[0] = true;
    }
    reg_st.push(mask);
}

std::vector<bool> mskAND(std::vector<bool> &msk1, std::vector<bool> &msk2) {
    std::vector<bool> msk_res(msk1.size(), false);
    for (int i = 0; i < msk1.size(); ++i) {
        msk_res[i] = msk1[i] | msk2[i];
    }
    return msk_res;
}

std::vector<bool> mskMUL(std::vector<bool> &msk1, std::vector<bool> &msk2) {
    std::vector<bool> msk_res(msk1.size(), false);
    for (int i = 0; i < msk1.size(); ++i) {
        for (int j = 0; j < msk2.size(); ++j) {
            if (msk1[i] && msk2[j] && i + j < msk1.size()) {
                msk_res[i + j] = true;
            }
        }
    }
    return msk_res;
}

std::vector<bool> mskITER(std::vector<bool> &msk) {
    std::vector<bool> msk_res(msk.size(), false);
    msk_res[0] = true;
    for (int k = 0; k <= msk.size(); ++k) {
        auto step = mskMUL(msk_res, msk);
        msk_res = mskAND(msk_res, step);
    }
    return msk_res;
}

std::pair<std::vector<bool>, std::vector<bool>> getTopTwice(std::stack<std::vector<bool>> &st) {
    if (st.size() < 2) {
        throw std::invalid_argument("Invalid regular format");
    }
    auto vec1 = st.top();
    st.pop();
    auto vec2 = st.top();
    st.pop();
    return {vec1, vec2};
}

void regAnd(std::stack<std::vector<bool>> &regStack) {
    auto [msk1, msk2] = getTopTwice(regStack);
    regStack.push(mskAND(msk1, msk2));
}

void regMul(std::stack<std::vector<bool>> &regStack) {
    auto [msk1, msk2] = getTopTwice(regStack);
    regStack.push(mskMUL(msk1, msk2));
}

void regIter(std::stack<std::vector<bool>> &regStack) {
    if (regStack.empty()) {
        throw std::invalid_argument("Invalid regular format");
    }
    auto msk = regStack.top();
    regStack.pop();
    regStack.push(mskITER(msk));
}

bool getAnswer(input &data) {
    std::stack<std::vector<bool>> regStack;
    for (char c : data.regular) {
        if (isLetter(c)) {
            push_letter(regStack, c, data);
        } else if (c == '+') {
            regAnd(regStack);
        } else if (c == '.') {
            regMul(regStack);
        } else if (c == '*') {
            regIter(regStack);
        }
    }

    if (regStack.size() != 1) {
        throw std::invalid_argument("Invalid regular format");
    }
    auto result = regStack.top();
    return result[data.symbCount];
}

void solve() {
    auto input_task = getInput();
    std::cout << (getAnswer(input_task) ? "YES" : "NO");
}
