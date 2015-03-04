#undef U
#include "gmock/gmock.h"
#ifndef GTEST_H_
	#define GTEST_H_
	#include "gtest/gtest.h"
#endif

int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
