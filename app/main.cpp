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

#include "readline_shell.hpp"

#include <metashell/parse_config.hpp>
#include <metashell/config.hpp>

#include <iostream>

int main(int argc_, const char* argv_[])
{
  using metashell::parse_config;
  using metashell::parse_config_result;

  metashell::config cfg = metashell::config::default_config;

  const parse_config_result
    r = parse_config(cfg, argc_, argv_, &std::cout, &std::cerr);

  if (r == metashell::run_shell)
  {
    readline_shell shell(cfg);
    shell.display_splash();
    shell.run();
  }
  return r == metashell::exit_with_error ? 1 : 0;
}

