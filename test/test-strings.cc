#include "zos.h"
#include "string.h"
#include "gtest/gtest.h"
#include <libgen.h>

namespace {

TEST(StrndupTest, CheckStrndupFunctionality) {
  // Test copying partial string
  const char* original = "Hello, World!";
  size_t length = 5; 

  char* copied = strndup(original, length);

  ASSERT_NE(copied, nullptr);

  EXPECT_STREQ(copied, "Hello");

  free(copied);

  // Test copying the entire string
  size_t full_length = strlen(original);
  char* full_copied = strndup(original, full_length);

  ASSERT_NE(full_copied, nullptr);

  EXPECT_STREQ(full_copied, original);

  free(full_copied);

  // Test 0 length
  char* zero_length_copied = strndup(original, 0);
  EXPECT_STREQ(zero_length_copied, "");
  free(zero_length_copied);
}

TEST(StpcpyTest, CheckStpcpyFunctionality) {
  const char *src = "hello";
  char dest[10];
  char *ret = stpcpy(dest, src);
  EXPECT_STREQ(dest, "hello");
  EXPECT_EQ(ret, dest + strlen(src));
  EXPECT_EQ(*ret, '\0');

  const char *src2 = " world";
  char *ret2 = stpcpy(ret, src2);
  EXPECT_STREQ(dest, "hello world");
  EXPECT_EQ(ret2, dest + strlen("hello world"));
  EXPECT_EQ(*ret2, '\0');
}

TEST(StpncpyTest, CheckStpncpyFunctionality) {
  // Test copying with n limit (source shorter than n)
  const char *src = "hello";
  char dest[10];
  memset(dest, 'X', sizeof(dest));  // Initialize with non-zero data
  char *ret = stpncpy(dest, src, 8);
  EXPECT_STREQ(dest, "hello");
  EXPECT_EQ(ret, dest + strlen(src));
  // Verify padding with zeros - check all padded bytes
  EXPECT_EQ(dest[5], '\0');
  EXPECT_EQ(dest[6], '\0');
  EXPECT_EQ(dest[7], '\0');
  EXPECT_EQ(dest[8], 'X');  // Byte at index 8 should remain unchanged

  // Test copying when source is longer than n (truncation)
  const char *src2 = "hello world";
  char dest2[10] = {0};
  char *ret2 = stpncpy(dest2, src2, 5);
  EXPECT_EQ(strncmp(dest2, "hello", 5), 0);
  EXPECT_EQ(ret2, dest2 + 5);  // Returns dest + n when truncated

  // Test copying exact length (source length equals n)
  const char *src3 = "test";
  char dest3[10] = {0};
  char *ret3 = stpncpy(dest3, src3, 4);
  EXPECT_EQ(strncmp(dest3, "test", 4), 0);
  EXPECT_EQ(ret3, dest3 + 4);  // Returns dest + n when len == n

  // Test with n = 0
  char dest4[10] = "unchanged";
  char *ret4 = stpncpy(dest4, "test", 0);
  EXPECT_STREQ(dest4, "unchanged");
  EXPECT_EQ(ret4, dest4);  // Returns dest when n == 0
}

} // namespace
