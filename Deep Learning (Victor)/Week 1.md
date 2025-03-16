* Gradient descent doesn't work on non-convex functions and can be stuck on local minimums rather than global.
* ![[Pasted image 20250305214650.png]]
  ![[Pasted image 20250305223728.png]]
* In that image notice that we're doing a interpolation of theta 1 and theta 2 (x -axis) and f(theta 1) and f(theta 2) for the y-axis, **Does those values will be always be related?** The intuition say yes, cause it is kind of a proportion between those two ranges.
* So for a convex function this will work:
	* $f(\lambda * \theta_{1} + (1 - \lambda)*\theta_{2}) \leq \lambda * f(\theta_{1}) + (1 - \lambda) * f(\theta_{2})$
* 
* 