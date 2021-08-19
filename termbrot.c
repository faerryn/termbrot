/*
 * Copyright 2020 Jiang Meng Liao <alexandre.liao@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>

int main(int argc, char** argv) {
  const unsigned max_it = 256;
  size_t width;
  size_t height;

  if (argc <= 1) {
    width = 64;
    height = width / 2;
  } else if (argc == 2) {
    width = strtol(argv[1], NULL, 10);
    height = width / 2;
  } else if (argc == 3) {
    width = strtol(argv[1], NULL, 10);
    height = strtol(argv[2], NULL, 10);
  }

  double cell_width = 4.0 / width;
  double cell_height = 4.0 / height;

  double midrow = height / 2.0;
  double midcol = width / 2.0;

  for (size_t row = 0; row < height; ++row) {
    for (size_t col = 0; col < width; ++col) {
      double relrow = row - midrow + 0.5;
      double relcol = col - midcol + 0.5;

      double complex c = relcol * cell_width + (relrow * cell_height) * I;
      double complex z = c;
      double r = 0.0;
      double g = 0.0;
      double b = 0.0;

      unsigned it = 0;
      for (; it < max_it; ++it) {
        double re_sqr = creal(z) * creal(z);
        double im_sqr = cimag(z) * cimag(z);

        if (re_sqr + im_sqr > 4.0) {
          r = sin(it / 8.0);
          g = sin(it / 8.0 + M_PI_4);
          b = sin(it / 8.0 + M_PI_2);
          break;
        }

        z = re_sqr - im_sqr + creal(c) + (2.0 * creal(z) * cimag(z) + cimag(c)) * I;
      }

      unsigned rb = r * 255.0;
      unsigned gb = g * 255.0;
      unsigned bb = b * 255.0;

      printf("\033[38;2;%u;%u;%um\u2588", rb, gb, bb);
    }
    putchar('\n');
  }
}
