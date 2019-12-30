/*
This file is a practice for Deng Junhui's book: "data structure[ISBN:9787302330646]"

Question:
Calculate hailstone sequence.
More detail at https://plus.maths.org/content/mathematical-mysteries-hailstone-sequences

                |{1}                     when n = 1
Hailstone(n) =  |{n} U {Hailstone(n/2)}  when n%2 == 0;
                |{n} U {HailStone(3n+1)} when n%2 == 1;
*/