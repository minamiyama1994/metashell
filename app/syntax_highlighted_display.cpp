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

#include "syntax_highlighted_display.hpp"

boost::optional<just::console::color>
syntax_highlighted_display::color_of_token(boost::wave::token_id id_)
{
  using just::console::color;
  using boost::optional;

  if (
    IS_CATEGORY(id_, boost::wave::CharacterLiteralTokenType)
    || IS_CATEGORY(id_, boost::wave::FloatingLiteralTokenType)
    || IS_CATEGORY(id_, boost::wave::IntegerLiteralTokenType)
    || IS_CATEGORY(id_, boost::wave::StringLiteralTokenType)
    || IS_CATEGORY(id_, boost::wave::BoolLiteralTokenType)
    || IS_CATEGORY(id_, boost::wave::PPTokenType)
  )
  {
    return color::magenta;
  }
  else if (IS_CATEGORY(id_, boost::wave::KeywordTokenType))
  {
    return color::bright_green;
  }
  else if (id_ == boost::wave::T_CCOMMENT || id_ == boost::wave::T_CPPCOMMENT)
  {
    return color::green;
  }
  else
  {
    return boost::optional<just::console::color>();
  }
}


