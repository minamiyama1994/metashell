// Metashell - Interactive C++ template metaprogramming shell
// Copyright (C) 2013, Abel Sinkovics (abel@sinkovics.hu)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "cxcodecompleteresults.hpp"
#include "cxstring.hpp"

using namespace metashell;

#include <iostream>

namespace
{
  template <class Cont>
  void add(const CXCompletionString& s_, Cont& out_)
  {
    for (int i = 0, e = clang_getNumCompletionChunks(s_); i != e; ++i)
    {
      if (clang_getCompletionChunkKind(s_, i) == CXCompletionChunk_TypedText)
      {
        out_.insert(cxstring(clang_getCompletionChunkText(s_, i)));
      }
    }
  }
}

cxcodecompleteresults::cxcodecompleteresults(CXCodeCompleteResults* r_) :
  _r(r_)
{
}

cxcodecompleteresults::~cxcodecompleteresults()
{
  clang_disposeCodeCompleteResults(_r);
}

void cxcodecompleteresults::fill(std::set<std::string>& out_) const
{
  out_.clear();

  if (_r)
  {
    for (unsigned int i = 0; i != _r->NumResults; ++i)
    {
      add(_r->Results[i].CompletionString, out_);
    }
  }
}


