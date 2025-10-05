# rand16

Just an example showing off a 16-bit variant of Xorshift. Could be useful for deterministic dithering for embedded, fixed-point DSP.

The full possible set is as follows:

```yaml
{a, b, c} = {1, 1, 14}
{a, b, c} = {1, 5, 2}
{a, b, c} = {1, 7, 4}
{a, b, c} = {1, 7, 11}
{a, b, c} = {1, 11, 3}
{a, b, c} = {2, 5, 1}
{a, b, c} = {2, 5, 13}
{a, b, c} = {2, 7, 13}
{a, b, c} = {3, 1, 12}
{a, b, c} = {3, 5, 11}
{a, b, c} = {3, 11, 1}
{a, b, c} = {3, 11, 11}
{a, b, c} = {3, 13, 9}
{a, b, c} = {4, 3, 7}
{a, b, c} = {4, 7, 1}
{a, b, c} = {4, 11, 11}
{a, b, c} = {5, 7, 14}
{a, b, c} = {5, 9, 8}
{a, b, c} = {5, 11, 6}
{a, b, c} = {5, 11, 11}
{a, b, c} = {6, 7, 13}
{a, b, c} = {6, 11, 5}
{a, b, c} = {7, 1, 11}
{a, b, c} = {7, 3, 4}
{a, b, c} = {7, 9, 8}
{a, b, c} = {7, 9, 13}
{a, b, c} = {8, 9, 5}
{a, b, c} = {8, 9, 7}
{a, b, c} = {9, 7, 13}
{a, b, c} = {9, 13, 3}
{a, b, c} = {11, 1, 7}
{a, b, c} = {11, 3, 13}
{a, b, c} = {11, 5, 3}
{a, b, c} = {11, 7, 1}
{a, b, c} = {11, 11, 3}
{a, b, c} = {11, 11, 4}
{a, b, c} = {11, 11, 5}
{a, b, c} = {12, 1, 3}
{a, b, c} = {12, 3, 13}
{a, b, c} = {13, 3, 11}
{a, b, c} = {13, 3, 12}
{a, b, c} = {13, 5, 2}
{a, b, c} = {13, 7, 2}
{a, b, c} = {13, 7, 6}
{a, b, c} = {13, 7, 9}
{a, b, c} = {13, 9, 7}
{a, b, c} = {14, 1, 1}
{a, b, c} = {14, 7, 5}
```

Each can be implemented by substituting the corresponding letter with its value.

```c
uint16_t xorshift16()
{
    rstate ^= rstate << a;
    rstate ^= rstate >> b;
    return rstate ^= rstate << c;
}
```
