#ifndef _BASE64_H
#define _BASE64_H

#include <cstdlib>
#include <string>

static const unsigned char to_b64_tab[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const unsigned char un_b64_tab[] = {
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 62,  255, 255, 255, 63,
	52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  255, 255, 255, 255, 255, 255,
	255, 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,
	15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  255, 255, 255, 255, 255,
	255, 26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,
	41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255
};

class Base64
{
public:
    static std::string encode(const char *in, int len)
    {
        const unsigned char *clear = (const unsigned char*)in;

        std::string encoded;
        encoded.resize(4 * ((len + 2) / 3));
        auto p = &encoded[0];

        while (len-- > 0)
        {
            int x, y;

            x = *clear++;
            *p++ = to_b64_tab[(x >> 2) & 63];

            if (len-- <= 0)
            {
                *p++ = to_b64_tab[(x << 4) & 63];
                *p++ = '=';
                *p++ = '=';
                break;
            }

            y = *clear++;
            *p++ = to_b64_tab[((x << 4) | ((y >> 4) & 15)) & 63];

            if (len-- <= 0)
            {
                *p++ = to_b64_tab[(y << 2) & 63];
                *p++ = '=';
                break;
            }

            x = *clear++;
            *p++ = to_b64_tab[((y << 2) | ((x >> 6) & 3)) & 63];

            *p++ = to_b64_tab[x & 63];
        }

        encoded.resize(p - &encoded[0]);
        return encoded;
    }

    static std::string decode(const std::string& in)
    {
        std::string decoded;
        decoded.resize(3 * (in.size() / 4) + 1);
        auto pd = &decoded[0];

        /* Each cycle of the loop handles a quantum of 4 input bytes. For the last
           quantum this may decode to 1, 2, or 3 output bytes. */

        auto pi = &in[0];
        auto pend = pi + in.size();
        while (pi != pend)
        {
            int x, y;
            x = (*pi++);

            if (x > 127 || (x = un_b64_tab[x]) == 255)
                return "";
            if (pi == pend)
                return "";
            y = (*pi++);
            if ((y = un_b64_tab[y]) == 255)
                return "";
            *pd++ = (x << 2) | (y >> 4);

            if (pi != pend && ((x = (*pi++)) == '='))
            {
                if ((pi != pend && *pi++ != '=') || pi != pend)
                    return "";
            }
            else
            {
                if (x > 127 || (x = un_b64_tab[x]) == 255)
                    return "";
                *pd++ = (y << 4) | (x >> 2);

                if (pi != pend && ((y = (*pi++)) == '='))
                {
                    if (pi != pend)
                        return "";
                }
                else
                {
                    if (y > 127 || (y = un_b64_tab[y]) == 255)
                        return "";
                    *pd++ = (x << 6) | y;
                }
            }
        }

        decoded.resize(pd - &decoded[0]);
        return decoded;
    }
};

#endif
