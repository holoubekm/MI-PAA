# MI-PAA Course
## Problémy a algoritmy
### CTU / ČVUT FIT

#### Task 1 - naive and aproximative Knapsack solver
We were implementing a naive and slightly improved aproximative solution using heuristic for the Knapsack problem. The main goal was to measure error of the approximative solution. The results contains graphs and the final report.

Solution can be compiled using `GNU make` on Linux and `Visual Studio` on Windows.

#### Task 2 - dynamic decomposition and FPTAS Knapsack solver
In the second part we took an advantage of previous one - another improvement was implementation of `branch and bounds` prunning. This approach effectively removes states which would never lead to a better solution that the current.

Another approach we implemented was `dynamic decomposition` and `fast polynomial-time approximation scheme` (`FPTAS`).

This version can be compiler only using the `GNU make`.

#### Task 3 - eomparison of methods 
We took previously programmed solver on the Knapsack problem and let it crush a lot of different instances. The basic difference was that results depend on the instance properties.

Folder contains the final report as well as graphs and exact runtimes.

#### Task 4 - evolution algorithm Knapsack solver
The last algorithm trying to solve the Knapsack problem was evolutin algorithm. As this is random algorithm results may (and will) change over time. 

The solution was created for the `Visual Studio`

#### Semestral work - evolution algorithm 3SAT solver
Our semestral work was focused on 3SAT problem. We took an advantage of previous experience with evolution programming. I was enough to copy solution of the 4th task and bend it. I had changed problem representation in the genom and added another parameter tuning features. My approach was to use parameter grid, when we iterate over each parameter's value until all parameter space is exhausted.

The final report describing my approach, overall quality and results is in the place.

Unfortunately this approach was not **fully appreciated** during the evaluation. **You have been warned!** 
