Structure credits to: Professor David

# Results for Assignment 01

## Improvement Iterations

Here's a table showing the improvements I did to make the application go faster.  The **Time** column in the table represents the _wall-clock time_ for a program run.

| Version | Time | Speedup | Memory (KB) | Changes |
| :-----: | ---- | :-----: | :------: | ------- |
| [01](./01) | 10.23s | &mdash; | 1043228 | Initial version - no changes |
| [02](./01_fast_auto) | 2.19s | 4.67x | 1040944 | Compiled with -Ofast to see speed vs. memory |
| [03](./01_fastest_auto) | 2.46s | 4.16x| 1040660 | Compiled with -O3 to see differences between -O3 and -Ofast |

## Profiling Analysis

### Initial Review

The program seems relatively slow, clocking in at 10.23 seconds. 

### Trying -Ofast flag

I see that we have dramatically increased our time (4.67x speedup!). 
The difference I noticed in the profiles is that, we are no longer seeing calls like 
+ `Transform::float4::dot(Vertex const&) const`
+ `Transform::float4::perspectiveDivide() const`
+ `Transform::operator*(Vertex const&)`

which I found interesting.

Instead, it used 
  + `computePerimeter(Face const&, std::span<Vertex, 18446744073709551615ul> const&)` 

for (01_fast_profile.txt) and (01_fastest_profile.txt), which I found it an odd replacement, taking up 49.3% and 55.32% of the program, respectively. 

I could not figure out what 
  + `std::span<Vertex, 18446744073709551615ul> const&`
 
means (referring to the elephant), but will update as I do a little more research.
