#include <gtest/gtest.h>
#include "Enemy.h"
#include "Slingshot.h"

/// <summary>
///Taken from the GoogleTest primer. 
/// </summary>

// The fixture for testing class Foo.
class EnemyTest : public testing::Test {
public:
    std::unique_ptr<Enemy> enemy;
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    EnemyTest() {
        // You can do set-up work for each test here.
                    
    }

    ~EnemyTest() override {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
        enemy = std::make_unique<Enemy>(50); // All enemnies in this test suite start with 50 HP.
                    
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }


};

class SlingshotTest : public testing::Test {
public:
    std::unique_ptr<Slingshot> slingshot;
protected:

    SlingshotTest() {
        // You can do set-up work for each test here.

    }

    ~SlingshotTest() override {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
        slingshot = std::make_unique<Slingshot>(100, "Red"); // All slingshot starts with 100 tension.
        
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
};




//A single test, not a fixture. No setup is called.
TEST(Enemy, FirstEnemy_test) {
    Enemy e(100);
    EXPECT_GT(e.getHealth(), 100);
    /*SUCCEED() << "Test test passed";
    FAIL() << "Test didn't pass";*/
}

TEST_F(EnemyTest, LethalDamagePopsPig) {
    enemy->takeDamage(60);
    EXPECT_TRUE(enemy->checkIfPopped());
}

//second test, not a fixture. setup not needed.
TEST(Enemy, SecondEnemy_test) {
    Enemy d(0);
    ASSERT_NE(d.getHealth(), 0);
}

//First slingshotTest, not a fixture. no setup needed.
TEST(Slingshot, FirstSlingshot_Test) {
    Slingshot t(0, "Red");
    EXPECT_LE(t.getTension(), 100);
}

//BirdColour Test, fixture, setup needed
TEST_F(SlingshotTest, Test_BirdColour) { 
    slingshot->loadBird("Red");
    std::string str = "Red";
    const char* c = str.c_str();

    EXPECT_EQ(slingshot->getBirdType(), c);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}