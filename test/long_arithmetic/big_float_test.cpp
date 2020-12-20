#include <gtest/gtest.h>

#include <limits>

#include "nnoops/long_arithmetic/big_float.hpp"
using namespace nnoops;

TEST(BigFloat, addition_test) {
  using BigFloatT = BigFloat<1024>;

  BigFloatT val1("3124.3312");
  BigFloatT val2("-12.41551");

  EXPECT_EQ(toPrettyString(val1 + val2), "");
  EXPECT_EQ(val1 + val2, BigFloatT("3111.91569"));
  EXPECT_EQ(val2 + val1, BigFloatT("3111.91569"));

  val1 = BigFloatT("0.312415");
  val2 = BigFloatT("0.00000312");

  EXPECT_EQ(val1 + val2, BigFloatT("0.31241812"));
  EXPECT_EQ(val2 + val1, BigFloatT("0.31241812"));
}

TEST(BigFloat, multiplication_test) {
  using BigFloatT = BigFloat<1024>;

  BigFloatT val1("3124.3312");
  BigFloatT val2("-12.41551");

  val1 *= val2;

  EXPECT_EQ(val1, BigFloatT("-38790.165256912"));

  val1 = BigFloatT("3124.3312");

  EXPECT_EQ(val1 * val2, BigFloatT("-38790.165256912"));
  EXPECT_EQ(val2 * val1, BigFloatT("-38790.165256912"));

  val2 *= BigFloatT("-1");

  EXPECT_EQ(val1 * val2, BigFloatT("38790.165256912"));
  EXPECT_EQ(val2 * val1, BigFloatT("38790.165256912"));

  val1 = BigFloatT("0.312415");
  val2 = BigFloatT("0.00000312");

  EXPECT_EQ(val1 * val2, BigFloatT("0.0000009747348"));
  EXPECT_EQ(val2 * val1, BigFloatT("0.0000009747348"));
}

TEST(BigFloat, inverse_test) {
  using BigFloatT = BigFloat<1024>;

  BigFloatT val("5.0");

  EXPECT_EQ(val.inverse(), BigFloatT("0.2"));

  // accuracy - 5
  val = BigFloatT("3.0", 5);

  EXPECT_EQ(val.inverse(), BigFloatT("0.33333"));

  // accuracy - 19
  val = BigFloatT("4134.6146161", 19);

  EXPECT_EQ(val.inverse(), BigFloatT("0.0002418605100717357"));

  // accuracy - 15
  val = BigFloatT("0.245555542", 15);

  EXPECT_EQ(val.inverse(), BigFloatT("4.072398414856383"));

  // accuracy - 15
  val = BigFloatT("-0.245555542", 15);

  EXPECT_EQ(val.inverse(), BigFloatT("-4.072398414856383"));
}

TEST(BigFloat, division_test) {
  using BigFloatT = BigFloat<1024>;

  // accuracy - 5
  BigFloatT val1("13.0", 5);
  BigFloatT val2("4.0", 5);

  EXPECT_EQ(val1 / val2, BigFloatT("3.25"));
  EXPECT_EQ(val2 / val1, BigFloatT("0.30768"));
  EXPECT_EQ(val1 / val1, BigFloatT("1.0"));
  EXPECT_EQ(val2 / val2, BigFloatT("1.0"));

  // accuracy - 5
  val1 = BigFloatT("121.0", 6);
  val2 = BigFloatT("5", 6);

  EXPECT_EQ(val1 / val2, BigFloatT("24.2"));
  EXPECT_EQ(val2 / val1, BigFloatT("0.04132"));
  EXPECT_EQ(val1 / val1, BigFloatT("1.0"));
  EXPECT_EQ(val2 / val2, BigFloatT("1.0"));
}

TEST(BigFloat, toPrettyString_test) {
  BigFloat<> val(1234);

  EXPECT_EQ(toPrettyString(val), "1234*e^(0)");

  val = 1234000000;

  EXPECT_EQ(toPrettyString(val), "1234*e^(6)");

  val = -1234;

  EXPECT_EQ(toPrettyString(val), "-1234*e^(0)");

  val = -1234000000;

  EXPECT_EQ(toPrettyString(val), "-1234*e^(6)");

  val = BigFloat<>("124.2134");

  EXPECT_EQ(toPrettyString(val), "1242134*e^(-4)");

  val = BigFloat<>("-124.2134");

  EXPECT_EQ(toPrettyString(val), "-1242134*e^(-4)");

  val = BigFloat<>("00000.00124");

  EXPECT_EQ(toPrettyString(val), "124*e^(-5)");

  val = BigFloat<>("-0.00124");

  EXPECT_EQ(toPrettyString(val), "-124*e^(-5)");

  val = BigFloat<>("-0.00124", 2);

  EXPECT_EQ(toPrettyString(val), "0*e^(0)");

  val = BigFloat<>("-0.1241124", 3);

  EXPECT_EQ(toPrettyString(val), "-124*e^(-3)");

  val = BigFloat<>("20000.0");

  EXPECT_EQ(toPrettyString(val), "2*e^(4)");

  val = BigFloat<>("20000");

  EXPECT_EQ(toPrettyString(val), "2*e^(4)");
}
