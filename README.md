# ranges-cpp
Implementation of ranges and its iterators and adaptors

Inspired from http://www.fluentcpp.com/2017/06/23/7-ways-better-cpp-summer/

    During my summer project of last year, I implemented some range adaptors. And I it made me learn a HELL of a lot. For this reason, I’m going to detail this project to you, so you can take inspiration to build your own:

    If you're not familiar with Ranges in C++, read Ranges: the STL to the Next Level,
    Implement a transform_iterator,
    Implement a transform range adaptor,
    Implement a filter_iterator,
    Implement a filter range adaptor,
    Implement a zip adaptor that takes 2 ranges and returns a view on pairs of objects \
    coming from these 2 ranges, then use it with the transform range adaptor,
    Generalise the zip adaptor by letting it take any number of ranges,
    Implement a Cartesian product range adaptor,
    Implement your own new range adaptor!


The implementation would be inspired from (may be line by line rewrite of) https://github.com/joboccara/ranges   
The coding would start from following 
http://www.fluentcpp.com/2017/01/12/ranges-stl-to-the-next-level/   
which has a quote that inspires this project
> A lot of manual operations performed on containers with for loops can be replaced by calls to algorithms of the STL.

**Following are learnings through the process:**
* std::copy(v1.begin(), v1.end(), std::back_inserter(v2));  std::back_inserter used here is an output iterator that does a push_back into the container it is passed, every time it is assigned to. This relieves the programmer from the sizing of the output.
* std::transform(input.begin(), input.end(), std::back_inserter(output), f); // transforms all elements applying f
* std::copy_if(input.begin(), input.end(), std::back_inserter(output), p); // filters the elements based on predicate p
* No easy way to combine tranform and copy_if. There is no transform_if. Ranges helps to solve this problem.
* Ranges are something that have begin and end which return iterators to traverse through the range.
```c++
     Range {
        begin();
        end();
     }
```   
   By this, it can be seen that all the stl containers are ranges by themselves.
* Smart iterators:
  * tranform_iterator - made of another iterator (it) and a function f. When deferenced, applies f to *it and return the result.
  * filter_iterator - made of another iterator (it) and a predicate p. When ++ is applied, 'it' is advanced until the element *it for which p holds
  * Range adaptors - enables association of ranges with smart iterators.
    * view adaptor - initial range remain unchanged but the produced range does not contain elements as its a view with customized iteration behaviour. Here is how range adaptor can be used.
    ```c++
    std::vector numbers = { 1, 2, 3, 4, 5 };
    ranges::accumulate(numbers | view::filter(isEven) | view::transform(multiplyBy2), 0);
    ```
    returns 2 * 2 + 4 * 2 = 12