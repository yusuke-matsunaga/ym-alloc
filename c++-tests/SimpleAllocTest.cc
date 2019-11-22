
/// @file SimpleAllocTest.cc
/// @brief SimpleAllocTest の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2019 Yusuke Matsunaga
/// All rights reserved.


#include <gtest/gtest.h>
#include "ym/SimpleAlloc.h"


BEGIN_NAMESPACE_YM

TEST(SimpleAllocTest, test1)
{
  SimpleAlloc alloc{};

  SizeType msize = 1025;
  auto p = alloc.get_memory(msize);

  alloc.put_memory(p, msize);
}

END_NAMESPACE_YM
