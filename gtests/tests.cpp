#include <gtest/gtest.h>
#include <solution.h>
#include <vector>
#include <random>
std::mt19937 rnd;

TEST(ClassInputTest, ConstructorTest) {
    input inp("abacaba", 'c', 3);
    EXPECT_EQ(inp.regular, "abacaba");
    EXPECT_EQ(inp.symbol, 'c');
    EXPECT_EQ(inp.symbCount, 3);
}

TEST(ClassInputTest, isValidTest) {
    input data1("abacaba", 'c', 22);
    input data2("abcda*..*", 'c', 22);
    input data3("abc+a*..*", 'c', 22);
    input data4("abc+a*..*", 'f', 22);
    EXPECT_EQ(data1.isValid(), true);
    EXPECT_EQ(data2.isValid(), false);
    EXPECT_EQ(data3.isValid(), true);
    EXPECT_EQ(data4.isValid(), false);
}

TEST(UsefulFunctionsTest, isLetterTest) {
    EXPECT_EQ(isLetter('a'), true);
    EXPECT_EQ(isLetter('b'), true);
    EXPECT_EQ(isLetter('c'), true);
    for (int i = 1; 'c' + i <= 'z'; ++i) {
        EXPECT_EQ(isLetter('c' + i), false);
    }
    for (int i = 0; 'A' + i <= 'Z'; ++i) {
        EXPECT_EQ(isLetter('A' + i), false);
    }
}

TEST(UsefulFunctionsTest, is_reg_char_test) {
    std::string s = "abbabc**..*aabccababab";
    for (char c : s) {
        EXPECT_EQ(is_reg_char(c), true);
    }
    std::string t = "78d9hfrwnerfeoiwfowierf_4123:;";
    for (char c : t) {
        EXPECT_EQ(is_reg_char(c), false);
    }
}

TEST(UsefulFunctionsTest, getTopTwiceTest) {
    std::stack<std::vector<bool>> st;
    std::vector<bool> v1 = {false, true};
    std::vector<bool> v2 = {false, false};
    std::vector<bool> v3 = {true, true};
    st.push(v1);
    EXPECT_ANY_THROW(getTopTwice(st));
    st.push(v2);
    st.push(v3);
    auto res = getTopTwice(st);
    std::pair<std::vector<bool>, std::vector<bool>> predicted_res = {v3, v2};
    EXPECT_EQ(res, predicted_res);
}

TEST(MaskTest, ANDTest) {
    for (int i = 1; i < 1000; ++i) {
        int msk_len = 50;
        std::vector<bool> msk1(msk_len, false), msk2(msk_len, false);
        for (int j = 0; j < msk_len; ++j) {
            msk1[j] = rnd() % 2;
            msk2[j] = rnd() % 2;
        }
        auto res = mskAND(msk1, msk2);
        for (int j = 0; j < msk_len; ++j) {
            EXPECT_EQ(res[j], (msk1[j] | msk2[j]));
        }
    }
}

TEST(MaskTest, MULTest) {
    for (int i = 1; i < 1000; ++i) {
        int msk_len = 50;
        std::vector<bool> msk1(msk_len, false), msk2(msk_len, false);
        for (int j = 0; j < msk_len; ++j) {
            msk1[j] = rnd() % 2;
            msk2[j] = rnd() % 2;
        }
        auto res = mskMUL(msk1, msk2);
        for (int n = 0; n < msk_len; ++n) {
            bool f = true;
            for (int j = 0; j <= n; ++j) {
                if (msk1[j] && msk2[n - j]) {
                    EXPECT_EQ(res[n], true);
                    f = false;
                }
            }
            if (f) {
                EXPECT_EQ(res[n], false);
            }
        }
    }
}

TEST(MaskTest, IterTest) {
    int msk_len = 50;
    for (int i = 1; i < msk_len; ++i) {
        std::vector<bool> msk(msk_len, false);
        msk[i] = true;
        auto res = mskITER(msk);
        for (int j = 0; j < msk_len; ++j) {
            if (j % i == 0) {
                EXPECT_EQ(res[j], true);
            } else {
                EXPECT_EQ(res[j], false);
            }
        }
    }
    std::vector<bool> msk(msk_len, false);
    msk[0] = true;
    auto res = mskITER(msk);
    for (int j = 1; j < msk_len; ++j) {
        EXPECT_EQ(res[j], false);
    }
}

TEST(RegTest, PushLetterTest) {
    std::stack<std::vector<bool>> reg_stack;
    input data("ababa", 'a', 3);
    push_letter(reg_stack, 'a', data);
    EXPECT_EQ(reg_stack.size(), 1);
    EXPECT_EQ(reg_stack.top().size(), 4);
    EXPECT_EQ(reg_stack.top()[0], false);
    EXPECT_EQ(reg_stack.top()[1], true);

    push_letter(reg_stack, 'b', data);
    EXPECT_EQ(reg_stack.size(), 2);
    EXPECT_EQ(reg_stack.top().size(), 4);
    EXPECT_EQ(reg_stack.top()[0], true);
    EXPECT_EQ(reg_stack.top()[1], false);
}

TEST(RegTest, regANDTest) {
    for (int i = 1; i < 1000; ++i) {
        int msk_len = 50;
        std::vector<bool> msk1(msk_len, false), msk2(msk_len, false);
        for (int j = 0; j < msk_len; ++j) {
            msk1[j] = rnd() % 2;
            msk2[j] = rnd() % 2;
        }
        std::stack<std::vector<bool>> reg_st;
        reg_st.push(msk1);
        reg_st.push(msk2);
        regAnd(reg_st);
        EXPECT_EQ(reg_st.size(), 1);
        for (int j = 0; j < msk_len; ++j) {
            EXPECT_EQ(reg_st.top()[j], (msk1[j] | msk2[j]));
        }
    }
}

TEST(RegTest, regMULTest) {
    for (int i = 1; i < 1000; ++i) {
        int msk_len = 50;
        std::vector<bool> msk1(msk_len, false), msk2(msk_len, false);
        for (int j = 0; j < msk_len; ++j) {
            msk1[j] = rnd() % 2;
            msk2[j] = rnd() % 2;
        }
        std::stack<std::vector<bool>> reg_st;
        reg_st.push(msk1);
        reg_st.push(msk2);
        regMul(reg_st);
        EXPECT_EQ(reg_st.size(), 1);
        for (int n = 0; n < msk_len; ++n) {
            for (int j = 0; j <= n; ++j) {
                if (msk1[j] && msk2[n - j]) {
                    EXPECT_EQ(reg_st.top()[n], true);
                }
            }
        }
    }
}

TEST(RegTest, regIterTest) {
    int msk_len = 50;
    for (int i = 1; i < msk_len; ++i) {
        std::stack<std::vector<bool>> reg_st;
        EXPECT_ANY_THROW(regIter(reg_st));
        std::vector<bool> msk(msk_len, false);
        msk[i] = true;
        reg_st.push(msk);
        regIter(reg_st);
        for (int j = 0; j < msk_len; ++j) {
            if (j % i == 0) {
                EXPECT_EQ(reg_st.top()[j], true);
            } else {
                EXPECT_EQ(reg_st.top()[j], false);
            }
        }
    }
}

TEST(AlgoTest, IncorrectDataTest) {
    input data("ab+cd", 'a', 3);
    EXPECT_ANY_THROW(getAnswer(data));
    input data1("+aba", 'a', 4);
    EXPECT_ANY_THROW(getAnswer(data1));
    input data2("bab+", 'a', 4);
    EXPECT_ANY_THROW(getAnswer(data2));
    data.regular = "*aaa";
    EXPECT_ANY_THROW(getAnswer(data));
    data.regular = "a*aaa";
    EXPECT_ANY_THROW(getAnswer(data));
    data.regular = "ab+c*";
    EXPECT_ANY_THROW(getAnswer(data));
    data.regular = ".bbaa";
    EXPECT_ANY_THROW(getAnswer(data));
    data.regular = "ab.abbabaab";
    EXPECT_ANY_THROW(getAnswer(data));
    data.regular = "cbfd";
    EXPECT_ANY_THROW(getAnswer(data));
    data.regular = "ab+c+.";
    EXPECT_ANY_THROW(getAnswer(data));
}

TEST(AlgoTest, TaskTest) {
    input data("ab.c.a.", 'a', 2);
    EXPECT_EQ(getAnswer(data), true);
    data.symbCount = 1;
    EXPECT_EQ(getAnswer(data), false);
    input data1("ab.a+c.a.", 'a', 2);
    EXPECT_EQ(getAnswer(data1), true);
    data1.symbCount = 1;
    EXPECT_EQ(getAnswer(data1), false);
    data1.symbCount = 3;
    EXPECT_EQ(getAnswer(data1), false);
    input data2("ab.a+c.a.*a.b.a+", 'a', 1);
    EXPECT_EQ(getAnswer(data2), true);
    data2.symbCount = 2;
    EXPECT_EQ(getAnswer(data2), false);
    data2.symbCount = 115;
    EXPECT_EQ(getAnswer(data2), true);
    input data3("aab.*c+a.*ab.+.c.", 'a', 2);
    EXPECT_EQ(getAnswer(data3), true);
    data3.symbCount = 161;
    EXPECT_EQ(getAnswer(data3), true);
    data3.symbCount = 0;
    EXPECT_EQ(getAnswer(data3), false);
}
