﻿
/// @file Alloc.cc
/// @brief Alloc の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2018, 2019 Yusuke Matsunaga
/// All rights reserved.


#include "ym/Alloc.h"


BEGIN_NAMESPACE_YM

//////////////////////////////////////////////////////////////////////
// クラス Alloc
//////////////////////////////////////////////////////////////////////

// @brief n バイトの領域を確保する．
void*
Alloc::get_memory(SizeType n)
{
  if ( n == 0 ) {
    return nullptr;
  }

  mUsedSize += n;
  if ( mMaxUsedSize < mUsedSize ) {
    mMaxUsedSize = mUsedSize;
  }

  return _get_memory(n);
}

// @brief n バイトの領域を開放する．
void
Alloc::put_memory(SizeType n,
		  void* block)
{
  mUsedSize -= n;

  _put_memory(n, block);
}

// @brief 今までに確保した全ての領域を破棄する．
void
Alloc::destroy()
{
  mUsedSize = 0;
  _destroy();
}

// @brief 内部状態を出力する．
void
Alloc::print_stats(ostream& s) const
{
  s << "maximum used size: " << max_used_size() << endl
    << "current used size: " << used_size() << endl
    << "allocated size:    " << allocated_size() << endl
    << "allocated count:   " << allocated_count() << endl
    << endl;
}

// @brief 真のアロケート関数
// @param[in] n 確保するメモリ量(単位はバイト)
// @note 確保した総量が制限値を越えていたら 0 を返す．
void*
Alloc::alloc(SizeType n)
{
  if ( mMemLimit > 0 && mAllocSize + n >= mMemLimit ) {
    // 総量が制限値を越えた．
    return 0;
  }
  mAllocSize += n;
  ++ mAllocCount;
  return ::operator new(n);
}

// @brief 新のフリー関数
// @param[in] n 解放するメモリ量(単位はバイト)
// @param[in] blk 解放するメモリ領域
void
Alloc::free(SizeType n,
	    void* blk)
{
  mAllocSize -= n;
  ::operator delete(blk);
}

END_NAMESPACE_YM
