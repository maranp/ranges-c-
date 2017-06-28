# ranges-cpp
Implementation of ranges and its iterators and adaptors

Inspired from http://www.fluentcpp.com/2017/06/23/7-ways-better-cpp-summer/
<quote>
During my summer project of last year, I implemented some range adaptors. And I it made me learn a HELL of a lot. For this reason, I’m going to detail this project to you, so you can take inspiration to build your own:

    If you’re not familiar with Ranges in C++, read Ranges: the STL to the Next Level,
    Implement a transform_iterator,
    Implement a transform range adaptor,
    Implement a filter_iterator,
    Implement a filter range adaptor,
    Implement a zip adaptor that takes 2 ranges and returns a view on pairs of objects coming from these 2 ranges, then use it with the transform range adaptor,
    Generalise the zip adaptor by letting it take any number of ranges,
    Implement a Cartesian product range adaptor,
    Implement your own new range adaptor!
</quote>

The implementation would be inspired from (may be line by line rewrite of) https://github.com/joboccara/ranges

The coding would start from following 
http://www.fluentcpp.com/2017/01/12/ranges-stl-to-the-next-level/
