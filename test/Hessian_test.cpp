/*******************************************************************************

   Tests for xad::Hessian class.

   This file is part of XAD, a comprehensive C++ library for
   automatic differentiation.

   Copyright (C) 2010-2024 Xcelerit Computing Ltd.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Affero General Public License as published
   by the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

******************************************************************************/

#include <XAD/XAD.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <complex>
#include <type_traits>
#include <typeinfo>
#include <vector>

using namespace ::testing;

template <class T>
T quad(T a, T b)
{
    T c = a * a;
    T d = b * b;
    return c + d;
}

TEST(HessianTest, SimpleQuadratic)
{
    typedef xad::fwd_adj<double> mode;
    typedef mode::active_type AD;

    std::vector<AD> x = {3, 2};

    xad::Hessian<AD> h;

    std::vector<std::vector<AD>> cross_hessian = {{2.0, 0.0}, {0.0, 2.0}};
    std::vector<std::vector<AD>> computed_hessian = h.compute(x);

    for (unsigned int i = 0; i < cross_hessian.size(); i++)
        for (unsigned int j = 0; j < cross_hessian.size(); j++)
            ASSERT_EQ(cross_hessian[i][j], computed_hessian[i][j]);
}
