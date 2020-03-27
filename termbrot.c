#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Complex {
  double re;
  double im;
};

int main(int argc, char** argv) {
  unsigned max_it = 256;
  size_t width;
  size_t height;

  if (argc <= 1) {
    width = 64;
    height = 32;
  } else if (argc == 2) {
    width = strtol(argv[1], NULL, 10);
    height = width / 2;
  } else if (argc == 3) {
    width = strtol(argv[1], NULL, 10);
    height = strtol(argv[2], NULL, 10);
  }

  double cell_width = 4.0 / width;
  double cell_height = 4.0 / height;

  int midrow = height / 2;
  int midcol = width / 2;

  size_t bufsize = width * height * sizeof(struct Complex);

  struct Complex* cs = malloc(bufsize);

  for (size_t row = 0; row < height; ++row) {
    for (size_t col = 0; col < width; ++col) {
      int relrow = row - midrow;
      int relcol = col - midcol;

      struct Complex* c = &cs[row * width + col];
      c->re = relcol * cell_width;
      c->im = relrow * cell_height;
    }
  }

  struct Complex* zs = malloc(bufsize);
  memcpy(zs, cs, bufsize);

  for (size_t row = 0; row < height; ++row) {
    for (size_t col = 0; col < width; ++col) {
      struct Complex* c = &cs[row * width + col];
      struct Complex* z = &zs[row * width + col];

      double r = 0.0;
      double g = 0.0;
      double b = 0.0;

      unsigned it = 0;
      for (; it < max_it; ++it) {
        double re_sqr = z->re * z->re;
        double im_sqr = z->im * z->im;

        if (re_sqr + im_sqr > 4.0) {
          r = sin(it / 8.0);
          g = sin(it / 8.0 + M_PI_4);
          b = sin(it / 8.0 + M_PI_2);
          break;
        }

        z->im = 2.0 * z->re * z->im + c->im;
        z->re = re_sqr - im_sqr + c->re;
      }


      unsigned rb = r * 255.0;
      unsigned gb = g * 255.0;
      unsigned bb = b * 255.0;

      printf("\033[38;2;%u;%u;%um\u2588", rb, gb, bb);
    }
    putchar('\n');
  }
}
