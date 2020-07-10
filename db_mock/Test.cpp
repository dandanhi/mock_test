#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;

class DataBaseConnect {
  public:
    MOCK_METHOD0(fetchRecord, int ());
    MOCK_METHOD1(logout, bool (string username));
    MOCK_METHOD2(login, bool (string username, string password));
    MOCK_METHOD2(login2, bool (string username, string password));
};

class MyDatabase {
  DataBaseConnect & dbC;

  public:
    MyDatabase(DataBaseConnect & _dbC) : dbC(_dbC) {}

    int Init(string username, string password) {
      int rvalue = rand() % 2;
      if (rvalue) {
        return dbC.login2(username, password);
      }

      if (!dbC.login(username, password)) {
        if (!dbC.login(username, password)) {
          cout << "DB FAILTURE 2nd TIME" << endl; return -1;
        }
      }

      cout << "DB SUCCESS" << endl; return 1;
    }
};

TEST(MyDBTest, LoginTest) {
  // Arrange
  DataBaseConnect mdb;
  MyDatabase db(mdb);
  ON_CALL(mdb, login(_, _))
  .WillByDefault(Return(true));

  ON_CALL(mdb, login2(_, _))
  .WillByDefault(Return(true));

  // Act
  int retValue = db.Init("Terminator", "I'll Back");

  // ASSERT
  EXPECT_EQ(retValue, 1);
};

TEST(MyDBTest, LoginFailture) {
  // Arrange
  DataBaseConnect mdb;
  MyDatabase db(mdb);
  EXPECT_CALL(mdb, login(_, _))
  .Times(2)
  .WillOnce(Return(false))
  .WillOnce(Return(false));

  // Act
  int retValue = db.Init("Terminator", "I'll Back");

  // ASSERT
  EXPECT_EQ(retValue, -1);
};

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}